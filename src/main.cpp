#include "StallardOS.hpp"
StallardOS Tasker1;

uint8_t count = 0;
volatile double erg;
extern volatile uint64_t msCurrentTimeSinceStart;
// StallardOSGPIO led2(14, PORTF, Output);
// StallardOSGPIO led3(15, PORTF, Output);
// StallardOSGPIO led11(9, PORTI, Output);
// StallardOSGPIO led21(10, PORTI, Output);
// StallardOSGPIO led31(11, PORTI, Output);

void taskNeu()
{
    StallardOSCanMessage testmessage;
    StallardOSCAN testCAN(StallardOSCAN1, CAN1M);
    while (1)
    {
        testmessage.ID = 123;
        testmessage.Val = 44;
        testCAN.sendMessage(&testmessage);
        testmessage.Val = 0;
        while(testCAN.receiveMessage(&testmessage, 123) == false)
        {
            Tasker1.delay(1000);
        }
        volatile int testttt = testmessage.Val;
    }
}

int main()
{
    //Tasker1.addFunction(tasktest, 1, 1, 30);
    Tasker1.addFunction(taskNeu, 2, 1, 12);
    Tasker1.startOS();
    while (1)
    {
        Tasker1.schedule();
    }
    //Should never get here
}