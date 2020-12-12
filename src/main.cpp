#include "StallardOS.hpp"
StallardOS Tasker1;

StallardOSGPIO led1(13, PORTF, Output);
StallardOSGPIO led2(14, PORTF, Output);
StallardOSGPIO led3(15, PORTF, Output);

StallardOSGPIO led11(9, PORTI, Output);
StallardOSGPIO led21(10, PORTI, Output);
StallardOSGPIO led31(11, PORTI, Output);
uint8_t count = 0;

void tasktest()
{
    //while (1)
    //{
    if (!(count % 2))
    {
        led1 = !led1;
        led2 = !led2;
        led3 = !led3;
    }
    else
    {
        led11 = !led11;
        led21 = !led21;
        led31 = !led31;
    }
    count++;
    //Tasker1.delay(300);
    //}
}

int main()
{
    Tasker1.addFunction(tasktest, 1, 1, 30);
    Tasker1.startOS();
    while (1)
    {
        Tasker1.schedule();
    }
    //Should never get here
}