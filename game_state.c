//
// Created by Caleb Cooper on 14/10/2024.
//

#include "game_state.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "initialising.h"

#define BALL_MESSAGE_LENGTH 4

void check_game_over(game_state_t *game_state, uint8_t *player_score) {
    if (*player_score == 3) {
        *game_state = END;
        uint8_t message[BALL_MESSAGE_LENGTH];
        message[0] = 0x1;
        message[1] = 0;
        message[2] = 0;
        message[3] = 0;
        for (int i = 0; i < BALL_MESSAGE_LENGTH; i++) {
            ir_uart_putc(message[i]);
        }

    }
}


void player_lost_round(uint8_t *player_score, slider_t *slider, ball_t *ball, game_state_t *game_state, bool *slider_drawn) {
    (*player_score)++;
    if (*player_score == 3) {
        check_game_over(game_state, player_score);
    } else {
        tinygl_clear();
        init_game(slider, ball);
        *slider_drawn = false;
    }
}

void show_winner(uint8_t player_score) {
    tinygl_clear();
    if (player_score == 3) {
        tinygl_text("LOSER");
    } else {
        tinygl_text("WINNER");
    }
}
