#include "StallardOS.hpp"

extern "C" volatile uint64_t msCurrentTimeSinceStart; //about 585 000 years of microsecond counting
extern "C" volatile uint64_t usCurrentTimeSinceStart; //about 585 000 years of microsecond counting
extern "C" volatile uint64_t taskMainTime;

//Kontext Switch
struct function_struct *currentTask = nullptr;
struct function_struct *nextTask = nullptr;
struct function_struct *taskMainStruct = nullptr;

extern "C" void StallardOS_SetSysClock(uint8_t clockspeed);
extern "C" void StallardOS_start();
extern "C" void StallardOS_delay();
extern "C" void StallardOS_noTask();
extern "C" void StallardOS_sudo();
extern "C" void StallardOS_unSudo();
extern "C" void StallardOS_delay();
extern "C" void StallardOS_endTask();
extern "C" void StallardOS_goBootloader();
extern "C" void enable_interrupts();
extern "C" void disable_interrupts();

/**
 * Waste Time if all tasks are in delay.
 *
 * @param 
 * @return
 */
void taskMain(void)
{
  while (1)
  {
  }
}

void flashOverCanHandle()
{
  STOS_CAN_PDU_Flash_Over_Can FOCMessage;
#ifdef contextSwitch
    while (1)
    {
#endif
    if (MS4_CAN.receiveMessage(&FOCMessage))
      {
      FOCMessage.unbuild();
        if (FOCMessage.ADCAN_EL_FoC_1.value == STOS_current_ECU_ID)
              {
                // StallardOS::goBootloader();
              }
          }
      }
#ifdef contextSwitch
      StallardOS::delay(100);
    }
#endif

/**
 * Create StallardOS RTOS.
 *
 * @param
 * @return
 */
StallardOS::StallardOS()
{
  //Basiswerte Initialisieren
  first_function_struct = nullptr;
  currentTask = nullptr;
  TCBsCreated = 0;
  //Für Context Switch
  createTCBs();
#ifdef contextSwitch
  taskMainStruct = addFunction(taskMain, -2, 255);
  if(taskMainStruct == nullptr) while(1);
  SysTick_Config((uint32_t)(168000000 / sysTickFreq));
  NVIC_EnableIRQ(SysTick_IRQn);
  
  // addFunction(flashOverCanHandle, -3, 3);
#endif
}

/**
 * Create Task control blocks.
 *
 * @param
 * @return
 */
void StallardOS::createTCBs()
{
  if (TCBsCreated >= countTasks) //Wenn schon genug TCBs erstellt wurden, nicht nochmal erstellen
  {
    return;
  }

  for (uint8_t i = 0; i < countTasks; i++)
  {
    struct function_struct *temp;
    temp = &taskArray[i]; //new struct function_struct;
    if (temp == nullptr)  //Wenn kein HEAP Platz mehr frei ist...
    {
      return; //Aus der Funktion rausspringen
    }

    if (first_function_struct == nullptr) //Wenn noch keine funktion hinzugefügt wurde
    {
      first_function_struct = temp; //Funktion als erste setzen
      temp->next = temp;
      temp->prev = temp;
    }
    else //wenn bereits eine funktion hinzugefügt wurde
    {
      temp->next = first_function_struct;
      first_function_struct->prev->next = temp;
      temp->prev = first_function_struct->prev;
      first_function_struct->prev = temp;
    }
    //alle Werte übertragen
    temp->function = nullptr;
    temp->priority = -1;

    temp->id = -1;
#ifdef contextSwitch
    temp->State = NEW;                        //New Task
    temp->Stack = temp->vals + sizeStack - 4; //End of Stack
#endif
#ifndef contextSwitch
    temp->lastExecTime = 0;
    temp->frequency = 0;
    temp->executable = true;
#endif
    temp->used = false;
    temp->continueInMS = 0;

    TCBsCreated++;
  }
}

