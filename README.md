# STM32F4_Scheduler
Rennstall Projekt


## `TaskScheduler();`  
    **Erzeuge einen Task Scheduler**  
    Es wird nur ein TaskScheduler pro CPU Kern benötigt  

## `void addFunction(void (*function)(), uint8_t prio, float exec_freq, uint16_t Execcount = 0);`  
    **Funktion hinzufügen**  
    `void (*function)()`  ->  Funktion, die hinzugefügt werden soll  
    `uint8_t prio`        ->  Priorität der Funktion (kleiner ist höher)  
    `float exec_freq`     ->  Frequenz mit der die Funktion ausgeführt werden soll in Hz  
    `uint16_t Execcount`  ->  Anzahl der Ausführungen (0 für unendlich -> default)  

## `void removeFunction(void (*function)());`  
    **Funktion entfernen**  
    `void (*function)()`  ->  Funktion, die entfernt werden soll  

///////////Setter Methods/////////////////////////////////////  
## `void setPriority(void (*function)(), uint8_t prio);`  
    **Priorität verändern**  
    `void (*function)()` ->   Funktion die verändert werden soll  
    `uint8_t prio`       ->   Neue Priorität  

## `void setFrequency(void (*function)(), float exec_freq);`  
    **Priorität verändern**  
    `void (*function)()` ->   Funktion die verändert werden soll  
    `float exec_freq`    ->   Neue Ausführfrequenz  

## `void setID(void (*function)(), uint8_t ID);`  
    **Priorität verändern**  
    `void (*function)()` ->   Funktion die verändert werden soll  
    `uint8_t ID`         ->   Neue ID  

//////////////////////////////////////////////////////////////  

## `void schedule();`  
    **Alleinige Ausführung in einer endlosen Schleife**  
    Hier werden die davor hinzugefügten Funktionen getriggert  
