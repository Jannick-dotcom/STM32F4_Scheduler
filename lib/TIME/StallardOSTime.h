#ifndef StallardOSTIME_H
#define StallardOSTIME_H

#include "inttypes.h"
#include "StallardOSHelpers.h"
#include "StallardOSsyscalls.h"

uint64_t StallardOSTime_getTimeMs();
uint64_t StallardOSTime_getTimeUs();

#endif