#ifndef STALLARDOSCANFILTER_H
#define STALLARDOSCANFILTER_H

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "StallardOScan.hpp"

/*
* A filter is used to filter for specific message IDs
* Defined filter IDs will be received
* 28 Filters can be used
* So that makes 14 per CAN
*/

extern "C" void StallardOSGeneralFaultHandler();

class StallardOSCANFilter
{
public:
    static uint8_t countFilters;
    uint8_t n;
    uint16_t id1;
    uint16_t id2;
    StallardOSCANFilter(uint16_t id1, uint16_t id2, CANports can);
    ~StallardOSCANFilter();
};

#endif