#include "StallardOSTime.h"

uint64_t StallardOSTime_getTimeMs()
{
    return uwTick;
}

uint64_t StallardOSTime_getTimeUs()
{
    CALL_PRIVILEGED();
    uint64_t timestamp = (uwTick * 1000) + ((SysTick->LOAD - SysTick->VAL) / (SystemCoreClock / 1000000));
    CALL_UNPRIVILEGED();
    return timestamp;
}