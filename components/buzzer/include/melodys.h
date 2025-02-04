/**
 * @file buzzer.h
 * @defgroup buzzer Buzzer Melodies
 * @brief ESP-IDF Buzzer Melodies
 * @{
 *
 * This file provides functions to play predefined melodies like the
 * Pirate theme, Super Mario theme, and Star Wars theme on a passive buzzer
 * using ESP-IDF.
 *
 * Copyright (c) 2024 Gus Di Stefano <narniancoder@gmail.com>
 *
 * MIT Licensed as described in the file LICENSE
 */

#ifndef __COMPONENTS_MELODYS_H__
#define __COMPONENTS_MELODYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Plays the "Pirate" theme melody on the buzzer.
     *
     * This function plays a preprogrammed "Pirates of Caribbean" theme melody using the buzzer.
     */
    void play_pirate();

    /**
     * @brief Plays the "Super Mario" theme melody on the buzzer.
     *
     * This function plays a preprogrammed "Super Mario" theme melody using the buzzer.
     */
    void play_super_mario(void);

    /**
     * @brief Plays the "Star Wars" theme melody on the buzzer.
     *
     * This function plays a preprogrammed "Star Wars" theme melody using the buzzer.
     */
    void play_star_wars(void);

#ifdef __cplusplus
}
#endif

#endif /* __COMPONENTS_MELODYS_H__ */

/** @} */
