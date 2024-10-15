/** @file   transmission.h
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Transmission functions for the game

    @defgroup Transmit
    This module implements the transmission functions required for the game. 
    It provides both sending and receiving functions to help transmit the necessary
    information between the two fun kits.

*/
#ifndef TRANSMIT_H
#define TRANSMIT_H

#include "player.h"
#include <stdint.h>
#include "game_state.h"

/** Transmits the ball to the other player
 * @param ball pointer to the ball to transmit
 * @param player pointer to the player to update
 * @param player_score pointer to the current score of the player
*/
void transmit_ball(ball_t *ball, player_t *player, uint8_t *player_score);

/**
 * Receives the transmission of the ball from the other player
 * @param ball pointer to the ball to display
 * @param player pointer to the player to update
 * @param player_score pointer to the current score of the player
 * @param game_state pointer the current state of the game
 */
void receive_transmission(ball_t *ball, player_t *player, uint8_t *player_score, game_state_t *game_state);

/** Sends the start notification to the other player */
void send_start_notification(void);

/** Receives the start notification from the other player
 * @param game_state the pointer to the current state of the game
 * @param player the pointer to the type of player the user is
 */
void receive_start_notification(game_state_t *game_state, player_t *player);

#endif
