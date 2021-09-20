## **Stallardo Operating System**
**StallardOS_CAN**


Funktionen Erklärung:

```
StallardOSCAN(CANports port, CANBauds baud);
````
erzeugt einen CAN interface.

Funktion Parameter:
```
Port -> auswahl der CAN Port
baud -> auswahl der Kommunikations Geschwindigkeit [Baud]
```



```
receiveMessage(StallardOSCanMessage *msg, uint16_t id);
```
Receive a CAN message, mit Boolean return (True/False)

Funktion Parameter:
```
msg -> Nachricht container
id -> id der zu empfangener Nachricht
```



```
sendMessage(StallardOSCanMessage *msg, uint8_t size);
````
Send a CAN message

Funktion Parameter:
```
msg -> zu versendener Nachricht
size -> NAchricht Große in Data Bytes (Max. 8)
````
