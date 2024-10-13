#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "timer0.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define X_POS 4
#define BALL_MESSAGE_LENGTH 4

typedef struct {
    uint8_t y1;
    uint8_t y2;
} slider_t;

typedef struct {
    uint8_t x;
    uint8_t y;
    int8_t direction;
    int8_t angle;
} ball_t;

typedef enum {
    START,
    PLAY,
    END
} game_state_t;

typedef enum {
    PLAYER1,
    PLAYER2
} player_t;

void init_system(void) {
    system_init();
    tinygl_init(PACER_RATE);
    pacer_init(PACER_RATE);
    navswitch_init();
    ir_uart_init();
}

void init_game(slider_t *slider, ball_t *ball) {
    slider->y1 = 2;
    slider->y2 = 4;

    ball->x = 0;
    ball->y = 3; // Starts the ball at a random position
    ball->direction = 1;
    ball->angle = 0;

    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(10);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

void update_slider(slider_t *slider, bool *slider_drawn) {
    if (!*slider_drawn) {
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), 1);
        *slider_drawn = true;
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && slider->y2 < 6) {
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), 0);
        slider->y1++;
        slider->y2++;
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), 1);
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH) && slider->y1 > 0) {
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), 0);
        slider->y1--;
        slider->y2--;
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), 1);
    }
}

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

void transmit_ball(ball_t *ball, player_t *player, uint8_t *player_score);

void update_ball(ball_t *ball, player_t *player, slider_t *slider, uint16_t *ball_tick, uint8_t *player_score, game_state_t *game_state, bool *slider_drawn) {
    (*ball_tick)++;
    if (*ball_tick < 200) {
        return;
    }
    *ball_tick = 0;
    tinygl_draw_point(tinygl_point(ball->x, ball->y), 0);

    if (ball->x == 3 && ball->y >= slider->y1 && ball->y <= slider->y2) { // Ball hits slider
        if (ball->y == slider->y1) { // Handle slider collisions
            ball->angle = -1;
        } else if (ball->y == slider->y2) {
            ball->angle = 1;
        } else {
            ball->angle = 0;
        }
        ball->direction = -1;
    } else if (ball->x == 0 && ball->direction == -1) { // Check if ball reaches player end
        transmit_ball(ball, player, player_score);
        return;
    } else if (ball->x == 4) {
        player_lost_round(player_score, slider, ball, game_state, slider_drawn);
        return;
    } else if ((ball->y == 0 && ball->angle != 0) || (ball->y == 6 && ball->angle != 0)) { // Check if ball hits wall
        if (ball->y == 0) { // Wall collisions change direction
            ball->angle = 1;
        } else if (ball->y == 6) {
            ball->angle = -1;
        }
    }

    ball->x += ball->direction; // Move ball
    ball->y += ball->angle;

    tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);
}

void transmit_ball(ball_t *ball, player_t *player, uint8_t *player_score) {
    uint8_t message[BALL_MESSAGE_LENGTH];

    message[0] = 0x0;
    message[1] = ball->y;
    message[2] = (ball->direction & 0x1) | ((ball->angle & 0x3) << 1);
    message[3] = *player_score;

    for (int i = 0; i < BALL_MESSAGE_LENGTH; i++) {
        ir_uart_putc(message[i]);
    }

    *player = PLAYER2;
    tinygl_draw_point(tinygl_point(ball->x, ball->y), 0);
}

void receive_transmission(ball_t *ball, player_t *player, uint8_t *player_score, game_state_t *game_state) {
    if (ir_uart_read_ready_p()) {
        uint8_t message[BALL_MESSAGE_LENGTH];

        for (int i = 0; i < BALL_MESSAGE_LENGTH; i++) {
            message[i] = ir_uart_getc();
        }
        if (message[0] == 0x0) {
        ball->y = message[1];
        ball->direction = message[2] & 0x1;
        ball->angle = (message[2] >> 1) & 0x3;
        *player_score = message[3];
        ball->direction = 1;
        *player = PLAYER1;
        tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);
        } else {
            *game_state = END;
        }

    }
}

void send_start_notification(void) {
    ir_uart_putc('S');
}

void recieve_start_notification(game_state_t *game_state, player_t *player) {
    if (ir_uart_read_ready_p()) {
        char ch = ir_uart_getc();
        if (ch == 'S') {
            *game_state = PLAY;
            *player = PLAYER2;
            tinygl_clear();
        }
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

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        switch (game_state) {
            case START:
                recieve_start_notification(&game_state, &player);
                if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                    send_start_notification();
                    game_state = PLAY;
                    player = PLAYER1;
                    tinygl_clear();
                }
                break;
            case PLAY:
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
            }

                break;
        }
    }
    return 0;
}