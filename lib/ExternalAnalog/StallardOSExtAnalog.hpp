#ifndef StallardOS_ExtAnalog
#define StallardOS_ExtAnalog

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>
#include "StallardOSconfig.h"
#include "StallardOSsem.hpp"
#include "StallardOSSPI.hpp"
#include "StallardOSGPIO.hpp"

extern "C" void StallardOSGeneralFaultHandler();

class StallardOSExtAnalog
{
private:
    StallardOSSPI spihandle;
    uint8_t channel;
    uint8_t adcNumber;
    
    StallardOSGPIO cs;
    StallardOSGPIO drdy;

    StallardOSSemaphore sem;
    uint8_t registerRead(uint8_t address);
    void registerWrite(uint8_t address, uint8_t value);
    uint16_t channelRead();

public:

/**
 * create a Analog input instance.
 *
 * @param adcNumber which adc to use
 * @param channel Number of channel
 */
    StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber);

/**
 * get a analog reading.
 *
 * @return analog value
 */
    uint16_t getValue();
};

#endif