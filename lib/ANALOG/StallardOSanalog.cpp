#include "StallardOSanalog.hpp"

StallardOSAnalog::StallardOSAnalog(StallardOSADC number, StallardOSADCChannel channel, ports port, uint8_t pin) : gpio(pin,port,Analog)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    // gpio = StallardOSGPIO(pin,port,Analog); //initialize the gpio as analog input pin
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_ADC2_CLK_ENABLE();
    __HAL_RCC_ADC3_CLK_ENABLE();
    const ADC_TypeDef *StallardOSAnalog_to_ADC_Typedef[] = {ADC1, ADC2, ADC3};
    hadc1.Instance = (ADC_TypeDef *)StallardOSAnalog_to_ADC_Typedef[number];
    hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.NbrOfDiscConversion = 0;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }
    // Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    ADC_ChannelConfTypeDef sConfig;
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    sConfig.Offset = 0;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }

    this->number = number;
    this->channel = channel;
#ifdef contextSwitch
    this->sem.give();
#endif
}


uint32_t StallardOSAnalog::getValue()
{
    uint32_t retVal;
#ifdef contextSwitch
    this->sem.take();
#endif
    HAL_ADC_Start(&hadc1);
    retVal = HAL_ADC_GetValue(&hadc1);
#ifdef contextSwitch
    this->sem.give();
#endif
    return retVal;
}