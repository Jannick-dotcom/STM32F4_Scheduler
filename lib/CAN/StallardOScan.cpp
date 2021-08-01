#include "StallardOScan.hpp"

extern "C" volatile uint64_t usCurrentTimeSinceStart; //about 585 000 years of microsecond counting

bool StallardOSCAN::can1used = false;
bool StallardOSCAN::can2used = false;

volatile StallardOSCanMessage StallardOSCAN::StallardOSCanFifo1[CAN_FIFO_size];
volatile StallardOSCanMessage StallardOSCAN::StallardOSCanFifo2[CAN_FIFO_size];

CAN_HandleTypeDef StallardOSCAN::can1handle;
CAN_HandleTypeDef StallardOSCAN::can2handle;

StallardOSCAN::StallardOSCAN(CANports port, CANBauds baud)
{
#ifdef contextSwitch
    this->sem.take();
#endif
#ifdef STM32F417xx
    if (port == StallardOSCAN1 && can1used == false)
    {
        CANR = StallardOSGPIO(CAN1_r_pin, CAN1_r_port, AFPP, nopull, GPIO_AF9_CAN1);
        CANT = StallardOSGPIO(CAN1_t_pin, CAN1_t_port, AFPP, nopull, GPIO_AF9_CAN1);
        canhandle.Instance = CAN1;
        __CAN1_CLK_ENABLE();
        can1used = true;
    }
    else
#endif
    if (port == StallardOSCAN2 && can2used == false)
    {
        CANR = StallardOSGPIO(CAN2_r_pin, CAN2_r_port, AFPP, nopull, GPIO_AF9_CAN2);
        CANT = StallardOSGPIO(CAN2_t_pin, CAN2_t_port, AFPP, nopull, GPIO_AF9_CAN2);
        canhandle.Instance = CAN2;
        __CAN1_CLK_ENABLE();
        __CAN2_CLK_ENABLE();
        can2used = true;
    }
    else //Already initialized
    {
#ifdef contextSwitch
        this->sem.give(); //release Semaphore
#endif
        return;
    }
    if (baud == CANBauds::CAN1M)
    {
        canhandle.Init.Prescaler = 3;          //3?
        canhandle.Init.TimeSeg1 = CAN_BS1_4TQ; //Sample Point 87.5%
        canhandle.Init.TimeSeg2 = CAN_BS2_2TQ;
    }
    else if (baud == CANBauds::CAN500k)
    {
        canhandle.Init.Prescaler = 6;          //6?
        canhandle.Init.TimeSeg1 = CAN_BS1_4TQ; //Sample Point 87.5%
        canhandle.Init.TimeSeg2 = CAN_BS2_2TQ;
    }

#ifdef CAN_debug
    canhandle.Init.Mode = CAN_MODE_LOOPBACK; //For Debugging -> the CAN sends message to itself
#else
    canhandle.Init.Mode = CAN_MODE_NORMAL; //Real CAN Networking
#endif
    canhandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
    canhandle.Init.TimeTriggeredMode = DISABLE;
    canhandle.Init.AutoBusOff = DISABLE;
    canhandle.Init.AutoWakeUp = DISABLE;
    canhandle.Init.AutoRetransmission = ENABLE;
    canhandle.Init.ReceiveFifoLocked = DISABLE;
    canhandle.Init.TransmitFifoPriority = DISABLE;

    if (HAL_CAN_Init(&canhandle) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give(); //release Semaphore
#endif
        StallardOSGeneralFaultHandler();
    }

    if (port == StallardOSCAN1)
    {
        can1handle = canhandle;
    }
    else
    {
        can2handle = canhandle;
    }

    if (HAL_CAN_Start(&canhandle) != HAL_OK)
    {
#ifdef contextSwitch
        this->sem.give(); //release Semaphore
#endif
        StallardOSGeneralFaultHandler();
    }

    NVIC_SetPriority(CAN1_RX0_IRQn, 0xFF);
    NVIC_SetPriority(CAN1_RX1_IRQn, 0xFF);
    NVIC_SetPriority(CAN2_RX0_IRQn, 0xFF);
    NVIC_SetPriority(CAN2_RX1_IRQn, 0xFF);
    if (HAL_CAN_ActivateNotification(&canhandle, CAN_IT_RX_FIFO0_FULL) != HAL_OK)
    {
        /* Notification Error */
        asm("bkpt");
    }
    if (HAL_CAN_ActivateNotification(&canhandle, CAN_IT_RX_FIFO1_FULL) != HAL_OK)
    {
        /* Notification Error */
        asm("bkpt");
    }
    HAL_NVIC_ClearPendingIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_ClearPendingIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_ClearPendingIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_ClearPendingIRQ(CAN2_RX1_IRQn);
    NVIC_EnableIRQ(CAN1_RX0_IRQn);
    NVIC_EnableIRQ(CAN1_RX1_IRQn);
    NVIC_EnableIRQ(CAN2_RX0_IRQn);
    NVIC_EnableIRQ(CAN2_RX1_IRQn);
#ifdef contextSwitch
    this->sem.give(); //release Semaphore
#endif
}

