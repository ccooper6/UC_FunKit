/** @file   transmission.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Transmission functions for the game
*/
#include "transmission.h"
#include <stdint.h>
#include "tinygl.h"
#include "ir_uart.h"
#include "player.h"
#include "ball.h"
#include "initialising.h"


void transmit_ball(ball_t *ball, player_t *player, uint8_t *player_score)
{
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

void receive_transmission(ball_t *ball, player_t *player, uint8_t *player_score, game_state_t *game_state)
{
    if (ir_uart_read_ready_p()) {
        uint8_t message[BALL_MESSAGE_LENGTH];

        for (int i = 0; i < BALL_MESSAGE_LENGTH; i++) {
            message[i] = ir_uart_getc();
        }
        if (message[0] == 0x0) {
            // Flip the y position to mirror it for the other board
            ball->y = TINYGL_HEIGHT - 1 - message[1];  // Assuming TINYGL_HEIGHT is the max height (e.g., 7)

            ball->direction = message[2] & 0x1;

            // Flip the angle (this depends on your angle convention)
            ball->angle = (message[2] >> 1) & 0x3;  // Extract original angle
            ball->angle = (ball->angle == 1) ? -1 : (ball->angle == -1) ? 1 : ball->angle;  // Mirror the angle

            *player_score = message[3];
            ball->direction = FORWARD;
            *player = PLAYER1;
            tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);
        } else {
            *game_state = END;
        }

    }
}

void send_start_notification(void)
{
    ir_uart_putc('S');
}

void receive_start_notification(game_state_t *game_state, player_t *player)
{
    if (ir_uart_read_ready_p()) {
        char ch = ir_uart_getc();
        if (ch == 'S') {
            *game_state = PLAY;
            *player = PLAYER2;
            tinygl_clear();
        }
    }
}
