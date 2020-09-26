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
void Jannix_SetSysClock(void);

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include "GPIO.h"

#define sizeStack 300      //300 * uint32_t
#define countTasks 10
#define coreFreq 180000000 //180MHz
#define Jannix_HSE_VALUE 25000000 //Frequency of ext osc / if no -> 16MHz

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
  uint8_t used;           //Ist dieser TCB schon belegt?

  //nur für normalen Schedule betrieb
  //float frequency;        //Soll ... mal pro Sekunde ausgeführt werden
  bool executable;    //Funktion ausführen?
  //uint32_t lastExecTime;  //Letzter Zeitpunkt der Ausführung

  //nur für KontextSwitch
  volatile taskState State;        //Status des Tasks
  volatile uint32_t *Stack;         //Stack pointer
  
  volatile uint32_t continueInMS;   //Delay amount

  ~function_struct();
};

class TaskScheduler
{
  /////////Variables
private:
  function_struct *first_function_struct; //Pointer auf das erste erstellte Function struct
  uint8_t TCBsCreated;

public:
  //Constructor
  TaskScheduler(); //Create a Task Scheduler

  //Function Methods
  //returns pointer to added struct or nullptr if not successful
  function_struct *addFunction(
    /*Funktion*/ void (*function)(), 
    /*ID of task*/ uint16_t id,                 //The ID must be different for different tasks
    /*Prioritaet*/ uint8_t prio,                //Tasks with prio 0 won't be interrupted and Tasks with prio 255 will only be executed to waste Time
    /*Executions per sec*/ float exec_freq = 1, //Must be bigger than 0 ! //not used by context switch
    /*Number of execs*/ uint16_t Execcount = 0);//not used by context switch
    //Eine Funktion zur Liste hinzufügen

  void createTCBs(void);      //create the structs for all the functions (count is "countTasks")

  void changeFunctionEnabled(
    /*Funktion*/ uint16_t id,
    /*Aktivieren oder Deaktivieren*/ bool act); 
    //Eine Funktion aus der Liste de/aktivieren

private:
  function_struct *searchFunction(/*Funktion*/ uint16_t id);
  function_struct *searchFreeFunction(void);
  
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
