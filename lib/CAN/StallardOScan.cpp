#include "StallardOScan.hpp"

StallardOSCanMessage STallardOS_CAN_messages[CAN_FIFO_size];

StallardOSCAN::StallardOSCAN(CANports port, CANBauds baud)
{
    if (port == StallardOSCAN1)
    {
        CANR = new StallardOSGPIO(CAN1_r_pin, PORTB, Output);
        CANT = new StallardOSGPIO(CAN1_t_pin, PORTB, Output);
        canhandle.Instance = CAN1;
    }
    else if (port == StallardOSCAN2)
    {
        CANR = new StallardOSGPIO(CAN2_r_pin, PORTB, Output);
        CANT = new StallardOSGPIO(CAN2_t_pin, PORTB, Output);
        canhandle.Instance = CAN2;
    }

    canhandle.Init.Prescaler = 5; //////////////////////////////////!!!!
    canhandle.Init.Mode = CAN_MODE_NORMAL;
    canhandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
    canhandle.Init.TimeSeg1 = CAN_BS1_1TQ;
    canhandle.Init.TimeSeg2 = CAN_BS2_1TQ;
    canhandle.Init.TimeTriggeredMode = DISABLE;
    canhandle.Init.AutoBusOff = DISABLE;
    canhandle.Init.AutoWakeUp = DISABLE;
    canhandle.Init.AutoRetransmission = DISABLE;
    canhandle.Init.ReceiveFifoLocked = DISABLE;
    canhandle.Init.TransmitFifoPriority = DISABLE;

    if (HAL_CAN_Init(&canhandle) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }
    if (HAL_CAN_Start(&canhandle) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }

    TxHeader.StdId = 0x321;
    TxHeader.ExtId = 0x01;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = 4;
    TxHeader.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_ActivateNotification(&canhandle, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        /* Notification Error */
        StallardOSGeneralFaultHandler();
    }
    HAL_CAN_Start(&canhandle);
}

bool StallardOSCAN::receiveMessage(StallardOSCanMessage *msg, uint8_t id)
{
    // return StallardOSCAN::getMessage(msg, id, this->interface);
    /* Get RX message */
    for(uint8_t i = 0; i < CAN_FIFO_size; i++)
    {
        if(STallardOS_CAN_messages[i].isread == 0 && interface == STallardOS_CAN_messages[i].interface)
        {
            if(id == STallardOS_CAN_messages[i].ID)
            {
                msg = &(STallardOS_CAN_messages[i]);
                return true;
            }
        }
    }
    msg = nullptr;
    return false;
}

void StallardOSCAN::sendMessage(StallardOSCanMessage *msg)
{
    HAL_CAN_AddTxMessage(&canhandle, &TxHeader, &(msg->Val), (uint32_t*)CAN_TX_MAILBOX0);
    return;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxhead;
    
    for(uint8_t i = 0; i < CAN_FIFO_size; i++)
    {
        if(STallardOS_CAN_messages[i].isread == 1)
        {
            HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxhead, &(STallardOS_CAN_messages[i].Val));
            STallardOS_CAN_messages[i].ID = rxhead.StdId;
            STallardOS_CAN_messages[i].interface = (hcan->Instance == CAN1 ? StallardOSCAN1 : StallardOSCAN2);
            STallardOS_CAN_messages[i].isread = 0;
            return;
        }
    }
    //Wenn wir hier angelangen haben wir eine Nachricht verloren, weil FIFO voll!!
    for(uint8_t i = 0; i < CAN_FIFO_size; i++)
    {
        STallardOS_CAN_messages[i].isread = 1;  //Alle Nachrichten "löschen"
    }
}