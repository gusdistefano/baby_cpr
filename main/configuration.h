// configuration.h
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Structure for configuration settings of CPR training.
 *
 * This structure holds the configuration details related to the training mode, 
 * including the compression rate, training time, and evaluation data.
 */
typedef struct
{
    uint32_t cpm;             /**< Compressions per minute */
    uint8_t time;             /**< Time in minutes */
    bool metronome_active;    /**< State of the metronome (active or not) */
    bool training_active;     /**< Indicates if training mode is active */
    bool evaluation_active;   /**< Indicates if an evaluation is in progress */
    int avg_cpm;              /**< Average compressions per minute */
    int correct_compressions; /**< Number of compressions with the correct depth */
    int shallow_compressions; /**< Number of compressions with depth below the correct range */
    int deep_compressions;    /**< Number of compressions with depth above the correct range */

} configuration_t;

/**
 * @brief Global configuration variable
 *
 * This variable holds the current configuration and status of the CPR training system.
 * It is shared across different parts of the program.
 */
extern configuration_t configuration;

#endif // CONFIGURATION_H
