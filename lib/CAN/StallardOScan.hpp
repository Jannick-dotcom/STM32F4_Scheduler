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

    static bool can1used;
    static bool can2used;

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
    
    /**
     *  Destroy a CAN interface
     */
    ~StallardOSCAN();

    /**
    * check the usage of the Software FiFo
    *
    * @return amount of Messages in the FiFo
    */
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
    * receive a can message.
    *
    * @param[in,out] msg the message container to be filled
    * @return true if a message is received, false otherwise
    */
    bool receiveMessage(StallardOSCanMessage *msg)
    {
        if (receiveMessage(msg, msg->ID))
        {
            return true;
        }
        return false;
    }

    /**
    * send a can message.
    *
    * @param msg message to send
    * @param size amount of Data Bytes. Maximum is 8
    */
    void sendMessage(StallardOSCanMessage *msg, uint8_t size);

    /**
    * send a can message.
    *
    * @param msg message to send, should be a struct from StallardOScanStructs.h !
    */
    void sendMessage(StallardOSCanMessage *msg);

};

#endif