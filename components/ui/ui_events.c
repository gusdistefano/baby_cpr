#include "ui.h"
#include "hall_sensor.h"

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "buzzer.h"
#include "notes.h"

#include "../../main/configuration.h"

#include <inttypes.h>

static const char *TAG = "UI_Events";

//---------------  LUT Y FUNCIONES ASOCIADAS --------------------------

typedef struct
{
    float depth;      // Profundidad recibida (dato)
    int16_t rotation; // Rotación correspondiente
    float cm;         // Correspondiente en centímetros
} DepthMapping;

// Tabla combinada con rotación de aguja y centímetros
DepthMapping lut[] = {
    {0.0, -1300, 0.0}, // Inicio de Zona 1    Rojo        0 cm
    {30, -920, 1.7},   // Fin de Zona 1       Rojo        0 a 1 cm
    {100, -700, 2.4},  // Fin de Zona 2       Amarillo    1 a 1.3 cm
    {370, 0, 3.6},     // Fin de Zona 3       Verde       1.3 a 2.8 cm
    {550, 240, 4.5},   // Fin de Zona 4       Amarillo    2.8 a 3.1 cm
    {1000, 570, 5.2},  // Fin de Zona 5       Rojo        3.1 a 4.1 a
};

static int map_depth_to_rotation(float depth)
{
    int size = sizeof(lut) / sizeof(lut[0]);

    if (depth <= lut[0].depth)
    {
        return lut[0].rotation;
    }
    if (depth >= lut[size - 1].depth)
    {
        return lut[size - 1].rotation;
    }

    for (int i = 0; i < size - 1; i++)
    {
        if (depth >= lut[i].depth && depth <= lut[i + 1].depth)
        {
            float ratio = (depth - lut[i].depth) / (lut[i + 1].depth - lut[i].depth);
            return lut[i].rotation + ratio * (lut[i + 1].rotation - lut[i].rotation);
        }
    }

    return 0;
}

static float map_depth_to_cm(float depth)
{
    int size = sizeof(lut) / sizeof(lut[0]);

    if (depth <= lut[0].depth)
    {
        return lut[0].cm;
    }
    if (depth >= lut[size - 1].depth)
    {
        return lut[size - 1].cm;
    }

    for (int i = 0; i < size - 1; i++)
    {
        if (depth >= lut[i].depth && depth <= lut[i + 1].depth)
        {

            float ratio = (depth - lut[i].depth) / (lut[i + 1].depth - lut[i].depth);
            return lut[i].cm + ratio * (lut[i + 1].cm - lut[i].cm);
        }
    }

    return 0.0;
}

extern QueueHandle_t hall_sensor_data_queue;

void consumidor_task(void *pvParameter)
{
    compression_data_t dato_recibido;
    char buffer[16];
    uint16_t correct, shallow, deep;
    float rotation, cm;

    static float current_rotation = -1300;
    uint16_t i = 0;

    while (1)
    {
        if (xQueueReceive(hall_sensor_data_queue, &dato_recibido, pdMS_TO_TICKS(100)) == pdTRUE)
        {
            i = 0;

            if (dato_recibido.compressions > 0)
            {
                correct = dato_recibido.correct_compressions * 100 / dato_recibido.compressions;
                shallow = dato_recibido.shallow_compressions * 100 / dato_recibido.compressions;
                deep = dato_recibido.deep_compressions * 100 / dato_recibido.compressions;
            }
            else
            {
                correct = 0;
                shallow = 0;
                deep = 0;
            }

            sprintf(buffer, "%i%%", correct);
            lv_label_set_text(ui_correct, buffer);

            sprintf(buffer, "%i%%", shallow);
            lv_label_set_text(ui_shallow, buffer);

            sprintf(buffer, "%i%%", deep);
            lv_label_set_text(ui_deep, buffer);

            sprintf(buffer, "%i", dato_recibido.cpm);
            lv_label_set_text(ui_frec, buffer);

            rotation = map_depth_to_rotation(dato_recibido.depth);
            lv_img_set_angle(ui_pointer, rotation);
            current_rotation = rotation;

            cm = map_depth_to_cm(dato_recibido.depth);
            sprintf(buffer, "%.1f", cm);
            lv_label_set_text(ui_depth, buffer);
        }
        else
        {
            if (i > 5)
            {
                if (current_rotation > -1300)
                {
                    current_rotation -= 80;
                    if (current_rotation < -1300)
                        current_rotation = -1300;
                }

                lv_img_set_angle(ui_pointer, current_rotation);

                cm = map_depth_to_cm(current_rotation);
                sprintf(buffer, "%.1f", cm);
                lv_label_set_text(ui_depth, buffer);

                sprintf(buffer, "%i", 0);
                lv_label_set_text(ui_frec, buffer);

                i = 0;
            }
            else
            {
                i++;
            }
        }
    }
}

