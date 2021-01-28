#include "StallardOS.hpp"
StallardOS Tasker1;

StallardOSGPIO led1(13, PORTF, Output);
StallardOSGPIO led2(14, PORTF, Output);
StallardOSGPIO led3(15, PORTF, Output);

StallardOSGPIO led11(9, PORTI, Output);
StallardOSGPIO led21(10, PORTI, Output);
StallardOSGPIO led31(11, PORTI, Output);
uint8_t count = 0;
volatile double erg;
extern "C" void FPU_IRQHandler();

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

void task2()
{
    volatile double k;
    for (uint16_t i = 0; i < 1000; i++)
    {
        k = 1.5468 / 2.5648 + i;
        FPU_IRQHandler(); //Manually call the interrupt handler
    }
    erg = k;
}

int main()
{
    Tasker1.addFunction(tasktest, 1, 1, 30);
    Tasker1.addFunction(task2, 2, 1, 12);
    Tasker1.startOS();
    while (1)
    {
        Tasker1.schedule();
    }
    //Should never get here
}