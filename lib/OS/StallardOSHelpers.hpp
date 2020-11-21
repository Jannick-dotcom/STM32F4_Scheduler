#ifndef StallardOSHelpers_H
#define StallardOSHelpers_H

#include <stdint.h>
#include "StallardOSconfig.h"
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

// #include "StallardOS.hpp"
#define functionModifier (uint32_t)0xFFFFFFFE     //Use the function pointer with lowest bit zero
#define sysTickTicks (uint32_t)(SystemCoreClock / sysTickFreq)

typedef enum {
  NEW,
  RUNNING,
  PAUSED,
  STOPPED
} taskState;

struct function_struct
{
  uint32_t vals[sizeStack];

  //Verkettete Liste
  function_struct *prev; //für verkettete liste
  function_struct *next; //für verkettete liste

  //Must have Variablen
  void (*function)();     //Auszuführende Funktion
  uint8_t priority;       //Priorität 0 wird nicht unterbrochen außer sie wünschen es durch ein Delay
  uint16_t id;            //ID des Tasks
  volatile bool used;           //Ist dieser TCB schon belegt?

  //nur für normalen Schedule betrieb
  //float frequency;        //Soll ... mal pro Sekunde ausgeführt werden
  volatile bool executable;    //Funktion ausführen?
  //uint32_t lastExecTime;  //Letzter Zeitpunkt der Ausführung

  //nur für KontextSwitch
  volatile taskState State;        //Status des Tasks
  volatile uint32_t *Stack;         //Stack pointer
  
  volatile uint32_t continueInMS;   //Delay amount

  // ~function_struct();
};


#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_noTask()
{
    asm("SVC #0");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_sudo()
{
    asm("SVC #3");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_unSudo()
{
    asm("SVC #4");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_start()
{
    asm("SVC #5");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_delay()
{
    asm("SVC #2");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_endTask()
{
    asm("SVC #1"); 
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_goBootloader()
{
    asm("SVC #6");
}

////////////////////////////////////////////////////////////////////////////////////////
//Enables all interrupts
////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
inline void enable_interrupts() 
{
	asm("CPSIE I");     //Instruction for enabling interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Disables all interrupts
////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
inline void disable_interrupts() 
{
	asm("CPSID I");     //Instruction for disabling interrupts
}

#ifdef __cplusplus
extern "C" 
#endif
inline void pendPendSV()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

#endif