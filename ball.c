/** @file   ball.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Ball functions for the game
*/
#include "ball.h"

#include <stdlib.h>

#include "tinygl.h"
#include "transmission.h"

bool ball_hits_slider(ball_t *ball, slider_t *slider)
{
    return ball->x == 3 && ball->y >= slider->y1 && ball->y <= slider->y2;
}

void change_ball_trajectory(ball_t *ball, slider_t *slider)
{
    if (ball->y == 6) { // Handle corner collisions
        ball->angle = -1;
    } else if (ball->y == 0) {
        ball->angle = 1;
    } else if (ball->y == slider->y1) { // Handle slider collisions
        ball->angle = -1;
    } else if (ball->y == slider->y2) {
        ball->angle = 1;
    } else {
        ball->angle = rand() % 3 - 1; // Randomise angle
    }
    ball->direction = -1;
}

bool ball_hits_wall(ball_t *ball)
{
    return (ball->y == 0 && ball->angle != 0) || (ball->y == 6 && ball->angle != 0);
}

bool ball_misses_slider(ball_t *ball)
{
    return ball->x == 0 && ball->direction == -1;
}

void update_ball(ball_t *ball, player_t *player, slider_t *slider, uint16_t *ball_tick, uint8_t *player_score, game_state_t *game_state, bool *slider_drawn)
{
    tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);

    (*ball_tick)++;
    if (*ball_tick < 200) {
        return;
    }

    *ball_tick = 0;
    tinygl_draw_point(tinygl_point(ball->x, ball->y), 0);

    if (ball_hits_slider(ball, slider)) { // Ball hits slider
        change_ball_trajectory(ball, slider);
    } else if (ball_misses_slider(ball)) { // Check if ball reaches player end
        transmit_ball(ball, player, player_score);
        return;
    } else if (ball->x == 4) { // Ball has reached end of screen
        player_lost_round(player_score, slider, ball, game_state, slider_drawn);
        return;
    } else if (ball_hits_wall(ball)) {
        if (ball->y == 0) {
            ball->angle = 1; // If left wall, send right
        } else if (ball->y == 6) {
            ball->angle = -1; // If right wall, send left
        }
    }

    ball->x += ball->direction; // Move ball
    ball->y += ball->angle;

    tinygl_draw_point(tinygl_point(ball->x, ball->y), 1);
}
