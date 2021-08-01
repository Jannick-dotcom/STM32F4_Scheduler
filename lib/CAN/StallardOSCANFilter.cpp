#include "StallardOSCANFilter.hpp"

uint8_t StallardOSCANFilter::countFilters = 0;

StallardOSCANFilter::StallardOSCANFilter(uint16_t id1, uint16_t id2, CANports can)
{
    if(id1 > 2047 || id2 > 2047 || this->countFilters > 27)
    {
        asm("bkpt");
        StallardOSGeneralFaultHandler();
    }
    this->id1 = id1;
    this->id2 = id2;
    n = countFilters;
    countFilters++;
    CAN_FilterTypeDef sFilterConfig;
    CAN_HandleTypeDef *canhandle;
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
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
    sFilterConfig.FilterIdHigh = id1 << 5; //insert first ID
    sFilterConfig.FilterIdLow = id2 << 5;
    sFilterConfig.FilterMaskIdHigh = 0xFFFF << 5; //Do nothing
    sFilterConfig.FilterMaskIdLow = 0xFFFF << 5;

    if(n & 0b1 == 0) // Evenly split filters to fifos
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
        /* Filter configuration Error */
        StallardOSGeneralFaultHandler();
    }
}

StallardOSCANFilter::~StallardOSCANFilter()
{
    countFilters--;
}