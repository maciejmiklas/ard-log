#ifndef ARD_LOG_H
#define ARD_LOG_H

#include "Arduino.h"
#include "stdarg.h"
#include "ArdTimer.h"
#include "ArdUtil.h"

#define PRINT_FREE_RAM true
#define LOG_DISABLED true

const static uint8_t PGBUF_SIZE = 100;
const static uint8_t SBUF_SIZE = 150;

void log_setup();
void log_cycle();
void log_freeRAM(char const *msg);

void log(const __FlashStringHelper *ifsh, ...);

#endif /* ARD_LOG_H */
