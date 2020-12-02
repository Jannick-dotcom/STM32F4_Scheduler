#include "StallardOS.hpp"
StallardOS Tasker1;

void tasktest()
{
    StallardOSGPIO led1(13, PORTF, Output);
    StallardOSGPIO led2(14, PORTF, Output);
    StallardOSGPIO led3(15, PORTF, Output);
    StallardOSGPIO test(15, PORTA, Output);
    led1 = 1;
    led2 = 1;
    led3 = 1;
    while (1)
    {
        for (uint8_t i = 1; i < 10; i++)
        {
            led1 = led2 = led3 = 1;
            Tasker1.delay(i);
            led1 = led2 = led3 = 0;
            Tasker1.delay(10 - i);
        }
        for (uint8_t i = 9; i > 0; i--)
        {
            led1 = led2 = led3 = 1;
            Tasker1.delay(i);
            led1 = led2 = led3 = 0;
            Tasker1.delay(10 - i);
        }
    }
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
    Tasker1.addFunction(tasktest, 1, 1);
    Tasker1.startOS();
    while (1)
        ;
    //Should never get here
}