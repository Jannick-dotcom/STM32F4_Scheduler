#include <mbed.h>
Serial pc(PD_8, PD_9); // tx, rx

#include "TaskScheduler.hpp"
TaskScheduler Tasker1;

int i = 0;

void task1(void)
{
  DigitalOut red(PB_14);
  while (1)
  {
    red.write(!red.read());
    //i++;
    //printf("task1\n");
  }
}

void task2(void)
{
  DigitalOut blue(PB_7);
  while (1)
  {
    blue.write(!blue.read());
    i++;
    //printf("\ttask2\n");
  }
}

void task3(void)
{
  DigitalOut green(PB_0);
  while (1)
  {
    green.write(!green.read());
    //i++;
    printf("\t\ttask3\n");
  }
}

int main()
{
  Tasker1.addFunction(task1, 1, 100);
  Tasker1.addFunction(task2, 2, 100);
  Tasker1.addFunction(task3, 2, 100);
  Tasker1.activateContextSwitch();
  //task2();
  while (1)
  {
    //Tasker1.schedule();
  }
}