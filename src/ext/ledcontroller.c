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

#define LC_ACT_REQUEST_BRIGHTNESS_VALUES 0x10
#define LC_ACT_REPLY_BRIGHTNESS_VALUES   0x11
#define LC_ACT_ROOM_SELECT               0x20
const uint8_t address = 0b11000110;
uint8_t brightness[16];
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
void reply_brightness_values(void);
void select_room(uint8_t room);

void lc_handle_packet(uint8_t *data, uint16_t length) {
    switch (data[0]) {
        case LC_ACT_REQUEST_BRIGHTNESS_VALUES:
            // Send brightness values
            reply_brightness_values();
            break;

        case LC_ACT_ROOM_SELECT:
            // Select a room
            select_room(data[1]);
            break;

        default:
            break;
    }
}

void reply_brightness_values(void) {
    // Make reply from received packet
    uint8_t *data = udp_prepare_reply();
    // Set action byte
    data[0] = LC_ACT_REPLY_BRIGHTNESS_VALUES;
    // Put all brightness values in
    uint8_t i = 0;
    while (i < 16) {
        data[1+i] = brightness[i];
        i++;
    }
    // Send packet
    // Length: 17 (action + 16x brightness)
    udp_send(17);
}

void select_room(uint8_t room) {
    if (room >= 16) {
        room = 0xFF;
    }
    selected_room = room;
}
