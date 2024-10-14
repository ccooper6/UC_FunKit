/** @file   initialising.h
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Initialising functions for the game

    @defgroup ?
*/
#ifndef INITIALISING_H
#define INITIALISING_H

#include "slider.h"
#include "ball.h"

/* Define polling rate in Hz */
#define PACER_RATE 500

/* Define rate the text moves for tinygl in Hz */
#define MESSAGE_RATE 10

/** Initialises the system - system, tinygl, pacer, navswitch and ir uart */
void init_system(void);

/** Initialises the slider and ball positions and sets the tinygl text settings.
 * @param slider pointer to the players slider to be initialised.
 * @param ball pointer to the players ball to be initialised.
 */
void init_game(slider_t *slider, ball_t *ball);

#endif
