#include "StallardOScan.hpp"

//StallardOSCanMessage STallardOS_CAN_messages[CAN_FIFO_size];
extern "C" volatile uint64_t msCurrentTimeSinceStart;

/**
 * crete a CAN interface.
 *
 * @param[in] port which CAN port to use
 * @param[in] baud Baud rate of the CAN. Has to be same on all devices
 * @return true if a message is received, false otherwise
 */
StallardOSCAN::StallardOSCAN(CANports port, CANBauds baud)
{
    this->sem.take();
    CAN_FilterTypeDef sFilterConfig;
    if (port == StallardOSCAN1)
    {
        CANR = StallardOSGPIO(CAN1_r_pin, CAN1_r_port, AFOD, pullup, GPIO_AF9_CAN1);
        CANT = StallardOSGPIO(CAN1_t_pin, CAN1_t_port, AFOD, pullup, GPIO_AF9_CAN1);
        canhandle.Instance = CAN1;
        __CAN1_CLK_ENABLE();
    }
    else if (port == StallardOSCAN2)
    {
        CANR = StallardOSGPIO(CAN2_r_pin, CAN2_r_port, AFOD, pullup, GPIO_AF9_CAN2);
        CANT = StallardOSGPIO(CAN2_t_pin, CAN2_t_port, AFOD, pullup, GPIO_AF9_CAN2);
        canhandle.Instance = CAN2;
        __CAN2_CLK_ENABLE();
    }
    if (baud == CANBauds::CAN1M)
    {
        canhandle.Init.Prescaler = 21;
    }
    else if (baud == CANBauds::CAN500k)
    {
        canhandle.Init.Prescaler = 42;
    }

    canhandle.Init.Mode = CAN_MODE_LOOPBACK; //For Debugging -> the CAN sends message to itself
    //canhandle.Init.Mode = CAN_MODE_NORMAL; //Real CAN Networking
    canhandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
    canhandle.Init.TimeSeg1 = CAN_BS1_6TQ; //Sample Point 87.5%
    canhandle.Init.TimeSeg2 = CAN_BS2_2TQ;
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

    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000 << 5;//When MSB low let it pass
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0400 << 5; //Just check msb
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;
    if (HAL_CAN_ConfigFilter(&canhandle, &sFilterConfig) != HAL_OK)
    {
        /* Filter configuration Error */
        StallardOSGeneralFaultHandler();
    }
    sFilterConfig.FilterBank = 1;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0400 << 5; //When MSB high let it pass
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0400 << 5; // Just check MSB
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
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
    TxHeader.ExtId = 0x01;  //Not used
    TxHeader.RTR = CAN_RTR_DATA;//Data Transmission
    TxHeader.IDE = CAN_ID_STD;//Standard Identifier -> 11 bit
    TxHeader.DLC = sizeof(StallardOSCanMessage::Val); //Bytezahl die zu senden ist
    TxHeader.TransmitGlobalTime = DISABLE;  //No Idea what this means
    this->sem.give();   //release Semaphore
}

StallardOSCAN::~StallardOSCAN() //Destructor
{
    HAL_CAN_Stop(&canhandle);
    HAL_CAN_DeInit(&canhandle); //Stop CAN interface
    // delete this->CANR;
    // delete this->CANT;
}

