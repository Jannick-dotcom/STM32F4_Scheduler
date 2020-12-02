#ifndef StallardOSHelpers_H
#define StallardOSHelpers_H

#include "stdint.h"
#include "StallardOSconfig.h"

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
  struct function_struct *prev; //für verkettete liste
  struct function_struct *next; //für verkettete liste

  //Must have Variablen
  void (*function)();     //Auszuführende Funktion
  uint8_t priority;       //Priorität 0 wird nicht unterbrochen außer sie wünschen es durch ein Delay
  uint16_t id;            //ID des Tasks
  volatile uint8_t used;           //Ist dieser TCB schon belegt?

  //nur für normalen Schedule betrieb
  //float frequency;        //Soll ... mal pro Sekunde ausgeführt werden
  volatile uint8_t executable;    //Funktion ausführen?
  //uint32_t lastExecTime;  //Letzter Zeitpunkt der Ausführung

  //nur für KontextSwitch
  volatile taskState State;        //Status des Tasks
  volatile uint32_t *Stack;         //Stack pointer
  
  volatile uint32_t continueInMS;   //Delay amount

  // ~function_struct();
};

#endif