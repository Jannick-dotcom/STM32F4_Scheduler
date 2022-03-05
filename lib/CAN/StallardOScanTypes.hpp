#ifndef StallardOScanTypes_hpp
#define StallardOScanTypes_hpp

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
    uint8_t dlc = 0;
    uint16_t ID = 0;         //Just 11 Bit !!!!
    volatile uint64_t Val = 0;            //Up to 8 Bytes
};

template <typename valueTemplate>
struct CAN_Signal
{
    const uint8_t countOfBits;
    const uint16_t startbit;
    const uint8_t rowcount;
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
        rawValue = (physValue - offset) / factor;
        uint64_t val = (uint64_t)((uint64_t)rawValue & (((uint64_t)1 << (uint64_t)countOfBits) - 1));
        if(isMotorola && countOfBits > 8)
        {
            uint64_t tempVal = val;
            uint64_t tempOut = 0;
            for(uint8_t i = 0; i < countOfBits/8; i++)
            {
                tempOut |= (tempVal & (0xFF)) << (((countOfBits/8)-i-1) * 8);
                tempVal = tempVal >> 8;
            }
            return tempOut << (uint64_t)startbit;
        }
        else
        {
            return val << (uint64_t)startbit;
        }
    }
    void unbuild(const uint64_t Val)
    {
        rawValue = ((Val & (~(((uint64_t)1 << startbit)-1))) & ((((uint64_t)1 << countOfBits)-1) << (uint64_t)startbit)) >> (uint64_t)startbit;
        if(isMotorola && countOfBits > 8)
        {
            uint64_t tempVal = rawValue;
            uint64_t tempOut = 0;
            for(uint8_t i = 0; i < countOfBits/8; i++)
            {
                tempOut |= (tempVal & (0xFF)) << (((countOfBits/8)-i-1) * 8);
                tempVal = tempVal >> 8;
            }
            rawValue = tempOut;
        }
        physValue = rawValue * factor + offset;
    }
    CAN_Signal operator=(float val)
    {
        physValue = val;
        return *this;
    }
    operator int() const { return rawValue; }
    operator float() const { return physValue; }
};

#endif