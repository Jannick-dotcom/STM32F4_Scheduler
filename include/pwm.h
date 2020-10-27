#ifndef StallardOSPWM_h
#define StallardOSPWM_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include "GPIO.h"

class StallardOSPWM
{
private:
    uint32_t pin;
    ports port;

public:
    StallardOSPWM(
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Frequency*/ uint16_t freq);
};

#endif