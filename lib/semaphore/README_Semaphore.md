## **Stallardo Operating System**
**semaphore**


________________________________________________________________________________________________________________________________
Semaphoren sind Data Strukturen die zur Prozesssynchronisation dienen. Die vermeiden Deadlocks in die Busssystemen 
indem sie der Auslastung der Leitung überprüfen und dann die "Nachricht Versenden" Erlaubnis erteilen.

Falls einen Funktion eine bestimmte Semaphor Wert bekommt, wird der code diesen Wert mit alle davor vergebene Werte vergleichen.
Wenn der Semaphor bereits verwendet wird, muss die Task (z.B. Funktion) warten bis der Semaphor wieder ferfügbar ist. 

Eine Gute Analogie dazu sind Ampeln in die Strassenverkehr.
_________________________________________________________________________________________________________________________________