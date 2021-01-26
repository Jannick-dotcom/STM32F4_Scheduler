#include "StallardOScan.hpp"

StallardOSCanMessage STallardOS_CAN_messages[CAN_FIFO_size];

/**
 * create a CAN instance.
 *
 * @param port which can port to use
 * @param baud which can baudrate to use
 */
void StallardOSCAN::init(CANports port, CANBauds baud)
{
    CAN_FilterTypeDef sFilterConfig;
    if (port == StallardOSCAN1)
    {
        CANR = new StallardOSGPIO(CAN1_r_pin, CAN1_r_port, AFOD, pullup, GPIO_AF9_CAN1);
        CANT = new StallardOSGPIO(CAN1_t_pin, CAN1_t_port, AFOD, pullup, GPIO_AF9_CAN1);
        canhandle.Instance = CAN1;
        __CAN1_CLK_ENABLE();
    }
    else if (port == StallardOSCAN2)
    {
        CANR = new StallardOSGPIO(CAN2_r_pin, CAN2_r_port, Output, pullup, GPIO_AF9_CAN2);
        CANT = new StallardOSGPIO(CAN2_t_pin, CAN2_t_port, Output), pullup, GPIO_AF9_CAN2;
        canhandle.Instance = CAN2;
        __CAN2_CLK_ENABLE();
    }
    if (baud == CANBauds::CAN1M)
    {
        canhandle.Init.Prescaler = 5; //////////////////////////////////!!!!
    }
    else if (baud == CANBauds::CAN500k)
    {
        canhandle.Init.Prescaler = 10; ////////////////////////////////!!!!!!
    }

    canhandle.Init.Mode = CAN_MODE_LOOPBACK; //For Debugging -> the CAN sends message to itself
    //canhandle.Init.Mode = CAN_MODE_NORMAL; //Real CAN Networking
    canhandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
    canhandle.Init.TimeSeg1 = CAN_BS1_6TQ;
    canhandle.Init.TimeSeg2 = CAN_BS2_2TQ;
    canhandle.Init.TimeTriggeredMode = DISABLE;
    canhandle.Init.AutoBusOff = DISABLE;
    canhandle.Init.AutoWakeUp = DISABLE;
    canhandle.Init.AutoRetransmission = ENABLE;
    canhandle.Init.ReceiveFifoLocked = DISABLE;
    canhandle.Init.TransmitFifoPriority = DISABLE;

    if (HAL_CAN_Init(&canhandle) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }

    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&canhandle, &sFilterConfig) != HAL_OK)
    {
        /* Filter configuration Error */
        StallardOSGeneralFaultHandler();
    }

    if (HAL_CAN_Start(&canhandle) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }

    TxHeader.StdId = 0x321; //Ids
    TxHeader.ExtId = 0x01;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = sizeof(StallardOSCanMessage::Val); //Bytezahl die zu senden ist
    TxHeader.TransmitGlobalTime = DISABLE;

    HAL_CAN_Start(&canhandle);
}

StallardOSCAN::StallardOSCAN(CANports port, CANBauds baud)
{
    init(port, baud);
}

/**
 * receive a can message.
 *
 * @param[out] msg the message container to be filled
 * @param[in] id the id of the message to receive
 * @return true if a message is received, false otherwise
 */
bool StallardOSCAN::receiveMessage(StallardOSCanMessage *msg, uint8_t id)
{
    // return StallardOSCAN::getMessage(msg, id, this->interface);
    /* Get RX message */

    if (HAL_CAN_GetRxFifoFillLevel(&canhandle, CAN_RX_FIFO0) > 0)
    {
        HAL_CAN_GetRxMessage(&canhandle, CAN_RX_FIFO0, &RxHeader, &msg->Val);
        return true;
    }
    else if (HAL_CAN_GetRxFifoFillLevel(&canhandle, CAN_RX_FIFO1) > 0)
    {
        HAL_CAN_GetRxMessage(&canhandle, CAN_RX_FIFO1, &RxHeader, &msg->Val);
        return true;
    }
    return false;
}

/**
 * send a can message.
 *
 * @param msg message to send
 */
void StallardOSCAN::sendMessage(StallardOSCanMessage *msg)
{
    HAL_CAN_AddTxMessage(&canhandle, &TxHeader, &(msg->Val), (uint32_t *)CAN_TX_MAILBOX0);
    return;
}