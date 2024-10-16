/** @file   game_state.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Functions affecting the state of the game
*/
#include "game_state.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "initialising.h"

/* Define the length of the message sent every time ball information is transmitted */

void check_game_over(game_state_t *game_state, uint8_t *player_score) {
    if (*player_score == LOSE_CONDITION) {
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
    if (*player_score == LOSE_CONDITION) {
        check_game_over(game_state, player_score);
    } else {
        tinygl_clear();
        init_game(slider, ball);
        *slider_drawn = false;
    }
}

void show_winner(uint8_t player_score) {
    tinygl_clear();
    if (player_score == LOSE_CONDITION) {
        tinygl_text("LOSER");
    } else {
        tinygl_text("WINNER");
    }
}
