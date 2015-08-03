#ifndef Log_H_
#define Log_H_

#include "Arduino.h"
#include "stdarg.h"
#include "Timer.h"
#include "Util.h"

#define PRINT_FREE_RAM true

#define PGBUF_SIZE 50
#define SBUF_SIZE 120

void log_setup();
void log_cycle();
void log_freeRAM(char const *msg);

//void debug(const char *fmt, ...);
void debug(const __FlashStringHelper *ifsh, ...);

#endif /* Log_H_ */
