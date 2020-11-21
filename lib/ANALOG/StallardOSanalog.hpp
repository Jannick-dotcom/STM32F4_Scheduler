#ifndef StallardOS_Analog
#define StallardOS_Analog

// #include "StallardOS.hpp"
#include <stm32f4xx_hal.h>

extern void StallardOSGeneralFaultHandler();

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

public:
    StallardOSAnalog(/*ADCNumber*/ StallardOSADC number, uint8_t channel);
    uint32_t getValue();
};

#endif