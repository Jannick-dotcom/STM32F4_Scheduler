#include "Jannix.hpp"
Jannix Tasker1;
JannixCAN canPimmel(JannixCAN1, CAN500k);
#include <random>

void task1(void)
{
    JannixGPIO red(14, PORTB, Output);
    uint8_t i = 0;
    JannixCanMessage sntmsg;
    sntmsg.ID = 123;
    sntmsg.Val = 0xFF;
    
    JannixCanMessage rcvmsg;
    canPimmel.sendMessage(&sntmsg);
    while(!canPimmel.getMessage(&rcvmsg));

    if(rcvmsg.Val > 0xF && rcvmsg.ID == 666)
    {
        //do shit
    }
    for (i= 0; i < 10; i++)
    {
        red = !red;
        Tasker1.delay(500);
    }
}

void task2(void)
{
    JannixGPIO blue(7, PORTB, Output);
    while (1)
    {
        blue = !blue;
        Tasker1.delay(250);
    }
}

void task3(void)
{
    JannixGPIO green(0, PORTB, Output);
    while (1)
    {
        green = !green;
        Tasker1.delay(125);
    }
}

int main()
{
    Tasker1.addFunction(task1, 2, 1);
    Tasker1.addFunction(task2, 3, 2);
    Tasker1.addFunction(task3, 4, 3);
    Tasker1.startOS();

    //Should never get here
    while (1)
    {
    }
}