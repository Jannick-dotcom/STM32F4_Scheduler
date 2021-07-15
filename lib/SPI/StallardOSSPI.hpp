#ifndef StallardOSSPI_h
#define StallardOSSPI_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>
#include "StallardOSconfig.h"
#include "StallardOSsem.hpp"
#include "StallardOSGPIO.hpp"

extern "C" void StallardOSGeneralFaultHandler();

typedef enum SPIBauds
{
    Normal = SPI_BAUDRATEPRESCALER_2
} SPIBauds;

class StallardOSSPI
{
private:
    StallardOSSemaphore sem;
    SPI_HandleTypeDef handle;
    StallardOSGPIO mosi;
    StallardOSGPIO miso;
    StallardOSGPIO sclk;

public:
    StallardOSSPI(SPI_TypeDef *inst, SPIBauds baud, gpio mosi, gpio miso, gpio sck);
    void send(uint8_t *data, uint16_t size);
    void receive(uint8_t *data, uint16_t size, uint16_t timeout);
};

#endif