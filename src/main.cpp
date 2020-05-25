#include <mbed.h>
Serial pc(PD_8, PD_9); // tx, rx
CAN can1(PB_8, PB_9);  //rd, td, freq[Hz]

#include "TaskScheduler.h"
TaskScheduler Tasker1;

DigitalOut blue(PB_7);
DigitalOut test(PG_2);
DigitalOut red(PB_14);
DigitalOut green(PB_0);

void task1(void)
{
  while(1)
  {
    pc.printf("task1");
  }
}

int main()
{
  Tasker1.addFunction(task1, 3, 10);
  while (1)
  {
    Tasker1.schedule();
  }
}