/**
 * @file ledcontroller.h
 * @brief Handles network calls and sets led brightness
 *
 * \copyright Copyright 2013 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <efcm@slashdev.nl>
 * @since 0.12.0
 */

#ifndef EXT_LEDCONTROLLER_H
#define EXT_LEDCONTROLLER_H

#include "../config.h"
#include <inttypes.h>
#include "../net/udp.h"
#include "tlc59116.h"

extern void lc_init(void);

extern void lc_handle_packet(uint8_t *data, uint16_t length);
#endif // EXT_LEDCONTROLLER_H
