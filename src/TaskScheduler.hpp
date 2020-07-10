#ifndef Task_Scheduler
#define Task_Scheduler

#include <mbed.h>
#include <stdint.h>
#define get_us us_ticker_read()

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
  uint16_t id;            //ID des Tasks

  //nur für normalen Schedule betrieb
  float frequency;        //Soll ... mal pro Sekunde ausgeführt werden
  bool executable;    //Funktion ausführen?
  uint32_t lastExecTime;  //Letzter Zeitpunkt der Ausführung
  

  //nur für KontextSwitch
  volatile taskState State;        //Status des Tasks
  volatile uint32_t *Stack;         //Stack pointer
  volatile uint32_t continueInMS;   //Delay amount
};

class TaskScheduler
{
  /////////Variables
private:
  uint8_t maxPrio;                        //Variable für die maximale Prio
  uint8_t count;                          //count of the functions added
  function_struct *first_function_struct; //Pointer auf das erste erstellte Function struct

  uint32_t lastScheduleTime;              //Die letzte Zeit an der der Scheduler ausgeführt wurde
  //Wichtig für Overflow Handling

public:
  //Constructor
  TaskScheduler(); //Create a Task Scheduler

  //Function Methods
  //return Wert 1 wenn erfolgreich
  uint8_t addFunction(
    /*Funktion*/ void (*function)(), 
    /*Prioritaet*/ uint8_t prio, 
    /*Executions per sec*/ float exec_freq, 
    /*Number of execs*/ uint16_t Execcount = 0);
    //Eine Funktion zur Liste hinzufügen

  void changeFunctionEnabled(
    /*Funktion*/ void (*function)(),
    /*Aktivieren oder Deaktivieren*/ bool act); 
    //Eine Funktion aus der Liste de/aktivieren

private:
  function_struct *searchFunction(/*Funktion*/ void (*function)());

public:
  //Setter Methods
  void setFunctionPriority(/*Funktion*/ void (*function)(), uint8_t prio);
  void setFunctionFrequency(/*Funktion*/ void (*function)(), float exec_freq);
  
  void setContextSwitch(uint8_t enable);  //Kontext Switching aktivieren oder Deaktivieren
  void startOS(void);                     //RTOS Starten (preemtive Multitasking)
  void delay(uint32_t milliseconds);      //RTOS führt solange einen anderen Task aus bevor er zum jetzigen zurückspringt

  //Main Loop Method
  void schedule(); //Execute in the Loop (cooperative Multitasking)
};
#endif //Task_Scheduler
