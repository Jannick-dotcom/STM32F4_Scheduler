#ifndef signalStruct_h
#define signalStruct_h

#include <stdint.h>

template <typename valueTemplate>
struct CAN_Signal
{
    valueTemplate value;
    uint8_t countOfBits;
    uint16_t startbit;
};

#endif