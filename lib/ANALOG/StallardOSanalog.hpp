#ifndef StallardOS_Analog
#define StallardOS_Analog

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "StallardOSFaultHandlers.hpp"

typedef enum StallardOSADC
{
    StallardOSADC1 = 0,
    StallardOSADC2 = 1,
    StallardOSADC3 = 2
} StallardOSADC;

class StallardOSAnalog
{
private:
    StallardOSADC number;
    uint8_t channel;

public:
    StallardOSAnalog(/*ADCNumber*/ StallardOSADC number, uint8_t channel);
};

StallardOSAnalog::StallardOSAnalog(StallardOSADC number, uint8_t channel)
{
    ADC_HandleTypeDef hadc1;
    const ADC_TypeDef *StallardOSAnalog_to_ADC_Typedef[] = {ADC1, ADC2, ADC3};
    hadc1.Instance = (ADC_TypeDef *)StallardOSAnalog_to_ADC_Typedef[number];
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }

    this->number = number;
    this->channel = channel;
}

#endif