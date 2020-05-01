#include <mbed.h>
Serial pc(PD_8, PD_9); // tx, rx
CAN can1(PB_8,PB_9); //rd, td, freq[Hz]


#include "TaskScheduler.h"
TaskScheduler Tasker1;
DigitalOut blue(PB_7);
DigitalOut test(PG_2);
DigitalOut red(PB_14);
DigitalOut green(PB_0);


uint8_t counter = 0;

void testCan()
{
  pc.printf("%i",can1.write(CANMessage(1, &counter, 1)));
  counter++;
}

void testLed()
{
  blue.write(!blue.read());
  test.write(!test.read());
}

void testLed2()
{
  red.write(!red.read());
}

void sendToPC()
{
  pc.printf("So I bims\n");
}

int main() {
  Tasker1.addFunction(testLed,1,2000000);     //Blinkt mit f/2 Hz
  //Tasker1.addFunction(testLed2,5,2);    //Blinkt mit f/2 Hz

  //Tasker1.addFunction(sendToPC, 10, 0.5);// 0,5 Hz communikation mit PC
  
  while(1)
  {
    //test.write(0);
    Tasker1.schedule();
    //test.write(1);
  }
}