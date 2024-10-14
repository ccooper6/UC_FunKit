//
// Created by Caleb Cooper on 14/10/2024.
//

#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include "game_state.h"
#include "player.h"
#include "slider.h"

typedef struct ball {
    uint8_t x;
    uint8_t y;
    int8_t direction;
    int8_t angle;
} ball_t;


void update_ball(ball_t *ball, player_t *player, slider_t *slider, uint16_t *ball_tick, uint8_t *player_score, game_state_t *game_state, bool *slider_drawn);

#endif //BALL_H
