/**
 * @file ledcontroller.c
 *
 * \copyright Copyright 2013 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <efcm@slashdev.nl>
 * @since 0.12.0
 */

#include "ledcontroller.h"

// Check if UDP is enabled
#ifndef NET_UDP
#error Led controller cannot work without NET_UDP
#endif // NET_UDP

const uint8_t address = 0b11000110;
volatile uint8_t selected_room;

void lc_init(void) {
    selected_room = 0xFF;
    tlc59116_sleep(address, 0);
    uint8_t i = 0;
    while (i < 16) {
        tlc59116_set_led_mode(address, i, TLC59116_LED_PWM);
        tlc59116_set_brightness(address, i, 0xFF);
        i++;
    }
}