extern "C" void CAN2_RX0_IRQHandler()
{
    StallardOSCAN::receiveMessage_FIFO(&StallardOSCAN::can2handle);
}

extern "C" void CAN2_RX1_IRQHandler()
{
    StallardOSCAN::receiveMessage_FIFO(&StallardOSCAN::can2handle);
}

extern "C" void CAN1_RX0_IRQHandler()
{
    StallardOSCAN::receiveMessage_FIFO(&StallardOSCAN::can1handle);
}

extern "C" void CAN1_RX1_IRQHandler()
{
    StallardOSCAN::receiveMessage_FIFO(&StallardOSCAN::can1handle);
}

StallardOSCAN::~StallardOSCAN() //Destructor
{
    HAL_CAN_Stop(&canhandle);
    HAL_CAN_DeInit(&canhandle); //Stop CAN interface
}

uint16_t StallardOSCAN::getSWFiFoFillLevel()
{
    uint16_t fillLevel = 0;
    volatile StallardOSCanMessage *fifoPtr;
    if(canhandle.Instance == CAN1)
        fifoPtr = StallardOSCAN::StallardOSCanFifo1;
    else if(canhandle.Instance == CAN2)
        fifoPtr = StallardOSCAN::StallardOSCanFifo2;
    else
    {
        return 0;
    }
    auto k = CAN_FIFO_size;
    for (k = 0; k < CAN_FIFO_size; k++) //Loop through whole fifo storage
    {
        if (fifoPtr[k].used)
        {
            fillLevel++;
        }
    }
    return fillLevel;
}

void StallardOSCAN::receiveMessage_FIFO(CAN_HandleTypeDef *canHand)
{
    CAN_RxHeaderTypeDef RxHeader;
    volatile StallardOSCanMessage *fifoPtr;
    if(canHand->Instance == CAN1)
        fifoPtr = StallardOSCAN::StallardOSCanFifo1;
    else if(canHand->Instance == CAN2)
        fifoPtr = StallardOSCAN::StallardOSCanFifo2;
    else
    {
        return;
    }
    auto oldestMessage = CAN_FIFO_size - 1; //initialize the oldest Message variable
    for (auto currentFifo = CAN_RX_FIFO0; currentFifo <= CAN_RX_FIFO1; currentFifo++)  //Loop through the two hardware fifos
    {
        auto messageCount = HAL_CAN_GetRxFifoFillLevel(canHand, currentFifo); //Read amount of messages in HW FiFo [0,1]
        for (auto i = uint32_t(0); i < messageCount; i++)                        //Loop through every new message in hardware FiFo
        {
            auto k = CAN_FIFO_size;
            for (k = 0; k < CAN_FIFO_size; k++) //Loop through whole fifo storage
            {
                if (fifoPtr[k].used == 0) //If unused
                {
                    if (HAL_CAN_GetRxMessage(canHand, currentFifo, &RxHeader, (uint8_t *)&fifoPtr[k].Val) == HAL_OK) //Get Message
                    {
                        fifoPtr[k].ID = RxHeader.StdId;                 //Copy to SW FiFo
                        fifoPtr[k].used = 1;                            //Indicate Message is occupied
                        fifoPtr[k].timestamp = usCurrentTimeSinceStart; //Save timestamp
                        fifoPtr[k].dlc = RxHeader.DLC;
                    }
                    break; //If unused found go with next message
                }
                else if (k == CAN_FIFO_size - 2) //FIFO full?
                {
                    //When fifo full delete the oldest message
                    if (HAL_CAN_GetRxMessage(canHand, currentFifo, &RxHeader, (uint8_t *)&fifoPtr[oldestMessage].Val) == HAL_OK) //Get Message
                    {
                        fifoPtr[oldestMessage].ID = RxHeader.StdId;                 //Delete oldest message and overwrite with new
                        fifoPtr[oldestMessage].used = 1;                            //Indicate still used
                        fifoPtr[oldestMessage].timestamp = usCurrentTimeSinceStart; //save new Timestamp
                        fifoPtr[oldestMessage].dlc = RxHeader.DLC;
                    }
                    break; //If unused found go with next message
                }
                else //If used and fifo not full
                {
                    if (fifoPtr[oldestMessage].timestamp > fifoPtr[k].timestamp) //When oldest message newer than this one
                    {
                        oldestMessage = k; //Set this to the new oldest message
                    }
                }
            }
        }
    }
}

