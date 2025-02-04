/*
 * License Agreement
 *
 * Copyright (c) 2024 Gus Di Stefano <narniancoder@gmail.com>
 * All rights reserved.
 *
 * This software and its associated documentation files (the "Software") are the property of the copyright holder.
 * The unauthorized reproduction, modification, distribution, sublicense, or sale of the Software is prohibited
 * unless explicitly permitted by the copyright holder.
 *
 * Permission is hereby granted, free of charge, to authorized individuals or entities for the sole purpose of
 * using the Software in accordance with the terms set forth by the copyright holder. This permission is non-transferable
 * and may be revoked at any time.
 *
 * Redistribution of this Software, whether in source or binary form, is strictly forbidden without prior written
 * permission from the copyright holder.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/**
 * @file hall_sensor.h
 * @defgroup hall_sensor Hall Sensor Module
 * @brief Module for handling the ESP-IDF Hall Sensor.
 *
 * This module provides functions to start, stop, suspend, and resume the task that reads
 * data from the Hall sensor using the ESP-IDF framework. It processes raw ADC values
 * and stores filtered data for further analysis.
 *
 * Copyright (c) 2024 Gus Di Stefano <narniancoder@gmail.com>
 * All rights reserved.
 * @{
 */

#ifndef __COMPONENTS_HALL_SENSOR_H__
#define __COMPONENTS_HALL_SENSOR_H__

#include <stdint.h>
#include <esp_err.h>
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Structure to store compression data.
 *
 * This structure holds information about the current and average compressions per minute (CPM),
 * as well as statistics about the depth of compressions (correct, shallow, deep).
 */
typedef struct
{
    int cpm;                     /**< Current compressions per minute */
    int avg_cpm;                 /**< Average compressions per minute */
    int compressions;            /**< Total number of compressions */
    float depth;                   /**< Depth of the last compression (measured in units) */
    int correct_compressions;    /**< Number of compressions with correct depth */
    int shallow_compressions;    /**< Number of compressions with depth below the correct range */
    int deep_compressions;       /**< Number of compressions with depth above the correct range */
} compression_data_t;


    /**
     * @brief Start the Hall sensor data producer task.
     *
     * This function initializes and starts the task that reads data from the Hall sensor,
     * processes it, and sends it to a queue for further handling.
     *
     * @note This function must be called before attempting to use the sensor data.
     */
    void hall_sensor_start(void);

    /**
     * @brief Suspend the Hall sensor data producer task.
     *
     * This function temporarily suspends the task that reads data from the Hall sensor.
     * Use this function to pause data collection without fully stopping the sensor.
     */
    void hall_sensor_suspend(void);

    /**
     * @brief Resume the Hall sensor data producer task.
     *
     * This function resumes the task that reads data from the Hall sensor after it has been suspended.
     * Use this function to restart data collection after a suspension.
     */
    void hall_sensor_resume(void);

    /**
     * @brief Stop the Hall sensor data producer task.
     *
     * This function stops the task that reads data from the Hall sensor and frees up any resources
     * that were allocated during the operation of the task.
     *
     * @note Once this function is called, the Hall sensor will no longer produce data until
     * hall_sensor_start() is called again.
     */
    void hall_sensor_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* __COMPONENTS_HALL_SENSOR_H__ */

/** @} */ // End of hall_sensor group
