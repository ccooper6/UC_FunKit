//
// Created by Caleb Cooper on 14/10/2024.
//

#include "initialising.h"

#include <stdlib.h>

#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "../fonts/font3x5_1.h"

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
    ball->y = rand() % 7; // Starts the ball at a random position
    ball->direction = 1;
    ball->angle = 0;

    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}