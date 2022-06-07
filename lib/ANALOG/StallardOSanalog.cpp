#include "StallardOSanalog.hpp"

StallardOSAnalog::StallardOSAnalog(StallardOSADC number, StallardOSADCChannel channel, ports port, uint8_t pin) : gpio(pin,port,Analog)
{

    this->sem.take();

    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_ADC2_CLK_ENABLE();
    #ifdef STM32F4xxxx
    __HAL_RCC_ADC3_CLK_ENABLE();
    const ADC_TypeDef *StallardOSAnalog_to_ADC_Typedef[] = {ADC1, ADC2, ADC3};
    #elif defined(STM32F1xxxx)
    const ADC_TypeDef *StallardOSAnalog_to_ADC_Typedef[] = {ADC1, ADC2};
    #endif
    hadc1.Instance = (ADC_TypeDef *)StallardOSAnalog_to_ADC_Typedef[number];
    #ifdef STM32F4xxxx
    hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    #endif
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.NbrOfDiscConversion = 0;
    #ifdef STM32F4xxxx
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    #endif
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    #ifdef STM32F4xxxx
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    #endif
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {

        this->sem.give();

        StallardOSGeneralFaultHandler();
    }
    // Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    ADC_ChannelConfTypeDef sConfig;
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    #ifdef STM32F4xxxx
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    sConfig.Offset = 0;
    #elif defined(STM32F1xxxx)
    sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
    #endif
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {

        this->sem.give();

        StallardOSGeneralFaultHandler();
    }

    this->number = number;
    this->channel = channel;

    this->sem.give();

}


uint32_t StallardOSAnalog::getValue()
{
    uint32_t retVal;

    this->sem.take();

    HAL_ADC_Start(&hadc1);
    retVal = HAL_ADC_GetValue(&hadc1);

    this->sem.give();

    return retVal;
}