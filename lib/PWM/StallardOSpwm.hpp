#ifndef StallardOSPWM_h
#define StallardOSPWM_h

#include "StallardOSGPIO.hpp"
#include "StallardOSconfig.h"
#include "StallardOSsem.hpp"

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

extern "C" void StallardOSGeneralFaultHandler();

typedef enum PWMalternateFunctions
{
    Tim1 = GPIO_AF1_TIM1,
    Tim2 = GPIO_AF1_TIM2,
    Tim3 = GPIO_AF2_TIM3,
    Tim4 = GPIO_AF2_TIM4,
    Tim5 = GPIO_AF2_TIM5,
    //Tim6 = NULL,
    //Tim7 = NULL,
    Tim8 = GPIO_AF3_TIM8,
    Tim9 = GPIO_AF3_TIM9,
    Tim10 = GPIO_AF3_TIM10,
    Tim11 = GPIO_AF3_TIM11,
    Tim12 = GPIO_AF9_TIM12,
    Tim13 = GPIO_AF9_TIM13,
    Tim14 = GPIO_AF9_TIM14
} PWMalternateFunctions;

class StallardOSpwm
{
private:
    uint32_t pin;
    ports port;
    uint32_t duty;
    uint32_t freq;
    uint8_t bitcount;
    uint8_t channel;

    StallardOSGPIO gpio;
    TIM_HandleTypeDef htim;
    StallardOSSemaphore sem;

public:
    StallardOSpwm(
        /*Timer to be used*/ TIM_TypeDef *instance,
        /*Timer Channel*/ uint8_t channel,
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Frequency*/ uint16_t freq,
        /*Number of bits to use*/ uint8_t bitcount);

    uint16_t operator=(uint16_t duty); //Set new Duty cycle
};

#endif