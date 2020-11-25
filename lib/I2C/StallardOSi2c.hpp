#ifndef StallardOSi2c_h
#define StallardOSi2c_h

// #include "StallardOSconfig.h"

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

extern void StallardOSGeneralFaultHandler();

class StallardOSi2c
{
private:
    /* data */
    I2C_HandleTypeDef hi2c;

public:
    StallardOSi2c(I2C_TypeDef *instance);
    void write(uint16_t addr, uint8_t *data, uint16_t bytes);
    uint8_t read(uint16_t addr, uint8_t *data, uint16_t bytes);
};

#endif