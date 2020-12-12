#ifndef StallardOS_h
#define StallardOS_h

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

#include "StallardOSHelpers.h"

#include "StallardOSGPIO.hpp"
#include "StallardOSpwm.hpp"
#include "StallardOSanalog.hpp"
#include "StallardOScan.hpp"
#include "StallardOSSerial.hpp"
#include "StallardOSi2c.hpp"
#include "StallardOSPID.hpp"

class StallardOS
{
private:
  struct function_struct *first_function_struct; //Pointer auf das erste erstellte Function struct
  uint8_t TCBsCreated;
  //Wichtig für Overflow Handling
  uint64_t lastScheduleTime; //Die letzte Zeit an der der Scheduler ausgeführt wurde

public:
  //Constructor
  StallardOS(); //Create a Task Scheduler

  struct function_struct *addFunction(
      /*Funktion*/ void (*function)(),
      /*ID of task*/ uint16_t id,                  //The ID must be different for different tasks
      /*Prioritaet*/ uint8_t prio,                 //Tasks with prio 0 won't be interrupted and Tasks with prio 255 will only be executed to waste Time
      /*Executions per sec*/ float exec_freq = 1,  //Must be bigger than 0 ! //not used by context switch
      /*Number of execs*/ uint16_t Execcount = 0); //not used by context switch

  void changeFunctionEnabled(
      /*Funktion*/ uint16_t id,
      /*Aktivieren oder Deaktivieren*/ bool act);

private:
  struct function_struct *searchFunction(/*Funktion*/ uint16_t id); //Search a TCB that matches the provided function
  struct function_struct *searchFreeFunction(void);                 //Search a TCB that isn't used
  void createTCBs(void);                                            //create the structs for all the functions (count is "countTasks")

public:
  void setFunctionPriority(/*Funktion*/ uint16_t id, /*New Priority*/ uint8_t prio);
  void setFunctionFrequency(/*Funktion*/ uint16_t id, /*New execution Frequency*/ float exec_freq);

  taskState getFunctionState(/*Funktion*/ uint16_t id);

  void startOS(void);                //RTOS Starten (preemtive Multitasking)
  void delay(uint32_t milliseconds); //RTOS führt solange einen anderen Task aus bevor er zum jetzigen zurückspringt
  void schedule();                   //Execute in the Loop (cooperative Multitasking)
};
#endif //StallardOS_h
