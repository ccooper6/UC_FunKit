/** @file   slider.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Slider functions for the game
    Updated 17 October 2024 by Caleb Cooper
*/
#include "slider.h"
#include "navswitch.h"
#include "tinygl.h"

void update_slider(slider_t *slider, bool *slider_drawn)
{
    if (!*slider_drawn) {
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), LED_ON);
        *slider_drawn = true;
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && slider->y2 < LEFT_WALL) {
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), LED_OFF);
        slider->y1++;
        slider->y2++;
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), LED_ON);
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH) && slider->y1 > RIGHT_WALL) {
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), LED_OFF);
        slider->y1--;
        slider->y2--;
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), LED_ON);
    }
}
