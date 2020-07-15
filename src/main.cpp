#include <mbed.h>
Serial pc(PD_8, PD_9); // tx, rx
#include "TaskScheduler.hpp"
TaskScheduler Tasker1;

int i = 0;

// void taskMain(void) //Hier wird die Überschüssige Zeit verbraten
// {
//   while(1);
// }

void task1(void)
{
  DigitalOut red(PB_14);
  for(uint8_t i = 0; i < 10; i++) {
    red.write(!red.read());
    Tasker1.delay(1000);
  }
}

void task2(void)
{
  DigitalOut blue(PB_7);
  while (1)
  {
    blue.write(!blue.read());
    Tasker1.delay(250);
  }
}

void task3(void)
{
  DigitalOut green(PB_0);
  while (1)
  {
    green.write(!green.read());
    Tasker1.delay(500);
  }
}

int main()
{
  // Tasker1.addFunction(taskMain, 2);
  Tasker1.addFunction(task1, 1);
  Tasker1.addFunction(task2, 1);
  Tasker1.addFunction(task3, 1);
  Tasker1.startOS();

  //Should never get here
  while (1)
  {
    //Tasker1.schedule();
  }
}