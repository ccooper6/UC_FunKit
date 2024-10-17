/** @file   initialising.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Initialising functions for the game
*/
#include "initialising.h"

#include <stdlib.h>
#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "../fonts/font3x5_1.h"

void init_system(void)
{
    system_init();
    tinygl_init(PACER_RATE);
    pacer_init(PACER_RATE);
    navswitch_init();
    ir_uart_init();
}

void init_game(slider_t *slider, ball_t *ball)
{
    slider->y1 = 2;
    slider->y2 = 4;

    ball->x = 0;
    ball->y = rand() % 7; // Starts the ball at a random position
    ball->direction = 1;
    ball->angle = rand() % 3 - 1; // Starts the ball at a random angle

    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}