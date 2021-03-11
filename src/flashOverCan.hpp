#ifndef FLASHOVERCAN_HPP
#define FLASHOVERCAN_HPP

#include "StallardOS.hpp"

extern StallardOS StallardOSJanniq;

void flashOverCanHandle()
{
    StallardOSCanMessage FOCMessage;
#ifdef contextSwitch
    while (1)
    {
#endif
        if (AD_CAN.receiveMessage(&FOCMessage, STOS_CAN_ID_FOC))
        {
            if(FOCMessage.Val[0] == STOS_current_ECU_ID) StallardOSJanniq.goBootloader();
        }
#ifdef contextSwitch
        StallardOSJanniq.delay(100);
    }
#endif
}

#endif