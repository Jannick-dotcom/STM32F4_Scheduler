#ifndef StallardOS_ExtAnalog
#define StallardOS_ExtAnalog

#include "StallardOSHelpers.h"
#include <stdint.h>
#include "StallardOSconfig.h"
#include "StallardOSsem.hpp"
#include "StallardOSSPI.hpp"
#include "StallardOSGPIO.hpp"
#include "StallardOSClass.hpp"
#include "StallardOSTime.h"

#define reg0Value 0
#define reg1Value 3

extern "C" void StallardOSGeneralFaultHandler();

class StallardOSExtAnalog
{
private:
    StallardOSSPI *spihandle;
    uint8_t channel;
    uint8_t adcNumber;
    
    static StallardOSGPIO cs1;
    static StallardOSGPIO drdy1;
    static StallardOSGPIO reset1;

    static StallardOSGPIO cs2;
    static StallardOSGPIO drdy2;
    static StallardOSGPIO reset2;

    static StallardOSSemaphore sem;
    static uint8_t adcInitialized;

    uint8_t registerRead(uint8_t address);
    void registerWrite(uint8_t address, uint8_t value);
    uint16_t channelRead(uint8_t channel);
public:

public:

/**
 * create a Analog input instance.
 *
 * @param adcNumber which adc to use
 * @param channel Number of channel
 */
    StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber, StallardOSSPI *spihandle);

/**
 * get a analog reading.
 *
 * @return analog value
 */
    int16_t getValue();
};

#endif