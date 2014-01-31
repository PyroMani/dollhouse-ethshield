/**
 * @file tlc59116.c
 *
 * \copyright Copyright 2013 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <efcm@slashdev.nl>
 * @since 0.12.0
 */

#include "tlc59116.h"

// Do we want TLC59116?
#ifdef EXT_TLC59116

// Check if COM_I2C is enabled
#ifndef COM_I2C
#error TLC59116 cannot work without COM_I2C
#endif // COM_I2C

/**
 * Speed for I2C to talk over
 */
const i2c_speed = 350;

void tlc59116_reset(void) {
    // Make sure i2c is initialized
    i2c_init(i2c_speed);
    // Start i2c
    if (i2c_start()) { /* Start failed */ }
    // Send reset command
    else if(i2c_send_address(0xD6)) { /* Send reset command failed */ }
    // Send first reset byte
    else if(i2c_send_byte(0xA5)) { /* Send first reset byte failed */ }
    // Send second reset byte
    else if(i2c_send_byte(0x5A)) { /* Send second reset byte failed */ }
    // Stop i2c
    i2c_stop();
}

void tlc59116_sleep(uint8_t address, uint8_t sleep) {
    // Sequence:
    // Start, select chip, select register, repeated start, select chip,
    // read register (not ack), start, repeated start, select chip,
    // select register, write new byte (sleep or not), stop

    // Make sure i2c is initialized
    i2c_init(i2c_speed);
    // Start i2c
    i2c_start();
    // Select chip (WRITE)
    i2c_send_address(I2C_WRITE(address));
    // Select register
    i2c_send_byte(0x00);
    // Repeated start
    i2c_start();
    // Select chip (READ)
    i2c_send_address(I2C_READ(address));
    // Read byte (do not ack)
    uint8_t old_state;
    i2c_receive_byte(0, &old_state);
    // Repeated start
    i2c_start();
    // Select chip (WRITE)
    i2c_send_address(I2C_WRITE(address));
    // Select register
    i2c_send_byte(0x00);
    // Write byte
    if (sleep) {
        i2c_send_byte(0x10);
    } else {
        i2c_send_byte(old_state & ~(0x10));
    }
    // Stop
    i2c_stop();
    // Wait for 500us to let chip start crystal
    _delay_us(500);
}

#endif // EXT_TLC59116
