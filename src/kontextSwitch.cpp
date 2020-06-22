
#include <stm32f4xx_hal.h>
#include "TaskScheduler.hpp"
//Kontext Switch
uint8_t switchEnable = 0;
function_struct *currentTask = nullptr;

extern "C" void SysTick_Handler(void)
{
    if (switchEnable && (currentTask != NULL))
    {
        if ((currentTask->State == RUNNING)) //Hier Task anhalten
        {
            asm("MRS r0, PSP");
            asm("MOV r0, %0" : : "r"(currentTask->Stack));

            asm("ADD r0, #32");
            asm("STMDB r0, {r4-r11}");

            //asm("MOV %0, LR" : "=r"(*(currentTask->Stack + 16)));

            currentTask->State = STOPPED;
            currentTask = currentTask->next; //Nächsten Task
        }

        // *******************************************************************************

        if (currentTask->State == NEW)
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            asm("MSR PSP, r0");

            asm("ADD r0, #32");
            asm("LDMIA r0, {r4-r11}");

            //asm("MOV LR, #0xFFFFFFFD");
            //asm("MOV LR, %0" : : "r"(currentTask->function));

            //asm("MOV LR, %0" : : "r"(*(currentTask->Stack + 16)));
            //Stackpointer irgendwie am Arsch wenn ich in die Funktion reinspringe
            currentTask->State = RUNNING;
        }

        if (currentTask->State == STOPPED) //Hier Task fortsetzen
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            asm("MSR PSP, r0");

            asm("ADD r0, #32");
            asm("LDMIA r0, {r4-r11}");

            //asm("MOV LR, %0" : : "r"(*(currentTask->Stack + 16)));

            currentTask->State = RUNNING;
        }
        asm("MOV r0, #0xFFFFFFFD");
        asm("bx r0");
    }
}