#ifndef AU_Timer_h
#define AU_Timer_h

#include "Arduino.h"
#include "Util.h"

typedef struct {
	uint16_t dd;
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
	uint16_t ml;
} Time;

/*
 * Measures the time passed by since given #startMilis and stores the result in #ts.
 */
void timer_sample(Time *ts, uint32_t startMilis);

void timer_sample(Time *ts);

#endif /* AU_Timer_h */
