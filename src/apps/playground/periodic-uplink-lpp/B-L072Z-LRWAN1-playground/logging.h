/**
 * @file logging.h
 * @author Dietrich Lucas (ld.adecy@gmail.com)
 * @brief Logging macros
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 * Notes:
 *   - after including this header, define LOG_LEVEL to one of this file constant : LOG_LEVEL_*
 * Example
 * 	#include "logging.h"
 * 	#define LOG_LEVEL LOG_LEVEL_WRN
 *
 *   - use with miniterm : python3 -m serial.tools.miniterm --raw /dev/ttyACM0 921600
 */

#ifndef _APP_LOGGING_H
#define _APP_LOGGING_H

#include <stdio.h>
#include <stdarg.h>

// for colors : https://xdevs.com/guide/color_serial/
#define CONFIG_LOG_COLOR_ENABLED 1

#define LOG_COLOR_RESET_ALL "\033[m"

#define LOG_COLOR_BLACK_ON_WHITE "\033[0;30;41m"
#define LOG_COLOR_RED "\033[0;31m"
#define LOG_COLOR_GREEN "\033[0;32m"
#define LOG_COLOR_YELLOW "\033[0;33m"
#define LOG_COLOR_BLUE "\033[0;34m"
#define LOG_COLOR_MAGENTA "\033[0;35m"
#define LOG_COLOR_CYAN "\033[0;36m"
#define LOG_COLOR_WHITE "\033[0;37m"
#define LOG_COLOR_DEFAULT "\033[0;39m"

#define LOG_COLOR_GRAY_ON_WHITE "\033[1;30m"
#define LOG_COLOR_BRIGHT_RED "\033[1;31m"
#define LOG_COLOR_BRIGHT_GREEN "\033[1;32m"
#define LOG_COLOR_BRIGHT_YELLOW "\033[1;33m"
#define LOG_COLOR_BRIGHT_BLUE "\033[1;34m"
#define LOG_COLOR_BRIGHT_MAGENTA "\033[1;35m"
#define LOG_COLOR_BRIGHT_CYAN "\033[1;36m"
#define LOG_COLOR_BRIGHT_WHITE "\033[1;37m"
#define LOG_COLOR_BRIGHT_DEFAULT "\033[0;39m"

#define LOG_COLOR_BG_BLACK "\033[0;40m"
#define LOG_COLOR_BG_RED "\033[0;41m"
#define LOG_COLOR_BG_GREEN "\033[0;42m"
#define LOG_COLOR_BG_YELLOW "\033[0;43m"
#define LOG_COLOR_BG_BLUE "\033[0;44m"
#define LOG_COLOR_BG_MAGENTA "\033[0;45m"
#define LOG_COLOR_BG_CYAN "\033[0;46m"
#define LOG_COLOR_BG_WHITE "\033[0;47m"
#define LOG_COLOR_BG_RESET "\033[0;49m"

#if CONFIG_LOG_COLOR_ENABLED
#   define LOG_COLOR_WRN LOG_COLOR_BRIGHT_YELLOW
#   define LOG_COLOR_ERR LOG_COLOR_BRIGHT_RED
#   define LOG_COLOR_RESET LOG_COLOR_RESET_ALL
#else
#   define LOG_COLOR_WRN ""
#   define LOG_COLOR_ERR ""
#   define LOG_COLOR_RESET ""
#endif

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERR 1
#define LOG_LEVEL_WRN 2
#define LOG_LEVEL_INF 3
#define LOG_LEVEL_DBG 4
#define LOG_LEVEL_VERBOSE 5
#define LOG_LEVEL_ALL LOG_LEVEL_VERBOSE

#define _log_printf printf

#define LOG(level, fmt, ...) \
    do { \
        if ((level) <= (LOG_LEVEL)) { \
            _log_printf(fmt, ## __VA_ARGS__); \
        } \
    } while (0)

#define LOG_VRB_RAW(fmt, ...) LOG(5, fmt, ## __VA_ARGS__)
#define LOG_DBG_RAW(fmt, ...) LOG(4, fmt, ## __VA_ARGS__)
#define LOG_INF_RAW(fmt, ...) LOG(3, fmt, ## __VA_ARGS__)
#define LOG_WRN_RAW(fmt, ...) LOG(2, LOG_COLOR_WRN fmt LOG_COLOR_RESET, ## __VA_ARGS__)
#define LOG_ERR_RAW(fmt, ...) LOG(1, LOG_COLOR_ERR fmt LOG_COLOR_RESET, ## __VA_ARGS__)

#define LOG_VRB(fmt, ...) LOG(5, fmt "\n", ## __VA_ARGS__)
#define LOG_DBG(fmt, ...) LOG(4, fmt "\n", ## __VA_ARGS__)
#define LOG_INF(fmt, ...) LOG(3, fmt "\n", ## __VA_ARGS__)
#define LOG_WRN(fmt, ...) LOG(2, LOG_COLOR_WRN fmt LOG_COLOR_RESET "\n", ## __VA_ARGS__)
#define LOG_ERR(fmt, ...) LOG(1, LOG_COLOR_ERR fmt LOG_COLOR_RESET "\n", ## __VA_ARGS__)


#define LOG_HEXDUMP(level, data, len) \
   do { \
	if ((level) <= (LOG_LEVEL)) { \
		for(unsigned int i = 0; i < (len); i++) { \
			_log_printf("%02x ", data[i]); \
		} \
		_log_printf("\n"); \
	} \
   } while (0)

#define LOG_HEXDUMP_WITHSTART(level, data, len, _start, _end) \
   do { \
	if ((level) <= (LOG_LEVEL)) { \
		_log_printf(_start); \
		for(unsigned int i = 0; i < (len); i++) { \
			_log_printf("%02x ", data[i]); \
		} \
		_log_printf(_end); \
	} \
   } while (0)

#if CONFIG_LOG_COLOR_ENABLED



#	define LOG_HEXDUMP_VRB(data, len) LOG_HEXDUMP(5, data, len)
#	define LOG_HEXDUMP_DBG(data, len) LOG_HEXDUMP(4, data, len)
#	define LOG_HEXDUMP_INF(data, len) LOG_HEXDUMP(3, data, len)
#	define LOG_HEXDUMP_WRN(data, len) LOG_HEXDUMP_WITHSTART(2, data, len, LOG_COLOR_WRN, LOG_COLOR_RESET "\n")
#	define LOG_HEXDUMP_ERR(data, len) LOG_HEXDUMP_WITHSTART(1, data, len, LOG_COLOR_ERR, LOG_COLOR_RESET "\n")

#else

#	define LOG_HEXDUMP_VRB(data, len) LOG_HEXDUMP(5, data, len)
#	define LOG_HEXDUMP_DBG(data, len) LOG_HEXDUMP(4, data, len)
#	define LOG_HEXDUMP_INF(data, len) LOG_HEXDUMP(3, data, len)
#	define LOG_HEXDUMP_WRN(data, len) LOG_HEXDUMP(2, data, len)
#	define LOG_HEXDUMP_ERR(data, len) LOG_HEXDUMP(1, data, len)

#endif

#endif /* _APP_LOGGING_H */