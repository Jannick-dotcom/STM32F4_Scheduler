#include "StallardOSsem.hpp"

extern volatile struct function_struct *currentTask;

StallardOSSemaphore::StallardOSSemaphore()
{
    val = 1;
}

void StallardOSSemaphore::give()
{
    if(currentTask != nullptr)
    {
        val++;
        currentTask->semVal = nullptr;
    }
}

void StallardOSSemaphore::take()
{
    if(currentTask != nullptr)
    {
        currentTask->semVal = &val;
        currentTask->waitingForSemaphore = 1;
        while (val < 1);
        disable_interrupts();
        val--;
        currentTask->waitingForSemaphore = 0;
        enable_interrupts();
    }
}
