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

void task1(void)
{
    StallardOSCanMessage test;
    StallardOSCAN adcan(StallardOSCAN1, CAN500k);
    StallardOSGPIO red(14, PORTB, Output);
    while (1)
    {
        test.ID = 123;
        test.Val = red;
        adcan.sendMessage(&test);
        adcan.receiveMessage(&test, 123);
        Tasker1.delay(500);
    }
}

void task2(void)
{
    StallardOSGPIO blue(7, PORTB, Output);
    while (1)
    {
        blue = !blue;
        Tasker1.delay(250);
    }
}

void task3(void)
{
    StallardOSGPIO green(0, PORTB, Output);
    while (1)
    {
        green = !green;
        Tasker1.delay(125);
    }
}

int main()
{
    // Tasker1.addFunction(task1, 2, 1);
    // Tasker1.addFunction(task2, 3, 2);
    // Tasker1.addFunction(task3, 4, 3);
    Tasker1.addFunction(tasktest, 1, 1, 30);
    Tasker1.startOS();
    while (1)
    {
        Tasker1.schedule();
    }
    //Should never get here
}