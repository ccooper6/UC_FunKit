/** @file   game_state.h
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Functions affecting the state of the game

    @defgroup
*/
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>
#include <stdbool.h>
#include "slider.h"

/* Forward declaration of ball_t (circular dependency)*/
typedef struct ball ball_t;

/* Defines the states a player can be in */
typedef enum {
    START,
    PLAY,
    END
} game_state_t;

/** Checks if the game is over and sends a message to the other player if it is
* @param game_state the pointer to current state of the game
* @param player_score the pointer to the current score of the player
*/
void check_game_over(game_state_t *game_state, uint8_t *player_score);

/** Increments the player score and resets the game if the player has lost the round
 * @param player_score the pointer to the current score of the player
 * @param slider the pointer to the players slider
 * @param ball the pointer to the players ball
 * @param game_state the pointer to the current state of the game
 * @param slider_drawn the pointer to whether the slider has been drawn yet or not
 */
void player_lost_round(uint8_t *player_score, slider_t *slider, ball_t *ball, game_state_t *game_state, bool *slider_drawn);

/** Displays the winner/loser of the game using tinygl text
 * @param player_score the current score of the player
 */
void show_winner(uint8_t player_score);

#endif
