#ifndef StallardOSCAN_h
#define StallardOSCAN_h

#include "StallardOSconfig.h"
#include "StallardOSGPIO.hpp"
#include "StallardOSsem.hpp"
#include "StallardOScan-IDs.h"

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
    uint16_t ID = 0;         //Just 11 Bit !!!!
    uint8_t *Val;            //Up to 8 Bytes
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
    StallardOSSemaphore sem;
    StallardOSCanMessage StallardOSCanFifo[CAN_FIFO_size];

    // void init(CANports port, CANBauds baud);
    void receiveMessage_FIFO();

public:
    /**
    * create a CAN interface.
    *
    * @param[in] port which CAN port to use
    * @param[in] baud Baud rate of the CAN. Has to be same on all devices
    * @return true if a message is received, false otherwise
    */
    StallardOSCAN(
        /*Portname*/ CANports port,
        /*CANPortnumber*/ CANBauds baud);
    ~StallardOSCAN();
    uint16_t getSWFiFoFillLevel();

    /**
    * receive a can message.
    *
    * @param[out] msg the message container to be filled
    * @param[in] id the id of the message to receive
    * @return true if a message is received, false otherwise
    */
    bool receiveMessage(StallardOSCanMessage *msg, uint8_t id);

    /**
    * send a can message.
    *
    * @param msg message to send
    * @param size amount of Data Bytes. Maximum is 4
    */
    void sendMessage(StallardOSCanMessage *msg, uint8_t size);
};

#endif