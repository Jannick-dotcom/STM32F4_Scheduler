
#include <stm32f4xx_hal.h>
#include "TaskScheduler.hpp"
//Kontext Switch
uint8_t switchEnable = 0;
function_struct *currentTask = nullptr;


/*
 * Enables all interrupts
 */
extern "C" void enable_interrupts() 
{
	__asm("CPSIE I");
}

/*
 * Disables all interrupts
 */
extern "C" void disable_interrupts() 
{
	__asm("CPSID I");
}

extern "C" void SysTick_Handler(void)
{
    // Set the 28th Bit to trigger PendSV interrupt
	*(unsigned long int volatile *)0xE000ED04 = (1U << 28);
    enable_interrupts();
}

extern "C" void pendsv_handler() 
{
    disable_interrupts();
    if (switchEnable && (currentTask != NULL))
    {
        if ((currentTask->State == RUNNING)) //Hier Task anhalten
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            asm("STMIA r0, {r4-r11}");

            currentTask->State = STOPPED;
            currentTask = currentTask->next; //Nächsten Task
        }

        // *******************************************************************************

        if (currentTask->State == NEW)
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            asm("LDMIA r0, {r4-r11}");
            asm("ADD r0, #32");
            asm("MSR PSP, r0");
            currentTask->State = RUNNING;
        }

        if (currentTask->State == STOPPED) //Hier Task fortsetzen
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            asm("LDMIA r0, {r4-r11}");
            asm("ADD r0, #32");
            asm("MSR PSP, r0");         
            currentTask->State = RUNNING;
        }
        //asm("MOV r0, #0xFFFFFFFD");
        //asm("bx r0");
    }
    enable_interrupts();
}