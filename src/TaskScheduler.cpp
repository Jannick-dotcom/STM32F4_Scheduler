#include "TaskScheduler.h"

TaskScheduler::TaskScheduler()
{
  //Basiswerte Initialisieren
  maxPrio = 0;
  currPrio = 0;
  count = 0;
  first_function_struct = nullptr;
  numberOverflows = 0;
  lastScheduleTime = 0;
}

void TaskScheduler::addFunction(void (*function)(), uint8_t prio, float exec_freq, uint16_t Execcount)
{
  function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct
  function_struct_ptr = first_function_struct;  //Beim ersten Struct anfangen
  function_struct* prev = nullptr;  //Previous pointer erstellen
  
  if(first_function_struct == nullptr) //Wenn noch keine funktion hinzugefügt wurde
  {
    function_struct_ptr = new function_struct; //ein neues erstellen
    if(function_struct_ptr == nullptr) //Wenn kein HEAP Platz mehr frei ist...
    {
      return; //Aus der Funktion rausspringen
    }
    first_function_struct = function_struct_ptr; //Funktion als erste setzen
  }
  else //wenn bereits eine funktion hinzugefügt wurde
  {
    while(function_struct_ptr != nullptr) //Solange bereits erstellte structs drin sind
    {
      prev = function_struct_ptr; //Den letzten Struct speichern
      function_struct_ptr = function_struct_ptr->next; //Das nächste nehmen
    }
    function_struct_ptr = new function_struct; //ein neues erstellen
    if(function_struct_ptr == nullptr) //Wenn kein HEAP Platz mehr frei ist...
    {
      return; //Aus der Funktion rausspringen
    }
  }
  
    
  function_struct_ptr->prev = prev;  //Das vorherige setzen
  function_struct_ptr->prev->next = function_struct_ptr; //Das nächste des vorherigen auf dieses setzen
  function_struct_ptr->next = nullptr; //nächstes als noch nicht gesetzt festlegen

  //alle Werte übertragen
  function_struct_ptr->function = function;
  function_struct_ptr->numberOfExecs = Execcount;
  function_struct_ptr->limitedAmount = 1 & Execcount; //Nur wenn die Anzahl der execs > 0 -> führe Funktion nur so oft aus
  function_struct_ptr->priority = prio;
  function_struct_ptr->frequency = exec_freq;
  function_struct_ptr->id = count;

  if (prio > maxPrio) maxPrio = prio; //Maximale Priorität updaten
  function_struct_ptr->countOver = numberOverflows;
  function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet
  count = count + 1; //Funktionszähler inkrementieren 
}

void TaskScheduler::schedule()
{
  uint8_t flag = 0;
  function_struct *function_struct_ptr; //Pointer auf Structs zu den Funktionen mit dem ich arbeite
  #ifndef Debug_TS                      //Wenn ich nicht debugge
    uint32_t currmicros = get_us;       //jetzige Systemzeit ermitteln
  #else                                 //Wenn ich debugge
    uint32_t currmicros = get_us * 10;  //Schnellerer Überlauf
  #endif

  if(currmicros < lastScheduleTime) //Wenn dieser Pimmelticker übergelaufen ist
  {
      numberOverflows++;                //Anzahl Overflows hochzählen
      function_struct_ptr = first_function_struct;  //Das erste Element auf einen Temp pointer
      while(function_struct_ptr != nullptr)         //Solange nicht das Letzte Element
      {
        function_struct_ptr->lastExecTime = (1000000.0 / function_struct_ptr->frequency) - (UINT32_MAX - function_struct_ptr->lastExecTime); //Letzte Ausführzeit berechnen, als hätte der Overflow nie Stattgefunden
        function_struct_ptr = function_struct_ptr->next;  //Nächstes Element
      }
  }

  lastScheduleTime = currmicros;        //Diese Zeit als letzte Zeit speichern an der der Scheduler gelaufen ist

#ifdef Task_Fair
  currPrio = 0; //jetzt angeschaute Priorität auf Null initialisieren
  for (uint16_t i = 0; i < maxPrio; i++) //id hochzählen
  {
    function_struct_ptr = first_function_struct; //Beim ersten anfangen
    while(function_struct_ptr != nullptr) //functions durchzählen
    {
      if (function_struct_ptr->id == i) //Wenn ID übereinstimmt
      {
        if ((function_struct_ptr->lastExecTime + (1000000.0 / function_struct_ptr->frequency)) < currmicros) //Wenn es wieder Zeit für eine Ausführung ist
        {
          if((function_struct_ptr->numberOfExecs > 0 || !(function_struct_ptr->limitedAmount))) //Wenn noch Ausführungen übrig sind
          {
            function_struct_ptr->lastExecTime = currmicros; //Die Zeit vor Anfang der Ausführung speichern
            function_struct_ptr->countOver = numberOverflows;
            (function_struct_ptr->function)();  //Hier die Funktion ausführen
            if(function_struct_ptr->limitedAmount) //Wenn die Funktion nur eine begrenzte Anzahl ausgeführt werden soll
            {
              function_struct_ptr->numberOfExecs--; //Zähler um eins dekrementieren
            }
            flag = 1;
            break;
          }
          else //Wenn keine Ausführungen mehr übrig sind
          {
            removeFunction(function_struct_ptr->function); //Speicher der gespeicherten Daten zu der Funktion wieder freigeben
          }
        }
      }
      function_struct_ptr = function_struct_ptr->next; //Zum nächsten Element der verketteten Liste übergehen
    }
    if(flag > 0) break;                                 //Wenn ausführung einer Funktion gemacht auch aus dieser FOR springen
  }
#endif
}

void TaskScheduler::removeFunction(void (*function)())
{
  function_struct* temp = searchFunction(function); //Funktion suchen
  if(temp != nullptr)   //Wenn die gefundene Funktion güötig ist
  {
    temp->next->prev = temp->prev; //Link von nächstem auf vorherigen
    temp->prev->next = temp->next; //Link von vorherigem zum nächsten
    //jetzt können wir dieses Element komplett vom speicher löschen
    delete temp; //Speicher wieder freigeben
  }
}

void TaskScheduler::setPriority(/*Funktion*/void (*function)(), uint8_t prio)
{
  function_struct* temp = searchFunction(function); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if(temp != nullptr) //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio;  //Die Priorität ändern
  }
}

void TaskScheduler::setFrequency(/*Funktion*/void (*function)(), float exec_freq)
{
  function_struct* temp = searchFunction(function); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if(temp != nullptr) //Wenn die übergebene Funktion gültig ist
  {
    temp->frequency = exec_freq; //Die Frequenz ändern
  }
}

function_struct* TaskScheduler::searchFunction(/*Funktion*/void (*function)())
{
  function_struct *temp = first_function_struct; //temporärer pointer erzeugen
  while(temp->function != function) //Solange Funktion noch nicht gefunden wurde
  {
    if(temp == nullptr) break; //wenn am ende der liste angekommen aufhören und zurück in main springen
    temp = temp->next;  //wenn nicht nächstes element anschauen
  }
  //Hier haben wir das richtige element schon gefunden -> temp
  return temp; //Element übergeben
}