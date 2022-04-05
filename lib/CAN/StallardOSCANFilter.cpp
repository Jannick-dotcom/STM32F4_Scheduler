#include "StallardOSCANFilter.hpp"
uint8_t StallardOSCANFilter::countFilters = 0;

StallardOSCANFilter::StallardOSCANFilter(uint16_t id1, uint16_t id2, CANports can): id1(id1), id2(id2)
{
    setup(can);
}

StallardOSCANFilter::StallardOSCANFilter(uint16_t id1, uint16_t id2): 
    id1(id1), id2(id2){}

StallardOSCANFilter::~StallardOSCANFilter()
{
    countFilters--;
}


void StallardOSCANFilter::setup(CANports can){
    if(id1 > 2047 || id2 > 2047 || this->countFilters > 27)
    {
        DEBUGGER_BREAK();
        StallardOSGeneralFaultHandler();
    }
    this->id1 = id1;
    this->id2 = id2;
    n = countFilters;
    countFilters++;
    CAN_FilterTypeDef sFilterConfig;
    CAN_HandleTypeDef *canhandle = nullptr;
    if (can == StallardOSCAN1)
    {
        sFilterConfig.FilterBank = 0 + n;
        canhandle = &StallardOSCAN::can1handle;
    }
    else if (can == StallardOSCAN2)
    {
        sFilterConfig.FilterBank = 14 + n;
        canhandle = &StallardOSCAN::can2handle;
    }
    else
    {
        DEBUGGER_BREAK();
        /* Filter configuration Error */
        StallardOSGeneralFaultHandler();
    }
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
    sFilterConfig.FilterIdHigh = id1 << 5; //insert first ID
    sFilterConfig.FilterIdLow = id2 << 5;
    sFilterConfig.FilterMaskIdHigh = 0xFFFF << 5; //Do nothing
    sFilterConfig.FilterMaskIdLow = 0xFFFF << 5;

    if((n & 0b1) == 0) // Evenly split filters to fifos
    {
        sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    }
    else
    {
        sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
    }
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;
    if (HAL_CAN_ConfigFilter(canhandle, &sFilterConfig) != HAL_OK)
    {
        DEBUGGER_BREAK();
        /* Filter configuration Error */
        StallardOSGeneralFaultHandler();
    }
}


StallardOSCANFilterDelayed::StallardOSCANFilterDelayed(uint16_t id1, uint16_t id2, CANports can): 
    StallardOSCANFilter(id1, id2), can(can), is_init(false){}

void StallardOSCANFilterDelayed::setup(){
    if(!is_init){
        is_init=true;
        StallardOSCANFilter::setup(can);
    }
}