/** @file   initialising.h
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Initialising functions for the game

    @defgroup Initialise
    This module is used to initialise the following modules:
    system.h, tinygl.h, pacer.h, navswitch.h, ir_uart.h
*/
#ifndef INITIALISING_H
#define INITIALISING_H

#include "slider.h"
#include "ball.h"

/* Define pacer rate in Hz */
#define PACER_RATE 500

/* Define the rate the text moves for tinygl in Hz */
#define MESSAGE_RATE 10

/** Initialises the system which involves system, tinygl, pacer, navswitch and ir uart */
void init_system(void);

/** Initialises the slider and ball positions and sets the tinygl text settings.
 * @param slider pointer to the players slider to be initialised.
 * @param ball pointer to the players ball to be initialised.
 */
void init_game(slider_t *slider, ball_t *ball);

#endif
