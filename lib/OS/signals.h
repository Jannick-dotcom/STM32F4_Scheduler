#pragma once
#include "StallardOSHelpers.h"

extern volatile struct function_struct* volatile currentTask;
extern volatile struct function_struct* volatile nextTask;

void jumpSignalHandler(uint32_t sig_fun_ptr)
{
    uint32_t Programcounter = *(nextTask->Stack+16); //get program counter -> must go to linkregister
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)0x01000000;
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)sig_fun_ptr | (1);
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)Programcounter;
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)12;
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)3;
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)2;
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)1;
    nextTask->Stack--;
    *nextTask->Stack = (uint32_t)0;
    
    nextTask->Stack--;
    *nextTask->Stack = 0xFFFFFFFD;

    #ifndef unprotectedBuild
    nextTask->Stack--;
    *nextTask->Stack = (CONTROL_nPRIV_Msk << CONTROL_nPRIV_Pos); //Control register (unprivileged)
    #endif

    for(uint8_t i = 11; i > 3; i--)
    {
        nextTask->Stack--;
        *nextTask->Stack = i;
    }
}

void checkSignal()
{
  if(nextTask == NULL)
  {
    return;
  }
  for(uint8_t i = 0; i < sizeof(nextTask->rcvSignal)/sizeof(signals); i++)
  {
    if(nextTask->rcvSignal[i] != SIG_NONE)
    {
      // if(nextTask->signalHandlers[nextTask->rcvSignal[i]] != NULL) //if signal handler exists for this signal
      // {
      //   void (*signalHandler)() = (void (*)())(nextTask->signalHandlers[nextTask->rcvSignal[i]]); //call this signal handler
      //   jumpSignalHandler((uint32_t)signalHandler);
      // }
      // else //Otherwise call the default handler for this signal
      // {
        jumpSignalHandler((uint32_t)taskOnEnd);
      // }
      break;
    }
  }
}