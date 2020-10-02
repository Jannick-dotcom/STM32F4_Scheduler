# STM32F4_Scheduler
Rennstall Projekt


`TaskScheduler();`  
    ** Erzeuge einen Task Scheduler **  
    Es wird nur ein TaskScheduler pro CPU Kern benötigt  

`void addFunction(void (*function)(), uint8_t prio, float exec_freq = 1, uint16_t Execcount = 0);`  
    ** Funktion hinzufügen **  
    `void (*function)()`  ->  Funktion, die hinzugefügt werden soll  
    `uint8_t prio`        ->  Priorität der Funktion (kleiner ist höher)  
    `float exec_freq`     ->  Frequenz mit der die Funktion ausgeführt werden soll in Hz (nicht für context switch relevant)
    `uint16_t Execcount`  ->  Anzahl der Ausführungen (0 für unendlich -> default)  (nicht für context switch relevant)

`void setPriority(void (*function)(), uint8_t prio);`  
    ** Priorität verändern **  
    `void (*function)()` ->   Funktion die verändert werden soll  
    `uint8_t prio`       ->   Neue Priorität  

`taskState getFunctionState(/*Funktion*/ uint16_t id);`
    ** Überprüfen ob ein Task läuft
    `uint16_t id`        ->   ID der funktion

`void startOS();`  
    ** Starten des OS **  
    Nach dem Aufruf dieser Methode wird das OS gestartet und ab dann nur noch in Tasks gearbeitet
