#include <mbed.h>
Serial pc(PD_8, PD_9); // tx, rx
CAN can1(PB_8, PB_9);  //rd, td, freq[Hz]

#include "TaskScheduler.h"
TaskScheduler Tasker1;
DigitalOut blue(PB_7);
DigitalOut test(PG_2);
DigitalOut red(PB_14);
DigitalOut green(PB_0);

uint32_t R0R12[13];
uint32_t SPLRPC[3];
uint32_t PSR_CTRL[4];

extern "C" int saveRegisters(uint32_t *value)
{
  uint16_t stackptr;
  asm("STR SP,  ")
  asm("STR PC, #value");
  return 1;
}

extern "C" int reloadRegisters(uint32_t *value)
{
  asm("LDR PC, #value");
  return 1;
}

int main()
{
  wait_ms(2000);

  saveRegisters(R0R12);

  pc.printf("Okay\n");

  int i = 0;
  while (1)
  {
    if (i < 100)
    {
      pc.printf("reloading!\n");
      reloadRegisters(R0R12);
      i++;
    }
    wait_ms(50);
  }
}