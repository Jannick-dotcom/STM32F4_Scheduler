#ifndef StallardOS_Analog
#define StallardOS_Analog

#include <stdint.h>
#include <stm32f4xx_hal.h>

class StallardOSAnalog
{
private:
    uint8_t state;
    uint32_t pin;

public:
    StallardOSAnalog(
        /*ADCNumber*/ uint8_t number
        );
};

StallardOSAnalog::StallardOSAnalog(uint8_t number)
{
    this->pin = (1 << number);

    this->state = 0;

    HAL_ADC_Start(ADC_CHANNEL_0);
}

#endif