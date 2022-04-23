#ifndef StallardOSCAN_h
#define StallardOSCAN_h
#include "StallardOSGPIO.hpp"
#include "StallardOSsem.hpp"

#include "StallardOScanIDs.h"
#include "StallardOScanTypes.hpp"
#include "StallardOScanStructs.hpp"
#include "StallardOSCANFilter.hpp"
#include "StallardOSHelpers.h"
#include "StallardOSTime.h"

extern StallardOSCanMessage *canarray[];
extern uint16_t idToOffset(uint16_t id);
extern void copyToBuffer(const StallardOSCanMessage *msg);

extern "C" void StallardOSGeneralFaultHandler();

uint8_t portsToAF(CANports port);

class StallardOSCAN
{
private:
    CAN_HandleTypeDef canhandle;
    CANports interface;
    CAN_TxHeaderTypeDef TxHeader;
    
    StallardOSGPIO CANT;
    StallardOSGPIO CANR;
    StallardOSSemaphore sem;
    volatile static StallardOSCanMessage StallardOSCanFifo1[CAN_FIFO_size];
    volatile static StallardOSCanMessage StallardOSCanFifo2[CAN_FIFO_size];

    static bool can1used;
    static bool can2used;

    // friend void CAN1_RX0_IRQHandler();
    // friend void CAN1_RX1_IRQHandler();
    // friend void CAN2_RX0_IRQHandler();
    // friend void CAN2_RX1_IRQHandler();

public:
    static CAN_HandleTypeDef can1handle;
    static CAN_HandleTypeDef can2handle;
    static void receiveMessage_FIFO(CAN_HandleTypeDef *canhandle);

    /**
    * create a CAN interface.
    *
    * @param[in] port which CAN port to use
    * @param[in] baud Baud rate of the CAN. Has to be same on all devices
    * @return true if a message is received, false otherwise
    */
    StallardOSCAN(gpio tx, gpio rx, CANports port, CANBauds baud, bool debug = false);

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
    bool receiveMessage(StallardOSCanMessage *msg);

    /**
    * receive a can message from an alternate software buffer.
    * after reading the message persists -> only one bufferspace per message
    *
    * @param[in,out] msg the message container to be filled
    * @return true if a message is received, false otherwise
    */
    bool receiveMessageOneMsgBuff(StallardOSCanMessage *msg);

    /**
    * send a can message.
    *
    * @param msg message to send
    * @param size amount of Data Bytes. Maximum is 8
    */
    int sendMessage(StallardOSCanMessage *msg, uint8_t size);

    /**
    * send a can message.
    *
    * @param msg message to send, should be a struct from StallardOScanStructs.h !
    */
    int sendMessage(StallardOSCanMessage *msg);

};

#ifdef STM32F417xx
extern StallardOSCAN MS4_CAN;
extern StallardOSCAN AD_CAN;
#define AD_CAN_PORT StallardOSCAN1
#define MS4_CAN_PORT StallardOSCAN2
#endif
#ifdef STM32F415xx
extern StallardOSCAN AD_CAN;
#define AD_CAN_PORT StallardOSCAN2
#endif
#ifdef STM32F407xx
extern StallardOSCAN MS4_CAN;
extern StallardOSCAN AD_CAN;
#define AD_CAN_PORT StallardOSCAN1
#define MS4_CAN_PORT StallardOSCAN2
#endif
#ifdef STM32F446xx
extern StallardOSCAN MS4_CAN;
extern StallardOSCAN AD_CAN;
#define AD_CAN_PORT StallardOSCAN1
#define MS4_CAN_PORT StallardOSCAN2
#endif
#ifdef STM32F1xxxx
extern StallardOSCAN AD_CAN;
#define AD_CAN_PORT StallardOSCAN1
#endif
#endif