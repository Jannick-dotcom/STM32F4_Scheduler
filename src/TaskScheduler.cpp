#include "TaskScheduler.hpp"

extern uint8_t switchEnable;
extern function_struct *currentTask;

template <class T> //Für alle Datentypen
T maxInt(T val)
{
  //einfach -1 zurückgeben -> Zweierkomplement (0b1111111...) -> unsigned -> maximale Zahl
  return -1;
}

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

uint8_t TaskScheduler::addFunction(void (*function)(), uint8_t prio, float exec_freq, uint16_t Execcount)
{
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
  function_struct_ptr->numberOfExecs = Execcount;
  function_struct_ptr->limitedAmount = Execcount > 0; //Nur wenn die Anzahl der execs > 0 -> führe Funktion nur so oft aus
  function_struct_ptr->priority = prio;
  function_struct_ptr->frequency = exec_freq;
  function_struct_ptr->id = count;
  /*function_struct_ptr->Stack = (uint32_t *)((malloc(stackSize * sizeof(uint32_t))));
  if (function_struct_ptr->Stack == nullptr)                        //Out of HEAP!!!
  {
    delete function_struct_ptr;
    return 0;
  }
  function_struct_ptr->State = NEW;                                                                  //New Task
  //////////////Software saved Registers///////////////////////////////////////////////////////////////////////
  uint32_t *stackptr = (uint32_t *)(function_struct_ptr->Stack);
  //////////////Hardware Saved Registers/////////////////////////////////////////////////////////////////////
  *(stackptr + 15) = 0x01000000;                                                  //XPSR
  *(stackptr + 14) = (uint32_t)function_struct_ptr->function & (uint32_t)~1;      //PC
  *(stackptr + 13) = (uint32_t)function_struct_ptr->function;                     //LR
  *(stackptr + 12) = 0x00000012;                                                  //R12
  *(stackptr + 11) = 0x00000003;                                                  //R3
  *(stackptr + 10) = 0x00000002;                                                  //R2
  *(stackptr + 9) = 0x00000001;                                                   //R1
  *(stackptr + 8) = 0x00000000;                                                   //R0

  *(stackptr + 7) = 0x00000011;                                                   //R11
  *(stackptr + 6) = 0x00000010;                                                   //R10
  *(stackptr + 5) = 0x00000009;                                                   //R9
  *(stackptr + 4) = 0x00000008;                                                   //R8
  *(stackptr + 3) = 0x00000007;                                                   //R7
  *(stackptr + 2) = 0x00000006;                                                   //R6
  *(stackptr + 1)  = 0x00000005;                                                  //R5
  *(stackptr + 0)  = 0x00000004;                                                  //R4
*/
  if (prio > maxPrio)
  {
    maxPrio = prio; //Maximale Priorität updaten
  }
  function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet
  count = count + 1;                     //Funktionszähler inkrementieren
  return 1;
}

void TaskScheduler::schedule()
{
  uint16_t endOfList = 0;               //Merker für das traversieren der Liste
  function_struct *function_struct_ptr; //Pointer auf Structs zu den Funktionen mit dem ich arbeite
  uint32_t currmicros = get_us;         //jetzige Systemzeit ermitteln und mit ihr weiterarbeiten

  if (currmicros < lastScheduleTime)    //Wenn timer übergelaufen ist
  {
    function_struct_ptr = first_function_struct; //Das erste Struct nehmen
    while (1)                                    //Solange Funktionen angelegt wurden
    {
      if (!(function_struct_ptr == first_function_struct && endOfList != 0))  //Wenn wieder beim ersten angelangt
      {
        break;  //aus der Schleife raus
      }
      endOfList++;    //Merker hochzählen
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

void TaskScheduler::removeFunction(void (*function)())
{
  function_struct *temp = searchFunction(function); //Funktion suchen
  if (temp != nullptr)                              //Wenn die gefundene Funktion gültig ist
  {
    temp->next->prev = temp->prev; //Link von nächstem auf vorherigen
    temp->prev->next = temp->next; //Link von vorherigem zum nächsten
    //jetzt können wir dieses Element komplett vom speicher löschen
    delete temp->Stack;
    delete temp; //Speicher wieder freigeben
    count--;
  }
}

void TaskScheduler::setPriority(/*Funktion*/ void (*function)(), uint8_t prio)
{
  function_struct *temp = searchFunction(function); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio; //Die Priorität ändern
  }
}

void TaskScheduler::setFrequency(/*Funktion*/ void (*function)(), float exec_freq)
{
  function_struct *temp = searchFunction(function); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                              //Wenn die übergebene Funktion gültig ist
  {
    temp->frequency = exec_freq; //Die Frequenz ändern
  }
}

void TaskScheduler::setContextSwitch(uint8_t enable)
{
  switchEnable = enable; //Jetzt Kontext switch erlauben
}

void TaskScheduler::startOS(void)
{
  currentTask = first_function_struct;
  currentTask->State = NEW;
  setContextSwitch(true);
  SysTick_Config(SystemCoreClock / 1000);
  NVIC_SetPriority(PendSV_IRQn, 0xff); /* Lowest possible priority */
	NVIC_SetPriority(SysTick_IRQn, 0x00); /* Highest possible priority */
  __set_PSP(__get_MSP());
  __set_CONTROL(0x03); /* Switch to Unprivilleged Thread Mode with PSP */
  __ISB();
}

function_struct *TaskScheduler::searchFunction(/*Funktion*/ void (*function)())
{
  uint16_t i = 0;
  function_struct *temp = first_function_struct; //temporärer pointer erzeugen
  while (temp->function != function)             //Solange Funktion noch nicht gefunden wurde
  {
    if (!(temp == first_function_struct && i != 0))
    {
      temp = temp->next; //wenn nicht nächstes element anschauen
      i++;
    }
    return nullptr; //wenn am ende der liste angekommen aufhören und zurück in main springen
  }
  //Hier haben wir das richtige element schon gefunden -> temp
  return temp; //Element übergeben
}