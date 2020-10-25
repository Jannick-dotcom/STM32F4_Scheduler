#ifndef JannixCAN_h
#define JannixCAN_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

#include "GPIO.h"

#define CAN1_t_pin 1////////////////////!!!!
#define CAN1_r_pin 1
#define CAN2_t_pin 1
#define CAN2_r_pin 1



typedef struct{
    uint8_t ID;
    uint8_t Val;
} JannixCanMessage;

typedef enum CANports
{
    JannixCAN1 = 0,
    JannixCAN2
} CANports;

typedef enum CANBauds
{
    CAN500k = 0,
    CAN1M = 1
} CANBauds;



class JannixCAN
{
private:
    CAN_HandleTypeDef canhandle;
    CAN_TxHeaderTypeDef TxHeader;
    CAN_RxHeaderTypeDef RxHeader;
    JannixGPIO *CANT;
    JannixGPIO *CANR;
public:
    JannixCAN(
        /*Portname*/ CANports port,
        /*CANPortnumber*/ CANBauds baud);

    bool getMessage(JannixCanMessage *msg);
    void sendMessage(JannixCanMessage *msg);
};

#endif