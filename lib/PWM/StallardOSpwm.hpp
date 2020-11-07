#ifndef StallardOSPWM_h
#define StallardOSPWM_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include "StallardOSGPIO.hpp"

class StallardOSpwm
{
private:
    uint32_t pin;
    ports port;
    uint32_t duty;
    uint32_t freq;

    StallardOSGPIO *gpio;

public:
    StallardOSpwm(
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Frequency*/ uint16_t freq);

    ~StallardOSpwm();   //Destructor

    uint32_t operator=(uint32_t duty);  //Set new Duty cycle
};

#endif