#ifndef StallardOSPWM_h
#define StallardOSPWM_h

#include "StallardOSGPIO.hpp"
#include "StallardOSconfig.h"
#include "StallardOSsem.hpp"

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

extern "C" void StallardOSGeneralFaultHandler();

class StallardOSpwm
{
private:
    uint32_t pin;
    ports port;
    uint32_t duty;
    uint32_t freq;
    uint8_t bitcount;

    StallardOSGPIO gpio;
    TIM_HandleTypeDef htim;
    StallardOSSemaphore sem;

public:
    StallardOSpwm(
        /*Timer to be used*/ TIM_TypeDef* instance,
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Frequency*/ uint16_t freq,
        /*Number of bits to use*/ uint8_t bitcount);

    ~StallardOSpwm();   //Destructor

    uint16_t operator=(uint16_t duty);  //Set new Duty cycle
};

#endif