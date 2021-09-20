## **Stallardo Operating System**
**StallardOS_PID**



Funktionen Erklärung:

```
StallardOSpwm::StallardOSpwm(TIM_TypeDef *instance, PWMChannel channel, uint8_t number, ports port, uint16_t freq, uint8_t bitcount) : 
    gpio(number, port, AFPP, nopull, mapToAlternateFunction(instance))
```
Ausgabe Berechnung

Funktion Parameter:
```
instance -> welche Timer verwenden wir
channel  -> Timer channel zu verwenden
number   -> nummer der pin auf der port
port     -> gpio port
freq     -> frequenz der pwm Signal
bitcount -> Bit Menge der pwm
```

```
StallardOSSerial::send(const char *dat, uint16_t bytes)

Data senden
```

Funktion Parameter:
```
dat   -> Data zu senden
bytes -> Menge der versendete Data Bytes
```


```
StallardOSSerial::read(const char *dat, uint16_t bytes)

Data lesen/empofangen
```

Funktion Parameter:
```
dat   -> container der gelesene Data
bytes -> Menge der gelesene Data Bytes
```