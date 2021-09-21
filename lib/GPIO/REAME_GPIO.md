## **Stallardo Operating System**
**StallardOS_GPIO**


Funktionen Erklärung:

```
StallardOSGPIO(uint8_t number, ports port, pinDir dir, bool initialState, pullMode pull)
```
erzeugt einen GPIO Pin.

Funktion Parameter:
```
number-> Port Nummer Auswahl [8 Bit Integer]
port  -> Port Auswahl        [8 Bit Integer]
dir   -> input oder output 
pull  -> internal pull-up oder pull-down
```


_______________________________________________________________
```
StallardOSGPIO(uint8_t number, ports port, pinDir dir, pullMode pull, uint32_t alternate)
```

Pin erzeugung mit alternative funktion zu einen normaler GPIO Pin.
Der Alternate Parameter gibt an was für eine Funktion diesen Pin annehmen wird, es ist keine normaler GPIO Pin mit digitale Zustände.
Es kann z.B: einen PWN, Serial... Pin sein.

Funktion Parameter:
```
number    -> Port Nummer Auswahl [8 Bit Integer]
port      -> Port Auswahl
dir       -> input oder output 
pull      -> internal pull-up oder pull-down 
alternate -> alternative zu einen normaler gpio Port [32 Bit Integer]
```
_______________________________________________________________
```
operator=(bool state)
```

Die Funktion ändert der Pin Status.

Funktion Parameter:
```
state  -> neue status, high oder low
return -> neue status
```

