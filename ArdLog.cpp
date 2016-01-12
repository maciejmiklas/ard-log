#include "ArdLog.h"

static struct Time {
	uint16_t dd;
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
	uint16_t ml;
} ts;

static uint16_t lastRam = 0;
static char *sbuf;
static char *pgbuf;

const static uint16_t TR_MS_SEC = 1000;
const static uint32_t TR_SEC_DD = 86400;
const static uint16_t TR_SEC_HH = 3600;
const static uint16_t TR_SEC_MM = 60;

//long milis =  126000000 + 1440000 + 17000;// 1d 11h 24m 17s
//long milis =  345600000 + 1440000 + 17000;// 4d 0h 24m 17s
//long milis =  446400000 + 1440000 + 17000;// 5d 4h 24m 17s
static inline void sampleTime() {
	uint32_t cycleMs = millis();
	uint32_t sec = cycleMs / TR_MS_SEC;

	// days
	ts.dd = sec / TR_SEC_DD;
	uint32_t tmp = sec - ts.dd * TR_SEC_DD;

	// hours of a day
	ts.hh = tmp / TR_SEC_HH;
	tmp -= ts.hh * TR_SEC_HH;

	// minutes of an hour
	ts.mm = tmp / TR_SEC_MM;
	tmp -= ts.mm * TR_SEC_MM;

	// seconds of a minute
	ts.ss = tmp;

	// millis of a second
	ts.ml = (cycleMs % 1000);
}

static inline HardwareSerial get() {
#if USE_SERIAL_1
	return Serial1;
#endif

#if USE_SERIAL_2
	return Serial2;
#endif

#if USE_SERIAL_3
	return Serial3;
#endif

	return Serial;
}

inline static uint16_t getFreeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (uint16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void log_setup() {
#if LOG
	get().begin(115200);

	sbuf = new char[SBUF_SIZE];
	pgbuf = new char[PGBUF_SIZE];

	log_cycle();
	log(F("Logger initialized, free RAM: %u"), getFreeRam());
#endif
}

void log_freeRAM(char const *msg) {
	uint16_t free = getFreeRam();
	log(F("Free RAM (%s): %u"), msg, free);
}

static inline void freeRAM() {
	uint16_t free = getFreeRam();
	if (lastRam != free) {
		lastRam = free;
		log(F("Free RAM: %u"), free);
	}
}

void log_cycle() {
#if LOG
	sampleTime();

#if PRINT_FREE_RAM
	freeRAM();
#endif
#endif
}

static inline void reset_sbuf() {
	for (uint8_t idx = 0; idx < SBUF_SIZE; idx++) {
		sbuf[idx] = 0;
	}
}

static inline void reset_pgbuf() {
	for (uint8_t idx = 0; idx < PGBUF_SIZE; idx++) {
		pgbuf[idx] = 0;
	}
}

inline static void pgmCopy(const __FlashStringHelper *ifsh, char *pgbuf, uint8_t bufSize) {
	PGM_P p = reinterpret_cast<PGM_P>(ifsh);
	unsigned char ch = 0;
	for(uint8_t pgbufIdx = 0; pgbufIdx < bufSize; pgbufIdx++) {
		ch = pgm_read_byte(p++);
		pgbuf[pgbufIdx] = ch;
		if(ch == 0) {
			break;
		}
	}
}

void log(const __FlashStringHelper *ifsh, ...) {
#if LOG
#if USE_CURRENT_TIME
	sampleTime();
#endif

	HardwareSerial ser = get();
	// print time
	reset_sbuf();
	sprintf(sbuf, ">>[%03u-%02u:%02u:%02u,%03u]-> ", ts.dd, ts.hh, ts.mm, ts.ss, ts.ml);
	ser.print(sbuf);

	// print the message
	reset_pgbuf();
	reset_sbuf();

	pgmCopy(ifsh, pgbuf, PGBUF_SIZE);
	va_list va;
	va_start(va, ifsh);
	vsprintf(sbuf, pgbuf, va);
	va_end(va);
	ser.println(sbuf);
#endif
}
