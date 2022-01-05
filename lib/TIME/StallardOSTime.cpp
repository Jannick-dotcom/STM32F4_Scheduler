#include "StallardOSTime.h"

uint64_t StallardOSTime_getTimeMs()
{
    return HAL_GetTick();
}

uint64_t StallardOSTime_getTimeUs()
{
    CALL_PRIVILEGED();
    uint64_t timestamp = (HAL_GetTick() * 1000) + (*(uint32_t*)0xE000E018 / (SystemCoreClock / 1000000));
    CALL_UNPRIVILEGED();
    return timestamp;
}