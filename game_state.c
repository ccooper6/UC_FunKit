/** @file   game_state.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Functions affecting the state of the game
    Updated 18 October 2024 by Caleb Cooper
*/
#include "game_state.h"
#include "tinygl.h"
#include "initialising.h"
#include "transmission.h"

void check_game_over(game_state_t *game_state, uint8_t *player_score)
{
    if (*player_score == LOSE_CONDITION) {
        *game_state = END;
        transmit_game_over();
    }
}


void player_lost_round(uint8_t *player_score, slider_t *slider, ball_t *ball, game_state_t *game_state, bool *slider_drawn)
{
    (*player_score)++;
    if (*player_score == LOSE_CONDITION) {
        check_game_over(game_state, player_score);
    } else {
        tinygl_clear();
        init_game(slider, ball);
        *slider_drawn = false;
    }
}

void show_winner(uint8_t player_score)
{
    tinygl_clear();
    if (player_score == LOSE_CONDITION) {
        tinygl_draw_message("LOSER", tinygl_point(0,6), 1);
    } else {
        tinygl_draw_message("WINNER", tinygl_point(0,6), 1);
    }
}
