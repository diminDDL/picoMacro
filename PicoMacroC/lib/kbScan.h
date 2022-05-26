#ifndef KB_SCAN_H_
#define KB_SCAN_H_

#include "pico/stdlib.h"

void initKbScan(uint inStartPin, uint outStartPin, uint inPinCount, uint outPinCount, uint freq);
uint16_t getKbReport();
static uint inStartPinL;
static uint outStartPinL;
static uint inPinCountL;
static uint outPinCountL;
static uint freqL;

#endif /* KB_SCAN_H_ */