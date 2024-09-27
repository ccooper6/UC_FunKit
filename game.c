#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

void showStartingMessage(void) {
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text("Group 306 - PONG!");
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

int main (void)
{
    system_init();
    tinygl_init (PACER_RATE);
    pacer_init (PACER_RATE);

    showStartingMessage();

    while (1)
    {
        pacer_wait();

        tinygl_update();

    }
    return 0;
}
