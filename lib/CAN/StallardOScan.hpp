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
    CANports interface;
    uint8_t ID = 0;
    uint8_t Val = 0;
    uint8_t isread = 1;
} StallardOSCanMessage;

class StallardOSCAN
{
private:
    CAN_HandleTypeDef canhandle;
    CANports interface;
    CAN_TxHeaderTypeDef TxHeader;
    CAN_RxHeaderTypeDef RxHeader;
    StallardOSGPIO *CANT;
    StallardOSGPIO *CANR;

    // void setMessage(StallardOSCanMessage msg);
    static bool getMessage(StallardOSCanMessage *msg, uint8_t id, CANports interface);

public:

    StallardOSCAN(
        /*Portname*/ CANports port,
        /*CANPortnumber*/ CANBauds baud);

    bool receiveMessage(StallardOSCanMessage *msg, uint8_t id);
    void sendMessage(StallardOSCanMessage *msg);
};

#endif