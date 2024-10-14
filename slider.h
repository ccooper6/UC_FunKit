//
// Created by Caleb Cooper on 14/10/2024.
//

#ifndef SLIDER_H
#define SLIDER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t y1;
    uint8_t y2;
} slider_t;

void update_slider(slider_t *slider, bool *slider_drawn);

#endif //SLIDER_H
