
#include <stm32f4xx_hal.h>
#include "TaskScheduler.hpp"
//Kontext Switch
volatile uint8_t switchEnable = 0;
volatile function_struct *currentTask = nullptr;

#define func (uint32_t)currentTask->function & ~1UL     //Use the function pointer with lowest bit zero
////////////////////////////////////////////////////////////////////////////////////////
//Set all the Interrupts and Values for the OS
void TaskScheduler::startOS(void)
{
  currentTask = first_function_struct;      //The current Task is the first one in the List
  currentTask->State = NEW;                 //The current Task is a new Task
  setContextSwitch(true);                   //Activate context switching
  SysTick_Config(SystemCoreClock / 1000);   //Set the frequency of the systick interrupt
  NVIC_SetPriority(PendSV_IRQn, 0xff); /* Lowest possible priority */
  NVIC_SetPriority(SysTick_IRQn, 0x00); /* Highest possible priority */
  __set_PSP(__get_MSP());                   //Init the PSP
  __set_CONTROL(0x03); /* Switch to Unprivilleged Thread Mode with PSP */
  asm("ISB");                               //After modifying the control Register flush all instructions (I don't understand why but ok)
}

////////////////////////////////////////////////////////////////////////////////////////
//Enables all interrupts
////////////////////////////////////////////////////////////////////////////////////////
extern "C" inline void enable_interrupts() 
{
	asm("CPSIE I");     //Instruction for enabling interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Disables all interrupts
////////////////////////////////////////////////////////////////////////////////////////
extern "C" inline void disable_interrupts() 
{
	asm("CPSID I");     //Instruction for disabling interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Set the PendSV exception to pending
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void SysTick_Handler(void)                           //In C Language
{    
    if(switchEnable) SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;       //If switchEnable set, set the PendSV to pending
    //trigger Pendsv
    enable_interrupts();                                        //enable all interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Switch the context
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void PendSV_Handler()                                //In C Language
{
    disable_interrupts();
    if (currentTask != NULL)                //If the current task is a Task
    {
        if ((currentTask->State == RUNNING)) //Hier Task anhalten
        {
            asm("MRS r0, PSP");     //Get Process Stack Pointer
            asm("STMDB r0!, {r4-r11}"); //Save additional not yet saved registers
            asm("MSR PSP, r0");     //Set Modified Stack pointer
            asm("MOV %0, r0" : "=r"(currentTask->Stack));   //Save Stack pointer

            currentTask->State = STOPPED;    //Save function state
            currentTask = currentTask->next; //Nächsten Task
        }

        if (currentTask->State == NEW)      //New Task
        {   
            asm("MOV r4, #0");                                 //R0
            asm("MOV r5, #1");                                 //R1
            asm("MOV r6, #2");                                  //R2
            asm("MOV r7, #3");                                  //R3
            asm("MOV r8, #0x12");                               //R12
            asm("MOV r9, %0" : : "r"(func));                    //LR
            asm("MOV r10, %0" : : "r"(func));                   //PC
            asm("MOV r11, #0x01000000");                        //XPSR

            asm("MRS r0, PSP");             //get PSP
            asm("STMDB r0!, {r4-r11}");     //Store prepared initial Data for R0-R3, R12, LR, PC, XPSR
            asm("MSR PSP, r0");             //set PSP
            
            currentTask->State = RUNNING;   //Save state as running
        }

        if (currentTask->State == STOPPED) //Hier Task fortsetzen
        {
            asm("MOV r0, %0" : : "r"(currentTask->Stack));  //get saved Stack pointer
            asm("LDMIA r0!, {r4-r11}");                     //load registers from memory
            asm("MSR PSP, r0");                             //set PSP
            currentTask->State = RUNNING;                   //Save state as running
        }
    }
    asm("MOV LR, #0xFFFFFFFD");                             //Set the LR to 0xFFFFFFFD to signal Process mode with psp
    enable_interrupts();                                    //Enable all interrupts
    asm("bx LR");                                           //Jump to LR address
}