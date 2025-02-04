#include <stdio.h>
#include "hall_sensor.h"
#include "dsp.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_timer.h"
#include <math.h>

#define ADC_CHANNEL CONFIG_HALL_SENSOR_ADC_CHANNEL
#define SENSOR_SAMPLES CONFIG_HALL_SENSOR_SAMPLES
#define SAMPLE_INTERVAL_MS CONFIG_HALL_SENSOR_SAMPLE_INTERVAL_MS

#define QUEUE_SIZE 30 // Queue size
#define ALPHA 0.47f   // Low-pass filter smoothing factor

#define MIN_PEAK_DIST 300  // Minimum distance between peaks in milliseconds for 200 CPM
#define MAX_PEAK_DIST 1500 // Maximum distance between peaks in milliseconds for 40 CPM

#define MIN_PEAK_HEIGHT 3.0f // Minimum height of a peak/valley to be detected
#define WINDOW_SIZE 18       // Time window for average CPM - 18 samples at 80 ms = 1440 ms used in stats()
#define MAX_DEPTH 200        // Maximum allowed depth
#define MIN_DEPTH 15         // Minimum allowed depth

#define MIN_SLOPE 0.0005f // Minimum slope required to detect peaks (adjust based on data)
#define MAX_IDLE_TIME 300 // Idle time to bypass the use of MIN_SLOPE

typedef struct
{
    int64_t time; // Timestamp in ms
    float value;
} data_point_t;

// Adjust depending on the function being used
//  last_peak = 0 and last_valley = -1 for detect_peaks
//  last_peak = -1 and last_valley = 0 for detect_valleys

data_point_t last_peak = {-1, -1};
data_point_t last_valley = {0, 0};
compression_data_t cpr_stats = {0, 0, 0, 0, 0, 0, 0};

static const char *TAG = "Hall Sensor";

QueueHandle_t hall_sensor_data_queue = NULL;        // Queue handle
static TaskHandle_t hall_sensor_task_handle = NULL; // Task handle

//------------------------------------------------------------------------------------------------------------

// Function to reset compression stats
static void reset_compression_stats()
{
    cpr_stats.cpm = 0;
    cpr_stats.avg_cpm = 0;
    cpr_stats.compressions = 0;
    cpr_stats.depth = 0;
    cpr_stats.correct_compressions = 0;
    cpr_stats.shallow_compressions = 0;
    cpr_stats.deep_compressions = 0;
}

/*
 * Updates compression stats (CPM and types) using the peaks and depth.
 */
static void stats(data_point_t last_peak, data_point_t current_peak, float depth)
{
    // Buffer to store CPM values for the last 3 seconds
    static float cpm_window[WINDOW_SIZE] = {0};
    static int index = 0;
    static int valid_entries = 0;    // Counter for valid entries
    static float sum_cpm_window = 0; // Accumulator for the average

    // Distance between peaks
    cpr_stats.cpm = 1000 * 60 / (current_peak.time - last_peak.time); // 1 sec / distance

    // Update the total number of compressions
    cpr_stats.compressions++;

    // Update compression type
    cpr_stats.depth = depth; // Depth of the last compression

    if (depth > MAX_DEPTH)
    {
        cpr_stats.deep_compressions++;
    }
    else if (depth < MIN_DEPTH)
    {
        cpr_stats.shallow_compressions++;
    }
    else
    {
        cpr_stats.correct_compressions++;
    }

    // Update the circular buffer
    int idx = index % WINDOW_SIZE;

    // Subtract the oldest value from the accumulator
    sum_cpm_window -= cpm_window[idx];
    // Add the new value to the buffer and accumulator
    cpm_window[idx] = cpr_stats.cpm;
    sum_cpm_window += cpr_stats.cpm;

    index++;

    // Increment valid entries until the buffer is full
    if (valid_entries < WINDOW_SIZE)
    {
        valid_entries++;
    }

    // Calculate the average of the last valid values
    cpr_stats.avg_cpm = sum_cpm_window / valid_entries; // Optimized dynamic average
}

/*
 * Detects valleys (inverted peaks, since the resting signal is high).
 */

