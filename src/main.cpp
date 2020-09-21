#include "TaskScheduler.h"
TaskScheduler Tasker1;

void task1(void)
{
    JannixGPIO red(7, PORTB, Output);
    while (1)
    {
        red = !red;
        //Tasker1.delay(100);
    }
}

// void task2(void)
// {
//     //DigitalOut blue(PB_7);
//     while (1)
//     {
//         //blue.write(!blue.read());
//         Tasker1.delay(200);
//     }
// }

// void task3(void)
// {
//     JannixGPIO green(0, PORTB, Output);
//     while (1)
//     {
//         green = !green;
//         Tasker1.delay(400);
//     }
// }

int main()
{
    // HAL_Init();
    //initSys();
    // SystemClock_Config();
    // SystemCoreClockUpdate();
    
    //Tasker1.addFunction(task1, 2, 1);
    // Tasker1.addFunction(task2, 3, 2);
    // Tasker1.addFunction(task3, 4, 3);
    // Tasker1.addFunction(restarterTask, 1, 4);
    //Tasker1.startOS();

    task1();

    //Should never get here
    while (1)
    {
    }
}