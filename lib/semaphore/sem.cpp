#include "sem.hpp"

extern struct function_struct *currentTask;

void StallardOSSemaphore::give()
{
    this->val++;
}

void StallardOSSemaphore::take()
{
    currentTask->semVal = &this->val;
    currentTask->waitingForSemaphore = 1;
    while(this->val < 1);
    this->val--;
    currentTask->waitingForSemaphore = 0;
    currentTask->semVal = nullptr;
}