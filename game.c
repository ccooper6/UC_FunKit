#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define X_POS 4

//static int update_count = 0;
//static int total_updates = 0;

//void showStartingMessage(void) {
//    const char* msg = "Group 306 - PONG!";
//    tinygl_font_set (&font5x7_1);
//    tinygl_text_speed_set (MESSAGE_RATE);
//    tinygl_text(msg);
//    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
//    total_updates = strlen(msg) * 5;
//}

int main (void)
{
    // Initialise the program
    system_init();
    tinygl_init (PACER_RATE);
    pacer_init (PACER_RATE);
    navswitch_init();

    // Initial start state of the slider bar
    uint8_t y1 = 2;
    uint8_t y2 = 4;

    // Draw initial slider bar
    tinygl_draw_line (tinygl_point (X_POS, y1), tinygl_point (X_POS, y2), 1);

    while (1)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) { // South is left when green light is top right of the board
            if (y2 < 6) { // Check slider bar doesn't go out of bounds
                tinygl_draw_line(tinygl_point(X_POS, y1), tinygl_point(X_POS, y2), 0); // Turn off old state
                y1++;
                y2++;
                tinygl_draw_line(tinygl_point(X_POS, y1), tinygl_point(X_POS, y2), 1); // Turn on new state
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (y1 > 0) { // Check slider bar doesn't go out of bounds
                tinygl_draw_line(tinygl_point(X_POS, y1), tinygl_point(X_POS, y2), 0); // Turn off old state
                y1--;
                y2--;
                tinygl_draw_line(tinygl_point(X_POS, y1), tinygl_point(X_POS, y2), 1); // Turn on new state
            }
        }

    }
    return 0;
}
