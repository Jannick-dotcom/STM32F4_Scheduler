## **Stallardo Operating System**
**StallardOS_OS**

info STALLARDO_OS: In mache  Zeilen fehlen Komentare, bzw nicht selbstverständlich wie man die Funktion verwendet:
Z 24-29, 40-44, 94-99; 

Funktionen Erklärung:

```
function_struct *StallardOS::addFunction(void (*function)(), uint16_t id, uint8_t prio, uint16_t refreshRate)```
Erzeugt einen neue Task in die "execute list"

Funktion Parameter:
```
funktion    -> task zu ausführen
id          -> Einzigartig id der Task
prio        -> Task priorität, geringere nummer bedeutet höhere Prio.
refreshRate -> Frequenz der ausführung
return      -> Pointer zu erzeugen tbc
```

```
StallardOS::changeFunctionEnabled(uint16_t id, bool act)

Enable/disable Task aus die Task List
```

Funktion Parameter:
```
id  -> einzigartig id der Task
act -> Boolean Wert, Task aktivierung
```

```
StallardOS::setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio)

Neue Task Prioritizierung setzen
```
Funktion Parameter:
```
id  -> einzigartig id der Task
prio -> neue Task Priorität, je kleiner der Wert, desto höher Prio
```

```
function_struct *StallardOS::searchFunction(/*ID*/ uint16_t id)

Task in die Liste suchen
````

Funktion Parameter:
```
id     -> Einzigartig id des Tasks
return -> Pointer zu tcb mit der Task
```

```
function_struct *StallardOS::searchFreeFunction(void)

sucht einen tcb die gerade nicht verwendet wird
```



```
StallardOS::delay(uint32_t milliseconds)

delay in millisekunden

Funktion PArameter:
```
milliseconds -> Menge an ms zu warten
```



```
StallardOS::getFunctionState(/*Funktion*/ uint16_t id)

Check Task Status
```

Funktion Parameter:
```
id -> Einzigartig Task id
return -> Task Status, siehe tasktate enum
```

