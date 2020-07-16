#include "TaskScheduler.hpp"

extern uint8_t switchEnable;
extern function_struct *currentTask;
extern function_struct *taskMainStruct;

////////////////////////////////////////////////////////////////////////////////////////
//Returns the maximum Unsigned Value of a Type
////////////////////////////////////////////////////////////////////////////////////////
template <class T> //Für alle Datentypen
T maxInt(T val)
{
  //einfach -1 zurückgeben -> Zweierkomplement (0b1111111...) -> unsigned -> maximale Zahl
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////////
//Just if no other Tasks have to be executed run this
////////////////////////////////////////////////////////////////////////////////////////
void taskMain(void) //Hier wird die Überschüssige Zeit verbraten
{
  while(1);
}

////////////////////////////////////////////////////////////////////////////////////////
//Constructor - Here we Create a TaskScheduler Object
////////////////////////////////////////////////////////////////////////////////////////
TaskScheduler::TaskScheduler()
{
  //Basiswerte Initialisieren
  first_function_struct = nullptr;
  lastScheduleTime = 0;

  //Für Context Switch
  taskMainStruct = addFunction(taskMain, 0, 255, 1);
  switchEnable = 0; //Jetzt noch kein Kontext switch erlauben
  currentTask = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Adds a new Task to the List of executable ones
////////////////////////////////////////////////////////////////////////////////////////
function_struct *TaskScheduler::addFunction(void (*function)(), uint16_t id, uint8_t prio, float exec_freq, uint16_t Execcount)
{
  if (function == nullptr || exec_freq <= 0 && searchFunction(id) == nullptr) //Make sure the parameters are correct
  {
    return nullptr;
  }

  function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct
  function_struct_ptr = new function_struct;      //ein neues erstellen

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
  function_struct_ptr->frequency = exec_freq;
  function_struct_ptr->id = id;

  function_struct_ptr->State = NEW; //New Task
  function_struct_ptr->continueInMS = 0;

  function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet
  return function_struct_ptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Here the normal Tasks get executed after another
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::schedule()
{
  uint16_t endOfList = 0;               //Merker für das traversieren der Liste
  function_struct *function_struct_ptr; //Pointer auf Structs zu den Funktionen mit dem ich arbeite
  uint32_t currmicros = get_us;         //jetzige Systemzeit ermitteln und mit ihr weiterarbeiten

  if (currmicros < lastScheduleTime) //Wenn timer übergelaufen ist
  {
    function_struct_ptr = first_function_struct; //Das erste Struct nehmen
    while (1)                                    //Solange Funktionen angelegt wurden
    {
      if (!(function_struct_ptr == first_function_struct && endOfList != 0)) //Wenn wieder beim ersten angelangt
      {
        break; //aus der Schleife raus
      }
      endOfList++;                                                                                                                                 //Merker hochzählen
      function_struct_ptr->lastExecTime = (1000000.0 / function_struct_ptr->frequency) - (maxInt(currmicros) - function_struct_ptr->lastExecTime); //neu berechnen wann diese Funktion zuletzt ausgeführt wurde
      function_struct_ptr = function_struct_ptr->next;                                                                                             //nächste funktion nehmen
    }
  }

  lastScheduleTime = currmicros; //Jetzige Schedule Zeit speichern

  function_struct_ptr = first_function_struct;
  endOfList = 0;
  while (!endOfList)
  {
    if ((function_struct_ptr->lastExecTime + (1000000.0 / function_struct_ptr->frequency)) < currmicros && function_struct_ptr->priority < 255)
    {
      function_struct_ptr->lastExecTime = currmicros;
      if (!switchEnable)
        (*function_struct_ptr->function)();
      break;
    }
    function_struct_ptr = function_struct_ptr->next;
    if (function_struct_ptr == first_function_struct)
    {
      endOfList = 1;
    }
  }
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

void TaskScheduler::removeFunction(uint16_t id)
{
  function_struct *temp = searchFunction(id);
  temp->removeFunction();
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
//Sets new Frequency of a Task
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::setFunctionFrequency(/*Funktion*/ uint16_t id, float exec_freq)
{
  if (exec_freq <= 0) //Make sure the parameters are correct
  {
    return;
  }

  function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    temp->frequency = exec_freq; //Die Frequenz ändern
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Activate or Deactivate context switching
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::setContextSwitch(uint8_t enable)
{
  switchEnable = enable; //Jetzt Kontext switch erlauben
}

////////////////////////////////////////////////////////////////////////////////////////
//Search a task in the list of executable ones
////////////////////////////////////////////////////////////////////////////////////////
function_struct *TaskScheduler::searchFunction(/*ID*/ uint16_t id)
{
  uint16_t i = 0;
  function_struct *temp = first_function_struct; //temporärer pointer erzeugen

  while (temp->id != id) //Solange Funktion noch nicht gefunden wurde
  {
    if (!(temp == first_function_struct && i != 0))
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
void TaskScheduler::delay(float milliseconds)
{
  currentTask->continueInMS = milliseconds; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird
  currentTask->executable = false;
  asm("SVC 0x00");
}

////////////////////////////////////////////////////////////////////////////////////////
//Remove the Function after it ended
////////////////////////////////////////////////////////////////////////////////////////
void function_struct::removeFunction()
{
  if (this->next != nullptr)
    this->next->prev = this->prev;
  if (this->prev != nullptr)
    this->prev->next = this->next;
  delete this;
}

////////////////////////////////////////////////////////////////////////////////////////
//Return the State of the Task
////////////////////////////////////////////////////////////////////////////////////////
taskState TaskScheduler::getFunctionState(/*Funktion*/ uint16_t id)
{
  function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    return temp->State;
  }
  else
  {
    return STOPPED;
  }
}