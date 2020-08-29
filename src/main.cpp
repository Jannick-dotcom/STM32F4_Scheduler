//#include <mbed.h>
//Serial pc(PD_8, PD_9); // tx, rx
#include "TaskScheduler.hpp"
TaskScheduler Tasker1;

void task1(void)
{
    //DigitalOut red(PB_14);
    for (int i = 0; i < 5; i++)
    {
        //red.write(!red.read());
        Tasker1.delay(100);
    }
}

void task2(void)
{
    //DigitalOut blue(PB_7);
    while (1)
    {
        //blue.write(!blue.read());
        Tasker1.delay(200);
    }
}

void task3(void)
{
    //DigitalOut green(PB_0);
    while (1)
    {
        //green.write(!green.read());
        Tasker1.delay(400);
    }
}

void restarterTask(void)
{
    while (1)
    {
      if(Tasker1.getFunctionState(2) == STOPPED) 
      {
          Tasker1.addFunction(task1, 2, 1);
      }
    //   if(Tasker1.getFunctionState(2) == STOPPED) Tasker1.addFunction(task2, 2, 1);
    //   if(Tasker1.getFunctionState(3) == STOPPED) Tasker1.addFunction(task3, 3, 1);
    //   Tasker1.delay(500);
    }
}

int main()
{
    Tasker1.addFunction(task1, 2, 1);
    Tasker1.addFunction(task2, 3, 2);
    Tasker1.addFunction(task3, 4, 3);
    //Tasker1.addFunction(restarterTask, 1, 4);
    Tasker1.startOS();

    //Should never get here
    while (1)
    {
        //Tasker1.schedule();
    }
}