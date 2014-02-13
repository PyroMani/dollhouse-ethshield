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
