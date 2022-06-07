#include "StallardOScan.hpp"

// GPIO/AFIO Regs
constexpr static uint32_t afioBase = 0x40010000UL;
constexpr static uint32_t mapr = afioBase + 0x004; // alternate pin function mapping

constexpr static uint32_t gpioABase = 0x40010800UL; // port A
constexpr static uint32_t crhA = gpioABase + 0x004; // cntrl reg for port b
constexpr static uint32_t odrA = gpioABase + 0x00c; // output data reg

constexpr static uint32_t gpioBBase = gpioABase + 0x400; // port B
constexpr static uint32_t crhB = gpioBBase + 0x004;      // cntrl reg for port b
constexpr static uint32_t odrB = gpioBBase + 0x00c;      // output data reg

// Clock
constexpr static uint32_t rcc = 0x40021000UL;
constexpr static uint32_t rccBase = 0x40021000UL;
constexpr static uint32_t apb1enr = rccBase + 0x01c;
constexpr static uint32_t apb2enr = rccBase + 0x018;

// Helpers
#define MMIO32(x) (*(volatile uint32_t *)(x))
#define MMIO16(x) (*(volatile uint16_t *)(x))
#define MMIO8(x) (*(volatile uint8_t *)(x))

static inline volatile uint32_t &periphBit(uint32_t addr, int bitNum) // peripheral bit tool
{
  return MMIO32(0x42000000 + ((addr & 0xFFFFF) << 5) + (bitNum << 2)); // uses bit band memory
}

#ifdef STM32F417xx
StallardOSCAN MS4_CAN(gpio(CAN2_t_port,CAN2_t_pin),gpio(CAN2_r_port,CAN2_r_pin),StallardOSCAN2, CAN1M);
StallardOSCAN AD_CAN(gpio(CAN1_t_port,CAN1_t_pin),gpio(CAN1_r_port,CAN1_r_pin),StallardOSCAN1, CAN500k);
#endif
#ifdef STM32F415xx
StallardOSCAN AD_CAN(gpio(CAN2_t_port,CAN2_t_pin),gpio(CAN2_r_port,CAN2_r_pin),StallardOSCAN2, CAN500k);
#endif
#ifdef STM32F407xx
StallardOSCAN MS4_CAN(gpio(CAN2_t_port,CAN2_t_pin),gpio(CAN2_r_port,CAN2_r_pin),StallardOSCAN2, CAN1M, true);
StallardOSCAN AD_CAN(gpio(CAN1_t_port,CAN1_t_pin),gpio(CAN1_r_port,CAN1_r_pin),StallardOSCAN1, CAN500k, true);
#endif
#ifdef STM32F446xx
StallardOSCAN MS4_CAN(gpio(CAN2_t_port,CAN2_t_pin),gpio(CAN2_r_port,CAN2_r_pin),StallardOSCAN2, CAN1M, true);
StallardOSCAN AD_CAN(gpio(CAN1_t_port,CAN1_t_pin),gpio(CAN1_r_port,CAN1_r_pin),StallardOSCAN1, CAN500k, true);
#endif
#ifdef STM32F1xxxx
StallardOSCAN AD_CAN(gpio(CAN1_t_port,CAN1_t_pin),gpio(CAN1_r_port,CAN1_r_pin),StallardOSCAN1, CAN500k);
#endif

bool StallardOSCAN::can1used = false;
bool StallardOSCAN::can2used = false;

volatile StallardOSCanMessage StallardOSCAN::StallardOSCanFifo1[CAN_FIFO_size];
volatile StallardOSCanMessage StallardOSCAN::StallardOSCanFifo2[CAN_FIFO_size];

CAN_HandleTypeDef StallardOSCAN::can1handle;
CAN_HandleTypeDef StallardOSCAN::can2handle;

void initFilters(CAN_HandleTypeDef *canHand)
{
    CAN_FilterTypeDef sFilterConfig;
    if(canHand->Instance == CAN1)
    {
        sFilterConfig.FilterBank = 14; // 0..13 for CAN1, 14..27 for CAN2
    }
    else
    {
        sFilterConfig.FilterBank = 0; // 0..13 for CAN1, 14..27 for CAN2
    }
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;
    HAL_CAN_ConfigFilter(canHand, &sFilterConfig);
}

StallardOSCAN::StallardOSCAN(gpio tx, gpio rx, CANports port, CANBauds baud, bool debug) :
#ifdef STM32F1xxxx
    CANT(tx.pin, tx.port, AFPP, nopull, portsToAF(port)),
    CANR(rx.pin, rx.port, Input, pullup, portsToAF(port))
