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
  uint8_t priority;       //Priorität 0 wird nicht unterbrochen außer sie wünschen es durch ein Delay
  uint16_t id;            //ID des Tasks

  //nur für normalen Schedule betrieb
  float frequency;        //Soll ... mal pro Sekunde ausgeführt werden
  bool executable;    //Funktion ausführen?
  uint32_t lastExecTime;  //Letzter Zeitpunkt der Ausführung
  

  //nur für KontextSwitch
  volatile taskState State;        //Status des Tasks
  volatile uint32_t *Stack;         //Stack pointer
  volatile float continueInMS;   //Delay amount

  void removeFunction();
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
  function_struct *addFunction(
    /*Funktion*/ void (*function)(), 
    /*ID of task*/ uint16_t ID,
    /*Prioritaet*/ uint8_t prio,                //Tasks with prio 0 won't be interrupted and Tasks with prio 255 will only be executed to waste Time
    /*Executions per sec*/ float exec_freq = 1, //Must be bigger than 0 !
    /*Number of execs*/ uint16_t Execcount = 0);
    //Eine Funktion zur Liste hinzufügen

  void changeFunctionEnabled(
    /*Funktion*/ uint16_t id,
    /*Aktivieren oder Deaktivieren*/ bool act); 
    //Eine Funktion aus der Liste de/aktivieren

  void removeFunction(
    /*Funktion*/ uint16_t id);
    //Eine Funktion aus der Liste löschen

private:
  function_struct *searchFunction(/*Funktion*/ uint16_t id);
  
public:
  //Setter Methods
  void setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio);
  void setFunctionFrequency(/*Funktion*/ uint16_t id, float exec_freq);
  
  //Getter Methods
  taskState getFunctionState(/*Funktion*/ uint16_t id);

  //Context Switch
  void setContextSwitch(uint8_t enable);  //Kontext Switching aktivieren oder Deaktivieren
  void startOS(void);                     //RTOS Starten (preemtive Multitasking)
  void delay(float milliseconds);      //RTOS führt solange einen anderen Task aus bevor er zum jetzigen zurückspringt

  //Main Loop Method
  void schedule(); //Execute in the Loop (cooperative Multitasking)
};
#endif //Task_Scheduler
