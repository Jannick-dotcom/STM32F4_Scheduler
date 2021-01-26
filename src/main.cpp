#include "StallardOS.hpp"
StallardOS Tasker1;
StallardOSCAN testCAN(StallardOSCAN1, CAN1M);
// StallardOSGPIO led2(14, PORTF, Output);
// StallardOSGPIO led3(15, PORTF, Output);
// StallardOSGPIO led11(9, PORTI, Output);
// StallardOSGPIO led21(10, PORTI, Output);
StallardOSGPIO led31(11, PORTI, Output);

void tasktest()
{
    while(1)
    {
        led31 != led31;
        Tasker1.delay(1000);
    }
}

void taskTestCAN()
{
    StallardOSCanMessage testmessage;
    uint8_t test = 0;
    while (1)
    {
        testmessage.ID = 123;
        testmessage.Val = test;
        testCAN.sendMessage(&testmessage);
        testmessage.Val = 0;
        // while(testCAN.receiveMessage(&testmessage, 123) == false)
        // {
        Tasker1.delay(1000);
        // }
        test++;
    }
}

extern "C" void StallardOS_goBootloader();
void flashOverCanHandle()
{
    StallardOSCanMessage FOCMessage;
    while (1)
    {
        if (testCAN.receiveMessage(&FOCMessage, 123))
        {
            //StallardOS_goBootloader();
        }
        Tasker1.delay(100);
    }
}

int main()
{
    Tasker1.addFunction(tasktest, 1, 1, 30);
    Tasker1.addFunction(flashOverCanHandle, 2, 1);
    Tasker1.addFunction(taskTestCAN, 3, 4);
    Tasker1.startOS();
    while (1)
    {
        Tasker1.schedule();
    }
    //Should never get here
}