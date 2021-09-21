## **Stallardo Operating System**
**StallardOS_GPIO**


Funktionen Erklärung:

```
StallardOSGPIO(uint8_t number, ports port, pinDir dir, bool initialState, pullMode pull)
```
Erzeugt einen GPIO Pin.

Funktion Parameter:
```
number-> Port Nummer Auswahl                                    [8Bit Integer]
port  -> Port Auswahl                                           [8Bit Integer]
dir   -> input oder output                                      [Boolean]
pull  -> internal pull-up oder pull-down                        [Boolean]
```


_______________________________________________________________
```
StallardOSGPIO(uint8_t number, ports port, pinDir dir, pullMode pull, uint32_t alternate)
```

Pin erzeugung mit alternative funktion zu einen normaler GPIO Pin.
Der Alternate Parameter gibt an was für eine Funktion diesen Pin annehmen wird. 
Anders als einen GPIO Pin, muss diesen Funktion keinen digital Zustand annehmen, 
es kann z.B.: einen PWM sein, oder Serial.

Funktion Parameter:
```
number    -> Port Nummer Auswahl                                [8Bit Integer]
port      -> Port Auswahl
dir       -> input oder output 
pull      -> internal pull-up oder pull-down 
alternate -> alternative zu einen normaler gpio Port            [32Bit Integer]
```
_______________________________________________________________
```
operator=(bool state)
```

Die Funktion ändert der Pin Status.

Funktion Parameter:
```
state  -> neue status, high oder low                            [Boolean]
return -> neue status                                           [Boolean]
```

