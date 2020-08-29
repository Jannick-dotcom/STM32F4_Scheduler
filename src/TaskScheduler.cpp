#include "TaskScheduler.hpp"

extern uint8_t switchEnable;
extern function_struct *currentTask;
extern function_struct *taskMainStruct;

////////////////////////////////////////////////////////////////////////////////////////
//Just if no other Tasks have to be executed run this
////////////////////////////////////////////////////////////////////////////////////////
void taskMain(void) //Hier wird die Überschüssige Zeit verbraten
{
  while(1)
  {

  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Constructor - Here we Create a TaskScheduler Object
////////////////////////////////////////////////////////////////////////////////////////
TaskScheduler::TaskScheduler()
{
  //Basiswerte Initialisieren
  first_function_struct = nullptr;
  currentTask = nullptr;
  
  //Für Context Switch
  taskMainStruct = addFunction(taskMain, 0, 255, 1);
  currentTask = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Adds a new Task to the List of executable ones
////////////////////////////////////////////////////////////////////////////////////////
function_struct *TaskScheduler::addFunction(void (*function)(), uint16_t id, uint8_t prio, float exec_freq, uint16_t Execcount)
{
  if (function == nullptr || exec_freq <= 0 || searchFunction(id) != nullptr) //Make sure the parameters are correct
  {
    return nullptr;
  }

  function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct
  
  asm("SVC #4");
  function_struct_ptr = new function_struct;      //ein neues erstellen
  asm("SVC #5");

  if (function_struct_ptr == nullptr) //Wenn kein HEAP Platz mehr frei ist...
  {
    return nullptr; //Aus der Funktion rausspringen
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
  // function_struct_ptr->frequency = exec_freq;
  function_struct_ptr->id = id;
  // function_struct_ptr->lastExecTime = 0;

  function_struct_ptr->State = NEW; //New Task
  function_struct_ptr->continueInMS = 0;

  function_struct_ptr->Stack = function_struct_ptr->vals + sizeStack - 4; //End of Stack

  // function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet
  return function_struct_ptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Here we en/disable a Task from the List
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::changeFunctionEnabled(uint16_t id, bool act)
{
  function_struct *temp = searchFunction(id); //Funktion suchen
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    temp->executable = act;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Sets new Priority of a Task
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio)
{
  function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio; //Die Priorität ändern
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Search a task in the list of executable ones
////////////////////////////////////////////////////////////////////////////////////////
function_struct *TaskScheduler::searchFunction(/*ID*/ uint16_t id)
{
  uint16_t i = 0;
  function_struct *temp = first_function_struct; //temporärer pointer erzeugen

  if(temp == nullptr)
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
//Delay for an amount of milliseconds
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::delay(uint32_t milliseconds)
{
  currentTask->continueInMS = milliseconds; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird
  currentTask->executable = false;
  asm("MOV R7, #2");      //Signal to SVC that he got called from delay
  asm("SVC 0x00");
}

////////////////////////////////////////////////////////////////////////////////////////
//Return the State of the Task
////////////////////////////////////////////////////////////////////////////////////////
taskState TaskScheduler::getFunctionState(/*Funktion*/ uint16_t id)
{
  function_struct *temp = searchFunction(id); //Hier die Funktion suchen
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    return temp->State;
  }
  else                                          //Ansonsten
  {
    return STOPPED;
  }
}

function_struct::~function_struct() //Destructor
{
  if(this != taskMainStruct)
  {
    this->next->prev = this->prev;
    this->prev->next = this->next;
  }
}