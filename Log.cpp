#include "Log.h"

static Time lt;
static uint32_t runMs;
static uint32_t lastStatusMs = 0;
static uint16_t lastRam = 0;

void log_setup() {
	Serial.begin(115200);
	runMs = ms();
	log_cycle();
	debug("Logger has been initialized");
}

static void log_status() {
	if (ms() - lastStatusMs < LOG_PRINT_STATUS_MS) {
		return;
	}
	lastStatusMs = ms();
	uint16_t free = getFreeRam();
	if (lastRam != free) {
		lastRam = free;
		debug("Status -> Free RAM: %u", free);
	}
}

void log_cycle() {
	timer_sample(&lt, runMs);
	log_status();
}

void debug(const char *fmt, ...) {
	char buf[120];

	// print time
	sprintf(buf, ">>[%03u-%02u:%02u:%02u,%03u]-> ", lt.dd, lt.hh, lt.mm, lt.ss,
			lt.ml);
	Serial.print(buf);

	// print the message
	va_list va;
	va_start(va, fmt);
	vsprintf(buf, fmt, va);
	va_end(va);
	Serial.println(buf);
}


