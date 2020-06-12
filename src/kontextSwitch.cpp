
#include <stm32f4xx_hal.h>
#include "TaskScheduler.hpp"
//Kontext Switch
uint8_t switchEnable = 0;
function_struct *currentTask = nullptr;
Ticker systemSwitchEvent;

extern "C" void SysTick_Handler(void)
{
    //asm("CPSID i");
    if (switchEnable && (currentTask != NULL))
    {
        if ((currentTask->State == RUNNING)) //Hier Task anhalten
        {
            asm("MRS r0, PSP");
            asm("ISB");
            asm("MOV %0, r0" : "=r"(currentTask->Stack));
            asm("ISB");
            asm("MOV %0, r4"  : "=r"(*(currentTask->Stack - 9)));
            asm("MOV %0, r5"  : "=r"(*(currentTask->Stack - 8)));
            asm("MOV %0, r6"  : "=r"(*(currentTask->Stack - 7)));
            asm("MOV %0, r7"  : "=r"(*(currentTask->Stack - 6)));
            asm("MOV %0, r8"  : "=r"(*(currentTask->Stack - 5)));
            asm("MOV %0, r9"  : "=r"(*(currentTask->Stack - 4)));
            asm("MOV %0, r10" : "=r"(*(currentTask->Stack - 3)));
            asm("MOV %0, r11" : "=r"(*(currentTask->Stack - 2)));
            asm("MOV %0, r12" : "=r"(*(currentTask->Stack - 1)));
            currentTask->State = STOPPED;
            currentTask = currentTask->next; //Nächsten Task
        }

        // *******************************************************************************
        

        if (currentTask->State == NEW)
        {
            currentTask->State = RUNNING;
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            asm("ISB");
            asm("MSR PSP, r0");
            asm("ISB");
            
            asm("MOV r4, %0" : : "r"(*(currentTask->Stack - 9)));
            asm("MOV r5, %0" : : "r"(*(currentTask->Stack - 8)));
            asm("MOV r6, %0" : : "r"(*(currentTask->Stack - 7)));
            asm("MOV r7, %0" : : "r"(*(currentTask->Stack - 6)));
            asm("MOV r8, %0" : : "r"(*(currentTask->Stack - 5)));
            asm("MOV r9, %0" : : "r"(*(currentTask->Stack - 4)));
            asm("MOV r10, %0" : : "r"(*(currentTask->Stack - 3)));
            asm("MOV r11, %0" : : "r"(*(currentTask->Stack - 2)));
            asm("MOV r12, %0" : : "r"(*(currentTask->Stack - 1)));
            //Stackpointer irgendwie am Arsch wenn ich in die Funktion reinspringe
        }

        if (currentTask->State == STOPPED) //Hier Task fortsetzen
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            asm("ISB");
            asm("MSR PSP, r0");
            asm("ISB");
            asm("MOV r4, %0" : : "r"(*(currentTask->Stack - 9)));
            asm("MOV r5, %0" : : "r"(*(currentTask->Stack - 8)));
            asm("MOV r6, %0" : : "r"(*(currentTask->Stack - 7)));
            asm("MOV r7, %0" : : "r"(*(currentTask->Stack - 6)));
            asm("MOV r8, %0" : : "r"(*(currentTask->Stack - 5)));
            asm("MOV r9, %0" : : "r"(*(currentTask->Stack - 4)));
            asm("MOV r10, %0" : : "r"(*(currentTask->Stack - 3)));
            asm("MOV r11, %0" : : "r"(*(currentTask->Stack - 2)));
            asm("MOV r12, %0" : : "r"(*(currentTask->Stack - 1)));
            currentTask->State = RUNNING;
        }
        asm("MOV LR, #0xFFFFFFFD");
        //asm("CPSIE i");
        //asm("bx r0");
    }
}