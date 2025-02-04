/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Gus Di Stefano <narniancoder@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/**
 * @file buzzer.h
 * @defgroup buzzer Buzzer Driver
 * @brief ESP-IDF Passive Buzzer Driver
 * @{
 *
 * Driver to control a passive buzzer using ESP-IDF. It provides functions
 * to initialize the buzzer and play tones with or without volume control.
 *
 * Copyright (c) 2024 Gus Di Stefano <narniancoder@gmail.com>
 *
 * MIT Licensed as described in the file LICENSE
 */

#ifndef __COMPONENTS_BUZZER_H__
#define __COMPONENTS_BUZZER_H__

#include <stdint.h>
#include <stdbool.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initializes the buzzer.
     *
     * This function sets up the output pin for the buzzer and prepares
     * it for playing sounds. It must be called before playing any tone
     * or music using the buzzer.
     */
    void init_buzzer(void);

    /**
     * @brief Plays music on the buzzer using PWM.
     *
     * This function is designed to play a series of musical notes or tones
     * with a specified frequency, duration, and volume. It is ideal for
     * generating melodies or sound patterns.
     *
     * @param[in] frequency    Frequency of the note in Hz.
     * @param[in] duration_ms  Duration of the note in milliseconds.
     * @param[in] volume       Volume of the note, ranging from 0 (mute) to the maximum allowed level.
     */
    void play_music(uint32_t frequency, uint32_t duration_ms, uint32_t volume);

    /**
     * @brief Plays music on the buzzer with a preconfigured volume.
     *
     * Similar to `play_music`, but the volume is not specified as a parameter.
     * Instead, it uses the volume configured through `menuconfig`. This is
     * useful for cases where consistent volume levels are desired without
     * manual adjustment.
     *
     * @param[in] frequency    Frequency of the note in Hz.
     * @param[in] duration_ms  Duration of the note in milliseconds.
     */
    void play_music_nv(uint32_t frequency, uint32_t duration_ms);

    /**
     * @brief Plays a simple tone.
     *
     * This function generates a tone at a specific frequency for a given duration.
     * It uses the system-wide volume configuration set via `menuconfig`.
     * Ideal for generating beeps, alarms, or other simple sound cues.
     *
     * @param[in] frequency    Frequency of the tone in Hz.
     * @param[in] duration_ms  Duration of the tone in milliseconds.
     */
    void play_tone(uint32_t frequency, uint32_t duration_ms);

#ifdef __cplusplus
}
#endif

#endif /* __COMPONENTS_BUZZER_H__ */

/** @} */
