## **Stallardo Operating System**
**StallardOS_CAN**


Funktionen Erklärung:

```
StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber, StallardOSSPI *spihandle);
````
erzeugt einen Analog input instance.

Funktion Parameter:
```
adcNumber -> Auswahl der ADC
Channel -> Auswahl der Channel Nummer
```



```
int16_t getValue();
```
liesst einen Analog Wert

Return: Analog Wert
```
