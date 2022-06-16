#ifndef StallardOScanTypes_hpp
#define StallardOScanTypes_hpp

#include "StallardOSHelpers.h"

typedef enum CANports
{
    StallardOSCAN1 = 0,
    StallardOSCAN2
} CANports;

typedef enum CANBauds
{
    CAN500k = 0,
    CAN1M = 1
} CANBauds;

struct StallardOSCanMessage
{
private:
    // virtual void nothing(){};
public:
    uint8_t used = 0;
    uint64_t timestamp = -1; //Set Timestamp to maximum
    uint16_t ID = 0;         //Just 11 Bit !!!!
    uint8_t persistent = 0;
    uint8_t dlc = 0;
    volatile uint64_t Val = 0;            //Up to 8 Bytes
};

template <typename valueTemplate>
struct CAN_Signal
{
    const uint8_t countOfBits;
private:
    const uint16_t startbit;
public:
    const uint8_t rowcount;
private:
    const uint8_t isMotorola;
    const float factor;
    const float offset;

    volatile valueTemplate rawValue;
public:
    volatile float physValue;
    
    CAN_Signal(valueTemplate val, uint8_t bitcount, uint16_t start, uint8_t row, uint8_t isMoto, float factor, float offset) : 
    countOfBits(bitcount), 
    startbit(start), 
    rowcount(row), 
    isMotorola(isMoto),
    factor(factor),
    offset(offset)
    {
        rawValue = val;
    }
    uint64_t build()
    {
        const uint64_t mask = (((uint64_t)1 << (uint64_t)countOfBits) - 1);
        rawValue = (physValue - offset) / factor;

        if(isMotorola){
            if(countOfBits > 8 && countOfBits <= 16){
                rawValue = __builtin_bswap16(rawValue);    
            }
            else if(countOfBits > 8 && countOfBits <= 32){
                rawValue = __builtin_bswap32(rawValue);
            }
            else if(countOfBits > 8){
                rawValue = __builtin_bswap64(rawValue);
            }

            uint64_t val = (uint64_t)rawValue & mask;  // required in case of overflow
            return val << (uint64_t)(startbit-7);
        }
        else{
            uint64_t val = (uint64_t)rawValue & mask;  // required in case of overflow
            return val << (uint64_t)startbit;
        }
    }
    void unbuild(const uint64_t Val)
    {
        if(isMotorola)
        {   
            const uint64_t signal_mask = (((uint64_t)1 << countOfBits)-1) << (startbit-7);
            rawValue = (Val&signal_mask) >> (startbit-7);

            if(countOfBits > 8 && countOfBits <= 16){
                rawValue = __builtin_bswap16(rawValue);    
            }
            else if(countOfBits > 8 && countOfBits <= 32){
                rawValue = __builtin_bswap32(rawValue);
            }
            else if(countOfBits > 8){
                rawValue = __builtin_bswap64(rawValue);
            }
        }
        else{
            const uint64_t signal_mask = ((((uint64_t)1 << countOfBits)-1) << (uint64_t)startbit);
            rawValue = (Val&signal_mask) >> startbit;
        }

        physValue = (rawValue * factor) + offset;
    }
    CAN_Signal operator=(float val)
    {
        physValue = val;
        return *this;
    }
    operator int() const { return physValue; }
    operator float() const { return physValue; }
    

    bool operator!=(struct CAN_Signal &ref) { return this->rawValue != ref.rawValue;}; //Comparison
    bool operator==(struct CAN_Signal &ref) { return this->rawValue == ref.rawValue;};
    bool operator>=(struct CAN_Signal &ref) { return this->rawValue >= ref.rawValue;}; //Comparison
    bool operator<=(struct CAN_Signal &ref) { return this->rawValue <= ref.rawValue;};
    bool operator<(struct CAN_Signal &ref) { return this->rawValue < ref.rawValue;}; //Comparison
    bool operator>(struct CAN_Signal &ref) { return this->rawValue > ref.rawValue;};
};

#endif