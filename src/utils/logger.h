/**
 * @file logger.h
 * @brief Log over usart functionality
 *
 * \copyright Copyright 2013 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <efcm@slashdev.nl>
 * @since 0.1.0
 */

#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include "../config.h"

// Do we want logging?
#if defined(UTILS_LOGGER_INFO) || defined(UTILS_LOGGER_DEBUG)

// Make sure USART is enabled
#ifndef COM_USART
#warning Using UTILS_DEBUG while COM_USART not enabled, forcing COM_USART
#define COM_USART
#endif // COM_USART

#include <inttypes.h>
#include <util/delay.h>
#include "../com/usart.h"

extern void logger_init(void);
extern void logger_string(char *string);
extern void logger_string_p(const char *pstring);
extern void logger_number(uint16_t value);
extern void logger_number_as_hex(uint16_t value);
extern void logger_array(uint8_t *data, uint16_t length, char glue);
extern void logger_ip(uint8_t *addr);
extern void logger_mac(uint8_t *addr);
extern const char logger_newline[] PROGMEM;
extern const char logger_dot[] PROGMEM;

#if defined(UTILS_LOGGER_DEBUG)

// Info level enabled
#define info_string(s) logger_string(s)
#define info_string_p(s) logger_string_p(s)
#define info_number(x) logger_number(x)
#define info_number_as_hex(x) logger_number_as_hex(x)
#define info_array(x, l) logger_array(x, l)
#define info_ip(ip) logger_ip(ip)
#define info_mac(mac) logger_mac(mac)
#define info_newline() logger_string_p(logger_newline)
// Debug level disabled
#define debug_string(s) logger_string(s)
#define debug_string_p(s) logger_string_p(s)
#define debug_number(x) logger_number(x)
#define debug_number_as_hex(x) logger_number_as_hex(x)
#define debug_array(x, l) logger_array(x, l)
#define debug_ip(ip) logger_ip(ip)
#define debug_mac(mac) logger_mac(mac)
#define debug_newline() logger_string_p(logger_newline)
#define debug_dot() logger_string_p(logger_dot)

#elif defined(UTILS_LOGGER_INFO)

// Info level enabled
#define info_string(s) logger_string(s)
#define info_string_p(s) logger_string_p(s)
#define info_number(x) logger_number(x)
#define info_number_as_hex(x) logger_number_as_hex(x)
#define info_array(x, l) logger_array(x, l)
#define info_ip(ip) logger_ip(ip)
#define info_mac(mac) logger_mac(mac)
#define info_newline() logger_string_p(logger_newline)
// Debug level disabled
#define debug_string(...) do {} while (0)
#define debug_string_p(...) do {} while (0)
#define debug_number(...) do {} while (0)
#define debug_number_as_hex(...) do {} while (0)
#define debug_array(...) do {} while (0)
#define debug_ip(ip) do {} while (0)
#define debug_mac(mac) do {} while (0)
#define debug_newline() do {} while (0)
#define debug_dot() do {} while(0)

#endif // UTILS_LOGGER_INFO


#else // UTILS_LOGGER_INFO || UTILS_LOGGER_DEBUG

// No logger wanted, create placeholders
#define logger_init(...) do {} while (0)
// Info level disabled
#define info_string(...) do {} while (0)
#define info_string_p(...) do {} while (0)
#define info_number(...) do {} while (0)
#define info_number_as_hex(...) do {} while (0)
#define info_array(...) do {} while (0)
#define info_ip(ip) do {} while (0)
#define info_mac(mac) do {} while (0)
#define info_newline() do {} while (0)
// Debug level disabled
#define debug_string(...) do {} while (0)
#define debug_string_p(...) do {} while (0)
#define debug_number(...) do {} while (0)
#define debug_number_as_hex(...) do {} while (0)
#define debug_array(...) do {} while (0)
#define debug_ip(ip) do {} while (0)
#define debug_mac(mac) do {} while (0)
#define debug_newline() do {} while(0)
#define debug_dot() do {} while (0)

#endif // UTILS_LOGGER_INFO || UTILS_LOGGER_DEBUG
#endif // UTILS_LOGGER_H
