/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ArdLog.h"

static struct Time {
	uint16_t dd;
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
	uint16_t ml;
} ts;

static uint16_t lastRam = 0;

#if ENABLE_LOGGER
/** Buffer for created message */
static char sbuf[SBUF_SIZE] = { 0 };

/** Buffer for sprintf-template passed as first argument to log method. */
static char pgbuf[PGBUF_SIZE] = { 0 };
#endif

const static uint16_t TR_MS_SEC = 1000;
const static uint32_t TR_SEC_DD = 86400;
const static uint16_t TR_SEC_HH = 3600;
const static uint16_t TR_SEC_MM = 60;

static inline HardwareSerial& serial();
static inline void pgmCopy(const __FlashStringHelper *ifsh);
static inline void reset_pgbuf();
static inline void reset_sbuf();
static inline void freeRAM();
static inline uint16_t getFreeRam();
static inline void sampleTime();

void log_setup() {
#if ENABLE_LOGGER
	serial().begin(SERIAL_SPEED);
	log_cycle();
	log(F("LOG ON,RAM:%u"), getFreeRam());
#endif
}

void log_freeRAM(char const *msg) {
	uint16_t free = getFreeRam();
	log(F("RAM(%s):%u"), msg, free);
}

void log_cycle() {
#if ENABLE_LOGGER
	sampleTime();
#if PRINT_FREE_RAM
	freeRAM();
#endif
#endif
}

void logs(const char* msg, uint8_t size) {
#if ENABLE_LOGGER
	HardwareSerial &ser = serial();
	ser.write(msg, size);
	ser.print('\n');
#endif
}

void logs(const __FlashStringHelper *ifsh, char* msg, uint8_t size) {
#if ENABLE_LOGGER
	HardwareSerial &ser = serial();
	reset_sbuf();
	pgmCopy(ifsh);
	ser.print(pgbuf);
	msg[size - 1] = '\0';
	ser.write(msg);
	ser.print('\n');
#endif
}

void logc(char val) {
	HardwareSerial &ser = serial();
	ser.print(val);
}

void logs(const __FlashStringHelper *ifsh, const char* msg, uint8_t size) {
#if ENABLE_LOGGER
	HardwareSerial &ser = serial();

	reset_sbuf();
	pgmCopy(ifsh);
	ser.print(pgbuf);
	ser.write(msg, size);
	ser.print('\n');
#endif
}

void log(const __FlashStringHelper *ifsh, ...) {
#if ENABLE_LOGGER
#if USE_CURRENT_TIME
	sampleTime();
#endif

	HardwareSerial &ser = serial();
	reset_sbuf();
#if LOG_FULL_TIME
	sprintf(sbuf, ">[%03u-%02u:%02u:%02u,%03u]>", ts.dd, ts.hh, ts.mm, ts.ss, ts.ml);
#endif

#if LOG_MIN_TIME
	sprintf(sbuf, ">[%02u:%02u,%03u]>", ts.mm, ts.ss, ts.ml);
#endif
	ser.print(sbuf);

	// print the message
	reset_pgbuf();
	reset_sbuf();

	pgmCopy(ifsh);
	va_list va;
	va_start(va, ifsh);
	vsprintf(sbuf, pgbuf, va);
	va_end(va);
	ser.println(sbuf);
#endif
}
// ###########################################################
// ### Private methods
// ###########################################################

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

static inline HardwareSerial& serial() {
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

static inline uint16_t getFreeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (uint16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

static inline void freeRAM() {
	uint16_t free = getFreeRam();
	if (lastRam != free) {
		lastRam = free;
		log(F("RAM:%u"), free);
	}
}

static inline void reset_sbuf() {
#if ENABLE_LOGGER
	for (uint8_t idx = 0; idx < SBUF_SIZE; idx++) {
		sbuf[idx] = ' ';
	}
	sbuf[SBUF_SIZE - 1] = '\0';
#endif
}

static inline void reset_pgbuf() {
#if ENABLE_LOGGER
	for (uint8_t idx = 0; idx < PGBUF_SIZE; idx++) {
		pgbuf[idx] = 0;
	}
#endif
}

static inline void pgmCopy(const __FlashStringHelper *ifsh) {
#if ENABLE_LOGGER
	PGM_P p = reinterpret_cast<PGM_P>(ifsh);
	unsigned char ch = 0;
	for(uint8_t pgbufIdx = 0; pgbufIdx < PGBUF_SIZE; pgbufIdx++) {
		ch = pgm_read_byte(p++);
		pgbuf[pgbufIdx] = ch;
		if(ch == 0) {
			break;
		}
	}
#endif
}
