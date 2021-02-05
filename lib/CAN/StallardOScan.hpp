#ifndef StallardOSCAN_h
#define StallardOSCAN_h

#include "StallardOSconfig.h"
#include "StallardOSGPIO.hpp"

extern "C" void StallardOSGeneralFaultHandler();

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

typedef struct
{
    uint8_t used = 0;
    uint64_t timestamp = -1; //Set Timestamp to maximum
    uint16_t ID = 0; //Just 11 Bit !!!!
    uint8_t *Val; //Up to 8 Bytes
} StallardOSCanMessage;

class StallardOSCAN
{
private:
    CAN_HandleTypeDef canhandle;
    CANports interface;
    CAN_TxHeaderTypeDef TxHeader;
    CAN_RxHeaderTypeDef RxHeader;
    StallardOSGPIO CANT;
    StallardOSGPIO CANR;
    
    StallardOSCanMessage StallardOSCanFifo[CAN_FIFO_size];
    
    // void init(CANports port, CANBauds baud);

public:

    StallardOSCAN(
        /*Portname*/ CANports port,
        /*CANPortnumber*/ CANBauds baud);
    ~StallardOSCAN();

    void receiveMessage_FIFO();
    bool receiveMessage(StallardOSCanMessage *msg, uint8_t id);
    void sendMessage(StallardOSCanMessage *msg, uint8_t size);
};

#endif