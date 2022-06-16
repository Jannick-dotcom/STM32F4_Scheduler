#ifndef StallardOSDAC_h
#define StallardOSDAC_h

// #include "StallardOSconfig.h"
#include "StallardOSGPIO.hpp"
#include "StallardOSsem.hpp"

extern "C" inline void StallardOSGeneralFaultHandler();
#ifdef STM32F4xxxx
typedef enum StallardOSDACChannel
{
    channel1 = DAC_CHANNEL_1,
    channel2 = DAC_CHANNEL_2
} StallardOSDACChannel;

class StallardOSDAC
{
private:
    StallardOSSemaphore sem;
    DAC_HandleTypeDef handle;
    DAC_ChannelConfTypeDef chanconf;
    StallardOSDACChannel channel;
    StallardOSGPIO gpio;

public:
    StallardOSDAC(DAC_TypeDef *dac, StallardOSDACChannel channel, ports port, uint8_t number);
    void setValue(uint16_t value); //12 Bit
};
#endif
#endif