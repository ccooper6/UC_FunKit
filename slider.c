/** @file   slider.c
    @author Caleb Cooper (cco139), Joshua Ching (jch438)
    @date   14 October 2024
    @brief  Slider functions for the game
*/
#include "slider.h"
#include "navswitch.h"
#include "tinygl.h"

void update_slider(slider_t *slider, bool *slider_drawn)
{
    if (!*slider_drawn) {
        tinygl_draw_line(tinygl_point(X_POS, slider->y1), tinygl_point(X_POS, slider->y2), 1);
        *slider_drawn = true;
    }

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
