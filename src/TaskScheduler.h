#ifndef Task_Scheduler
#define Task_Scheduler

////////////Scheduler Mode////////////////////
#define Task_Fair  //nach priorität und hinzufügunsreihenfolge ausführen
#define Task_other //nach Prioritätsreihenfolge ausführen

////////////ContextSwitch/////////////////////
#define Task_contextSwitch  //Content switching aktivieren
#define stackSize 16 //60

////////////IDE///////////////////////////////
#define On_PIO //IDE spezifizieren
//#define On_Arduino

//////////////////////////////////////////////

#ifdef Debug_TS
#warning TimerOverflow Debugging ist aktiviert
#endif

#ifdef On_Arduino
#include <Arduino.h>
#define get_us micros
#endif

#ifdef On_PIO
#include <mbed.h>
#include <stdint.h>
#define get_us us_ticker_read()
#endif

typedef enum {
  NEW,
  RUNNING,
  STOPPED
} taskState;

struct function_struct
{
  //Verkettete Liste
  function_struct *prev; //für verkettete liste
  function_struct *next; //für verkettete liste

  //Must have Variablen
  void (*function)();     //Auszuführende Funktion
  uint8_t priority;       //Priorität
  float frequency;        //Soll ... mal pro Sekunde ausgeführt werden
  bool limitedAmount;     //Soll eine begrenzte Anzahl an Ausführungen haben?
  uint16_t numberOfExecs; //Wie oft soll die Funktion noch ausgeführt werden
  uint64_t lastExecTime;  //Letzter Zeitpunkt der Ausführung
  uint16_t id;            //ID des Tasks

  //KontextSwitch
  uint32_t arr[40];
  taskState State;        //Status des Tasks
  uint32_t *Stack;
  uint32_t Stackpointer;
};

class TaskScheduler
{
  /////////Variables
public:
  uint8_t maxPrio;                        //Variable für die maximale Prio
  //uint8_t currPrio;                     //Zählvariable für Priorität
  uint8_t count;                          //count of the functions added
  function_struct *first_function_struct; //Pointer auf das erste erstellte Function struct
  uint32_t lastScheduleTime;              //Die letzte Zeit an der der Scheduler ausgeführt wurde
                                          //Wichtig für Overflow Handling

public:
  //Constructor
  TaskScheduler(); //Create a Task Scheduler

  //Function Methods
  void addFunction(
    /*Funktion*/ void (*function)(), 
    /*Prioritaet*/ uint8_t prio, 
    /*Executions per sec*/ float exec_freq, 
    /*Number of execs*/ uint16_t Execcount = 0);

  void removeFunction(/*Funktion*/ void (*function)()); //Eine Funktion aus der Liste löschen

private:
  function_struct *searchFunction(/*Funktion*/ void (*function)());

public:
  //Setter Methods
  void setPriority(/*Funktion*/ void (*function)(), uint8_t prio);
  void setFrequency(/*Funktion*/ void (*function)(), float exec_freq);
  
  void activateContextSwitch(void);

  //Main Loop Method
  void schedule(); //Execute in the Loop
};
#endif //Task_Scheduler
