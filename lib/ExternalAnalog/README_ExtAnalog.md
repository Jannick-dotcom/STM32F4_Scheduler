## **Stallardo Operating System**
**StallardOS_CAN**


Funktionen Erklärung:

_________________________________________________________________________________________


Funktion:
```
StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber, StallardOSSPI *spihandle);
````
erzeugt einen Analog input instance.

Funktion Parameter:
```
adcNumber  -> Auswahl der ADC                       [8Bit Integer]
Channel    -> Auswahl der Channel Nummer            [8Bit Integer]
```


_______________________________________________________________


Funktion:
```
getValue();
```

Die Funktion liesst (return) einen Analog Wert      [16Bit Integer]

