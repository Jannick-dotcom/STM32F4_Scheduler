#ifndef SEM_H_
#define SEM_H_

#include <stdint.h>
#include "StallardOSHelpers.h"

class StallardOSSemaphore
{
    volatile uint32_t val = 1;
public:
    StallardOSSemaphore();

    void take();
    void give();

};

#endif