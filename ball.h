/** @file   ball.h
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Ball functions for the game

    @defgroup ?
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
