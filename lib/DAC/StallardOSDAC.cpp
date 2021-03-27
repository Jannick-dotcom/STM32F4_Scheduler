#include "StallardOSDAC.hpp"

StallardOSDAC::StallardOSDAC()
{
    handle.Instance = DAC1;
    // handle.Instance = DAC2;
    chanconf.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
    chanconf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
    HAL_DAC_ConfigChannel(&handle, &chanconf, channel);
    HAL_DAC_Init(&handle);
    HAL_DAC_SetValue(&handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2048);
    HAL_DAC_Start(&handle, DAC_CHANNEL_1);
}

void StallardOSDAC::setValue(uint16_t value)
{
    HAL_DAC_SetValue(&handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2048);
    HAL_DAC_Start(&handle, DAC_CHANNEL_1);
}