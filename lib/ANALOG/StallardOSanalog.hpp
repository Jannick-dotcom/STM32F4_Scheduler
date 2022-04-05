#ifndef StallardOS_Analog
#define StallardOS_Analog

#include "StallardOSHelpers.h"
#include <stdint.h>
#include "StallardOSsem.hpp"
#include "StallardOSGPIO.hpp"

extern "C" void StallardOSGeneralFaultHandler();

typedef enum StallardOSADC
{
    StallardOSADC1 = 0,
    StallardOSADC2 = 1,
    StallardOSADC3 = 2
} StallardOSADC;

typedef enum StallardOSADCChannel
{
    ch0 = ADC_CHANNEL_0,
    ch1 = ADC_CHANNEL_1,
    ch2 = ADC_CHANNEL_2,
    ch3 = ADC_CHANNEL_3,
    ch4 = ADC_CHANNEL_4,
    ch5 = ADC_CHANNEL_5,
    ch6 = ADC_CHANNEL_6,
    ch7 = ADC_CHANNEL_7,
    ch8 = ADC_CHANNEL_8,
    ch9 = ADC_CHANNEL_9,
    ch10 = ADC_CHANNEL_10,
    ch11 = ADC_CHANNEL_11,
    ch12 = ADC_CHANNEL_12,
    ch13 = ADC_CHANNEL_13,
    ch14 = ADC_CHANNEL_14,
    ch15 = ADC_CHANNEL_15,
    ch16 = ADC_CHANNEL_16,
    ch17 = ADC_CHANNEL_17,
    ch18 = ADC_CHANNEL_18
} StallardOSADCChannel;

class StallardOSAnalog
{
private:
    ADC_HandleTypeDef hadc1;
    StallardOSADC number;
    uint8_t channel;
    StallardOSGPIO gpio;
    StallardOSSemaphore sem;

public:

/**
 * create a Analog input instance.
 *
 * @param number which ADC number to use
 * @param channel channel number of the adc
 * @param port GPIO port
 * @param pin GPIO pin
 */
    StallardOSAnalog(/*ADCNumber*/ StallardOSADC number, StallardOSADCChannel channel, ports port, uint8_t pin);

/**
 * get a analog reading.
 *
 * @return analog value
 */
    uint32_t getValue();
};

#endif