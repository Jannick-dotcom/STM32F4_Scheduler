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
    volatile double k;
    StallardOSGPIO led1(13, PORTF, Output);
    while (1)
    {
        volatile uint64_t nowT = msCurrentTimeSinceStart;
        for (uint32_t i = 0; i < 200000; i++)
        {
            k = ((1.5468f / 2.5648f) * 1.201649984f) + i;
        }
        volatile uint32_t timeTaken = msCurrentTimeSinceStart - nowT;
        erg = k;
        Tasker1.delay(1000);
    }
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