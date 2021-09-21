## **Stallardo Operating System**
**StallardOS_CAN**


Funktionen Erklärung:


_______________________________________________________________
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

```
receiveMessage(StallardOSCanMessage *msg, uint16_t id);
```

Empfängt a CAN message, mit Boolean return (True/False)


Funktion Parameter:
```
msg -> Nachricht container
id -> id der zu empfangener Nachricht
```



_______________________________________________________________


```
sendMessage(StallardOSCanMessage *msg, uint8_t size);
````
Send a CAN message

Funktion Parameter:
```
msg -> zu versendener Nachricht
size -> NAchricht Große in Data Bytes (Max. 8)
````
