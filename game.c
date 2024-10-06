#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "navswitch.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define X_POS 4

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
    ball->y = 3;
    ball->direction = 1;
    ball->angle = 0;

    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(10);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

void update_slider(slider_t *slider) {
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

void update_ball(ball_t *ball, slider_t *slider, uint16_t *ball_tick) {
    (*ball_tick)++;
    if (*ball_tick >= 200) {
        *ball_tick = 0;
        tinygl_draw_point(tinygl_point(ball->x, ball->y), 0);

        if (ball->x == 3 && (ball->y >= slider->y1 && ball->y <= slider->y2)) {
            ball->angle = (ball->y == slider->y1) ? -1 : (ball->y == slider->y2) ? 1 : 0;
            ball->direction = -1;
        } else if (ball->x == 4) {
            return;
        } else if (ball->x != 0) {
            if (ball->y == 0 && ball->angle != 0) {
                ball->angle = 1;
            } else if (ball->y == 6 && ball->angle != 0) {
                ball->angle = -1;
            }
        } else {
            ball->direction = 1;
            ball->angle = 0;
        }

        ball->x += ball->direction;
        ball->y += ball->angle;

        tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);
    }
}

void transmit_ball(ball_t *ball, player_t *player) {
    if (ball->x == 0 && ball->direction == -1) {
        ir_uart_putc(ball->y | (ball->angle << 3));
        *player = PLAYER2;
        tinygl_draw_point(tinygl_point(ball->x, ball->y), 0);
    }
}

void receive_ball(ball_t *ball, player_t *player) {
    if (ir_uart_read_ready_p()) {
        char ch = ir_uart_getc();
        ball->y = ch & 0x7;
        ball->angle = (ch >> 3) & 0x7;
        ball->direction = 1;
        *player = PLAYER1;
        tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);
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

int main(void) {
    slider_t slider;
    ball_t ball;
    game_state_t game_state = START;
    uint16_t ball_tick = 0;

    init_system();
    init_game(&slider, &ball);
    tinygl_text("CHOOSE PLAYER 1");

    player_t player;

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
                update_slider(&slider);
                if (player == PLAYER1) {
                    update_ball(&ball, &slider, &ball_tick);
                    transmit_ball(&ball, &player);
                } else {
                    receive_ball(&ball, &player);
                }
                break;
            case END:
                // Handle end state
                break;
        }
    }
    return 0;
}