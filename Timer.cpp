#include "Timer.h"

const uint8_t TR_MS_SEC = 1000;
const uint8_t TR_SEC_DD = 86400;
const uint8_t TR_SEC_HH = 3600;
const uint8_t TR_SEC_MM = 60;

void timer_sample(Time *ts) {
	timer_sample(ts, 0);
}

//long milis =  126000000 + 1440000 + 17000;// 1d 11h 24m 17s
//long milis =  345600000 + 1440000 + 17000;// 4d 0h 24m 17s
//long milis =  446400000 + 1440000 + 17000;// 5d 4h 24m 17s
void timer_sample(Time *ts, uint32_t timeMilis) {
	uint32_t milis = ms() - timeMilis;
	uint32_t sec = milis / TR_MS_SEC;

	// days
	ts->dd = sec / TR_SEC_DD;
	uint32_t tmp = sec - ts->dd * TR_SEC_DD;

	// hours of a day
	ts->hh = tmp / TR_SEC_HH;
	tmp -= ts->hh * TR_SEC_HH;

	// minutes of an hour
	ts->mm = tmp / TR_SEC_MM;
	tmp -= ts->mm * TR_SEC_MM;

	// seconds of a minute
	ts->ss = tmp;

	// millis of a second
	ts->ml = (milis % 1000);
}

