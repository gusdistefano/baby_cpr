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
 * @file lcd.h
 * @defgroup LCD_Touch LCD & Touch Component
 * @brief Component for LCD & Touch screen handling in ESP-IDF.
 * @{
 *
 * This component provides an interface for initializing and controlling
 * an LCD display and touch panel using the ESP-IDF framework. It includes
 * functions to initialize the SPI bus, set up the display and touch panel,
 * control the backlight, and draw basic shapes.
 *
 * Copyright (c) 2024 Gus Di Stefano <narniancoder@gmail.com>
 *
 * MIT Licensed as described in the file LICENSE
 */

#ifndef __COMPONENTS_LCD_H__
#define __COMPONENTS_LCD_H__

#include <stdint.h>
#include <stdbool.h>
#include <esp_err.h>
#include "esp_lcd_panel_io.h"
#include "esp_lcd_touch.h"
#include "hardware.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Controls the backlight of the LCD.
     *
     * This function sets the state of the LCD backlight. A state of 1 turns
     * the backlight on, while a state of 0 turns it off.
     *
     * @param state The state to set the backlight to.
     *              1 for on, 0 for off.
     */
    void backlight(uint8_t state);

    /**
     * @brief Initializes the SPI bus for communication with the LCD and Touch panel.
     *
     * This function configures the SPI bus with the necessary parameters and returns
     * the SPI host device that can be used for communication.
     *
     * @return spi_host_device_t The initialized SPI host device.
     */
    spi_host_device_t init_spi_bus(void);

    /**
     * @brief Initializes the touch panel.
     *
     * This function initializes the touch panel using the given SPI host device.
     *
     * @param spi_host The SPI host device to be used for communication with the touch panel.
     * @return esp_lcd_touch_handle_t The handle for the initialized touch panel.
     */
    esp_lcd_touch_handle_t init_touch_panel(spi_host_device_t spi_host);

    /**
     * @brief Initializes the LCD display.
     *
     * This function initializes the LCD display, setting it up for use with the
     * LVGL library.
     *
     * @param spi_host The SPI host device to be used for communication with the display.
     * @param disp_drv The display driver for LVGL.
     * @return esp_lcd_panel_handle_t The handle for the initialized display.
     */
    esp_lcd_panel_handle_t init_display(spi_host_device_t spi_host, lv_disp_drv_t *disp_drv);

    /**
     * @brief Initializes the LVGL (LittlevGL) graphics library for the display and touch screen.
     *
     * This function initializes the LVGL library, the SPI bus, the display, and the touch panel,
     * and sets up the required buffers for drawing. It also registers the display and touch drivers
     * with LVGL and installs a periodic tick timer to update LVGL. Additionally, it creates a task
     * for the LVGL task loop and displays the initial widget on the screen.
     *
     * The initialization process includes:
     * - Initializing the SPI bus for communication with the display and touch panel.
     * - Setting up the LVGL display buffer and touch input drivers.
     * - Registering the LVGL display and touch drivers to the LVGL framework.
     * - Allocating memory for the draw buffers used by LVGL.
     * - Creating a task for the LVGL loop, which is responsible for updating the display.
     * - Installing a periodic timer to call LVGL tick functions at a specified interval.
     *
     * This function is essential for setting up the LVGL graphics environment and making the
     * display and touch functionality ready for use in the application.
     *
     * @note This function uses FreeRTOS and ESP-IDF features, such as tasks, timers, and semaphores.
     * @note The memory allocated for the draw buffers must be large enough to hold at least 1/10
     * of the screen size, as recommended by LVGL documentation.
     */
    void init_LVGL();

#ifdef __cplusplus
}
#endif

#endif /* __COMPONENTS_LCD_H__ */

/** @} */
