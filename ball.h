#ifndef BALL_H
#define BALL_H
#include "system.h"
#include "game.h"
#include "player.h"
#include "tinygl.h"
#include "slider.h"
#include "pong_system.h"
#include "pong_game.h"


typedef struct {
    uint8_t x;
    uint8_t y;
    int8_t direction;
    int8_t angle;
} ball_t;


void update_ball(ball_t *ball, player_t *player, slider_t *slider, uint16_t *ball_tick, uint8_t *player_score, game_state_t *game_state, bool *slider_drawn);

void transmit_ball(ball_t *ball, player_t *player, uint8_t *player_score);

#endif