/**
 * @file i2c.c
 *
 * \copyright Copyright 2013 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <efcm@slashdev.nl>
 * @since 0.11.0
 */

#include "i2c.h"

// Do we want I2C?
#ifdef COM_I2C

void i2c_init(uint16_t bitrateKHz) {
    
    // Disable power reduction mode
    PRR &= ~(1<<PRTWI);
    
    uint8_t prescaler;
    
    // Clear prescaler bits
    TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
    
    // Decide which prescaler to use
    if (bitrateKHz < 3) {
        prescaler = 64;
        TWSR = (1 << TWPS1) | (1 << TWPS0);
    } else if (bitrateKHz < 10) {
        prescaler = 16;
        TWSR |= (1 << TWPS1);
    } else if (bitrateKHz < 38) {
        prescaler = 4;
        TWSR |= (1 << TWPS0);
    } else {
        prescaler = 1;
    }
    
    // Calculate bitrate divider
    // SCL = F_CPU / (16 + 2(div) * prescaler)
    // div = (F_CPU / (2001*SCL*prescaler))
    TWBR = (F_CPU / 2001 / bitrateKHz / prescaler) - 7;
    
    // Enable TWI
    TWCR |= (1 << TWEN);
}

void i2c_disable(void) {
    TWCR &= ~(1 << TWEN);
}

#if defined(UTILS_LOGGER_INFO) || defined(UTILS_LOGGER_DEBUG)
void i2c_error(const char *msg) {
    info_string_p(PSTR("I2C error: "));
    info_string_p(msg);
    info_newline();
#ifdef UTILS_LOGGER_DEBUG
    debug_string_p(PSTR("TWSR: 0x"));
    debug_number_as_hex(TWSR);
    debug_newline();
#endif // UTILS_LOGGER_DEBUG
}
#else // UTILS_LOGGER_INFO || UTILS_LOGGER_DEBUG
#define i2c_error(...) do {} while (0)
#endif // UTILS_LOGGER_INFO || UTILS_LOGGER_DEBUG

#endif // COM_I2C
