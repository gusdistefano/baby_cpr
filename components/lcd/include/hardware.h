#pragma once
#include "driver/spi_common.h"

/*

Vertical mode (default):
                X (horizontal): 0 to 239 pixels
                Y (vertical): 0 to 319 pixels

Landscape mode (horizontal):
                X (now horizontal): 0 to 319 pixels
                (now vertical): 0 to 239 pixels
*/

// LCD Configuration
#define CONFIG_LCD_PIXEL_CLOCK_HZ (40 * 1000 * 1000)  /**< LCD pixel clock in Hz */
#define CONFIG_LCD_CMD_BITS       (8)                  /**< Number of bits for commands */
#define CONFIG_LCD_PARAM_BITS     (8)                  /**< Number of bits for parameters */
#define CONFIG_LCD_SPI            SPI2_HOST            /**< SPI bus to use for LCD */
#define CONFIG_LCD_BACKLIGHT      (gpio_num_t) GPIO_NUM_27  /**< GPIO for backlight */
#define CONFIG_LCD_SPI_CLK        (gpio_num_t) GPIO_NUM_18  /**< SPI clock GPIO */
#define CONFIG_LCD_SPI_MOSI       (gpio_num_t) GPIO_NUM_23  /**< SPI MOSI GPIO */
#define CONFIG_LCD_SPI_MISO       (gpio_num_t) GPIO_NUM_19  /**< SPI MISO GPIO (if needed) */
#define CONFIG_LCD_DC             (gpio_num_t) GPIO_NUM_2   /**< Data/Command select GPIO */
#define CONFIG_LCD_CS             (gpio_num_t) GPIO_NUM_5   /**< Chip Select GPIO */
#define CONFIG_LCD_RESET          (gpio_num_t) GPIO_NUM_4   /**< Reset GPIO (-1 if not used) */
#define CONFIG_LCD_BUSY           (gpio_num_t) GPIO_NUM_NC  /**< Busy GPIO (not connected) */

// Touchscreen resolution
#define CONFIG_LCD_HRES 240  /**< Horizontal resolution of the screen */
#define CONFIG_LCD_VRES 320  /**< Vertical resolution of the screen */
      
// Touchscreen Configuration
#define CONFIG_TOUCH_CLOCK_HZ ESP_LCD_TOUCH_SPI_CLOCK_HZ /**< Touchscreen SPI clock */
#define CONFIG_TOUCH_SPI      SPI2_HOST                  /**< SPI bus for touchscreen */
#define CONFIG_TOUCH_SPI_CLK  CONFIG_LCD_SPI_CLK         /**< Touchscreen SPI clock GPIO */
#define CONFIG_TOUCH_SPI_MOSI CONFIG_LCD_SPI_MOSI        /**< Touchscreen MOSI GPIO */
#define CONFIG_TOUCH_SPI_MISO CONFIG_LCD_SPI_MISO        /**< Touchscreen MISO GPIO */
#define CONFIG_TOUCH_CS       (gpio_num_t) GPIO_NUM_21   /**< Touchscreen CS GPIO */
#define CONFIG_TOUCH_DC       (gpio_num_t) GPIO_NUM_NC   /**< Touchscreen DC GPIO */
#define CONFIG_TOUCH_RST      (gpio_num_t) GPIO_NUM_4    /**< Touchscreen reset GPIO */
#define CONFIG_TOUCH_IRQ      (gpio_num_t) GPIO_NUM_NC   /**< Touchscreen IRQ GPIO */    

#define TOUCH_X_RES_MIN 18    /**< Minimum X resolution for touch */
#define TOUCH_X_RES_MAX 219   /**< Maximum X resolution for touch */

#define TOUCH_Y_RES_MIN 31    /**< Minimum Y resolution for touch */
#define TOUCH_Y_RES_MAX 303   /**< Maximum Y resolution for touch */

// Basic colors in RGB565 format
#define RED_COLOR 0xf800     /**< Red color in RGB565 */
#define GREEN_COLOR 0x07e0   /**< Green color in RGB565 */
#define BLUE_COLOR 0x001f    /**< Blue color in RGB565 */
#define BLACK_COLOR 0x0000   /**< Black color in RGB565 */
#define WHITE_COLOR 0xFFFF   /**< White color in RGB565 */
#define YELLOW_COLOR 0xFFE0  /**< Yellow color in RGB565 (Red + Green) */
#define CYAN_COLOR 0x07FF    /**< Cyan color in RGB565 (Green + Blue) */
#define MAGENTA_COLOR 0xF81F /**< Magenta color in RGB565 (Red + Blue) */
#define SQUARE_SIZE 20       /**< Size of the square to be drawn */

#define LVGL_TICK_PERIOD_MS    2   /**< LVGL tick period in milliseconds (range 2 to 10 ms) */
#define LVGL_TASK_MAX_DELAY_MS 500 /**< Maximum delay for LVGL tasks in milliseconds */
#define LVGL_TASK_MIN_DELAY_MS 2   /**< Minimum delay for LVGL tasks in milliseconds (range 1 to 5 ms) */
#define LVGL_TASK_STACK_SIZE   (4 * 1024) /**< Stack size for LVGL tasks */
#define LVGL_TASK_PRIORITY     2   /**< Priority of LVGL tasks */
