## **Stallardo Operating System**
**StallardOS_Serial**



Funktionen Erklärung:


_________________________________________________________________________________________


Funktion:
```
StallardOSSerial(USART_TypeDef *serPort, uint32_t baud)
```

Erzeugen einer Serieller Instance.

Funktion Parameter:
```
serPort -> welche Serial verwenden wir                              (Pointer)
baud    -> Baud Rate (Übertragungsgeschwindigkeit in Bit/s)         [32Bit Integer]
```


_________________________________________________________________________________________


Funktion:
```
send(const char *dat, uint16_t bytes)
```

Senden von Data.

Funktion Parameter:
```
dat   -> Data zu senden                                             [Char (Pointer)]
bytes -> Menge an Bytes zu senden                                   [16Bits Double]
```


_________________________________________________________________________________________


Funktion:
```
read(char *dat, uint16_t bytes)
```

Data lesen.

Funktion Parameter:
```
dat   -> Container der gelesener Data                               [Char (Pointer)]
bytes -> Große der gelesene Data                                    [16Bit Integer]
```

