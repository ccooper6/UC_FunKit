/** @file   game.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Main functions for the pong game
    Updated 18 October 2024 by Caleb Cooper
*/
#include <stdlib.h>
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ball.h"
#include "player.h"
#include "game_state.h"
#include "slider.h"
#include "transmission.h"
#include "initialising.h"

/* The amount of ticks required before the game restarts */
#define MIN_FINISHED_TICKS 4500

/* The minimum y value initially of the slider */
#define MIN_SLIDER_Y 1

/* The maximum y value initially of the slider */
#define MAX_SLIDER_Y 3

/**
 * Resets all variables to default values
 * @param slider pointer to the slider to reset
 * @param ball pointer to the ball to reset
 * @param player pointer to the player to reset
 * @param game_state pointer to the game state to reset
 * @param ball_tick pointer to the ball tick to reset
 * @param player_score pointer to the player score to reset
 * @param end_text_set pointer to the end text set to reset
 * @param slider_drawn pointer to the slider_drawn boolean value to reset
 * @param count pointer to the count to reset
 * @param game_over_ticks pointer to the ticks to reset
 */
void reset_variables(slider_t* slider, ball_t *ball, player_t *player, game_state_t *game_state, uint16_t *ball_tick, uint8_t *player_score, bool *end_text_set, bool *slider_drawn, uint8_t *count, uint32_t *game_over_ticks)
{
    slider->y1 = MIN_SLIDER_Y;
    slider->y2 = MAX_SLIDER_Y;
    ball->x = 0;
    ball->y = 0;
    ball->angle = 0;
    ball->direction = 0;
    *player = PLAYER1;
    *game_state = START;
    *ball_tick = 0;
    *player_score = 0;
    *end_text_set = false;
    *slider_drawn = false;
    *count = 0;
    *game_over_ticks = 0;
}

int main(void)
{
    slider_t slider;
    ball_t ball;
    player_t player;
    game_state_t game_state;
    uint16_t ball_tick;
    uint8_t player_score;
    bool end_text_set;
    bool slider_drawn;
    uint8_t count;
    uint32_t game_over_ticks;

    reset_variables(&slider, &ball, &player, &game_state, &ball_tick, &player_score, &end_text_set, &slider_drawn, &count, &game_over_ticks);

    init_system();
    init_game(&slider, &ball);

    tinygl_text("CLICK TO START");

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        count++;

        switch (game_state) {
            case START:
                srand(count);
                receive_start_notification(&game_state, &player);
                if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                    send_start_notification();
                    game_state = PLAY;
                    player = PLAYER1;
                    tinygl_clear();
                }
                break;
            case PLAY:
                srand(count);
                if (player_score >= LOSE_CONDITION) {
                    check_game_over(&game_state, &player_score);
                }
                update_slider(&slider, &slider_drawn);
                if (player == PLAYER1) {
                    update_ball(&ball, &player, &slider, &ball_tick, &player_score, &game_state, &slider_drawn);
                } else {
                    receive_transmission(&ball, &player, &player_score, &game_state);
                }

                break;
            case END:
                if (!end_text_set) {
                    show_winner(player_score);
                    end_text_set = true;
                    game_over_ticks = 0;
                }

                if (game_over_ticks >= MIN_FINISHED_TICKS) {

                    reset_variables(&slider, &ball, &player, &game_state, &ball_tick, &player_score, &end_text_set, &slider_drawn, &count, &game_over_ticks);

                    init_system();
                    init_game(&slider, &ball);

                    tinygl_clear();
                    tinygl_text("PLAY AGAIN");
                }
                game_over_ticks++;
                break;
        }
    }
    return 0;
}