#ifndef AU_Log_h
#define AU_Log_h

#include "Arduino.h"
#include "stdarg.h"
#include "Timer.h"
#include "Util.h"

#define PRINT_FREE_RAM true
#define LOG_DISABLED false

const static uint8_t PGBUF_SIZE = 100;
const static uint8_t SBUF_SIZE = 150;

void log_setup();
void log_cycle();
void log_freeRAM(char const *msg);

//void debug(const char *fmt, ...);
void debug(const __FlashStringHelper *ifsh, ...);

#endif /* AU_Log_h */
