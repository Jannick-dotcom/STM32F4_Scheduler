#ifndef StallardOSCAN_h
#define StallardOSCAN_h
// #include <typeinfo>
#include "StallardOSconfig.h"
#include "StallardOSGPIO.hpp"
#include "StallardOSsem.hpp"

#include "StallardOScanIDs.h"
#include "StallardOScanTypes.hpp"
#include "StallardOScanStructs.hpp"


extern "C" void StallardOSGeneralFaultHandler();

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
    AD_CAN_STRUCT adCan;
    MS_CAN_STRUCT msCAN;

    // void init(CANports port, CANBauds baud);
    void receiveMessage_FIFO();
    bool translateToStruct(StallardOSCanMessage *msg);

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
    bool receiveMessage(StallardOSCanMessage *msg, uint16_t id);

    /**
    * send a can message.
    *
    * @param msg message to send
    * @param size amount of Data Bytes. Maximum is 8
    */
    void sendMessage(StallardOSCanMessage *msg, uint8_t size);

    void sendMessage(StallardOSCanMessage *msg);

};

#endif