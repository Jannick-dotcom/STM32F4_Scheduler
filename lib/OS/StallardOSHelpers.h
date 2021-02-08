#ifndef StallardOSHelpers_H
#define StallardOSHelpers_H

#include "stdint.h"
#include "StallardOSconfig.h"

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
#ifdef contextSwitch
  uint32_t vals[sizeStack];
#endif
  //Verkettete Liste
  struct function_struct *prev; //für verkettete liste
  struct function_struct *next; //für verkettete liste

  //Must have Variablen
  void (*function)();     //Auszuführende Funktion
  uint8_t priority;       //Priorität 0 wird nicht unterbrochen außer Prozess wünscht es durch ein Delay
  uint16_t id;            //ID des Tasks
  volatile uint8_t used;  //Ist dieser TCB schon belegt?
  volatile uint8_t executable;    //Funktion ausführen?

#ifndef contextSwitch
  //nur für normalen Schedule betrieb
  float frequency;        //Soll ... mal pro Sekunde ausgeführt werden
  uint64_t lastExecTime;  //Letzter Zeitpunkt der Ausführung
#endif
#ifdef contextSwitch
  //nur für KontextSwitch
  volatile uint32_t stackUsage;
  volatile taskState State;        //Status des Tasks
  volatile uint32_t *Stack;         //Stack pointer
  volatile uint8_t waitingForSemaphore; //Is task waiting for a semaphore
  volatile uint16_t *semVal;
#endif
  volatile uint32_t continueInMS;   //Delay amount
};

#endif