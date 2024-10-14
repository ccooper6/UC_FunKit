//
// Created by Caleb Cooper on 14/10/2024.
//

#ifndef TRANSMIT_H
#define TRANSMIT_H

#include "ball.h"
#include "player.h"
#include <stdint.h>
#include "game_state.h"

void transmit_ball(ball_t *ball, player_t *player, uint8_t *player_score);
void receive_transmission(ball_t *ball, player_t *player, uint8_t *player_score, game_state_t *game_state);
void send_start_notification(void);
void recieve_start_notification(game_state_t *game_state, player_t *player);

#endif //TRANSMIT_H
