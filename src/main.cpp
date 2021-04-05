#include "StallardOS.hpp"
#include "flashOverCan.hpp"

// StallardOSGPIO led1(13, PORTF, Output,1);
// StallardOSGPIO led2(14, PORTF, Output,1);
// StallardOSGPIO led3(15, PORTF, Output,1);
// StallardOSGPIO led11(9, PORTI, Output,1);
// StallardOSGPIO led21(10, PORTI, Output,1);
// StallardOSGPIO led31(11, PORTI, Output,1);
StallardOSpwm fadingLED(TIM1,13, PORTF, 1000, 8);

StallardOS StallardOSJanniq;

void tasktest()
{
    // StallardOSAnalog testAnalog(StallardOSADC1, 1, PORTA, 1);
#ifdef contextSwitch
    while (1)
    {
#endif
        // volatile uint32_t test = testAnalog.getValue();
        // led1 = !led1;
#ifdef contextSwitch
        // StallardOSJanniq.delay(500);
        StallardOSJanniq.yield();
        //StallardOSJanniq.getCPUload();
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