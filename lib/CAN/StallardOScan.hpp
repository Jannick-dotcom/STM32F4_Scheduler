#ifndef StallardOSCAN_h
#define StallardOSCAN_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

#include "StallardOSGPIO.hpp"

#define CAN1_t_pin 1////////////////////!!!!
#define CAN1_r_pin 1
#define CAN2_t_pin 1
#define CAN2_r_pin 1

typedef struct{
    uint8_t ID;
    uint8_t Val;
} StallardOSCanMessage;

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

class StallardOSCAN
{
private:
    CAN_HandleTypeDef canhandle;
    CAN_TxHeaderTypeDef TxHeader;
    CAN_RxHeaderTypeDef RxHeader;
    StallardOSGPIO *CANT;
    StallardOSGPIO *CANR;

    StallardOSCanMessage messages[20];

    void setMessage(StallardOSCanMessage msg);
public:
    StallardOSCAN(
        /*Portname*/ CANports port,
        /*CANPortnumber*/ CANBauds baud);

    bool getMessage(StallardOSCanMessage *msg, uint8_t id);
    void sendMessage(StallardOSCanMessage *msg);
};

#endif