#ifdef contextSwitch
/**
 * Add a new Task to execute list.
 *
 * @param function Task to execute.
 * @param id unique id of the task.
 * @param prio priority of the task, lower means higher.
 * @param refreshRate frequency of execution.
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunction(void (*function)(), uint16_t id, uint8_t prio, uint16_t refreshRate)
#else
/**
 * Add a new Task to execute list.
 *
 * @param function Task to execute.
 * @param id unique id of the task.
 * @param prio priority of the task, lower means higher.
 * @param exec_freq frequency of execution through the normal scheduler.
 * @param Execcount amount of executes of this task, no value is endless.
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunction(void (*function)(), uint16_t id, uint8_t prio, uint16_t exec_freq, uint16_t Execcount)
#endif
{
  if (function == nullptr || searchFunction(id) != nullptr || refreshRate > 1000) //Make sure the parameters are correct
  {
    return nullptr;
  }
#ifndef contextSwitch
  if (exec_freq == 0)
  {
    return nullptr;
  }
#endif

  struct function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct

  function_struct_ptr = searchFreeFunction();
  if (function_struct_ptr == nullptr)
  {
    //function_struct_ptr = new struct function_struct; //ein neues erstellen
    //if (function_struct_ptr == nullptr)               //Wenn kein HEAP Platz mehr frei ist...
    //{
    return nullptr; //Aus der Funktion rausspringen
    //}
  }

  if (first_function_struct == nullptr) //Wenn schon funktionen hinzugefügt wurden
  {
    return nullptr;
  }

  //alle Werte übertragen
  function_struct_ptr->function = function;
  function_struct_ptr->executable = true;
  function_struct_ptr->priority = prio;
  function_struct_ptr->id = id;
  function_struct_ptr->error = 0;

#ifdef contextSwitch
  function_struct_ptr->refreshRate = refreshRate;
  function_struct_ptr->lastYield = 0;
  function_struct_ptr->State = NEW;                                       //New Task
  function_struct_ptr->Stack = function_struct_ptr->vals + sizeStack - 4; //End of Stack
#else
  function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet
  function_struct_ptr->frequency = exec_freq;
#endif
  function_struct_ptr->used = true;
  function_struct_ptr->waitingForSemaphore = 0;
  function_struct_ptr->continueInMS = 0;
  return function_struct_ptr;
}

/**
 * Here we en/disable a Task from the List.
 *
 * @param id unique id of the task.
 * @param act boolean value, activation of task.
 */
void StallardOS::changeFunctionEnabled(uint16_t id, bool act)
{
  struct function_struct *temp = searchFunction(id); //Funktion suchen
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    temp->executable = act;
  }
}

/**
 * Sets new Priority of a Task
 *
 * @param id unique id of the task.
 * @param prio new priority, lower means higher
 */
void StallardOS::setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio)
{
  struct function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio; //Die Priorität ändern
  }
}

void StallardOS::switchPrivilegeLevel(bool status)
{
  if(status == false)
  {
    asm("SVC #4");
  }
  else
  {
    asm("SVC #3");
  }
  
}

/**
 * Search a task in the list
 *
 * @param id unique id of the task.
 * @return pointer to the tcb with the task
 */
struct function_struct *StallardOS::searchFunction(/*ID*/ uint16_t id)
{
  uint16_t i = 0;
  struct function_struct *temp = first_function_struct; //temporärer pointer erzeugen

  if (temp == nullptr)
  {
    return nullptr;
  }

  while (temp->id != id) //Solange Funktion noch nicht gefunden wurde
  {
    if (temp != first_function_struct || i == 0)
    {
      temp = temp->next; //wenn nicht nächstes element anschauen
      i++;
    }
    else
    {
      return nullptr; //wenn am ende der liste angekommen aufhören und zurück in main springen
    }
  }
  //Hier haben wir das richtige element schon gefunden -> temp
  return temp; //Element übergeben
}

/**
 * search a tcb that is currently not used
 *
 */
struct function_struct *StallardOS::searchFreeFunction(void)
{
  uint16_t i = 0;
  struct function_struct *temp = first_function_struct; //temporärer pointer erzeugen

  if (temp == nullptr)
  {
    return nullptr;
  }

  while (temp->used) //Solange Funktion noch nicht gefunden wurde
  {
    if (temp != first_function_struct || i == 0)
    {
      temp = temp->next; //wenn nicht nächstes element anschauen
      i++;
    }
    else
    {
      return nullptr; //wenn am ende der liste angekommen aufhören und zurück in main springen
    }
  }
  //Hier haben wir das richtige element schon gefunden -> temp
  return temp; //Element übergeben
}

/**
 * delay for an amount of milliseconds
 *
 * @param milliseconds the amount of msec to wait.
 */
void StallardOS::delay(uint32_t milliseconds)
{
  if(currentTask == nullptr) //wenn im bootup
  {
    uint64_t continueTimeStamp = msCurrentTimeSinceStart + (milliseconds * 1000);
    while (msCurrentTimeSinceStart < continueTimeStamp);
  }
  currentTask->continueInMS += milliseconds; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird

#ifdef contextSwitch
  StallardOS_delay();
#else
  uint64_t continueTimeStamp = msCurrentTimeSinceStart + (milliseconds * 1000);
  while (msCurrentTimeSinceStart < continueTimeStamp);
#endif
}

