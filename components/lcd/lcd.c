#include <stdlib.h>
#include <string.h>

#include "esp_err.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_timer.h"

#include "esp_lcd_ili9341.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_touch_xpt2046.h"

#include "lcd.h"
#include "hardware.h"
#include "ui.h"

static const char *TAG = "Lcd_&_Touch";

static SemaphoreHandle_t lvgl_mux = NULL;

static void process_coordinates(esp_lcd_touch_handle_t tp, uint16_t *x, uint16_t *y, uint16_t *strength, uint8_t *point_num, uint8_t max_point_num)
{

    // Map for X
    int x_value = (*x - TOUCH_X_RES_MIN) * (CONFIG_LCD_HRES) / (TOUCH_X_RES_MAX - TOUCH_X_RES_MIN);
    *x = (x_value < 0) ? 0 : ((x_value > CONFIG_LCD_HRES) ? CONFIG_LCD_HRES : x_value);

    // Map for Y
    int y_value = (*y - TOUCH_Y_RES_MIN) * (CONFIG_LCD_VRES) / (TOUCH_Y_RES_MAX - TOUCH_Y_RES_MIN);
    *y = (y_value < 0) ? 0 : ((y_value > CONFIG_LCD_VRES) ? CONFIG_LCD_VRES : y_value);
}

// Configure/setup touch driver
esp_lcd_touch_handle_t init_touch_panel(spi_host_device_t spi_host)
{
    esp_lcd_touch_handle_t tp = NULL;
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;

    ///////////////////////////  INIT TOUCH IO PANEL ///////////////////////////////////////////////////
    ESP_LOGI(TAG, "Install touch panel IO");
    esp_lcd_panel_io_spi_config_t tp_io_config = ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(CONFIG_TOUCH_CS);

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)spi_host, &tp_io_config, &tp_io_handle));

    ///////////////////////////  INIT TOUCH DRIVER /////////////////////////////////////////
    esp_lcd_touch_config_t tp_cfg = {
        .x_max = CONFIG_LCD_HRES,
        .y_max = CONFIG_LCD_VRES,
        .rst_gpio_num = CONFIG_TOUCH_RST,
        .int_gpio_num = CONFIG_TOUCH_IRQ,
        .levels = {.reset = 0, .interrupt = 0},
        .flags = {
            .swap_xy = 1,  // Landscape : swap 1. miror x=1, mirror y=1
            .mirror_x = 1, // portrait : mirror x=1
            .mirror_y = 1,
        },
        .process_coordinates = process_coordinates,
        .interrupt_callback = NULL};

    ESP_ERROR_CHECK(esp_lcd_touch_new_spi_xpt2046(tp_io_handle, &tp_cfg, &tp));

    return tp;
}

// callback for touch
static void lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    /* Read touch controller data */
    esp_lcd_touch_read_data((esp_lcd_touch_handle_t)drv->user_data);

    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates((esp_lcd_touch_handle_t)drv->user_data, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0)
    {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void backlight(uint8_t state)
{
    gpio_set_direction(CONFIG_LCD_BACKLIGHT, GPIO_MODE_OUTPUT);
    gpio_set_level(CONFIG_LCD_BACKLIGHT, state ? 1 : 0);
}

static bool lvgl_notify_flush_ready(esp_lcd_panel_io_handle_t panel_io,
                                    esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

// Setup SPI
spi_host_device_t init_spi_bus(void)
{
    ESP_LOGI(TAG, "Initialize SPI bus");
    spi_bus_config_t spi_buscfg = {
        .mosi_io_num = CONFIG_LCD_SPI_MOSI,
        .miso_io_num = CONFIG_LCD_SPI_MISO,
        .sclk_io_num = CONFIG_LCD_SPI_CLK,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = CONFIG_LCD_HRES * 80 * sizeof(uint16_t)};

    ESP_ERROR_CHECK(spi_bus_initialize(CONFIG_LCD_SPI, &spi_buscfg, SPI_DMA_CH_AUTO));

    return CONFIG_LCD_SPI;
}

esp_lcd_panel_handle_t init_display(spi_host_device_t spi_host, lv_disp_drv_t *disp_drv)
{

    ESP_LOGI(TAG, "Turn off LCD backlight");
    backlight(0);

    ///////////////////////////  INIT LCD IO PANEL ///////////////////////////////////////////////////
    esp_lcd_panel_io_handle_t lcd_io_handle = NULL;

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_spi_config_t lcd_io_config = {
        .dc_gpio_num = CONFIG_LCD_DC,
        .cs_gpio_num = CONFIG_LCD_CS,
        .pclk_hz = CONFIG_LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = CONFIG_LCD_CMD_BITS,
        .lcd_param_bits = CONFIG_LCD_PARAM_BITS,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .on_color_trans_done = lvgl_notify_flush_ready,
        .user_ctx = disp_drv};
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)spi_host, &lcd_io_config, &lcd_io_handle));

    ///////////////////////////  INIT LCD PANEL DRIVER ///////////////////////////////////////////////////
    ESP_LOGI(TAG, "Install ILI9341 panel driver");
    esp_lcd_panel_handle_t lcd_panel = NULL;
    const esp_lcd_panel_dev_config_t lcd_panel_devcfg = {
        .reset_gpio_num = CONFIG_LCD_RESET,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
        .bits_per_pixel = 16};

    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(lcd_io_handle, &lcd_panel_devcfg, &lcd_panel));

    ////////////////////////  INIT DISPLAY //////////////////////////////////
    ESP_ERROR_CHECK(esp_lcd_panel_reset(lcd_panel));
    ESP_ERROR_CHECK(esp_lcd_panel_init(lcd_panel));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(lcd_panel, true));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(lcd_panel, false, false));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(lcd_panel, false));

    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(lcd_panel, true));
    backlight(1);

    return lcd_panel;
}

