#ifndef StallardOSSPI_h
#define StallardOSSPI_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>
#include "StallardOSconfig.h"
#include "StallardOSsem.hpp"

extern "C" void StallardOSGeneralFaultHandler();

class StallardOSSPI
{
private:
    StallardOSSemaphore sem;
    SPI_HandleTypeDef handle;

public:
    StallardOSSPI(SPI_TypeDef *inst, uint32_t baud);
    void send(uint8_t *data, uint16_t size);
    void receive(uint8_t *data, uint16_t size, uint16_t timeout);
};

#endif