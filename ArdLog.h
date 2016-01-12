#ifndef ARD_LOG_H
#define ARD_LOG_H

#include "Arduino.h"
#include "stdarg.h"

#define PRINT_FREE_RAM true
#define LOG false

/**
 * True will get current time on each call on log(), otherwise we will get one sample for each log_cycle() and
 * in this case all messages within single cycle will have the same timestamp.
 */
#define USE_CURRENT_TIME false

/**
 * 4 serial hardware ports are supported: 1,2,3. If all are set to false we will use default Serial.
 */
#define USE_SERIAL_1 false
#define USE_SERIAL_2 false
#define USE_SERIAL_3 false

const static uint8_t PGBUF_SIZE = 100;
const static uint8_t SBUF_SIZE = 150;

void log_setup();
void log_cycle();

void log_freeRAM(char const *msg);
void log(const __FlashStringHelper *ifsh, ...);

#endif /* ARD_LOG_H */