void StallardOSCAN::receiveMessage_FIFO()
{
    this->sem.take();   //Block Semaphore
    auto oldestMessage = sizeof(StallardOSCanFifo) / sizeof(StallardOSCanMessage) - 1;  //initialize the oldest Message variable
    for (auto currentFifo = CAN_RX_FIFO0; currentFifo <= CAN_RX_FIFO1; currentFifo++) //Loop through the two hardware fifos
    {
        auto messageCount = HAL_CAN_GetRxFifoFillLevel(&canhandle, currentFifo);    //Read amount of messages in HW FiFo [0,1]
        for (auto i = 0; i < messageCount; i++)                             //Loop through every new message in hardware FiFo
        {
            for (auto k = 0; k < sizeof(StallardOSCanFifo) / sizeof(StallardOSCanMessage); k++) //Loop through whole fifo storage
            {
                if (StallardOSCanFifo[k].used == 0) //If unused
                {
                    if (HAL_CAN_GetRxMessage(&canhandle, currentFifo, &RxHeader, StallardOSCanFifo[k].Val) == HAL_OK) //Get Message
                    {
                        //What do i do here??????
                        // if(!(RxHeader.StdId & 0x400) && currentFifo == 1)
                        // {
                        //     volatile int k = 0;
                        // }
                        StallardOSCanFifo[k].ID = RxHeader.StdId;//Copy to SW FiFo
                        StallardOSCanFifo[k].used = 1;              //Indicate Message is occupied
                        StallardOSCanFifo[k].timestamp = msCurrentTimeSinceStart;   //Save timestamp
                    }
                    break;  //If unused found go with next message
                }
                else if(k == sizeof(StallardOSCanFifo) / sizeof(StallardOSCanMessage) - 2) //FIFO full?
                {
                    //TODO: Find a way around the stopping of fifo filling
                    //When fifo full delete everything or the oldest message
                    if (HAL_CAN_GetRxMessage(&canhandle, currentFifo, &RxHeader, StallardOSCanFifo[oldestMessage].Val) == HAL_OK) //Get Message
                    {
                        StallardOSCanFifo[oldestMessage].ID = RxHeader.StdId;   //Delete oldest message and overwrite with new
                        StallardOSCanFifo[oldestMessage].used = 1;              //Indicate still used
                        StallardOSCanFifo[oldestMessage].timestamp = msCurrentTimeSinceStart;//save new Timestamp
                    }
                    break;  //If unused found go with next message
                }
                else    //If used and fifo not full
                {
                    if(StallardOSCanFifo[oldestMessage].timestamp > StallardOSCanFifo[k].timestamp) //When oldest message newer than this one
                    {
                        oldestMessage = k;  //Set this to the new oldest message
                    }
                }
            }
        }
    }
    this->sem.give(); //release Semaphore
}


/**
 * receive a can message.
 *0
 * @param[out] msg the message container to be filled
 * @param[in] id the id of the message to receive
 * @return true if a message is received, false otherwise
 */
bool StallardOSCAN::receiveMessage(StallardOSCanMessage *msg, uint8_t id)
{
    this->sem.take();
    receiveMessage_FIFO(); //Receive the Messages from Hardware FiFo ->6 Messages total
    if (msg == nullptr) //if provided message for storing is valid
    {
        this->sem.give();   //Set the Semaphore free
        return false;   //return false status
    }
    for (auto k = 0; k < sizeof(StallardOSCanFifo) / sizeof(StallardOSCanMessage); k++) //Loop through whole fifo storage
    {
        if (StallardOSCanFifo[k].used && StallardOSCanFifo[k].ID == id) //If ID of message in FiFo is same as we are looking for
        {
            *msg = StallardOSCanFifo[k];    //copy the message
            StallardOSCanFifo[k].used = 0;  //set the FiFo message to unused
            StallardOSCanFifo[k].timestamp = -1;    //reset timestamp
            this->sem.give();   //release Semaphore
            return true;    //indicate success
        }
    }
    this->sem.give();   //release semaphore
    return false;       //return false status
}

/**
 * send a can message.
 *
 * @param msg message to send
 * @param size amount of Data Bytes. Maximum is 4
 */
void StallardOSCAN::sendMessage(StallardOSCanMessage *msg, uint8_t size)
{
    this->sem.take();   //Block the semaphore
    if(msg != nullptr && size > 4)        //Check if the size and the message are valid
    {
        this->sem.give();   //release semaphore
        return;
    }
    TxHeader.StdId = msg->ID;   //copy the id
    TxHeader.RTR = CAN_RTR_DATA;//indicate Data Transmission
    TxHeader.IDE = CAN_ID_STD;  //Set Standard Identifier -> 11 bit
    TxHeader.DLC = size;        //Set Amount of Data bytes

    while (HAL_CAN_GetTxMailboxesFreeLevel(&canhandle) < 3); //Wait until all TX Mailboxes are free
    HAL_CAN_AddTxMessage(&canhandle, &TxHeader, msg->Val, (uint32_t *)CAN_TX_MAILBOX0); //Add message to transmit mailbox
    this->sem.give();   //release Semaphore
    return;
}