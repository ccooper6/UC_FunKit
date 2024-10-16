#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ball.h"
#include "player.h"
#include "game_state.h"
#include "slider.h"
#include "transmission.h"
#include "initialising.h"

#include <stdlib.h>

void reset_variables(slider_t* slider, ball_t *ball, player_t *player, game_state_t *game_state, uint16_t *ball_tick, uint8_t *player_score, bool *end_text_set, bool *slider_drawn, uint8_t *count, uint32_t *game_over_ticks)
{
    slider->y1 = 1;
    slider->y2 = 3;
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

    tinygl_text("CHOOSE PLAYER 1");



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

                if (game_over_ticks >= 4500) {

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