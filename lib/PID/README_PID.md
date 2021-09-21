## **Stallardo Operating System**
**StallardOS_PID**



Funktionen Erklärung:


___________________________________________________________________________________


Funktion:
```
calculate_pid(double setpoint, double input)
```
Ausgabe Berechnung

Funktion Parameter:
```
setpoint -> setpoint von der Controller         [64Bits Double]
input    -> input der pid Controller            [64Bits Double]
return   -> output der pid Controller
```


___________________________________________________________________________________


Funktion:
```
changeFunctionEnabled(uint16_t id, bool act)

Enable/disable Task aus die Task List
```

Funktion Parameter:
```
id  -> einzigartig id der Task                  [16Bit Integer]
act -> Boolean Wert, Task aktivierung           [Boolean]
```