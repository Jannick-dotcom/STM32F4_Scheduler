#include "StallardOSDAC.hpp"

StallardOSDAC::StallardOSDAC(DAC_TypeDef *dac, StallardOSDACChannel channel, ports port, uint8_t number)
{
    __HAL_RCC_DAC_CLK_ENABLE();
    this->channel = channel;
    handle.Instance = dac;
    gpio = StallardOSGPIO(number, port, Analog);
    chanconf.DAC_Trigger = DAC_TRIGGER_NONE;
    chanconf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
    HAL_DAC_Init(&handle);
    HAL_DAC_ConfigChannel(&handle, &chanconf, channel);
    HAL_DAC_Start(&handle, channel);
    HAL_DAC_SetValue(&handle, channel, DAC_ALIGN_12B_R, 255);
}

void StallardOSDAC::setValue(uint16_t value)
{
    HAL_DAC_SetValue(&handle, channel, DAC_ALIGN_12B_R, value);
    // HAL_DAC_Start(&handle, DAC_CHANNEL_1);
}