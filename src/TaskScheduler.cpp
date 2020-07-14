#include "TaskScheduler.hpp"

extern uint8_t switchEnable;
extern function_struct *currentTask;

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
//Constructor - Here we Create a TaskScheduler Object
////////////////////////////////////////////////////////////////////////////////////////
TaskScheduler::TaskScheduler()
{
  //Basiswerte Initialisieren
  maxPrio = 0;
  //currPrio = 0;
  count = 0;
  first_function_struct = nullptr;
  lastScheduleTime = 0;

  //Für Context Switch
  switchEnable = 0; //Jetzt noch kein Kontext switch erlauben
  currentTask = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Adds a new Task to the List of executable ones
////////////////////////////////////////////////////////////////////////////////////////
uint8_t TaskScheduler::addFunction(void (*function)(), uint8_t prio, float exec_freq, uint16_t Execcount)
{
  if (function == nullptr || exec_freq <= 0) //Make sure the parameters are correct
  {
    return 0;
  }

  function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct
  function_struct_ptr = new function_struct;      //ein neues erstellen

  if (function_struct_ptr == nullptr) //Wenn kein HEAP Platz mehr frei ist...
  {
    return 0; //Aus der Funktion rausspringen
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
  function_struct_ptr->id = count;

  function_struct_ptr->State = NEW; //New Task
  function_struct_ptr->continueInMS = 0;

  if (prio > maxPrio)
  {
    maxPrio = prio; //Maximale Priorität updaten
  }
  function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet
  count = count + 1;                     //Funktionszähler inkrementieren
  return 1;
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
    if ((function_struct_ptr->lastExecTime + (1000000.0 / function_struct_ptr->frequency)) < currmicros)
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
void TaskScheduler::changeFunctionEnabled(void (*function)(), bool act)
{
  if (function == nullptr) //Make sure the parameters are correct
  {
    return;
  }
  function_struct *temp = searchFunction(function); //Funktion suchen
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    temp->executable = act;
  }
}

void TaskScheduler::removeFunction(void (*function)())
{
  if (function == nullptr)
  {
    return;
  }
  function_struct *temp = searchFunction(function);
  if (temp != nullptr)
  {
    if (temp->next != nullptr)
      temp->next->prev = temp->prev;
    if (temp->prev != nullptr)
      temp->prev->next = temp->next;
    delete temp;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Sets new Priority of a Task
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::setFunctionPriority(/*Funktion*/ void (*function)(), uint8_t prio)
{
  if (function == nullptr) //Make sure the parameters are correct
  {
    return;
  }

  function_struct *temp = searchFunction(function); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio; //Die Priorität ändern
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Sets new Frequency of a Task
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::setFunctionFrequency(/*Funktion*/ void (*function)(), float exec_freq)
{
  if (function == nullptr || exec_freq <= 0) //Make sure the parameters are correct
  {
    return;
  }

  function_struct *temp = searchFunction(function); //Hier die Funktion speichern von der die Priorität geändert werden soll
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
function_struct *TaskScheduler::searchFunction(/*Funktion*/ void (*function)())
{
  uint16_t i = 0;
  function_struct *temp = first_function_struct; //temporärer pointer erzeugen
  if (function == nullptr)                       //Make sure the parameters are correct
  {
    return nullptr;
  }

  while (temp->function != function) //Solange Funktion noch nicht gefunden wurde
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