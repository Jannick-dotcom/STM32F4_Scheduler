#include "StallardOS.hpp"

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
extern "C" void StallardOS_SetSysClock(uint8_t);
extern "C" volatile uint64_t msCurrentTimeSinceStart; //about 585 000 years of microsecond counting 

//Kontext Switch
struct function_struct *currentTask = nullptr;
struct function_struct *nextTask = nullptr;
struct function_struct *taskMainStruct = nullptr;

////////////////////////////////////////////////////////////////////////////////////////
//Just if no other Tasks have to be executed run this
////////////////////////////////////////////////////////////////////////////////////////
void taskMain(void) //Hier wird die Überschüssige Zeit verbraten
{
  while (1)
  {
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Constructor - Here we Create a StallardOS Object
////////////////////////////////////////////////////////////////////////////////////////
StallardOS::StallardOS()
{
  //Basiswerte Initialisieren
  first_function_struct = nullptr;
  currentTask = nullptr;
  TCBsCreated = 0;

  //Für Context Switch
  taskMainStruct = addFunction(taskMain, 0, 255);
  createTCBs();
}

////////////////////////////////////////////////////////////////////////////////////////
//Adds new Tasks to the List
////////////////////////////////////////////////////////////////////////////////////////
void StallardOS::createTCBs()
{
  if (TCBsCreated >= countTasks) //Wenn schon genug TCBs erstellt wurden, nicht nochmal erstellen
  {
    return;
  }

  for (uint8_t i = 0; i < countTasks; i++)
  {
    struct function_struct *temp;
    temp = new struct function_struct;
    if (temp == nullptr) //Wenn kein HEAP Platz mehr frei ist...
    {
      break; //Aus der Funktion rausspringen
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
    temp->executable = true;
    temp->priority = -1;
    // function_struct_ptr->frequency = exec_freq;
    temp->id = -1;
    // function_struct_ptr->lastExecTime = 0;

    temp->State = NEW; //New Task
    temp->used = false;
    temp->continueInMS = 0;

    temp->Stack = temp->vals + sizeStack - 4; //End of Stack
    TCBsCreated++;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Adds a new Task to the List of executable ones
////////////////////////////////////////////////////////////////////////////////////////
struct function_struct *StallardOS::addFunction(void (*function)(), uint16_t id, uint8_t prio, float exec_freq, uint16_t Execcount)
{
  if (function == nullptr || searchFunction(id) != nullptr) //Make sure the parameters are correct
  {
    return nullptr;
  }

  struct function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct

  function_struct_ptr = searchFreeFunction();
  if (function_struct_ptr == nullptr)
  {
    function_struct_ptr = new struct function_struct; //ein neues erstellen
    if (function_struct_ptr == nullptr)               //Wenn kein HEAP Platz mehr frei ist...
    {
      return nullptr; //Aus der Funktion rausspringen
    }
  }

  if (first_function_struct == nullptr) //Wenn noch keine funktion hinzugefügt wurde
  {
    first_function_struct = function_struct_ptr; //Funktion als erste setzen
    function_struct_ptr->next = function_struct_ptr;
    function_struct_ptr->prev = function_struct_ptr;
  }
  else //wenn bereits eine funktion hinzugefügt wurde
  {
    function_struct_ptr->next = first_function_struct;
    first_function_struct->prev->next = function_struct_ptr;
    function_struct_ptr->prev = first_function_struct->prev;
    first_function_struct->prev = function_struct_ptr;
  }

  //alle Werte übertragen
  function_struct_ptr->function = function;
  function_struct_ptr->executable = true;
  function_struct_ptr->priority = prio;
  function_struct_ptr->frequency = exec_freq;
  function_struct_ptr->id = id;
  function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet

  function_struct_ptr->State = NEW; //New Task
  function_struct_ptr->used = true;
  function_struct_ptr->continueInMS = 0;

  function_struct_ptr->Stack = function_struct_ptr->vals + sizeStack - 4; //End of Stack

  return function_struct_ptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Here we en/disable a Task from the List
////////////////////////////////////////////////////////////////////////////////////////
void StallardOS::changeFunctionEnabled(uint16_t id, bool act)
{
  struct function_struct *temp = searchFunction(id); //Funktion suchen
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    temp->executable = act;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Sets new Priority of a Task
////////////////////////////////////////////////////////////////////////////////////////
void StallardOS::setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio)
{
  struct function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio; //Die Priorität ändern
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Search a task in the list of executable ones/*
////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////
//Search a free task in the list
////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////
//Delay for an amount of milliseconds
////////////////////////////////////////////////////////////////////////////////////////
void StallardOS::delay(uint32_t milliseconds)
{
  currentTask->continueInMS = milliseconds; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird
  currentTask->executable = false;
  
  #ifdef contextSwitch
  StallardOS_delay();
  #else
  uint64_t continueTimeStamp = msCurrentTimeSinceStart + (milliseconds * 1000);
  while(msCurrentTimeSinceStart < continueTimeStamp);
  #endif
}

////////////////////////////////////////////////////////////////////////////////////////
//Return the State of the Task
////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////
//Set all the Interrupts and Values for the OS
////////////////////////////////////////////////////////////////////////////////////////
void StallardOS::startOS(void)
{
  StallardOS_SetSysClock(168);
  SystemCoreClockUpdate();
  enable_interrupts();
  if (first_function_struct != nullptr)
  {
    currentTask = first_function_struct; //The current Task is the first one in the List
#ifdef contextSwitch
    NVIC_EnableIRQ(SVCall_IRQn);
    asm("MRS R0, MSP");
    asm("MSR PSP, R0");
    asm("MOV R0, #2");
    asm("MSR CONTROL, R0");
    asm("ISB");
    StallardOS_start();
#else
    while (SysTick_Config(SystemCoreClock / (uint32_t)1000000)) //microsecond counter
      ;
    NVIC_SetPriority(SysTick_IRQn, 0x00);
    NVIC_EnableIRQ(SysTick_IRQn);
#endif
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Sets new Frequency of a Task
////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////
//Here the normal Tasks get executed after another
////////////////////////////////////////////////////////////////////////////////////////
void StallardOS::schedule()
{
  uint16_t endOfList = 0;                     //Merker für das traversieren der Liste
  function_struct *function_struct_ptr;       //Pointer auf Structs zu den Funktionen mit dem ich arbeite
  lastScheduleTime = msCurrentTimeSinceStart; //Jetzige Schedule Zeit speichern

  function_struct_ptr = first_function_struct->next;
  endOfList = 0;
  while (function_struct_ptr != first_function_struct)
  {
    if ((function_struct_ptr->lastExecTime + (1000000.0 / function_struct_ptr->frequency)) < msCurrentTimeSinceStart && function_struct_ptr->priority < 255)
    {
      function_struct_ptr->lastExecTime = msCurrentTimeSinceStart;
      (*function_struct_ptr->function)();
      break;
    }
    function_struct_ptr = function_struct_ptr->next;
  }
}