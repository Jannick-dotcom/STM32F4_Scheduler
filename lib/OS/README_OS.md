## **Stallardo Operating System**
**StallardOS_OS**


Funktionen Erklärung:


Funktion:
```
StallardOS()
```

Erzeugt StallardOS RTOS

Funktion Parameter:
```
void
```


_________________________________________________________________________________________


Funktion:
```
createTBCs()
```

Erzeugt Task controll blocks.

Funktion Parameter:
```
void
```


_________________________________________________________________________________________


Funktion:
```
addFunction(void (*function)(), uint16_t id, uint8_t prio, stack_T stackSize, uint16_t refreshRate)```
```

Erzeugt einen neue Task in die "execute list"

Funktion Parameter:
```
funktion    -> task zu ausführen                                           
id          -> Einzigartig id der Task                                  [16Bit Integer]
prio        -> Task priorität, geringere nummer bedeutet höhere Prio.   [8Bit Integer]
stackSize   -> number of elements to store on stack (NOT size in Bytes) [32Bit Integer on STM32]
refreshRate -> Frequenz der ausführung                                  [16Bit Integer]
return      -> Pointer zu der erzeugten tbc                             [16Bit Integer]
```




___________________________________________________________________________________________________


Funktion:
```
changeFunctionEnabled(uint16_t id, bool act)
```

Enable/disable Task aus die Task List


Funktion Parameter:
```
id  -> einzigartig id der Task                                          [16Bit Integer]
act -> Boolean Wert, Task aktivierung                                   [Boolean]
```


___________________________________________________________________________________________________


Funktion:
```
setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio)
```

Neue Task Prioritizierung setzen

Funktion Parameter:
```
id  -> einzigartig id der Task                                          [16Bit Integer]
prio -> neue Task Priorität, je kleiner der Wert, desto höher Prio      [8Bit Integer]
```


___________________________________________________________________________________________________


Funktion:
```
searchFunction(/*ID*/ uint16_t id)
```

Task in die Liste suchen


Funktion Parameter:
```
id     -> Einzigartig id des Tasks                                      [16Bit Integer]
return -> Pointer zu tcb mit der Task
```


___________________________________________________________________________________________________


Funktion:
```
searchFreeFunction(void)
```

sucht einen tcb die gerade nicht verwendet wird



___________________________________________________________________________________________________


Funktion:
```
delay(uint32_t milliseconds)
```

delay Funktion in millisekunden

Funktion PArameter:
```
milliseconds -> Menge an ms zu warten                                   [32Bit Integer]
```


___________________________________________________________________________________________________


Funktion:
```
getFunctionState(/*Funktion*/ uint16_t id)
```

Check Task Status


Funktion Parameter:
```
id      -> Einzigartig Task id                                          [16Bit Integer]
return  -> Task Status, siehe tasktate enum
```



_________________________________________________________________________
**StallardOSClass**

Funktionen Erklärung:


Funktion:
```
StakkardOS();
```

creates a TaskScheduler

```
addFunction(void (*function)(), uint16_t id, uint8_t prio, stack_T stackSize, uint16_t refreshRate = 0);
```

Weisst eine eingegebene Funktion Eigenschaften diz zu Scheduling benötigt werden.

Funktion Parameter:
```
*function   -> Zeiger zur Funktion die gescheduled werden muss
id          -> Einzigartige ID des Tasks
prio        -> 0 - 255, je kleiner der Wert, desto großer die Priotität
stackSize   -> number of elements to store on stack (NOT size in Bytes)
refreshrate -> Muss großer sein als 0 !, nicht verwendet von Contextswitch
```


_________________________________________________________________________________________

Funktion:
```
setFunctionPriority(/*Funktion*/ uint16_t id, /*New Priority*/ uint8_t prio);
```

Weisst eine Funktion einen neue Prio.



Funktion Parameter:
```
id   -> Einzigartige ID der Funktion
prio -> neue Prio Wert [0 bis 255]
```