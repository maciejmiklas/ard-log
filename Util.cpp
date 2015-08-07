#include <Util.h>

static uint32_t cycleMs = 0;

void sortu8(uint8_t arr[], uint8_t size) {
	uint8_t i, temp, j;
	for (i = 1; i < size; i++) {
		temp = arr[i];
		j = i - 1;
		while ((temp < arr[j]) && (j >= 0)) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = temp;
	}
}

void util_setup() {
	util_cycle();
}

void util_cycle() {
	cycleMs = millis();
}

uint32_t ms() {
	return cycleMs;
}

uint16_t getFreeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (uint16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

uint16_t abs16(int16_t val) {
	return val > 0 ? val : val * -1;

}

uint8_t abs8(int8_t val) {
	return val > 0 ? val : val * -1;
}

uint8_t maskL(uint8_t bits) {
	uint8_t bv;

	switch (bits) {
	default:
	case 0:
		bv = B00000000;
		break;

	case 1:
		bv = B10000000;
		break;

	case 2:
		bv = B11000000;
		break;

	case 3:
		bv = B11100000;
		break;

	case 4:
		bv = B11110000;
		break;

	case 5:
		bv = B11111000;
		break;

	case 6:
		bv = B11111100;
		break;

	case 7:
		bv = B11111110;
		break;

	case 8:
		bv = B11111111;
		break;
	}
	return bv;
}
uint8_t maskR(uint8_t bits) {
	uint8_t bv;

	switch (bits) {
	default:
	case 0:
		bv = B00000000;
		break;

	case 1:
		bv = B00000001;
		break;

	case 2:
		bv = B00000011;
		break;

	case 3:
		bv = B00000111;
		break;

	case 4:
		bv = B00001111;
		break;

	case 5:
		bv = B00011111;
		break;

	case 6:
		bv = B00111111;
		break;

	case 7:
		bv = B01111111;
		break;

	case 8:
		bv = B11111111;
		break;

	}
	return bv;
}

boolean inline checkBit(uint8_t byte, uint8_t bit) {
	return byte & (1 << bit);
}

void fbyte(uint8_t byte, char *buf) {
	uint8_t bit = 7;
	for (uint8_t idx = 0; idx < 8; idx++) {
		buf[idx] = checkBit(byte, bit) ? '1' : '0';
		bit--;
	}

	buf[8] = NULL;
}

uint8_t** alloc2DArray8(uint8_t rows, uint8_t cols) {
	uint8_t **array = new uint8_t*[rows];
	for (uint8_t row = 0; row < rows; row++) {
		array[row] = new uint8_t[cols];
	}
	return array;
}

uint8_t** init2DArray8(uint8_t rows, uint8_t cols) {
	uint8_t **array = new uint8_t*[rows];
	for (uint8_t row = 0; row < rows; row++) {
		array[row] = new uint8_t[cols];
		for (uint8_t col = 0; col < cols; col++) {
			array[row][col] = 0;
		}
	}
	return array;
}

void delete2DArray(uint8_t **array, uint8_t rows, uint8_t cols) {
	for (uint8_t row = 0; row < rows; row++) {
		delete (array[row]);
	}
	delete (array);
}

void cpgm(const __FlashStringHelper *ifsh, char* pgbuf, uint8_t bufSize) {
	PGM_P p = reinterpret_cast<PGM_P>(ifsh);
	unsigned char ch = 0;
	for(uint8_t pgbufIdx = 0;pgbufIdx<bufSize;pgbufIdx++) {
		ch = pgm_read_byte(p++);
		pgbuf[pgbufIdx]=ch;
		if(ch == 0) {
			break;
		}
	}
}
