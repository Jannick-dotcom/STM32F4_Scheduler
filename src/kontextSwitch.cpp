
#include <stm32f4xx_hal.h>
#include "TaskScheduler.hpp"
//Kontext Switch
uint8_t switchEnable = 0;
function_struct *currentTask = nullptr;

#define func (uint32_t)currentTask->function & ~1UL

/*
 * Enables all interrupts
 */
extern "C" inline void enable_interrupts() 
{
	asm("CPSIE I");
}

/*
 * Disables all interrupts
 */
extern "C" inline void disable_interrupts() 
{
	asm("CPSID I");
}

extern "C" void SysTick_Handler(void)
{
    // Set the 28th Bit to trigger PendSV interrupt
    //0xE000E008 = base address
    //0xE000E00C = base address + 0x04
	//*(unsigned long int volatile *)0xE000E00C |= (1U << 28);  //Interrupt control and state register
    
    if(switchEnable) SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    //trigger Pendsv
    enable_interrupts();
}

extern "C" void PendSV_Handler() 
{
    disable_interrupts();
    if (currentTask != NULL)
    {
        if ((currentTask->State == RUNNING)) //Hier Task anhalten
        {
            asm("MRS r0, PSP");
            asm("STMDB r0!, {r4-r11}");
            asm("MSR PSP, r0");
            asm("MOV %0, r0" : "=r"(currentTask->Stack));

            currentTask->State = STOPPED;
            currentTask = currentTask->next; //Nächsten Task
        }

        // *******************************************************************************

        if (currentTask->State == NEW)
        {   
            asm("MOV r4, #0");                                 //R0
            asm("MOV r5, #1");                                 //R1
            asm("MOV r6, #2");                                  //R2
            asm("MOV r7, #3");                                  //R3
            asm("MOV r8, #0x12");                               //R12
            asm("MOV r9, %0" : : "r"(func));                    //LR
            asm("MOV r10, %0" : : "r"(func));                   //PC
            asm("MOV r11, #0x01000000");                        //XPSR

            //asm("PUSH {r0-r7}");

            asm("MRS r0, PSP");
            asm("STMDB r0!, {r4-r11}");
            asm("MSR PSP, r0");
            
            currentTask->State = RUNNING;
        }

        if (currentTask->State == STOPPED) //Hier Task fortsetzen
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));
            //asm("POP {r4-r11}");
            asm("LDMIA r0!, {r4-r11}");
            asm("MSR PSP, r0");
            currentTask->State = RUNNING;
        }
    }
    asm("MOV LR, #0xFFFFFFFD");
    enable_interrupts();
    //asm("bx r0");
}