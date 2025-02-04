#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "lcd.h"

#include "buzzer.h"
#include "notes.h"

#include "hall_sensor.h"

#include "ui.h"

#include "configuration.h"

/////// GLOBAL VARIABLES ////////////////////////////////

/**
 * @brief Global configuration parameters.
 *
 * This structure holds the initial configuration values, including compressions per minute (CPM),
 * session time, and states for metronome, training, and evaluation modes. It is used throughout 
 * the application to manage the CPR session parameters and statistics.
 */
configuration_t configuration = {
    .cpm = 100,               /**< Compressions per minute */
    .time = 1,                /**< Time in minutes */
    .metronome_active = false,/**< Metronome is off initially */
    .training_active = false, /**< Training mode is off initially */
    .evaluation_active = false, /**< Evaluation is off initially */
    .avg_cpm = 0,             /**< Initial average compressions per minute */
    .correct_compressions = 0, /**< Initial number of correct compressions */
    .shallow_compressions = 0, /**< Initial number of shallow compressions */
    .deep_compressions = 0,   /**< Initial number of deep compressions */
};

/**
 * @brief Main application entry point.
 *
 * This is the main function that runs when the application starts. It initializes the necessary 
 * hardware components, including the buzzer and LCD display, and prepares the system for use.
 */
void app_main(void)
{
    // Initialize the buzzer
    init_buzzer();

    // Initialize the LCD with LVGL (LittlevGL) library
    init_LVGL();
}
