/** @file   ball.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Ball functions for the game
*/
#include "ball.h"
#include "tinygl.h"
#include "transmission.h"

void update_ball(ball_t *ball, player_t *player, slider_t *slider, uint16_t *ball_tick, uint8_t *player_score, game_state_t *game_state, bool *slider_drawn) {
    tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);

    (*ball_tick)++;
    if (*ball_tick < 200) {
        return;
    }

    *ball_tick = 0;
    tinygl_draw_point(tinygl_point(ball->x, ball->y), 0);

    if (ball->x == 3 && ball->y >= slider->y1 && ball->y <= slider->y2) { // Ball hits slider
        if (ball->y == 6) { // Handle corner collisions
            ball->angle = -1;
        } else if (ball->y == 0) {
            ball->angle = 1;
        } else if (ball->y == slider->y1) { // Handle slider collisions
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