///////////////////////  VENTANA TRAINING ///////////////////////

//--------------- Metronomo -------------------------------
// Timer del metrónomo
TimerHandle_t metronome_timer;

// Callback del temporizador
static void metronome_cb(TimerHandle_t xTimer)
{
    play_tone(NOTE_A4, 150);
}

void init_metronome_timer()
{
    if (!metronome_timer)
    {
        metronome_timer = xTimerCreate(
            "MetronomeTimer",
            pdMS_TO_TICKS(600), // Intervalo inicial
            pdTRUE,             // Periódico
            NULL,
            metronome_cb);

        if (!metronome_timer)
        {
            ESP_LOGE(TAG, "Error al crear el temporizador del metrónomo");
        }
    }
}

// Función para actualizar el temporizador basado en `configuration.cpm`
static void update_metronome_timer()
{
    if (!metronome_timer)
    {
        init_metronome_timer();
    }

    if (metronome_timer && configuration.cpm > 0) // Verificar que el temporizador exista y CPM sea válido
    {
        uint32_t interval_ms = 60000 / configuration.cpm;

        if (xTimerChangePeriod(metronome_timer, pdMS_TO_TICKS(interval_ms), 0) != pdPASS)
        {
            ESP_LOGE(TAG, "Error al cambiar el periodo del temporizador");
        }
    }
    else if (configuration.cpm == 0)
    {
        ESP_LOGW(TAG, "El valor de CPM es 0, no se actualizó el temporizador");
    }
}

// Función para manejar el evento del botón
void toggle_metronome_event_handler(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    bool checked = lv_obj_has_state(btn, LV_STATE_CHECKED);

    if (checked)
    {
        ESP_LOGI(TAG, "Metronome activado");
        update_metronome_timer(); // Actualiza el temporizador con el intervalo correcto
        xTimerStart(metronome_timer, 0);
        configuration.metronome_active = true;
    }
    else
    {
        ESP_LOGI(TAG, "Metronome desactivado");
        xTimerStop(metronome_timer, 0);
        configuration.metronome_active = false;
    }
}

//--------- botones Init / Stop / Back --------------------------

// Declarar el identificador de la tarea del consumidor
static TaskHandle_t consumidor_task_handle = NULL;

void init_training(lv_event_t *e)
{
    char buffer[16];
    if (!configuration.training_active)
    {
        // limpiar etiquetas
        sprintf(buffer, "%i", 0);
        lv_label_set_text(ui_frec, buffer);

        sprintf(buffer, "%i%%", 0);
        lv_label_set_text(ui_correct, buffer);
        lv_label_set_text(ui_shallow, buffer);
        lv_label_set_text(ui_deep, buffer);

        sprintf(buffer, "%.1f", 0.0f);
        lv_label_set_text(ui_depth, buffer);

        hall_sensor_start();
        if (xTaskCreate(consumidor_task, "Consumidor Task", 4096, NULL, 2, &consumidor_task_handle) != pdPASS)
        {
            ESP_LOGE(TAG, "Failed to create Consumidor Task");
            consumidor_task_handle = NULL;
        }
        configuration.training_active = true;
    }
}

void stop_training(lv_event_t *e)
{
    if (configuration.training_active)
    {

        lv_img_set_angle(ui_pointer, -1300);
        hall_sensor_stop();

        if (consumidor_task_handle != NULL)
        {
            vTaskDelete(consumidor_task_handle);
            consumidor_task_handle = NULL;
            ESP_LOGI(TAG, "Consumidor Task deleted");
        }

        // Liberar la cola si existe
        if (hall_sensor_data_queue != NULL)
        {
            vQueueDelete(hall_sensor_data_queue);
            hall_sensor_data_queue = NULL; // Evita referencias a una cola eliminada
            ESP_LOGI(TAG, "Queue deleted");
        }
        configuration.training_active = false;
    }
}

void btn_back_training(lv_event_t *e)
{
    // Detener el metrónomo si está activo
    if (configuration.metronome_active)
    {
        ESP_LOGI(TAG, "Metronome desactivado al salir");
        xTimerStop(metronome_timer, 0);         // Detener el temporizador del metrónomo
        configuration.metronome_active = false; // Restablecer el flag a su valor predeterminado
    }

    // Limpiar el estado del botón de metrónomo
    lv_obj_clear_state(ui_btnMetro, LV_STATE_CHECKED);

    ESP_LOGI(TAG, "Estado del botón de metrónomo restablecido");

    if (configuration.training_active)
    {
        stop_training(NULL);
    }
}

