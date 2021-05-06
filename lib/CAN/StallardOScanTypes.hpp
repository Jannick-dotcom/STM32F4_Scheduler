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
// private:
//     virtual void nothing(){};
public:
    uint8_t used = 0;
    uint64_t timestamp = -1; //Set Timestamp to maximum
    uint8_t dlc = 0;
    uint16_t ID = 0;         //Just 11 Bit !!!!
    uint8_t Val[8];            //Up to 8 Bytes
};

template <typename valueTemplate>
struct CAN_Signal //: private StallardOSCanMessage
{
public:
    valueTemplate value;
    uint8_t countOfBits;
    uint16_t startbit;
    CAN_Signal(valueTemplate val, uint8_t bitcount, uint16_t start)
    {
        value = val;
        countOfBits = bitcount;
        startbit = start;
    }
    uint64_t build()
    {
        return value << startbit;
        // return (value<<startbit)|((1<<startbit)-1);
    }
    CAN_Signal operator=(valueTemplate val)
    {
        value = val;
        return *this;
    }
};

#endif