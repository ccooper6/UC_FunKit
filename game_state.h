//
// Created by Caleb Cooper on 14/10/2024.
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>
#include <stdbool.h>
#include "slider.h"

typedef struct ball ball_t;

typedef enum {
    START,
    PLAY,
    END
} game_state_t;

void check_game_over(game_state_t *game_state, uint8_t *player_score);
void player_lost_round(uint8_t *player_score, slider_t *slider, ball_t *ball, game_state_t *game_state, bool *slider_drawn);
void show_winner(uint8_t player_score);

#endif //GAME_STATE_H