bool StallardOSCAN::receiveMessage(StallardOSCanMessage *msg, uint16_t id)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    // receiveMessage_FIFO(&canhandle); //Receive the Messages from Hardware FiFo ->6 Messages total
    if (msg == nullptr) //if provided message for storing is valid
    {
#ifdef contextSwitch
        this->sem.give(); //Set the Semaphore free
#endif
        return false; //return false status
    }

    volatile StallardOSCanMessage *fifoPtr;
    if(canhandle.Instance == CAN1)
        fifoPtr = StallardOSCAN::StallardOSCanFifo1;
    else if(canhandle.Instance == CAN2)
        fifoPtr = StallardOSCAN::StallardOSCanFifo2;
    else
    {
        return false;
    }
    auto k = CAN_FIFO_size;
    for (k = 0; k < CAN_FIFO_size; k++) //Loop through whole fifo storage
    {
        if (fifoPtr[k].used && (fifoPtr[k].ID == id || id == uint16_t(-1))) //If ID of message in FiFo is same as we are looking for
        {
            // *msg = (StallardOSCanMessage)(StallardOSCAN::StallardOSCanFifo[k]);         //copy the message
            msg->dlc = fifoPtr[k].dlc;
            msg->ID = fifoPtr[k].ID;
            msg->timestamp = fifoPtr[k].timestamp;
            msg->used = fifoPtr[k].used;
            msg->Val = fifoPtr[k].Val;

            fifoPtr[k].used = 0;       //set the FiFo message to unused
            fifoPtr[k].timestamp = -1; //reset timestamp
            fifoPtr[k].dlc = 0;
#ifdef contextSwitch
            this->sem.give(); //release Semaphore
#endif
            return true; //indicate success
        }
    }
#ifdef contextSwitch
    this->sem.give(); //release semaphore
#endif
    return false; //return false status
}

int StallardOSCAN::sendMessage(StallardOSCanMessage *msg, uint8_t size)
{
    uint32_t tempTransmMailb;
#ifdef contextSwitch
    this->sem.take(); //Block the semaphore
#endif
    if (msg == nullptr || size > 8 || size == 0) //Check if the size and the message are valid
    {
#ifdef contextSwitch
        this->sem.give(); //release semaphore
#endif
        return -1;
    }
    TxHeader.StdId = msg->ID;    //copy the id
    TxHeader.RTR = CAN_RTR_DATA; //indicate Data Transmission
    TxHeader.IDE = CAN_ID_STD;   //Set Standard Identifier -> 11 bit
    TxHeader.DLC = size;         //Set Amount of Data bytes

    while (HAL_CAN_GetTxMailboxesFreeLevel(&canhandle) < 1)
        ;
    // HAL_CAN_AbortTxRequest(&canhandle,-1);         //Wait until all TX Mailboxes are free
    HAL_CAN_AddTxMessage(&canhandle, &TxHeader, (uint8_t *)&msg->Val, &tempTransmMailb); //Add message to transmit mailbox
#ifdef contextSwitch
    this->sem.give(); //release Semaphore
#endif
    return HAL_CAN_GetError(&canhandle);
}

int StallardOSCAN::sendMessage(StallardOSCanMessage *msg)
{
    return sendMessage(msg, msg->dlc);
}