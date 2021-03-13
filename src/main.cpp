#include "StallardOS.hpp"
#include "flashOverCan.hpp"

StallardOSGPIO led1(13, PORTF, Output);
// StallardOSGPIO led2(14, PORTF, Output);
// StallardOSGPIO led3(15, PORTF, Output);
// StallardOSGPIO led11(9, PORTI, Output);
// StallardOSGPIO led21(10, PORTI, Output);
// StallardOSGPIO led31(11, PORTI, Output);
// StallardOSpwm fadingLED(TIM1,13, PORTF, 1000, 8);

StallardOS StallardOSJanniq;

void tasktest()
{
#ifdef contextSwitch
    while (1)
    {
#endif
        led1 = !led1;
#ifdef contextSwitch
        //StallardOSJanniq.delay(500);
        StallardOSJanniq.yield();
        // StallardOSJanniq.getCPUload();
    }
#endif
}

void taskTestCAN()
{
    StallardOSCanMessage testmessage;
    uint8_t data = STOS_current_ECU_ID;
    
#ifdef contextSwitch
    while (1)
    {
#endif
        testmessage.ID = STOS_CAN_ID_FOC;
        testmessage.Val[0] = data;
        AD_CAN.sendMessage(&testmessage, sizeof(data));
#ifdef contextSwitch
        StallardOSJanniq.delay(1000);
    }
#endif
}

int main()
{
    StallardOSJanniq.addFunction(tasktest, 1, 1, 2);
    StallardOSJanniq.addFunction(flashOverCanHandle, 2, 1);
    StallardOSJanniq.addFunction(taskTestCAN, 3, 4);
    StallardOSJanniq.startOS();
    while (1)
    {
        #ifndef contextSwitch
        StallardOSJanniq.schedule();
        #endif
    }
    //Should never get here
}