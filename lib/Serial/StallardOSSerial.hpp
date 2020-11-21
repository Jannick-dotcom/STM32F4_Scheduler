#ifndef StallardOSSerial_h
#define StallardOSSerial_h

#include "StallardOSconfig.h"
extern void StallardOSGeneralFaultHandler();

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

typedef enum serialPorts
{
    StallardOSUSART_1,
    StallardOSUSART_2,
    StallardOSUSART_3,
    StallardOSUSART_4,
    StallardOSUSART_5,
    StallardOSUSART_6,
    StallardOSUSART_7,
    StallardOSUSART_8,
    StallardOSUSART_9,
    StallardOSUSART_10
} serialPorts;

class StallardOSSerial
{
private:
    UART_HandleTypeDef huart;
public:
    StallardOSSerial(serialPorts serPort, uint32_t baud);
    void send(const char *dat, size_t bytes);
};
#endif