#include "StallardOSHelpers.h"
#include "StallardOScanTypes.hpp"

#ifdef STM32F4xxxx
uint8_t portsToAF(CANports port)
{
    switch (port)
    {
    case CANports::StallardOSCAN1:
        return GPIO_AF9_CAN1;
        break;
    case CANports::StallardOSCAN2:
        return GPIO_AF9_CAN2;
        break;
    default:
        return -1;
        break;
    }
}
#elif defined(STM32F1xxxx)
uint8_t portsToAF(CANports port)
{
    switch (port)
    {
    case CANports::StallardOSCAN1:
        return GPIO_MODE_AF_PP;
        break;
    case CANports::StallardOSCAN2:
        return GPIO_MODE_AF_PP;
        break;
    default:
        return -1;
        break;
    }
}
#endif