void load_training(lv_event_t *e)
{

    char buffer[16];
    sprintf(buffer, "%i", 0);
    lv_label_set_text(ui_frec, buffer);

    sprintf(buffer, "%i%%", 0);
    lv_label_set_text(ui_correct, buffer);
    lv_label_set_text(ui_shallow, buffer);
    lv_label_set_text(ui_deep, buffer);

    sprintf(buffer, "%.1f", 0.0f);
    lv_label_set_text(ui_depth, buffer);
    lv_img_set_angle(ui_pointer, -1300); // bajar la aguja a cero
};

//////////////// VENTANA CONFIGURACION ////////////////////////

// carga de parametros en ventana configuracion
void load_configuration(lv_event_t *e)
{
    ESP_LOGI(TAG, "Cargando datos de configuracion");

    lv_obj_t *minDropdown = ui_minDropdown;
    lv_obj_t *cpmDropDown = ui_cpmDropdown;

    switch (configuration.time)
    {
    case 1:
        lv_dropdown_set_selected(minDropdown, 0);
        break;
    case 2:
        lv_dropdown_set_selected(minDropdown, 1);
        break;
    case 3:
        lv_dropdown_set_selected(minDropdown, 2);
        break;
    case 4:
        lv_dropdown_set_selected(minDropdown, 3);
        break;
    case 5:
        lv_dropdown_set_selected(minDropdown, 4);
        break;
    default:
        lv_dropdown_set_selected(minDropdown, 0);
        break;
    }

    switch (configuration.cpm)
    {
    case 100:
        lv_dropdown_set_selected(cpmDropDown, 0);
        break;
    case 110:
        lv_dropdown_set_selected(cpmDropDown, 1);
        break;
    case 120:
        lv_dropdown_set_selected(cpmDropDown, 2);
        break;
    case 130:
        lv_dropdown_set_selected(cpmDropDown, 3);
        break;
    case 140:
        lv_dropdown_set_selected(cpmDropDown, 4);
        break;
    default:
        lv_dropdown_set_selected(cpmDropDown, 0);
        break;
    }
}

void save_configuration(lv_event_t *e)
{
    char min_str[16];
    char cpm_str[16];

    lv_dropdown_get_selected_str(ui_minDropdown, min_str, sizeof(min_str));
    lv_dropdown_get_selected_str(ui_cpmDropdown, cpm_str, sizeof(cpm_str));

    if (strcmp(min_str, "1:00") == 0)
        configuration.time = 1;
    else if (strcmp(min_str, "2:00") == 0)
        configuration.time = 2;
    else if (strcmp(min_str, "3:00") == 0)
        configuration.time = 3;
    else if (strcmp(min_str, "4:00") == 0)
        configuration.time = 4;
    else if (strcmp(min_str, "5:00") == 0)
        configuration.time = 5;

    if (strcmp(cpm_str, "100") == 0)
        configuration.cpm = 100;
    else if (strcmp(cpm_str, "110") == 0)
        configuration.cpm = 110;
    else if (strcmp(cpm_str, "120") == 0)
        configuration.cpm = 120;
    else if (strcmp(cpm_str, "130") == 0)
        configuration.cpm = 130;
    else if (strcmp(cpm_str, "140") == 0)
        configuration.cpm = 140;
};

///////////// VENTANA EVALUACION /////////////////////

// Variables globales
static TimerHandle_t time_counter_timer = NULL;
static uint32_t remaining_time = 0;

static TaskHandle_t evaluation_task_handle = NULL;

static void evaluation_task(void *pvParameter)
{
    compression_data_t dato_recibido;

    while (1)
    {
        if (xQueueReceive(hall_sensor_data_queue, &dato_recibido, pdMS_TO_TICKS(100)) == pdTRUE)
        {

            if (dato_recibido.compressions > 0)
            {
                configuration.correct_compressions = dato_recibido.correct_compressions * 100 / dato_recibido.compressions;
                configuration.shallow_compressions = dato_recibido.shallow_compressions * 100 / dato_recibido.compressions;
                configuration.deep_compressions = dato_recibido.deep_compressions * 100 / dato_recibido.compressions;
                configuration.avg_cpm = dato_recibido.avg_cpm;

                printf("correct = %i\n", configuration.correct_compressions);
                printf("shallow = %i\n", configuration.shallow_compressions);
                printf("deep = %i\n", configuration.deep_compressions);
                printf("avg = %i\n", configuration.avg_cpm);
            }
            else
            {
                configuration.correct_compressions = 0;
                configuration.shallow_compressions = 0;
                configuration.deep_compressions = 0;
            }
        }
    }
}

// Conversión de segundos a MM:SS y actualización de LVGL
static void update_time_display(uint32_t time_seconds)
{
    char buffer[12]; // Formato MM:SS
    uint32_t minutes = time_seconds / 60;
    uint32_t seconds = time_seconds % 60;

    sprintf(buffer, "%01" PRIu32 ":%02" PRIu32, minutes, seconds);

    lv_label_set_text(ui_evalTime, buffer);
}