static bool lvgl_acquire(int timeout_ms)
{

    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);

    if (xSemaphoreTake(lvgl_mux, timeout_ticks) == pdTRUE)
    {
        return true;
    }
    return false;
}

static bool lvgl_release()
{

    if (xSemaphoreGive(lvgl_mux) == pdTRUE)
    {
        return true;
    }
    return false;
}

static void lvgl_port_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Starting LVGL task");

    while (1)
    {
        if (lvgl_acquire(LVGL_TASK_MAX_DELAY_MS))
        {
            lv_timer_handler();

            lvgl_release();
        }
        else
        {
            // Si no se pudo adquirir, imprimir advertencia
            ESP_LOGW(TAG, "No se pudo adquirir semáforo. Reintentando.");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// callback for lvgl - dibujar el buffer
static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

static void lvgl_increase_tick(void *pvParameters)
{
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

void init_LVGL()
{
    static lv_disp_drv_t disp_drv;   // display
    lv_indev_drv_t indev_drv; // touch

    spi_host_device_t bus_spi = init_spi_bus();
    esp_lcd_panel_handle_t lcd_panel = init_display(bus_spi, &disp_drv);
    esp_lcd_touch_handle_t touch_handle = init_touch_panel(bus_spi);

    static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();

    // alloc draw buffers used by LVGL
    ESP_LOGI(TAG, "Heap DMA free: %d bytes", heap_caps_get_free_size(MALLOC_CAP_DMA));

    lv_color_t *buf1 = heap_caps_malloc(CONFIG_LCD_HRES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1);
    lv_color_t *buf2 = heap_caps_malloc(CONFIG_LCD_HRES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2);

    ESP_LOGI(TAG, "Initializing buffers...");
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, CONFIG_LCD_HRES * 20);
    ESP_LOGI(TAG, "Heap DMA free after buffers : %d bytes", heap_caps_get_free_size(MALLOC_CAP_DMA));

    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = CONFIG_LCD_VRES;
    disp_drv.ver_res = CONFIG_LCD_HRES;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = lcd_panel;
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

    ESP_LOGI(TAG, "Register Touch driver to LVGL");
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.disp = disp;
    indev_drv.read_cb = lvgl_touch_cb;
    indev_drv.user_data = touch_handle;
    lv_indev_drv_register(&indev_drv);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = lvgl_increase_tick,
        .name = "lvgl_tick"};
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));

    ESP_LOGI(TAG, "Create LVGL task");
    lvgl_mux = xSemaphoreCreateMutex();
    configASSERT(lvgl_mux);

    xTaskCreate(lvgl_port_task, "LVGL", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL);

    ESP_LOGI(TAG, "Display LVGL Widget");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    if (lvgl_acquire(-1))
    {
        ui_init();
        // Release the mutex
        lvgl_release();
    }
}
