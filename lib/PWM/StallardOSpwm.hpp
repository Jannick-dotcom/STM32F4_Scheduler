#ifndef StallardOSPWM_h
#define StallardOSPWM_h

#include "StallardOSGPIO.hpp"
#include "StallardOSconfig.h"
#include "StallardOSsem.hpp"

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

extern "C" inline void StallardOSGeneralFaultHandler();

typedef enum PWMChannel
{
    PWMch1 = TIM_CHANNEL_1,
    PWMch2 = TIM_CHANNEL_2, 
    PWMch3 = TIM_CHANNEL_3,
    PWMch4 = TIM_CHANNEL_4
}PWMChannel;

typedef enum PWMalternateFunctions
{
    STOS_Tim1 = GPIO_AF1_TIM1,
    STOS_Tim2 = GPIO_AF1_TIM2,
    STOS_Tim3 = GPIO_AF2_TIM3,
    STOS_Tim4 = GPIO_AF2_TIM4,
    STOS_Tim5 = GPIO_AF2_TIM5,
    //STOS_Tim6 = NULL,
    //STOS_Tim7 = NULL,
    STOS_Tim8 = GPIO_AF3_TIM8,
    STOS_Tim9 = GPIO_AF3_TIM9,
    STOS_Tim10 = GPIO_AF3_TIM10,
    STOS_Tim11 = GPIO_AF3_TIM11,
    STOS_Tim12 = GPIO_AF9_TIM12,
    STOS_Tim13 = GPIO_AF9_TIM13,
    STOS_Tim14 = GPIO_AF9_TIM14
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
        /*Timer Channel*/ PWMChannel channel,
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Frequency*/ uint16_t freq,
        /*Number of bits to use*/ uint8_t bitcount);

    uint16_t operator=(uint16_t duty); //Set new Duty cycle
};

#endif