#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "ir_uart.h"

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
    ir_uart_init ();


    // Initial start state of the slider bar
    uint8_t y1 = 2;
    uint8_t y2 = 4;

    // Initial start state of the ball
    uint8_t ball_x1 = 0;
    uint8_t ball_y1 = 3;
    uint8_t ball_direction = 1;
    uint8_t angle_y = 0;

    // Draw initial slider bar
    tinygl_draw_line (tinygl_point (X_POS, y1), tinygl_point (X_POS, y2), 1);

    tinygl_draw_point(tinygl_point (ball_x1, ball_y1), 1);

    uint16_t ball_tick = 0;

    while (1)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        ball_tick++;


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
        if (ball_tick >= 200) {
            ball_tick = 0;
            tinygl_draw_point(tinygl_point(ball_x1, ball_y1), 0);

            if (ball_x1 == 3 && (ball_y1 >= y1 && ball_y1 <= y2)) {
                if (ball_y1 == y1) {
                    angle_y = -1;
                } else if (ball_y1 == y2) {
                    angle_y = 1;
                }
                ball_direction = -1;
            } else if (ball_x1 == 4) {
                return;
            } else if (ball_x1 != 0) {
                if (ball_y1 == 0 && angle_y != 0) {
                    angle_y = 1;
                } else if (ball_y1 == 6 && angle_y != 0) {
                    angle_y = -1;
                }
            } else {
                ball_direction = 1;
                angle_y = 0;  
            }

            ball_x1 += ball_direction;
            ball_y1 += angle_y;

            tinygl_draw_point(tinygl_point(ball_x1, ball_y1), 1);
        }

        // ir transmit
		if (ball_x1 == 0) {
        	ir_uart_putc(ball_y1);
                //un draw the ball
            tinygl_draw_point(tinygl_point(ball_x1, ball_y1), 0);
		}

        // if revieve a message, draw the ball according to the message
        if (ir_uart_read_ready_p()) {
            char ch;
            ch = ir_uart_getc ();
            ball_x1 = 0;
            ball_y1 = ch;
            ball_direction = 1;
            angle_y = 0;

            tinygl_draw_point(tinygl_point(ball_x1, ball_y1), 1);

        }



    }
    return 0;
}
