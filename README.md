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

**Funktion hinzufügen**
```
void addFunction(void (*function)(), uint16_t id, uint8_t prio);
```  
> void (*function)()      ->  Funktion, die hinzugefügt werden soll

> uint16_t id           ->  Eindeutige ID des Tasks - (2 identische möglich)

> uint8_t prio            ->  Priorität der Funktion (kleiner ist höher)


**Priorität verändern** 
```
void setFunctionPriority(uint16_t id, uint8_t prio);
``` 
> uint16_t id             ->   ID der Funktion

> uint8_t prio            ->   Neue Priorität  

**Überprüfen ob ein Task läuft**
```
taskState getFunctionState(/*Funktion*/ uint16_t id);
```
> uint16_t id             ->   ID der Funktion

**Starten des OS** 
```
void startOS();
```

**Warte x millisekunden**
```
void delay(uint32_t milliseconds);
```
> uint32_t milliseconds   ->  Wartedauer

**Eine Funktion aus der Liste de/aktivieren**
```
void changeFunctionEnabled(uint16_t id, bool act);
```

> uint16_t id             ->  ID der Funktion

> bool act                ->  De/Aktivieren

### **StallardOSCAN:**
[HeaderFile](include/can.h)

**Erzeuge ein CANBus** 
```
StallardOSCAN(CANports port, CANBauds baud);
```
 
> CANports port           ->  Welcher CAN Port

> CANBauds baud           ->  Baudrate

**Hole Message vom CAN** 
```
bool getMessage(StallardOSCanMessage *msg);
```

**Sende Message über CAN**
```
void sendMessage(StallardOSCanMessage *msg);
```

### **StallardOSGPIO:**
[HeaderFile](include/GPIO.hpp)

**Erzeuge ein GPIO**
```
StallardOSGPIO(uint8_t number, ports port, pinDir dir, pullMode pull)
```

> uint8_t number          ->  Nummer des Pins

> ports port              ->  Port des Pins

> pinDir dir              ->  Input oder Output

> pullMode pull           ->  Pullup oder Pulldown

### **Mögliche Operatoren mit GPIOs:**
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