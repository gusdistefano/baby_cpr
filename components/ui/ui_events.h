/**
 * @file ui_events.h
 * @brief Header file defining event handlers for the graphical user interface (GUI).
 *
 * This header file declares a collection of event handler functions to handle
 * various user interactions in the graphical user interface (GUI). These functions 
 * are designed to work with the LVGL library and are triggered by events such as button 
 * clicks, toggles, and navigation actions.
 *
 * The file includes handlers for:
 * - Loading and saving configurations.
 * - Initializing, stopping, and navigating training sessions.
 * - Initializing, stopping, and navigating evaluation sessions.
 * - Loading and managing results display.
 * - Handling metronome toggling during training.
 *
 * Each function is designed to handle specific user actions and update the GUI or
 * application state accordingly.
 *
 * @note All functions take a parameter of type `lv_event_t*`, which represents
 *       the event data provided by the LVGL library.
 * 
 * @author Gus
 * @date 2024
 */

#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Load the configuration settings in the GUI.
 * @param e Event data from LVGL.
 */
void load_configuration(lv_event_t * e);

/**
 * @brief Save the current configuration settings from the GUI.
 * @param e Event data from LVGL.
 */
void save_configuration(lv_event_t * e);

/**
 * @brief Initialize the training session.
 * @param e Event data from LVGL.
 */
void init_training(lv_event_t * e);

/**
 * @brief Stop the training session.
 * @param e Event data from LVGL.
 */
void stop_training(lv_event_t * e);

/**
 * @brief Handle the "Back" button action during training.
 * @param e Event data from LVGL.
 */
void btn_back_training(lv_event_t * e);

/**
 * @brief Toggle the metronome on or off during training.
 * @param e Event data from LVGL.
 */
void toggle_metronome_event_handler(lv_event_t * e);

/**
 * @brief Load the training session screen or settings.
 * @param e Event data from LVGL.
 */
void load_training(lv_event_t * e);

/**
 * @brief Initialize the evaluation session.
 * @param e Event data from LVGL.
 */
void init_evaluation(lv_event_t * e);

/**
 * @brief Handle the "Back" button action during evaluation.
 * @param e Event data from LVGL.
 */
void btn_back_evaluation(lv_event_t * e);

/**
 * @brief Stop the evaluation session.
 * @param e Event data from LVGL.
 */
void stop_evaluation(lv_event_t * e);

/**
 * @brief Load the evaluation session screen or settings.
 * @param e Event data from LVGL.
 */
void load_evaluation(lv_event_t * e);

/**
 * @brief Load the results screen or data in the GUI.
 * @param e Event data from LVGL.
 */
void load_results(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _UI_EVENTS_H */
