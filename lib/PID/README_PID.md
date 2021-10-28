## **Stallardo Operating System**
**StallardOS_PID**



Funktionen Erklärung:


Funktion:
```
StallardosPID(double p_gain, double i_gain, double d_gain)

Creates a PID Controler
```

Funktion Parameter:
```
p_gain  -> Gain of the P part
i_gain  -> Gain of the I part
d_gain  -> Gain of the D part
```


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