/**
 * Make sure the Task has a predefined refresh rate that must be held
 * The Task gets executed every (1 / refreshRate) seconds
 *
 * @param id unique id of the task.
 * @param prio new priority, lower means higher
 */
void StallardOS::yield()
{
  if (currentTask->refreshRate != 0)
  {
    if (currentTask->lastYield + (1000 / currentTask->refreshRate) > getRuntimeMs()) //If task takes longer than expected
    {
      currentTask->error++;
    }
    else if (currentTask->error > 0) //if not and errors happened
    {
      currentTask->error--;
    }
    currentTask->continueInMS = (1000 / currentTask->refreshRate) - (getRuntimeMs() - currentTask->lastStart); //Calculate next execution time so we can hold the refresh rate
    currentTask->lastYield = getRuntimeMs();
// currentTask->executable = false;
#ifdef contextSwitch
    StallardOS_delay();
#endif
    currentTask->lastStart = getRuntimeMs();
  }
}

/**
 * Check the state of a task
 *
 * @param id unique id of the task.
 * @return state of the task, see taskstate enum
 */
#ifdef contextSwitch
taskState StallardOS::getFunctionState(/*Funktion*/ uint16_t id)
{
  struct function_struct *temp = searchFunction(id); //Hier die Funktion suchen
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    return temp->State;
  }
  else //Ansonsten
  {
    return STOPPED;
  }
}

uint8_t StallardOS::getCPUload()
{
  float val;
  val = (1.0 - float(taskMainTime) / float(getRuntimeMs())) * 100.0;
  return val;
}

#endif

/**
 * Start the StallardOS operating system
 *
 */
void StallardOS::startOS(void)
{
  enable_interrupts();
  if (first_function_struct != nullptr)
  {
    currentTask = first_function_struct; //The current Task is the first one in the List
#ifdef contextSwitch
    NVIC_EnableIRQ(SVCall_IRQn);
    asm("MRS R0, MSP");
    asm("SUB R0, #100"); //Reserve some space for Handlers (100*4 Byte)
    asm("MSR PSP, R0");
    asm("MOV R0, #3");
    asm("MSR CONTROL, R0");
    asm("ISB");
    StallardOS_start();
#else
    while (SysTick_Config(SystemCoreClock / (uint32_t)1000)) //millisecond counter
      ;
    NVIC_SetPriority(SysTick_IRQn, 0x00);
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(FPU_IRQn);
#endif
  }
}

/**
 * Search a task in the list
 *
 * @param id unique id of the task.
 * @param exec_freq new execution frequency of the task
 */
#ifndef contextSwitch
void StallardOS::setFunctionFrequency(/*Funktion*/ uint16_t id, float exec_freq)
{
  if (exec_freq <= 0) //Make sure the parameters are correct
  {
    return;
  }

  function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                        //Wenn die übergebene Funktion gültig ist
  {
    temp->frequency = exec_freq; //Die Frequenz ändern
  }
}
#endif

uint64_t StallardOS::getRuntimeMs()
{
  return msCurrentTimeSinceStart;
}

uint64_t StallardOS::getRuntimeUs()
{
  return usCurrentTimeSinceStart;
}

void StallardOS::goBootloader()
{
  StallardOS_goBootloader();
}

/**
 * Basic scheduling algorithm
 *
 */
#ifndef contextSwitch
void StallardOS::schedule()
{
  // uint16_t endOfList = 0;                     //Merker für das traversieren der Liste
  function_struct *function_struct_ptr;       //Pointer auf Structs zu den Funktionen mit dem ich arbeite
  lastScheduleTime = msCurrentTimeSinceStart; //Jetzige Schedule Zeit speichern

  function_struct_ptr = first_function_struct->next;
  // endOfList = 0;
  while (function_struct_ptr != first_function_struct)
  {
    if (function_struct_ptr->frequency <= 0 || function_struct_ptr->used == 0)
    {
      function_struct_ptr = function_struct_ptr->next;
      continue;
    }
    if ((function_struct_ptr->lastExecTime + (1000.0 / function_struct_ptr->frequency)) < msCurrentTimeSinceStart && function_struct_ptr->priority < 255)
    {
      function_struct_ptr->lastExecTime = msCurrentTimeSinceStart;
      (*function_struct_ptr->function)();
      break;
    }
    function_struct_ptr = function_struct_ptr->next;
  }
}
#endif