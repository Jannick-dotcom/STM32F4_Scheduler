#include "StallardOS.hpp"

void tasktest()
{
    char datasend[] = "Hello World";
    StallardOSSerial Serial(UART4, 115200);
    Serial.send(datasend, sizeof(datasend));
    Serial.read(datasend, sizeof(datasend));
}