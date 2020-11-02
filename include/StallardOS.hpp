/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Powered by:
//
//    OSama
//        bin
//          Janniq 
//              *.*
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef Task_Scheduler_h
#define Task_Scheduler_h

// #define useSystickAltering
// void StallardOS_SetSysClock(void);

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include "StallardOSHelpers.hpp"
#include "StallardOSGPIO.hpp"
#include "StallardOScan.hpp"

#define sizeStack 300      //300 * uint32_t
#define countTasks 3
#define defaultSysTickFreq 1000.0
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

class StallardOS
{
  /////////Variables
private:
  function_struct *first_function_struct; //Pointer auf das erste erstellte Function struct
  uint8_t TCBsCreated;

public:
  //Constructor
  StallardOS(); //Create a Task Scheduler

  //Function Methods
  //returns pointer to added struct or nullptr if not successful
  function_struct *addFunction(
    /*Funktion*/ void (*function)(), 
    /*ID of task*/ uint16_t id,                 //The ID must be different for different tasks
    /*Prioritaet*/ uint8_t prio);                //Tasks with prio 0 won't be interrupted and Tasks with prio 255 will only be executed to waste Time
    //Eine Funktion zur Liste hinzufügen

  void changeFunctionEnabled(
    /*Funktion*/ uint16_t id,
    /*Aktivieren oder Deaktivieren*/ bool act); 
    //Eine Funktion aus der Liste de/aktivieren

private:
  function_struct *searchFunction(/*Funktion*/ uint16_t id);  //Search a TCB that matches the provided function
  function_struct *searchFreeFunction(void);      //Search a TCB that isn't used
  void createTCBs(void);      //create the structs for all the functions (count is "countTasks")
  
public:
  //Setter Methods
  void setFunctionPriority(/*Funktion*/ uint16_t id, /*New Priority*/ uint8_t prio);
  // void setFunctionFrequency(/*Funktion*/ uint16_t id, /*New execution Frequency*/ float exec_freq);
  
  //Getter Methods
  taskState getFunctionState(/*Funktion*/ uint16_t id);

  //Context Switch
  void startOS(void);                     //RTOS Starten (preemtive Multitasking)
  void delay(uint32_t milliseconds);         //RTOS führt solange einen anderen Task aus bevor er zum jetzigen zurückspringt

};
#endif //Task_Scheduler