#else
    CANT(tx.pin, tx.port, AFPP, nopull, portsToAF(port)),
    CANR(rx.pin, rx.port, AFPP, pullup, portsToAF(port))
#endif
{
    this->sem.take();

#ifndef STM32F415xx
    if (port == StallardOSCAN1 && can1used == false)
    {
        MMIO32(apb2enr) |= (1 << 3) | (1 << 0); // enable gpioB = b3 and afio = b0 clks
        MMIO32(mapr) |= (2 << 13);              // alt func, CAN remap to B9+B8 
        MMIO32(crhB) &= 0xFFFFFF00;             // clear control bits for pins 8 & 9 of Port B
        MMIO32(crhB) |= 0b1000;              // pin8 for rx, b0100 = b01xx, floating, bxx00 input
        periphBit(odrB, 8) = true;            // set input will pullup resistor for single wire with pullup mode
        MMIO32(crhB) |= 0b1001 << 4;            // set output
        canhandle.Instance = CAN1;
        __CAN1_CLK_ENABLE();
        can1used = true;
    }
#endif
#ifdef STM32F4xxxx
    if (port == StallardOSCAN2 && can2used == false)
    {
        canhandle.Instance = CAN2;
        __CAN1_CLK_ENABLE();
        __CAN2_CLK_ENABLE();
        can2used = true;
    }
#endif
    if(port != StallardOSCAN1 && port != StallardOSCAN2) //Already initialized
    {

        this->sem.give(); //release Semaphore

        return;
    }
    if (baud == CANBauds::CAN1M)
    {
        #ifdef STM32F4xxxx
        canhandle.Init.Prescaler = 3;
        canhandle.Init.TimeSeg1 = CAN_BS1_4TQ; //Sample Point 87.5%
        canhandle.Init.TimeSeg2 = CAN_BS2_2TQ;
        #elif defined(STM32F1xxxx)
        canhandle.Init.Prescaler = 3;
        canhandle.Init.TimeSeg1 = CAN_BS1_7TQ; //Sample Point 87.5%
        canhandle.Init.TimeSeg2 = CAN_BS2_4TQ;
        #endif
    }
    else if (baud == CANBauds::CAN500k)
    {
        #ifdef STM32F4xxxx
        canhandle.Init.Prescaler = 6;          //6?
        canhandle.Init.TimeSeg1 = CAN_BS1_4TQ; //Sample Point 87.5%
        canhandle.Init.TimeSeg2 = CAN_BS2_2TQ;
        #elif defined(STM32F1xxxx)
        canhandle.Init.Prescaler = 9;
        canhandle.Init.TimeSeg1 = CAN_BS1_5TQ; //Sample Point 87.5%
        canhandle.Init.TimeSeg2 = CAN_BS2_2TQ;
        #endif
    }

    #ifndef notHaveCan
    if(debug)
    {
        canhandle.Init.Mode = CAN_MODE_LOOPBACK; //For Debugging -> the CAN sends message to itself
    }
    else
    {
        canhandle.Init.Mode = CAN_MODE_NORMAL; //Real CAN Networking
    }
    #else
    canhandle.Init.Mode = CAN_MODE_SILENT_LOOPBACK;
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

        this->sem.give(); //release Semaphore

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
        this->sem.give(); //release Semaphore
        DEBUGGER_BREAK();
        while (1);        
        StallardOSGeneralFaultHandler();
    }

    NVIC_SetPriority(CAN1_RX0_IRQn, 0xFF);
    NVIC_SetPriority(CAN1_RX1_IRQn, 0xFF);
    #ifdef STM32F4xxxx
    NVIC_SetPriority(CAN2_RX0_IRQn, 0xFF);
    NVIC_SetPriority(CAN2_RX1_IRQn, 0xFF);
    #endif
    if (HAL_CAN_ActivateNotification(&canhandle, CAN_IT_RX_FIFO0_FULL) != HAL_OK)
    {
        /* Notification Error */
        DEBUGGER_BREAK();
    }
    if (HAL_CAN_ActivateNotification(&canhandle, CAN_IT_RX_FIFO1_FULL) != HAL_OK)
    {
        /* Notification Error */
        DEBUGGER_BREAK();
    }
    HAL_NVIC_ClearPendingIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_ClearPendingIRQ(CAN1_RX1_IRQn);
    #ifdef STM32F4xxxx
    HAL_NVIC_ClearPendingIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_ClearPendingIRQ(CAN2_RX1_IRQn);
    #endif
    NVIC_EnableIRQ(CAN1_RX0_IRQn);
    NVIC_EnableIRQ(CAN1_RX1_IRQn);
    #ifdef STM32F4xxxx
    NVIC_EnableIRQ(CAN2_RX0_IRQn);
    NVIC_EnableIRQ(CAN2_RX1_IRQn);
    #endif
    initFilters(&canhandle);
    this->sem.give(); //release Semaphore
        

}

