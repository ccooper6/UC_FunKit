/** @file   ball.h
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Ball functions for the game

    @defgroup Ball
    This module implements the structure and functions required to implement a working ball. 
*/
#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include "game_state.h"
#include "player.h"
#include "slider.h"

/** Structure defining state of a ball.  */
typedef struct ball {
    uint8_t x;
    uint8_t y;
    int8_t direction;
    int8_t angle;
} ball_t;

/** Checks if the ball has hit the slider
* @param ball the pointer to the ball to check
* @param slider the pointer to the slider to check
*/
bool ball_hits_slider(ball_t *ball, slider_t *slider);

/**
* Changes the trajectory of the ball when it hits the slider or the wall
* @param ball the pointer to the ball to change the angle and direction of
* @param slider the pointer to the slider use to base the changes off
*/
void change_ball_trajectory(ball_t *ball, slider_t *slider);

/** Checks if the ball has hit the wall
 * @param ball the pointer to the ball to check
 */
bool ball_hits_wall(ball_t *ball);

/** Checks if the ball has missed the slider
 * @param ball the pointer to the ball to check
 */
bool ball_misses_slider(ball_t *ball);

/**
 * Updates the balls position according to direction, angle and collisions
 * @param ball the ball to update
 * @param player the player to update
 * @param slider the slider to check position of
 * @param ball_tick how many ticks have passed since last update
 * @param player_score the current score of the player
 * @param game_state the current state of the game
 * @param slider_drawn whether the slider has been drawn yet or not
 */
void update_ball(ball_t *ball, player_t *player, slider_t *slider, uint16_t *ball_tick, uint8_t *player_score, game_state_t *game_state, bool *slider_drawn);

#endif
