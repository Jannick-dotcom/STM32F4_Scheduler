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
    uint64_t Val;            //Up to 8 Bytes
};

template <typename valueTemplate>
struct CAN_Signal
{
public:
    valueTemplate value;
    const uint8_t countOfBits;
    const uint16_t startbit;
    CAN_Signal(valueTemplate val, uint8_t bitcount, uint16_t start) : countOfBits(bitcount), startbit(start)
    {
        value = val;
        // countOfBits = bitcount;
        // startbit = start;
    }
    uint64_t build()
    {
        return (value & prepareMask()) << startbit;
    }
    uint64_t prepareMask()
    {
        uint8_t mask = 0;
        for(uint8_t i = 0; i < countOfBits; i++)
        {
            mask = (mask << 1) | 1;
        }
        return mask;
    }
    CAN_Signal operator=(valueTemplate val)
    {
        value = val;
        return *this;
    }
};

#endif