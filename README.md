# **STM32F4_SOS_94**
## **Stallardo Operating System**
**StallardOS**

Unterschied zu mbed???
- Braucht ein Bruchteil der Zeit zum Kompilieren
- Bessere Nachvollziehbarkeit
- Einfachere Konfigurierbarkeit
- Genau auf unsere Steuergeräte im Rennstall zugeschnitten

### **StallardOS:**
[HeaderFile](include/StallardOS.hpp)
```
StallardOS();  
**Erzeuge ein StallardOS**  
Es wird nur ein StallardOS pro CPU Kern benötigt  
```
```
void addFunction(void (*function)(), uint16_t id, uint8_t prio);
**Funktion hinzufügen**  
void (*function)()      ->  Funktion, die hinzugefügt werden soll
uint16_t id             ->  Eindeutige ID des Tasks - (2 identische möglich)
uint8_t prio            ->  Priorität der Funktion (kleiner ist höher)
```
```
void setFunctionPriority(uint16_t id, uint8_t prio);
**Priorität verändern**  
uint16_t id             ->   ID der Funktion
uint8_t prio            ->   Neue Priorität  
```
```
taskState getFunctionState(/*Funktion*/ uint16_t id);
**Überprüfen ob ein Task läuft**
uint16_t id             ->   ID der Funktion
```
```
void startOS();
**Starten des OS** 
```
```
void delay(uint32_t milliseconds);
**Warte x millisekunden**
uint32_t milliseconds   ->  Wartedauer
```
```
void changeFunctionEnabled(uint16_t id, bool act);
**Eine Funktion aus der Liste de/aktivieren**
uint16_t id             ->  ID der Funktion
bool act                ->  De/Aktivieren
```

### **StallardOSCAN:**
[HeaderFile](include/can.h)
```
StallardOSCAN(CANports port, CANBauds baud);
**Erzeuge ein CANBus**  
CANports port           ->  Welcher CAN Port
CANBauds baud           ->  Baudrate

bool getMessage(StallardOSCanMessage *msg);
**Hole Message vom CAN** 

void sendMessage(StallardOSCanMessage *msg);
```

### **StallardOSGPIO:**
[HeaderFile](include/GPIO.hpp)
```
StallardOSGPIO(uint8_t number, ports port, pinDir dir, pullMode pull)
**Erzeuge ein GPIO**
uint8_t number          ->  Nummer des Pins
ports port              ->  Port des Pins
pinDir dir              ->  Input oder Output
pullMode pull           ->  Pullup oder Pulldown
```

#### **Mögliche Operatoren mit GPIOs:**
```
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
```