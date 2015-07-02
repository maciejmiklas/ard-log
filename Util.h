#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Arduino.h"

void util_setup();
void util_cycle();

void sortu8(uint8_t arr[], uint8_t size);
uint32_t ms();
uint16_t getFreeRam();

uint16_t abs16(int16_t val);
uint8_t abs8(int8_t val);

uint8_t maskL(uint8_t bits);
uint8_t maskR(uint8_t bits);

void fbyte(uint8_t byte, String &buf);

#endif /* DOMAIN_H_ */