#ifdef STM32F4xxxx
extern "C" void CAN2_RX0_IRQHandler()
{
    StallardOSCAN::receiveMessage_FIFO(&StallardOSCAN::can2handle);
}

extern "C" void CAN2_RX1_IRQHandler()
{
    StallardOSCAN::receiveMessage_FIFO(&StallardOSCAN::can2handle);
}
#endif
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
    #ifdef STM32F4xxxx
    else if(canhandle.Instance == CAN2)
        fifoPtr = StallardOSCAN::StallardOSCanFifo2;
    #endif
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
    #ifdef STM32F4xxxx
    else if(canHand->Instance == CAN2)
        fifoPtr = StallardOSCAN::StallardOSCanFifo2;
    #endif
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
                        fifoPtr[k].timestamp = StallardOSTime_getTimeUs(); //Save timestamp
                        fifoPtr[k].dlc = RxHeader.DLC;
                        StallardOSCanMessage temp;
                        temp.ID = RxHeader.StdId;
                        temp.timestamp = fifoPtr[k].timestamp;
                        temp.Val = fifoPtr[k].Val;
                        temp.used = true;
                        copyToBuffer(&temp);
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
                        fifoPtr[oldestMessage].timestamp = StallardOSTime_getTimeUs(); //save new Timestamp
                        fifoPtr[oldestMessage].dlc = RxHeader.DLC;
                        StallardOSCanMessage temp;
                        temp.ID = RxHeader.StdId;
                        temp.timestamp = fifoPtr[oldestMessage].timestamp;
                        temp.Val = fifoPtr[k].Val;
                        temp.used = true;
                        copyToBuffer(&temp);
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

    this->sem.take();

    receiveMessage_FIFO(&canhandle); //Receive the Messages from Hardware FiFo ->6 Messages total
    if (msg == nullptr) //if provided message for storing is valid
    {

        this->sem.give(); //Set the Semaphore free

        return false; //return false status
    }

    volatile StallardOSCanMessage *fifoPtr;
    if(canhandle.Instance == CAN1)
        fifoPtr = StallardOSCAN::StallardOSCanFifo1;
    #ifdef STM32F4xxxx
    else if(canhandle.Instance == CAN2)
        fifoPtr = StallardOSCAN::StallardOSCanFifo2;
    #endif
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

            this->sem.give(); //release Semaphore

            return true; //indicate success
        }
    }

    this->sem.give(); //release semaphore

    return false; //return false status
}

bool StallardOSCAN::receiveMessage(StallardOSCanMessage *msg)
{
    if (receiveMessage(msg, msg->ID))
    {
        return true;
    }
    return false;
}

bool StallardOSCAN::receiveMessageOneMsgBuff(StallardOSCanMessage *msg)
{
    uint16_t tempoffset = idToOffset(msg->ID);
    if(tempoffset == -1 || canarray[tempoffset]->used == false) return false;
    msg = canarray[tempoffset];
    return true;
}

int StallardOSCAN::sendMessage(StallardOSCanMessage *msg, uint8_t size)
{
    uint32_t tempTransmMailb;

    this->sem.take(); //Block the semaphore

    if (msg == nullptr || size > 8 || size == 0) //Check if the size and the message are valid
    {

        this->sem.give(); //release semaphore

        return -1;
    }
    TxHeader.StdId = msg->ID;    //copy the id
    TxHeader.RTR = CAN_RTR_DATA; //indicate Data Transmission
    TxHeader.IDE = CAN_ID_STD;   //Set Standard Identifier -> 11 bit
    TxHeader.DLC = size;         //Set Amount of Data bytes

    while (HAL_CAN_GetTxMailboxesFreeLevel(&canhandle) < 1)
    {
        __NOP();
    }
    // HAL_CAN_AbortTxRequest(&canhandle,-1);         //Wait until all TX Mailboxes are free
    HAL_CAN_AddTxMessage(&canhandle, &TxHeader, (uint8_t *)&msg->Val, &tempTransmMailb); //Add message to transmit mailbox

    this->sem.give(); //release Semaphore

    return HAL_CAN_GetError(&canhandle);
}

int StallardOSCAN::sendMessage(StallardOSCanMessage *msg)
{
    return sendMessage(msg, msg->dlc);
}