static void detect_valleys(data_point_t current, data_point_t previous)
{
    static float last_derivative = 0; // Previous derivative
    float current_derivative = current.value - previous.value;
    static int counter = 0;

    // Detect valleys (inverted peaks) -> Change from negative to positive slope
    if (last_derivative < 0 && current_derivative > 0)
    { // Change to positive slope
        // Check if there is a previous peak

        if (last_peak.time != -1)
        {
            // Check if the valley exceeds height, distance, and slope thresholds
            float slope = fabs(last_peak.value - previous.value) / (previous.time - last_valley.time); // Slope

            // Valley must exceed height and time distance thresholds
            if ((last_peak.value - previous.value) > MIN_PEAK_HEIGHT && // Minimum height required
                (previous.time - last_valley.time) > MIN_PEAK_DIST)     // Minimum peak-to-peak distance

            {
                if (slope > MIN_SLOPE) 
                {
                    stats(last_valley, previous, last_peak.value - previous.value);
                    counter++;
                    if (xQueueSend(hall_sensor_data_queue, &cpr_stats, portMAX_DELAY) != pdPASS)
                    {
                        printf("Error: Queue is full, data could not be sent\n");
                    }
                    last_valley = previous;
                }
            }
        }
    }

    // Detect peaks (inverted valleys) -> Change from positive to negative slope
    if (last_derivative > 0 && current_derivative < 0)
    {
        last_peak = previous; // Save peak (equivalent to inverted valley)
    }

    // Update previous derivative
    last_derivative = current_derivative;
}

// Initialize ADC in One-shot mode
static esp_err_t init_adc(adc_oneshot_unit_handle_t *adc_handle)
{
    esp_err_t ret;

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE};

    ret = adc_oneshot_new_unit(&init_config, adc_handle);
    if (ret != ESP_OK)
    {
        return ret;
    }

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12, // Attenuation for voltages up to ~2450 mV
        .bitwidth = ADC_BITWIDTH_DEFAULT};

    ret = adc_oneshot_config_channel(*adc_handle, ADC_CHANNEL_0, &config);
    if (ret != ESP_OK)
    {
        return ret;
    }

    return ESP_OK;
}

/*
 * Reads data from the Hall sensor using the ADC, filters it with a low-pass filter,
 * and calls detect_valleys() to detect valleys in the processed signal.
 */
static void hall_sensor_task(void *pvParameters)
{
    float adc_accum = 0;
    int raw_value;
    float filtered_value = 2200;
    data_point_t current = {0, 0};
    data_point_t previous = {0, 0};

    // Initialize ADC
    static bool adc_initialized = false; // Flag to control initialization
    static adc_oneshot_unit_handle_t adc1_handle;

    if (!adc_initialized) // If not initialized
    {
        esp_err_t ret = init_adc(&adc1_handle); // Try to initialize
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "CANNOT INITIALIZE ADC - CHECK");
            vTaskDelete(NULL); // Delete task if initialization fails
            return;            // Exit the function to avoid issues
        }

        adc_initialized = true; // Mark as initialized only if successful
        ESP_LOGI(TAG, "ADC successfully initialized");
    }

    while (1)
    {
        // Read ADC and average the samples
        adc_accum = 0;
        for (uint8_t i = 0; i < SENSOR_SAMPLES; i++)
        {
            adc_oneshot_read(adc1_handle, ADC_CHANNEL, &raw_value);
            adc_accum += raw_value;
        }
        adc_accum /= SENSOR_SAMPLES; // Averaging the samples

        // Filter using a low-pass filter
        low_pass_filter(&filtered_value, &adc_accum, ALPHA);

        // Update the data points
        previous = current;
        current.time = esp_timer_get_time() / 1000; // Time in ms
        current.value = filtered_value;

        // Detect peaks and valleys
        detect_valleys(current, previous);

        // Wait until the next sample
        vTaskDelay(pdMS_TO_TICKS(SAMPLE_INTERVAL_MS));
    }
}

// Start the Hall sensor task and create the queue
void hall_sensor_start(void)
{
    reset_compression_stats(); // Clear statistics
    // Create the queue to store compression data
    hall_sensor_data_queue = xQueueCreate(QUEUE_SIZE, sizeof(compression_data_t));
    if (hall_sensor_data_queue == NULL)
    {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }
    ESP_LOGI(TAG, "Queue created ..");
    if (xTaskCreate(hall_sensor_task, "hall_sensor_task", 2048, NULL, 2, &hall_sensor_task_handle) != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create hall_sensor_task");
        // If task creation fails, delete the created queue
        vQueueDelete(hall_sensor_data_queue);
        hall_sensor_data_queue = NULL;
        return;
    };
    ESP_LOGI(TAG, "Task created ..");
}

// Suspend the Hall sensor task
void hall_sensor_suspend(void)
{
    if (hall_sensor_task_handle != NULL)
    {
        vTaskSuspend(hall_sensor_task_handle);
    }
}

// Resume the Hall sensor task
void hall_sensor_resume(void)
{
    if (hall_sensor_task_handle != NULL)
    {
        vTaskResume(hall_sensor_task_handle);
    }
}

// Stop the Hall sensor task
void hall_sensor_stop(void)
{
    if (hall_sensor_task_handle != NULL)
    {
        vTaskDelete(hall_sensor_task_handle);
        hall_sensor_task_handle = NULL;
    }
}
