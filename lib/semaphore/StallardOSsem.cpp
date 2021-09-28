#include "StallardOSsem.hpp"

extern volatile struct function_struct *currentTask;

StallardOSSemaphore::StallardOSSemaphore()
{
    val = 1;
}

void StallardOSSemaphore::give()
{
    val++;
    currentTask->semVal = nullptr;
}

void StallardOSSemaphore::take()
{
    if(currentTask != nullptr)
    {
        currentTask->semVal = &val;
        currentTask->waitingForSemaphore = 1;
    }
    while (val < 1);
    val--;
    if(currentTask != nullptr)
    {
        currentTask->waitingForSemaphore = 0;
    }
}
