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
public:
    volatile valueTemplate value;
    const uint8_t countOfBits;
    const uint16_t startbit;
    const uint8_t rowcount;
    const uint8_t isMotorola;
    CAN_Signal(valueTemplate val, uint8_t bitcount, uint16_t start, uint8_t row, uint8_t isMoto) : countOfBits(bitcount), startbit(start), rowcount(row), isMotorola(isMoto)
    {
        value = val;
        // countOfBits = bitcount;
        // startbit = start;
    }
    uint64_t build()
    {
        return (uint64_t)((uint64_t)value & (((uint64_t)1 << (uint64_t)countOfBits) - 1)) << (uint64_t)startbit;
    }
    void unbuild(const uint64_t Val)
    {
        value = ((Val & (~(((uint64_t)1 << startbit)-1))) & ((((uint64_t)1 << countOfBits)-1) << (uint64_t)startbit)) >> (uint64_t)startbit;
        if(isMotorola && countOfBits > 8)
        {
            uint8_t *arr = (uint8_t*)&value;
            valueTemplate temp = 0;
            for(uint8_t i = countOfBits/8; i > 0; i--)
            {
                temp |= arr[i-1] << (i * 8);
            }
            value = temp;
        }
    }
    CAN_Signal operator=(valueTemplate val)
    {
        value = val;
        return *this;
    }
};

#endif