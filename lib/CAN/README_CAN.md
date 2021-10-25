## **Stallardo Operating System**
**StallardOS_CAN**


Funktionen Erklärung:


_________________________________________________________________________________________


Funktion:
```
StallardOSCAN(CANports port, CANBauds baud);

````
Die Funktion erzeugt einen CAN interface.



Funktion Parameter:
```
Port -> auswahl der CAN Port
baud -> auswahl der Kommunikations Geschwindigkeit [Baud]
```


_______________________________________________________________


Funktion:
```
receiveMessage(StallardOSCanMessage *msg, uint16_t id);
```

Empfängt eine CAN message, mit Boolean return (True/False).


Funktion Parameter:
```
msg -> Nachricht container                      (Pointer)
id -> id der zu empfangener Nachricht           [16Bit Integer]
```



_______________________________________________________________


Funktion:
```
sendMessage(StallardOSCanMessage *msg, uint8_t size);
````
Sendet a CAN message.

Funktion Parameter:
```
msg -> zu versendener Nachricht
size -> NAchricht Große in Data Bytes           [8Bit Integer]
````
