/** @file   slider.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Slider functions for the game

    @defgroup
*/
#ifndef SLIDER_H
#define SLIDER_H

#include <stdint.h>
#include <stdbool.h>

/* The x position of the slider, this does not change */
#define X_POS 4

/* Defines the two maximum y coordinates of the slider */
typedef struct {
    uint8_t y1;
    uint8_t y2;
} slider_t;

/**
* Updates the slider position according to navswitch events
* @param slider pointer to the slider to update
* @param slider_drawn pointer to whether the slider has been drawn yet or not
*/
void update_slider(slider_t *slider, bool *slider_drawn);

#endif
