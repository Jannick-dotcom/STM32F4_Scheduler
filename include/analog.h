#ifndef Jannix_Analog
#define Jannix_Analog

#include <stdint.h>
#include <stm32f4xx_hal.h>

class JannixAnalog
{
private:
    uint8_t state;
    uint32_t pin;

public:
    JannixAnalog(
        /*ADCNumber*/ uint8_t number
        );
};

JannixAnalog::JannixAnalog(uint8_t number)
{
    this->pin = (1 << number);

    this->state = 0;

    HAL_ADC_Start(ADC_CHANNEL_0);
}

#endif