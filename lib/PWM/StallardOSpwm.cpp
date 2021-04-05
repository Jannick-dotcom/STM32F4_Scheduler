#include "StallardOSpwm.hpp"
#include <math.h>

/**
 * create a pwm instance.
 *
 * @param instance which timer to use
 * @param number number of the pin on the port
 * @param port gpio port
 * @param freq frequency of the pwm
 * @param bitcount number of bits for the pwm
 */
StallardOSpwm::StallardOSpwm(TIM_TypeDef *instance, uint8_t number, ports port, uint16_t freq, uint8_t bitcount)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    this->gpio = StallardOSGPIO(number, port, AFPP, nopull, GPIO_AF1_TIM1); //GPIO_AF2_TIM3 GPIO_AF3_TIM8
    this->freq = freq;
    this->bitcount = bitcount; //TODO: Make it variable!
    __HAL_RCC_TIM1_CLK_ENABLE();
    TIM_OC_InitTypeDef sConfigOC;
    htim.Instance = instance;
    htim.Init.Prescaler = (SystemCoreClock / freq) / pow(2, bitcount);
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = pow(2, bitcount) - 1;
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
    if (HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }
    if (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1) != HAL_OK)
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
 * delete a pwm instance.
 *
 */
StallardOSpwm::~StallardOSpwm()
{
    // delete this->gpio;
}

/**
 * create a pwm instance.
 *
 * @param duty which timer to use
 * @return duty cycle set
 */
uint16_t StallardOSpwm::operator=(uint16_t duty)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    this->duty = duty;
    // HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_1);
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = duty;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    
    __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, duty);

//     if (HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
//     {
// #ifdef contextSwitch
//         this->sem.give();
// #endif
//         StallardOSGeneralFaultHandler();
//     }
//     if (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1) != HAL_OK)
//     {
// #ifdef contextSwitch
//         this->sem.give();
// #endif
//         StallardOSGeneralFaultHandler();
//     }
#ifdef contextSwitch
    this->sem.give();
#endif
    return duty;
}