// Callback del temporizador
static void timer_callback(TimerHandle_t xTimer)
{
    if (remaining_time > 0)
    {
        remaining_time--;
        update_time_display(remaining_time);

        if (remaining_time == 0)
        {
            ESP_LOGI(TAG, "Tiempo completado");
            configuration.evaluation_active = false;
            xTimerStop(time_counter_timer, 0);

            // detener sensor, eliminar tarea y cola
            hall_sensor_stop();

            if (evaluation_task_handle != NULL)
            {
                vTaskDelete(evaluation_task_handle);
                evaluation_task_handle = NULL;
                ESP_LOGI(TAG, "Evaluation Task deleted");
            }
            // Liberar la cola si existe
            if (hall_sensor_data_queue != NULL)
            {
                vQueueDelete(hall_sensor_data_queue);
                hall_sensor_data_queue = NULL;
                ESP_LOGI(TAG, "Queue deleted");
            }

            configuration.evaluation_active = false;
            lv_scr_load(ui_ResultsScreen);
        }
    }
}

// Función para iniciar el temporizador
void init_timer(void)
{
    if (time_counter_timer == NULL)
    {
        time_counter_timer = xTimerCreate("Time Counter", pdMS_TO_TICKS(1000), pdTRUE, NULL, timer_callback);
        if (time_counter_timer == NULL)
        {
            ESP_LOGE(TAG, "Error al crear el temporizador");
        }
    }
}

// Evento del botón "Inicio"
void init_evaluation(lv_event_t *e)
{
    if (!configuration.evaluation_active)
    {
        configuration.evaluation_active = true;
        ESP_LOGI(TAG, "Evaluacion iniciada");

        init_timer();
        remaining_time = configuration.time * 60;
        update_time_display(remaining_time);
        xTimerStart(time_counter_timer, 0);

        hall_sensor_start();

        if (xTaskCreate(evaluation_task, "Evaluation Task", 4096, NULL, 2, &evaluation_task_handle) != pdPASS)
        {
            ESP_LOGE(TAG, "Failed to create Consumidor Task");
            evaluation_task_handle = NULL;
        }
    }
}

// Evento del botón "Stop"
void stop_evaluation(lv_event_t *e)
{
    if (configuration.evaluation_active)
    {

        if (time_counter_timer != NULL)
        {
            xTimerStop(time_counter_timer, 0);
        }
        update_time_display(0);

        hall_sensor_stop();

        if (evaluation_task_handle != NULL)
        {
            vTaskDelete(evaluation_task_handle);
            evaluation_task_handle = NULL;
            ESP_LOGI(TAG, "Evaluation Task deleted");
        }

        if (hall_sensor_data_queue != NULL)
        {
            vQueueDelete(hall_sensor_data_queue);
            hall_sensor_data_queue = NULL;
            ESP_LOGI(TAG, "Queue deleted");
        }

        configuration.evaluation_active = false;
        ESP_LOGI(TAG, "Evaluacion detenida");
    }
}

// Evento del botón "Volver"
void btn_back_evaluation(lv_event_t *e)
{
    if (configuration.evaluation_active)
    {
        stop_evaluation(e);
    }
    ESP_LOGI(TAG, "Saliendo de Evaluacion");
}

// carga de datos al iniciar ventana
void load_evaluation(lv_event_t *e)
{
    char buffer[16];
    sprintf(buffer, "%0i:00", configuration.time);
    lv_label_set_text(ui_confTime, buffer);
    lv_label_set_text(ui_evalTime, buffer);

    sprintf(buffer, "%li", configuration.cpm);
    lv_label_set_text(ui_confCpm, buffer);

    ESP_LOGI(TAG, "Entrando Evaluacion");
};

////////////////// VENTANA RESULTADOS ////////////////////////////////////

void load_results(lv_event_t *e)
{
    char buffer[16];
    sprintf(buffer, "%0i:00", configuration.time);
    lv_label_set_text(ui_confTime1, buffer);
    lv_label_set_text(ui_evalTime1, buffer);

    sprintf(buffer, "%li", configuration.cpm);
    lv_label_set_text(ui_confCpm1, buffer);

    sprintf(buffer, "%i%%", configuration.correct_compressions);
    lv_label_set_text(ui_correct1, buffer);

    sprintf(buffer, "%i%%", configuration.shallow_compressions);
    lv_label_set_text(ui_shallow1, buffer);

    sprintf(buffer, "%i%%", configuration.deep_compressions);
    lv_label_set_text(ui_deep1, buffer);

    sprintf(buffer, "%i", configuration.avg_cpm);
    lv_label_set_text(ui_evalCpm, buffer);
};