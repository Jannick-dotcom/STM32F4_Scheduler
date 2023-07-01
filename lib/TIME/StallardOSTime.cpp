#include "StallardOSTime.h"

uint64_t StallardOSTime_getTimeMs()
{
    return uwTick;
}

uint64_t StallardOSTime_getTimeUs()
{
    CALL_PRIVILEGED();
    uint64_t timestamp = (uwTick * 1000) + ((SysTick->LOAD - SysTick->VAL) / (runFreq));
    // CALL_UNPRIVILEGED();
    disable_privilege();
    return timestamp;
}