#include "kbScan.h"
#include "config.h"
#include "pico/stdlib.h"
#include <stdio.h>

void initKbScan(uint inStartPin, uint outStartPin, uint inPinCount, uint outPinCount, uint freq){
    inStartPinL = inStartPin;
    outStartPinL = outStartPin;
    inPinCountL = inPinCount;
    outPinCountL = outPinCount;
    freqL = freq;
    // TODO
    // set the active pin as output and actually output what we need while keeping the rest as input
    for(uint i = 0; i < inPinCount; i++){
        gpio_init(inStartPin + i);
        gpio_init(outStartPin + i);
        gpio_set_dir(inStartPin + i, GPIO_IN);
        gpio_set_dir(outStartPin + i, GPIO_IN);
    }
}

uint16_t getKbReport(){
    uint16_t report = 0;
    uint bit = 0;
    for (uint i = outPinCountL - 1; i + 1 > 0; i--){
        gpio_set_dir(outStartPinL + i, GPIO_OUT);
        gpio_put(outStartPinL + i, true);
        for (uint j = 0; j < inPinCountL; j++){
            report = report | gpio_get(inStartPinL + j) << bit;
            bit++;
        }
        gpio_put(outStartPinL + i, false);
        gpio_set_dir(outStartPinL + i, GPIO_IN);
    }
    return report;
}

bool isPressedAtPos(uint16_t report, uint8_t pos)
{
  return (report & (1 << pos)) != 0;
}