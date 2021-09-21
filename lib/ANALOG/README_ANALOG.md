
## **Stallardo Operating System**
**StallardOS_ANALOG**

Was ist ein gpio? 

Es ist ein General Purpouse Input/Output, oder "Allzweckeeingabe/-ausgabe",
dessen Verhalten, unabhängig on Eingabe oder Ausgabe, programiert werden kann.


Der **StallardOS ANALOG** ermöglicht die Einstellung von unterschiedliche Pins der Microcontroller,
die mit andere Hardware komunizieren.

_______________________________________________________________


Funktion:
```
StallardOSAnalog(StallardOSADC number, uint8_t channel)
````
Erzeugt einen analog Input instance.

Funktion Parameter:
```
number -> welche ADC nummer ist zu verwenden
Channel -> Channel nummer für the ADC1          [8Bit Integer]
```
