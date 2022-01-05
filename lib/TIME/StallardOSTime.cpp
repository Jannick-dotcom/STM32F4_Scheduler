#include "StallardOSTime.h"

uint64_t StallardOSTime_getTimeMs()
{
    return HAL_GetTick();
}

uint64_t StallardOSTime_getTimeUs()
{
    __ASM volatile("SVC #0");
    uint64_t timestamp = (HAL_GetTick() * 1000) + (*(uint32_t*)0xE000E018 / (SystemCoreClock / 1000000));
    __ASM volatile("SVC #1");
    return timestamp;
}