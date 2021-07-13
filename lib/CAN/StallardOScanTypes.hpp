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
    virtual void nothing(){};
public:
    uint8_t used = 0;
    uint64_t timestamp = -1; //Set Timestamp to maximum
    uint8_t dlc = 0;
    uint16_t ID;         //Just 11 Bit !!!!
    volatile uint64_t Val;            //Up to 8 Bytes
};

template <typename valueTemplate>
struct CAN_Signal
{
private:
    
public:
    volatile valueTemplate rawValue;
    const uint8_t countOfBits;
    const uint16_t startbit;
    const uint8_t rowcount;
    const uint8_t isMotorola;
    volatile float physValue;
    
    CAN_Signal(valueTemplate val, uint8_t bitcount, uint16_t start, uint8_t row, uint8_t isMoto) : countOfBits(bitcount), startbit(start), rowcount(row), isMotorola(isMoto)
    {
        rawValue = val;
        // countOfBits = bitcount;
        // startbit = start;
    }
    uint64_t build()
    {
        uint64_t val = (uint64_t)((uint64_t)rawValue & (((uint64_t)1 << (uint64_t)countOfBits) - 1)) << (uint64_t)startbit;
        if(isMotorola && countOfBits > 8)
        {
            uint8_t *arr = (uint8_t*)&val;
            uint64_t temp = 0;
            for(uint8_t i = countOfBits/8; i > 0; i--)
            {
                temp |= (uint64_t)arr[i-1] << (((countOfBits/8)-i) * 8);
            }
            return temp;
        }
        else
        {
            return val;
        }
    }
    void unbuild(const uint64_t Val)
    {
        rawValue = ((Val & (~(((uint64_t)1 << startbit)-1))) & ((((uint64_t)1 << countOfBits)-1) << (uint64_t)startbit)) >> (uint64_t)startbit;
        if(isMotorola && countOfBits > 8)
        {
            uint8_t *arr = (uint8_t*)&rawValue;
            uint64_t temp = 0;
            for(uint8_t i = countOfBits/8; i > 0; i--)
            {
                temp |= (uint64_t)arr[i-1] << (((countOfBits/8)-i) * 8);
            }
            rawValue = temp;
        }
    }
    CAN_Signal operator=(valueTemplate val)
    {
        rawValue = val;
        return *this;
    }
};

#endif