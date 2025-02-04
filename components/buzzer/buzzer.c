#include <stdio.h>
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "buzzer.h"

#define BUZZER_PIN CONFIG_BUZZER_PIN
#define DEFAULT_VOLUME CONFIG_BUZZER_DEFAULT_VOLUME

#define LEDC_HS_TIMER LEDC_TIMER_0
#define LEDC_HS_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_CHANNEL LEDC_CHANNEL_0

void init_buzzer(void)
{
    // Timer configuration for the PWM channel
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // 13-bit resolution (8192 levels)
        .freq_hz = 1000,                      // Initial frequency set to 1kHz (can be dynamically adjusted)
        .speed_mode = LEDC_HS_MODE,           // High-speed mode
        .timer_num = LEDC_HS_TIMER,           // Timer number
        .clk_cfg = LEDC_AUTO_CLK              // Auto clock configuration
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_HS_CH0_CHANNEL,
        .duty = 0,              // Initial duty cycle set to 0 (buzzer off)
        .gpio_num = BUZZER_PIN, // GPIO pin connected to the buzzer
        .speed_mode = LEDC_HS_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_HS_TIMER};

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

// Function to play a MUSIC on the buzzer using PWM
void play_music(uint32_t frequency, uint32_t duration_ms, uint32_t volume)
{
    // Set the duty cycle based on the volume
    int duty_cycle = (8192 * volume) / 100; // 8192 represents 100% duty cycle for 13-bit resolution

    if (frequency > 0)
    {
        // Change the PWM signal frequency
        ledc_set_freq(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_0, frequency);

        // Set the duty cycle to 50% (to produce sound)
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty_cycle); // 50% duty cycle
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);

        // Wait for the duration of the note
        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        // Stop the sound
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0); // Set duty cycle to 0%
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    }
    else
    {
        // Wait for the duration of the note
        vTaskDelay(pdMS_TO_TICKS(duration_ms));
    }
    // Pause between notes
    vTaskDelay(pdMS_TO_TICKS(50)); // 50 ms pause between notes
}

// Function to play a tone on the buzzer without specifying volume (for compatibility with play_music)
void play_music_nv(uint32_t frequency, uint32_t duration_ms)
{
    play_music(frequency, duration_ms, DEFAULT_VOLUME); // Call the original function with the default volume
}

// Function to play a tone on the buzzer using PWM
void play_tone(uint32_t frequency, uint32_t duration_ms)
{
    // Set the duty cycle based on the volume
    int duty_cycle = (8192 * DEFAULT_VOLUME) / 100; // 8192 represents 100% duty cycle for 13-bit resolution

    if (frequency > 0)
    {
        // Change the PWM signal frequency
        ledc_set_freq(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_0, frequency);

        // Set the duty cycle to 50% (to produce sound)
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty_cycle); // 50% duty cycle
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);

        // Wait for the duration of the note
        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        // Stop the sound
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0); // Set duty cycle to 0%
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    }
    else
    {
        // Wait for the duration of the note
        vTaskDelay(pdMS_TO_TICKS(duration_ms));
    }
}