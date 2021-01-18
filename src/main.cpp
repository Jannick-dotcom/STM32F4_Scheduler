#include "StallardOS.hpp"
StallardOS Tasker1;

uint8_t count = 0;
volatile double erg;
extern volatile uint64_t msCurrentTimeSinceStart;

// StallardOSGPIO led2(14, PORTF, Output);
// StallardOSGPIO led3(15, PORTF, Output);
// StallardOSGPIO led11(9, PORTI, Output);
// StallardOSGPIO led21(10, PORTI, Output);
// StallardOSGPIO led31(11, PORTI, Output);

void taskNeu()
{
    StallardOSAnalog a0(StallardOSADC1, 2);
    StallardOSGPIO testIn(2, PORTG, Input, pullup);
    volatile uint8_t test2 = testIn.read();
    uint16_t test = a0.getValue();
    erg = test;
}

int main()
{
    //Tasker1.addFunction(tasktest, 1, 1, 30);
    Tasker1.addFunction(taskNeu, 2, 1, 12);
    Tasker1.startOS();
    while (1)
    {
        Tasker1.schedule();
    }
    //Should never get here
}