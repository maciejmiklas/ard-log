#include "Log.h"

static Time lt;
static uint16_t lastRam = 0;
static char *sbuf;
static char *pgbuf;

void log_setup() {
#if LOG_DISABLED
	return;
#endif
	Serial.begin(115200);

	sbuf = new char[SBUF_SIZE];
	pgbuf = new char[PGBUF_SIZE];

	log_cycle();
	debug(F("Logger initialized, free RAM: %u"), getFreeRam());
}

void log_freeRAM(char const *msg) {
	uint16_t free = getFreeRam();
	debug(F("Free RAM (%s): %u"), msg, free);
}

static void log_status() {
	uint16_t free = getFreeRam();
	if (lastRam != free) {
		lastRam = free;
		debug(F("Status -> Free RAM: %u"), free);
	}
}

void log_cycle() {
#if LOG_DISABLED
	return;
#endif
	timer_sample(&lt);

#if PRINT_FREE_RAM
	log_status();
#endif
}

void reset_sbuf() {
	for (uint8_t idx = 0; idx < SBUF_SIZE; idx++) {
		sbuf[idx] = 0;
	}
}

void reset_pgbuf() {
	for (uint8_t idx = 0; idx < PGBUF_SIZE; idx++) {
		pgbuf[idx] = 0;
	}
}

void debug(const __FlashStringHelper *ifsh, ...) {
#if LOG_DISABLED
	return;
#endif
	// print time
	reset_sbuf();
	sprintf(sbuf, ">>[%03u-%02u:%02u:%02u,%03u]-> ", lt.dd, lt.hh, lt.mm, lt.ss, lt.ml);
	Serial.print(sbuf);

	// print the message
	reset_pgbuf();
	reset_sbuf();

	pgmCopy(ifsh, pgbuf, PGBUF_SIZE);
	va_list va;
	va_start(va, ifsh);
	vsprintf(sbuf, pgbuf, va);
	va_end(va);
	Serial.println(sbuf);
}
