#ifndef StallardOSHelpers_H
#define StallardOSHelpers_H

#include "stdint.h"

#include "StallardOSconfig.h"

#define functionModifier (uint32_t)0xFFFFFFFE //Use the function pointer with lowest bit zero
// #define sysTickTicks (uint32_t)(SystemCoreClock / 1000)

#ifdef __cplusplus
extern "C"
{
#endif
  void StallardOS_SetSysClock(uint8_t clockspeed);
  void StallardOS_goBootloader();
  void enable_interrupts();
  void disable_interrupts();
#ifdef __cplusplus
}
#endif

typedef enum
{
  NEW = 0,
  RUNNING,
  PAUSED,
  STOPPED
} taskState;


typedef enum{
  SV_PENDSV = 2
} svCalls;

typedef uint32_t stack_T;

struct function_struct
{
  uint8_t staticAlloc;                    //Is the stack static or dynamically allocated?
  volatile stack_T *Stack;             //Stack pointer
  volatile stack_T *vals;              //Stack pointer for future knowledge of initial stack ptr, for example in fault handlers
  volatile stack_T *stackBase;         //lowest address of stack allocation, used for MPU config
  uint32_t stackSize;                  //Number of elements possible to store on stack, NOT size in bytes
  uint8_t stackSize_MPU;


  volatile struct function_struct *prev; //für verkettete liste
  volatile struct function_struct *next; //für verkettete liste

  //Must have Variablen
  void (*function)();          //Auszuführende Funktion
  volatile uint8_t priority;            //Priorität 0 wird nicht unterbrochen außer Prozess wünscht es durch ein Delay
  volatile uint16_t id;                 //ID des Tasks
  volatile uint8_t used;       //Ist dieser TCB schon belegt?
  volatile uint8_t executable; //Funktion ausführen?

  // volatile uint8_t error; //Error in Task scheduling has happened

  //nur für KontextSwitch
  volatile uint16_t refreshRate;
  volatile uint64_t lastYield;
  volatile uint64_t lastStart;
  // volatile uint32_t stackUsage;
  volatile taskState State;             //Status des Tasks
  volatile uint8_t waitingForSemaphore; //Is task waiting for a semaphore
  volatile uint16_t *semVal;
  volatile uint64_t continueInUS; //Delay amount

};

#endif