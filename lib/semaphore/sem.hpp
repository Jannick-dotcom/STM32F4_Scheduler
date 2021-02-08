#ifndef SEM_H_
#define SEM_H_

#include <stdint.h>
#include "StallardOSHelpers.h"

class StallardOSSemaphore
{
    uint16_t val = 1;
public:
    void take();
    void give();
};

#endif