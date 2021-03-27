#ifndef StallardOSDAC_h
#define StallardOSDAC_h

#include "StallardOSconfig.h"
#include "StallardOSGPIO.hpp"
#include "StallardOSsem.hpp"

extern "C" void StallardOSGeneralFaultHandler();

class StallardOSDAC
{
private:
    StallardOSSemaphore sem;
    DAC_HandleTypeDef handle;
    DAC_ChannelConfTypeDef chanconf;
    uint32_t channel;
    StallardOSGPIO gpio;

public:
    StallardOSDAC();
    void setValue(uint16_t value); //12 Bit
};

#endif