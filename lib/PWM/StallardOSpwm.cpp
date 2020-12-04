#include "StallardOSpwm.hpp"

StallardOSpwm::StallardOSpwm(TIM_TypeDef* instance, uint8_t number, ports port, uint16_t freq)
{
    this->gpio = new StallardOSGPIO(number, port, Output);
    if(this->gpio == nullptr)
    {
        StallardOSGeneralFaultHandler();
    }
    this->freq = freq;

    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
    htim.Instance = instance;
    htim.Init.Prescaler = 0;
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = 0;
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim.Init.RepetitionCounter = 0;
    //htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }
    if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }
    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
    sSlaveConfig.InputTrigger = TIM_TS_ITR0;
    //if (HAL_TIM_SlaveConfigSynchro(&htim, &sSlaveConfig) != HAL_OK)
    //{
    //    Error_Handler();
    //}
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
    {
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
        StallardOSGeneralFaultHandler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim, &sBreakDeadTimeConfig) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }
    //HAL_TIM_MspPostInit(&htim);
    HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
}

StallardOSpwm::~StallardOSpwm()
{
    delete this->gpio;
}

uint32_t StallardOSpwm::operator=(uint32_t duty)
{
    this->duty = duty;
    HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_1);
    htim.Init.Period = 0;
    HAL_TIM_PWM_Init(&htim);
    HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
    return duty;
}