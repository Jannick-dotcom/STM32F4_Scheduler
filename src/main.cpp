#include <mbed.h>
Serial pc(PD_8, PD_9); // tx, rx

#include "TaskScheduler.h"
TaskScheduler Tasker1;

void task1(void)
{
  while (1)
  {
    pc.printf("task1\n");
  }
}

void task2(void)
{
  while (1)
  {
    pc.printf("\ttask2\n");
  }
}

void task3(void)
{
  while (1)
  {
    pc.printf("\t\ttask3\n");
  }
}

int main()
{
  Tasker1.addFunction(task1, 1, 1);
  Tasker1.addFunction(task2, 2, 1);
  Tasker1.addFunction(task3, 2, 1);
  //Tasker1.activateContextSwitch();
  while(1);
}