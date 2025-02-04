#include "notes.h"
#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define VOLUME CONFIG_DEFAULT_VOLUME

// Custom delay_ms function
void delay_ms(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

// Function to play the Pirates of the Caribbean theme
void play_pirate()
{
    play_music_nv(NOTE_D4, 200); // 293.66 ~ NOTE_D4 Hz
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 200);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 200);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 200);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 200);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 200);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_C5, 100); // NOTE_C5.25 ~ NOTE_C5 Hz
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D5, 100); // NOTE_D5.33 ~ NOTE_D5 Hz
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D5, 100);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D5, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_E5, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_F5, 100); // NOTE_F5.45 ~ NOTE_F5 Hz
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_F5, 100);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_F5, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_F5, 100); // 783.99 ~ NOTE_F5 Hz
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_E5, 100);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_E5, 100);
    vTaskDelay(pdMS_TO_TICKS(200));
    play_music_nv(NOTE_D5, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_C5, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_C5, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
    play_music_nv(NOTE_D5, 100);
    vTaskDelay(pdMS_TO_TICKS(300));
    play_music_nv(NOTE_D4, 100);
    vTaskDelay(pdMS_TO_TICKS(100));
}

void play_super_mario()
{

    play_music_nv(NOTE_E7, 80);
    play_music_nv(NOTE_E7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_E7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_C7, 80);
    play_music_nv(NOTE_E7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_G7, 80);
    play_music_nv(0, 240);
    play_music_nv(NOTE_G6, 80);
    play_music_nv(0, 240);
    play_music_nv(NOTE_C7, 80);
    play_music_nv(0, 160);
    play_music_nv(NOTE_G6, 80);
    play_music_nv(0, 160);
    play_music_nv(NOTE_E6, 80);
    play_music_nv(0, 160);
    play_music_nv(NOTE_A6, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_B6, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_AS6, 80);
    play_music_nv(NOTE_A6, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_G6, 100);
    play_music_nv(NOTE_E7, 100);
    play_music_nv(NOTE_G7, 100);
    play_music_nv(NOTE_A7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_F7, 80);
    play_music_nv(NOTE_G7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_E7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_C7, 80);
    play_music_nv(NOTE_D7, 80);
    play_music_nv(NOTE_B6, 80);
    play_music_nv(0, 160);
    play_music_nv(NOTE_C7, 80);
    play_music_nv(0, 160);
    play_music_nv(NOTE_G6, 80);
    play_music_nv(0, 160);
    play_music_nv(NOTE_E6, 80);
    play_music_nv(0, 160);
    play_music_nv(NOTE_A6, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_B6, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_AS6, 80);
    play_music_nv(NOTE_A6, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_G6, 100);
    play_music_nv(NOTE_E7, 100);
    play_music_nv(NOTE_G7, 100);
    play_music_nv(NOTE_A7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_F7, 80);
    play_music_nv(NOTE_G7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_E7, 80);
    play_music_nv(0, 80);
    play_music_nv(NOTE_C7, 80);
    play_music_nv(NOTE_D7, 80);
    play_music_nv(NOTE_B6, 80);
    play_music_nv(0, 160);
}

void play_star_wars()
{
    play_music_nv(NOTE_A3, 500);
    play_music_nv(NOTE_A3, 500);
    play_music_nv(NOTE_A3, 500);
    play_music_nv(NOTE_F3, 375);
    play_music_nv(NOTE_C4, 125);

    play_music_nv(NOTE_A3, 500);
    play_music_nv(NOTE_F3, 375);
    play_music_nv(NOTE_C4, 125);
    play_music_nv(NOTE_A3, 1000);

    play_music_nv(NOTE_E4, 500);
    play_music_nv(NOTE_E4, 500);
    play_music_nv(NOTE_E4, 500);
    play_music_nv(NOTE_F4, 375);
    play_music_nv(NOTE_C4, 125);

    play_music_nv(NOTE_GS3, 500);
    play_music_nv(NOTE_F3, 375);
    play_music_nv(NOTE_C4, 125);
    play_music_nv(NOTE_A3, 1000);

    play_music_nv(NOTE_A4, 500);
    play_music_nv(NOTE_A3, 375);
    play_music_nv(NOTE_A3, 125);
    play_music_nv(NOTE_A4, 500);
    play_music_nv(NOTE_GS4, 375);
    play_music_nv(NOTE_G4, 125);

    play_music_nv(NOTE_FS4, 125);
    play_music_nv(NOTE_E4, 125);
    play_music_nv(NOTE_F4, 250);
    play_music_nv(0, 250);
    play_music_nv(NOTE_AS3, 250);
    play_music_nv(NOTE_DS4, 500);
    play_music_nv(NOTE_D4, 375);
    play_music_nv(NOTE_CS4, 125);

    play_music_nv(NOTE_C4, 125);
    play_music_nv(NOTE_B3, 125);
    play_music_nv(NOTE_C4, 250);
    play_music_nv(0, 250);
    play_music_nv(NOTE_F3, 250);
    play_music_nv(NOTE_GS3, 500);
    play_music_nv(NOTE_F3, 375);
    play_music_nv(NOTE_A3, 125);

    play_music_nv(NOTE_C4, 500);
    play_music_nv(NOTE_A3, 375);
    play_music_nv(NOTE_C4, 125);
    play_music_nv(NOTE_E4, 1000);

    play_music_nv(NOTE_A4, 500);
    play_music_nv(NOTE_A3, 375);
    play_music_nv(NOTE_A3, 125);
    play_music_nv(NOTE_A4, 500);
    play_music_nv(NOTE_GS4, 375);
    play_music_nv(NOTE_G4, 125);

    play_music_nv(NOTE_FS4, 125);
    play_music_nv(NOTE_E4, 125);
    play_music_nv(NOTE_F4, 250);
    play_music_nv(0, 250);
    play_music_nv(NOTE_AS3, 250);
    play_music_nv(NOTE_DS4, 500);
    play_music_nv(NOTE_D4, 375);
    play_music_nv(NOTE_CS4, 125);

    play_music_nv(NOTE_C4, 125);
    play_music_nv(NOTE_B3, 125);
    play_music_nv(NOTE_C4, 250);
    play_music_nv(0, 250);
    play_music_nv(NOTE_F3, 250);
    play_music_nv(NOTE_GS3, 500);
    play_music_nv(NOTE_F3, 375);
    play_music_nv(NOTE_C4, 125);

    play_music_nv(NOTE_A3, 500);
    play_music_nv(NOTE_F3, 375);
    play_music_nv(NOTE_C4, 125);
    play_music_nv(NOTE_A3, 1000);
}
