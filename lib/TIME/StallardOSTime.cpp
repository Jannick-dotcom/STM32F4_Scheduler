#include "StallardOSTime.h"

uint64_t StallardOSTime_getTimeMs()
{
    return HAL_GetTick();
}

uint64_t StallardOSTime_getTimeUs()
{
    CALL_PRIVILEGED();
    uint64_t timestamp = (HAL_GetTick() * 1000) + SysTick->LOAD - (SysTick->VAL / (SystemCoreClock / 1000000));
    CALL_UNPRIVILEGED();
    return timestamp;
}