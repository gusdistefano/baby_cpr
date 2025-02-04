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
 * @file dsp.h
 * @defgroup dsp
 * @{
 *
 * ESP-IDF Digital Signal Processing
 *
 * Copyright (c) 2024 Gus Di Stefano <narniancoder@gmail.com>
 *
 * MIT Licensed as described in the file LICENSE
 */

#ifndef __COMPONENTS_DSP_H__
#define __COMPONENTS_DSP_H__

#include <stdint.h>
#include <stdbool.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Struct to represent a Kalman Filter.
     */
    typedef struct
    {
        float q; //!< Process variance (how much the system is believed to change)
        float r; //!< Measurement variance (how much the measurement is trusted)
        float x; //!< Estimated value (state)
        float p; //!< Estimated error of the estimation
        float k; //!< Kalman gain (weight between measurement and estimation)
    } kalmanFilter_t;

    /**
     * @brief Initialize a Kalman Filter.
     *
     * @param kf Pointer to the Kalman Filter structure.
     * @param q Process variance, which represents how much the system is expected to change.
     *           Typical range: 0.001 to 1.0.
     *           - Lower values assume the system changes slowly (good for stable processes).
     *           - Higher values assume the system changes rapidly (useful when tracking fast-changing data).
     * @param r Measurement variance, indicating how much the measurement is trusted.
     *           Typical range: 0.1 to 10.0.
     *           - Lower values assume high trust in the measurements (less noisy sensors).
     *           - Higher values assume low trust in measurements (noisy sensors).
     * @param initial_value Initial estimated value.
     *           Set this to an estimated starting point close to the expected measurement range.
     * @return `ESP_OK` on success.
     */
    esp_err_t kalman_init(kalmanFilter_t *kf, float q, float r, float initial_value);

    /**
     * @brief Apply a new measurement to the Kalman filter and update the estimated state.
     *
     * This function uses the Kalman filter algorithm to predict and update the estimated state
     * based on the new measurement provided.
     *
     * @param kf Pointer to the Kalman Filter structure.
     * @param measurement Pointer to the new measurement value from the sensor.
     * @return The updated estimated state after applying the measurement.
     */
    float kalman_update(kalmanFilter_t *kf, const float *measurement);

    /**
     * @brief Applies an Exponential Moving Average (Low Pass Filter) to smooth the input signal.
     *
     * This function uses a simple Exponential Moving Average (EMA) formula to apply low-pass filtering
     * to the input signal. It helps reduce noise and smooth rapid variations in sensor readings.
     *
     * Formula:
     *      *filtered_value = alpha * (*filtered_value) + (1 - alpha) * (*current_value);
     *
     * @param filtered_value Pointer to the previous filtered value (output of the last filtering step).
     * @param current_value Pointer to the latest sensor measurement or input signal value.
     * @param alpha  Pointer the smoothing factor between 0 and 1.
     *        - Closer to 1: Retains more of the previous value (slower response, more smoothing).
     *        - Closer to 0: Follows the input more closely (faster response, less smoothing).
     */
    void low_pass_filter(float *filtered_value, const float *current_value, const float alpha);

#ifdef __cplusplus
}
#endif

#endif /* __COMPONENTS_DSP_H__ */
