#include "StallardOSTime.h"

uint64_t StallardOSTime_getTimeMs()
{
    return HAL_GetTick();
}

uint64_t StallardOSTime_getTimeUs()
{
    uint32_t *SysTick_VAL = (uint32_t*)(SysTick_BASE + 0x08);
    CALL_PRIVILEGED();
    uint64_t timestamp = (HAL_GetTick() * 1000) + (*SysTick_VAL / (SystemCoreClock / 1000000));
    CALL_UNPRIVILEGED();
    return timestamp;
}