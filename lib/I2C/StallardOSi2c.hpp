#ifndef StallardOSi2c_h
#define StallardOSi2c_h

// #include "StallardOSconfig.h"

#include "StallardOSHelpers.h"
#include <stdint.h>
#include "StallardOSsem.hpp"
#include "StallardOSGPIO.hpp"
extern "C" void StallardOSGeneralFaultHandler();

class StallardOSi2c
{
private:
    /* data */
    I2C_HandleTypeDef hi2c;
    StallardOSSemaphore sem;

public:
    StallardOSGPIO scl;
    StallardOSGPIO sda;
    StallardOSi2c(I2C_TypeDef *instance, uint32_t freq);
    uint8_t write(uint16_t addr, uint8_t *data, uint16_t bytes);
    uint8_t read(uint16_t addr, uint8_t *data, uint16_t bytes);
};

#endif