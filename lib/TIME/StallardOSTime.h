#ifndef StallardOSTIME_H
#define StallardOSTIME_H

#include "inttypes.h"
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include "StallardOSsyscalls.h"

uint64_t StallardOSTime_getTimeMs();
uint64_t StallardOSTime_getTimeUs();

#endif