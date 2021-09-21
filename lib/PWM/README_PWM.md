## **Stallardo Operating System**
**StallardOS_PID**



Funktionen Erklärung:


___________________________________________________________________________________
```
StallardOSpwm(TIM_TypeDef *instance, PWMChannel channel, uint8_t number, ports port, uint16_t freq, uint8_t bitcount) : 
    gpio(number, port, AFPP, nopull, mapToAlternateFunction(instance))
```
Ausgabe Berechnung


Funktion Parameter:

```
instance -> welche Timer verwenden wir      [Instance Pointer]
channel  -> Timer channel zu verwenden
number   -> nummer der pin auf der port     [8Bit Integer]
port     -> gpio port
freq     -> frequenz der pwm Signal         [16Bit Integer]
bitcount -> Bit Menge der pwm               [8Bit Integer]
```


___________________________________________________________________________________
```
send(const char *dat, uint16_t bytes)

Data senden
```

Funktion Parameter:
```
dat   -> Data zu senden                     [8Bit Char]
bytes -> Menge der versendete Data Bytes    [16Bit Integer]
```


___________________________________________________________________________________
```
read(const char *dat, uint16_t bytes)

Data lesen/empofangen
```

Funktion Parameter:
```
dat   -> container der gelesene Data        [Char (Pointer)]
bytes -> Menge der gelesene Data Bytes      [16Bit Integer]
```