#ifndef StallardOS_Analog
#define StallardOS_Analog

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
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
    StallardOSAnalog(/*ADCNumber*/ StallardOSADC number, uint8_t channel, ports port, uint8_t pin);

/**
 * get a analog reading.
 *
 * @return analog value
 */
    uint32_t getValue();
};

#endif