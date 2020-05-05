#ifndef Task_Scheduler
#define Task_Scheduler

#define Task_Fair           //nach priorität und hinzufügunsreihenfolge ausführen
//#define Task_Priority     //nach Prioritätsreihenfolge ausführen

#define On_PIO              //IDE spezifizieren
//#define Debug_TS            //Debugging signalisieren

#ifdef Debug_TS
  #warning Debugging ist aktiviert
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



struct function_struct
{
  function_struct* prev;    //für verkettete liste
  function_struct* next;    //für verkettete liste

  void (*function)();       //Auszuführende Funktion
  uint8_t priority;         //Priorität
  float frequency;          //Soll ... mal pro sekunde ausgeführt werden
  bool limitedAmount;       //Soll eine begrenzte Anzahl an ausführungen haben?
  uint16_t numberOfExecs;   //Wie oft soll die Funktion noch ausgeführt werden
  uint32_t countOver;       //Anzahl der Overflows bei der letzten ausführung
  uint64_t lastExecTime;    //Letzter Zeitpunkt der ausführung
  uint16_t id;               //ID des Tasks -> maximal 16 536 Tasks
};

class TaskScheduler
{
  /////////Variables
private:
  uint8_t maxPrio;          //Variable für die maximale Prio
  uint8_t currPrio;         //Zählvariable für Priorität
  uint8_t count;            //count of the functions added
  function_struct *first_function_struct; //Pointer auf das erste erstellte Function struct
  uint32_t lastScheduleTime;//Die letzte Zeit an der der Scheduler ausgeführt wurde
  uint32_t numberOverflows; //Anzahl der Overflows seit Start

  function_struct *searchFunction(/*Funktion*/void (*function)());
public:
  /////////Methods////////////
  TaskScheduler(); //constructor
  void addFunction(/*Funktion*/void (*function)(), /*Prioritaet*/ uint8_t prio, /*Executions per sec*/ float exec_freq, /*Number of execs*/ uint16_t Execcount = 0);
  void removeFunction(/*Funktion*/void (*function)()); //Eine Funktion aus der Liste löschen
 
  //Setter Methods
  void setPriority(/*Funktion*/void (*function)(), uint8_t prio);
  void setFrequency(/*Funktion*/void (*function)(), float exec_freq);

  void schedule(); //Execute in the Loop
};
#endif //Task_Scheduler
