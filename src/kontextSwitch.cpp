#include "TaskScheduler.h"
#include "stm32f4xx.h"

//Kontext Switch
uint8_t switchEnable = 0;
function_struct *currentTask = nullptr;
Ticker systemSwitchEvent;

#include "registers.h"
//Fehler der Linkregister Values
//Ich tippe auf extra overhead beim reinspringen in die isr
void systemSwitchEvent_Handler(void) //interrupt von Ticker
{
    if (switchEnable && (currentTask != NULL))
    {
        if ((currentTask->State == RUNNING))       //Hier Task anhalten
        {
            saveRegisters();
            currentTask->State = STOPPED;
        }
        
        /*******************************************************************************/
        currentTask = currentTask->next;    //Nächsten Task

        if(currentTask->State == NEW)
        {
            currentTask->State = RUNNING;
            asm("MOV r14, %0" : :"r"  (*(currentTask->function))); //Move value from r14 / LR
        }

        if (currentTask->State == STOPPED)     //Hier Task fortsetzen
        {
            restoreRegisters();
            currentTask->State = RUNNING;
        }
    }
}