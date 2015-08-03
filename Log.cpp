#include "Log.h"

static Time lt;
static uint16_t lastRam = 0;
static char sbuf[SBUF_SIZE];
static char pgbuf[PGBUF_SIZE];

void log_setup() {
	Serial.begin(115200);
	log_cycle();
	debug(F("Logger initialized, free RAM: %u"), getFreeRam());
}

void log_freeRAM(char const *msg) {
	uint16_t free = getFreeRam();
	debug(F("Free RAM (%s): %u"), msg, free);
}

static inline void log_status() {
	uint16_t free = getFreeRam();
	if (lastRam != free) {
		lastRam = free;
		debug(F("Status -> Free RAM: %u"), free);
	}
}

void log_cycle() {
	timer_sample(&lt);

#if PRINT_FREE_RAM
	log_status();
#endif
}

void static cpgm(const __FlashStringHelper *ifsh) {
	PGM_P p = reinterpret_cast<PGM_P>(ifsh);
	uint8_t idx = 0;
	unsigned char ch = 0;
	do {
		ch = pgm_read_byte(p++);
		pgbuf[idx++]=ch;
		if(idx == PGBUF_SIZE) {
			break;
		}
	}while (ch != 0);
}

void debug(const __FlashStringHelper *ifsh, ...) {
// print time
	sprintf(sbuf, ">>[%03u-%02u:%02u:%02u,%03u]-> ", lt.dd, lt.hh, lt.mm, lt.ss, lt.ml);
	Serial.print(sbuf);

// print the message
	cpgm(ifsh);
	va_list va;
	va_start(va, ifsh);
	vsprintf(sbuf, pgbuf, va);
	va_end(va);
	Serial.println(sbuf);
}

