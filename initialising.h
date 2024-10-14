//
// Created by Caleb Cooper on 14/10/2024.
//

#ifndef INITIALISING_H
#define INITIALISING_H

#include "slider.h"
#include "ball.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

void init_system(void);
void init_game(slider_t *slider, ball_t *ball);

#endif //INITIALISING_H
