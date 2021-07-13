#ifndef SEM_H_
#define SEM_H_

#include <stdint.h>
#include "StallardOSHelpers.h"

class StallardOSSemaphore
{
    volatile uint16_t val = 1;
public:
    StallardOSSemaphore();
#ifdef contextSwitch
    void take();
    void give();
#endif
};

#endif