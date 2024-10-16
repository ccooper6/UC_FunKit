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

int main(void) {
    slider_t slider;
    ball_t ball;
    player_t player;
    game_state_t game_state = START;
    uint16_t ball_tick = 0;

    init_system();

    init_game(&slider, &ball);
    tinygl_text("CHOOSE PLAYER 1");

    uint8_t player_score = 0;
    bool end_text_set = false;
    bool slider_drawn = false;
    uint8_t count = 0;
    uint32_t game_over_ticks = 0;

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
                if (player_score >= 3) {
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
                    game_over_ticks = 0;  // Reset here
                }

                if (game_over_ticks >= 5500) {

                    game_state = START;
                    player_score = 0;
                    end_text_set = false;
                    slider_drawn = false;
                    tinygl_clear();
                    tinygl_text("PLAY AGAIN");
                    game_over_ticks = 0;  // Reset here
                    ball_tick = 0;
                    init_game(&slider, &ball);
                }
                game_over_ticks++;
                break;
        }
    }
    return 0;
}