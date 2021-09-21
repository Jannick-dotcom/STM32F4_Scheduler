## **Stallardo Operating System**
**StallardOS_Serial**



Funktionen Erklärung:


_________________________________________________________________________________________
```
StallardOSSerial::StallardOSSerial(USART_TypeDef *serPort, uint32_t baud)
```

Erzeugen einer Serieller Instance

Funktion Parameter:
```
serPort -> welche Serial verwenden wir
baud    -> Baud Rate (Übertragungsgeschwindigkeit)
```


_________________________________________________________________________________________
```
send(const char *dat, uint16_t bytes)
```

senden von Data

Funktion Parameter:
```
dat   -> Data zu senden
bytes -> Menge an Bytes zu senden
```


_________________________________________________________________________________________
```
read(char *dat, uint16_t bytes)
```

Data lesen

Funktion Parameter:
```
dat   -> Container der gelesener Data
bytes -> Große der gelesene Data
```

