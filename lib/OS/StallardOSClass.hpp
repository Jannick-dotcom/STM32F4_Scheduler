#ifndef StallardOSClass_h
#define StallardOSClass_h

#include "StallardOSHelpers.h"

class StallardOS
{
private:
  struct function_struct taskArray[countTasks];
  struct function_struct *first_function_struct; //Pointer auf das erste erstellte Function struct
  uint8_t TCBsCreated;

  #ifndef contextSwitch
  //Wichtig für Overflow Handling
  uint64_t lastScheduleTime; //Die letzte Zeit an der der Scheduler ausgeführt wurde
  #endif

public:
  //Constructor
  StallardOS(); //Create a Task Scheduler
  #ifdef contextSwitch
  struct function_struct *addFunction(void (*function)(), uint16_t id, uint8_t prio, uint16_t refreshRate = 0);
  #else
  struct function_struct *addFunction(
      /*Funktion*/ void (*function)(),
      /*ID of task*/ uint16_t id,                  //The ID must be different for different tasks
      /*Prioritaet*/ uint8_t prio,                 //Tasks with prio 0 won't be interrupted and Tasks with prio 255 will only be executed to waste Time
      /*Executions per sec*/ uint16_t refreshRate,  //Must be bigger than 0 ! //not used by context switch
      /*Number of execs*/ uint16_t Execcount = 0); //not used by context switch
  #endif
  void changeFunctionEnabled(
      /*Funktion*/ uint16_t id,
      /*Aktivieren oder Deaktivieren*/ bool act);

private:
  struct function_struct *searchFunction(/*Funktion*/ uint16_t id); //Search a TCB that matches the provided function
  struct function_struct *searchFreeFunction(void);                 //Search a TCB that isn't used
  void createTCBs(void);                                            //create the structs for all the functions (count is "countTasks")

public:
  void setFunctionPriority(/*Funktion*/ uint16_t id, /*New Priority*/ uint8_t prio);
  // void switchPrivilegeLevel(bool status);
  #ifndef contextSwitch
  void setFunctionFrequency(/*Funktion*/ uint16_t id, /*New execution Frequency*/ float exec_freq);
  #endif
  #ifdef contextSwitch
  taskState getFunctionState(/*Funktion*/ uint16_t id);
  uint8_t getCPUload();
  #endif
  uint64_t getRuntimeMs();
  uint64_t getRuntimeUs(); 
  static void goBootloader();
  // static void flashOverCanHandle();
  

  void startOS(void);                //RTOS Starten (preemtive Multitasking)
  static void delay(uint32_t milliseconds); //RTOS führt solange einen anderen Task aus bevor er zum jetzigen zurückspringt
  void yield();                      //RTOS sagen, dass jetzt der Code zuende ist
  #ifndef contextSwitch
  void schedule();                   //Execute in the Loop (cooperative Multitasking)
  #endif
};

#endif