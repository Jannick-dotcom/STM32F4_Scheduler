# STM32F4_ROS
Rennstall Operating System

Unterschied zu mbed???
-Braucht ein Bruchteil der Zeit zum Kompilieren
-Bessere Nachvollziehbarkeit
-Einfachere Konfigurierbarkeit
-Genau auf unsere Steuergeräte im Rennstall zugeschnitten

JANNIX:
`Jannix();`  
    **Erzeuge ein Jannix**  
    Es wird nur ein Jannix pro CPU Kern benötigt  

`void addFunction(void (*function)(), uint16_t id, uint8_t prio);`  
    **Funktion hinzufügen**  
    `void (*function)()`  ->  Funktion, die hinzugefügt werden soll
    `uint16_t id`         ->  Eindeutige ID des Tasks - (2 identische möglich)
    `uint8_t prio`        ->  Priorität der Funktion (kleiner ist höher)

`void setFunctionPriority(uint16_t id, uint8_t prio);`  
    **Priorität verändern**  
    `uint16_t id`        ->   ID der Funktion
    `uint8_t prio`       ->   Neue Priorität  

`taskState getFunctionState(/*Funktion*/ uint16_t id);`
    **Überprüfen ob ein Task läuft**
    `uint16_t id`        ->   ID der Funktion

`void startOS();`  
    **Starten des OS**  
    Nach dem Aufruf dieser Methode wird das OS gestartet und ab dann nur noch in Tasks gearbeitet

`void delay(uint32_t milliseconds);`
    **Warten für eine bestimmte Anzahl an millisekunden**
    `uint32_t milliseconds` ->  Wartedauer [ms]

`void changeFunctionEnabled(uint16_t id, bool act);`
    **Eine Funktion aus der Liste de/aktivieren**
    `uint16_t id`        ->  ID der Funktion
    `bool act`           ->  Aktivieren oder deaktivieren

JannixCAN:
`JannixCAN(CANports port, CANBauds baud);`  
    **Erzeuge ein CANBus**  
    `CANports port`      ->  Welcher CAN Port wird verwendet
    CANBauds baud        ->  Baudrate

`bool getMessage(JannixCanMessage *msg);`

`void sendMessage(JannixCanMessage *msg);`

JannixGPIO:
`JannixGPIO(uint8_t number, ports port, pinDir dir, pullMode pull)`
    **Erzeuge ein GPIO**
    `uint8_t number`     ->  Nummer des Pins auf dem Port
    `ports port`         ->  Port des Pins
    `pinDir dir`         ->  Input oder Output
    `pullMode pull`      ->  Pullup oder Pulldown

Mögliche Operatoren mit GPIOs:
    - GPIO = (bool) wert
    - GPIO = !GPIO
    - GPIO1 && GPIO2
    - GPIO1 || GPIO2
    - GPIO1 != GPIO2
    - GPIO1 < GPIO2
    - GPIO1 > GPIO2
    - GPIO1 <= GPIO2
    - GPIO1 >= GPIO2
    - GPIO1 == GPIO2
