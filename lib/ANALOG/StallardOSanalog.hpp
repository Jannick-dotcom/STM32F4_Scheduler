#ifndef StallardOS_Analog
#define StallardOS_Analog

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>
#include "StallardOSsem.hpp"

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
    StallardOSSemaphore sem;

public:
    StallardOSAnalog(/*ADCNumber*/ StallardOSADC number, uint8_t channel);
    uint32_t getValue();
};

#endif