#include "StallardOSpwm.hpp"
#include <math.h>

uint8_t mapToAlternateFunction(TIM_TypeDef *instance)
{
    if (instance == TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();
        return STOS_Tim1;
    }
    else if (instance == TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
        return STOS_Tim2;
    }
    else if (instance == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
        return STOS_Tim3;
    }
    else if (instance == TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
        return STOS_Tim4;
    }
    else if (instance == TIM5)
    {
        __HAL_RCC_TIM5_CLK_ENABLE();
        return STOS_Tim5;
    }
    // else if (instance == TIM6)
    // {
    //     __HAL_RCC_TIM6_CLK_ENABLE();
    //     return STOS_Tim6;
    // }
    // else if (instance == TIM7)
    // {
    //     __HAL_RCC_TIM7_CLK_ENABLE();
    //     return STOS_Tim7;
    // }
    else if (instance == TIM8)
    {
        __HAL_RCC_TIM8_CLK_ENABLE();
        return STOS_Tim8;
    }
    else if (instance == TIM9)
    {
        __HAL_RCC_TIM9_CLK_ENABLE();
        return STOS_Tim9;
    }
    else if (instance == TIM10)
    {
        __HAL_RCC_TIM10_CLK_ENABLE();
        return STOS_Tim10;
    }
    else if (instance == TIM11)
    {
        __HAL_RCC_TIM11_CLK_ENABLE();
        return STOS_Tim11;
    }
    else if (instance == TIM12)
    {
        __HAL_RCC_TIM12_CLK_ENABLE();
        return STOS_Tim12;
    }
    else if (instance == TIM13)
    {
        __HAL_RCC_TIM13_CLK_ENABLE();
        return STOS_Tim13;
    }
    else if (instance == TIM14)
    {
        __HAL_RCC_TIM14_CLK_ENABLE();
        return STOS_Tim14;
    }
    else
        return -1;
}

/**
 * create a pwm instance.
 *
 * @param instance which timer to use
 * @param channel Timer channel to use
 * @param number number of the pin on the port
 * @param port gpio port
 * @param freq frequency of the pwm
 * @param bitcount number of bits for the pwm
 */
StallardOSpwm::StallardOSpwm(TIM_TypeDef *instance, PWMChannel channel, uint8_t number, ports port, uint16_t freq, uint8_t bitcount) : 
    gpio(number, port, AFPP, nopull, mapToAlternateFunction(instance))
{
#ifdef contextSwitch
    this->sem.take();
#endif
    // this->gpio = StallardOSGPIO(number, port, AFPP, nopull, mapToAlternateFunction(instance));
    this->freq = freq;
    this->channel = channel;
    this->bitcount = bitcount;
    TIM_OC_InitTypeDef sConfigOC;
    htim.Instance = instance;
    if(instance == TIM1 || instance == TIM8 || instance == TIM9 || instance == TIM10 || instance == TIM11)
    {
        htim.Init.Prescaler = (168000000 / (freq)) / ((uint32_t)1 << bitcount);
    }
    else
    {
        htim.Init.Prescaler = (168000000 / (4*freq)) / ((uint32_t)1 << bitcount);
    }
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = ((uint32_t)1 << bitcount) - 1;
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim.Init.RepetitionCounter = 0;
    htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }
    if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, this->channel) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }
    if (HAL_TIM_PWM_Start(&htim, this->channel) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }
#ifdef contextSwitch
    this->sem.give();
#endif
}

/**
 * create a pwm instance.
 *
 * @param duty duty cycle of the pwm signal
 * @return duty cycle set
 */
uint16_t StallardOSpwm::operator=(uint16_t duty)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    this->duty = duty;
    __HAL_TIM_SET_COMPARE(&htim, this->channel, duty);
#ifdef contextSwitch
    this->sem.give();
#endif
    return duty;
}