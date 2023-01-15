#ifndef StallardOSSPI_h
#define StallardOSSPI_h

#include "StallardOSHelpers.h"
#include <stdint.h>
// #include "StallardOSconfig.h"
#include "StallardOSsem.hpp"
#include "StallardOSGPIO.hpp"

extern "C" void StallardOSGeneralFaultHandler();

typedef enum SPIBauds
{
    Normal = SPI_BAUDRATEPRESCALER_2,
    Slow = SPI_BAUDRATEPRESCALER_64
} SPIBauds;

class StallardOSSPI
{
private:
    StallardOSSemaphore sem;
    SPI_HandleTypeDef handle;
    StallardOSGPIO mosi;
    StallardOSGPIO miso;
    StallardOSGPIO sclk;
    uint8_t toAlternateFunc(SPI_TypeDef *inst);

public:
    StallardOSSPI(SPI_TypeDef *inst, SPIBauds baud, gpio mosi, gpio miso, gpio sck);
    void send(uint8_t *data, uint16_t size);
    void receive(uint8_t *data, uint16_t size, uint32_t timeout);
};

#endif