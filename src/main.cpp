#include <mbed.h>
Serial pc(PD_8, PD_9); // tx, rx

#include "TaskScheduler.hpp"
TaskScheduler Tasker1;

DigitalOut red(PB_14, 1);
DigitalOut green(PB_0, 1);
DigitalOut blue(PB_7, 1);

void task1(void)
{
  while (1)
  {
    red.write(!red.read());
  }
}

void task2(void)
{
  while (1)
  {
    blue.write(!blue.read());
  }
}

void task3(void)
{
  while (1)
  {
    green.write(!green.read());
  }
}

int main()
{
  Tasker1.addFunction(task1, 1, 100);
  Tasker1.addFunction(task2, 2, 100);
  Tasker1.addFunction(task3, 2, 100);
  Tasker1.activateContextSwitch();
  while (1)
  {
  }
}