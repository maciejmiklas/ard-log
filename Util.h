#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Arduino.h"

void util_setup();
void util_cycle();

void sortu8(uint8_t arr[], uint8_t size);
uint32_t ms();
uint16_t getFreeRam();
boolean inline checkBit(uint8_t byte, uint8_t bit);
void fbyte(uint8_t byte, char *buf);

uint16_t abs16(int16_t val);
uint8_t abs8(int8_t val);

uint8_t maskL(uint8_t bits);
uint8_t maskR(uint8_t bits);

uint8_t** alloc2DArray8(uint8_t rows, uint8_t cols);
uint8_t** init2DArray8(uint8_t rows, uint8_t cols);
void delete2DArray(uint8_t **array, uint8_t rows, uint8_t cols);

void cpgm(const __FlashStringHelper *ifsh, char* pgbuf, uint8_t bufSize);

#endif /* DOMAIN_H_ */
