## **Stallardo Operating System**
**StallardOS_CAN**


Funktionen Erklärung:
_______________________________________________________________
```
StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber, StallardOSSPI *spihandle);
````
erzeugt einen Analog input instance.

Funktion Parameter:
```
adcNumber -> Auswahl der ADC
Channel -> Auswahl der Channel Nummer
```


_______________________________________________________________
```
int16_t getValue();
```

Die Funktion liesst (return) einen Analog Wert


```
