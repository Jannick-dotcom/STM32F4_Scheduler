#include "StallardOSHelpers.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>

extern struct function_struct *currentTask;
extern struct function_struct *taskMainStruct;
extern struct function_struct *nextTask;

void StallardOSGeneralFaultHandler() //restarts a Task when a fault occurs
{
    // asm("TST    LR, #4"); //firstly, find the PC
    // asm("ITE    EQ");
    // asm("MRSEQ	R0, MSP");
    // asm("MRSNE	R0, PSP");

    // asm("LDR	R0, [R0, #24]"); //PC is in R0
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    if (taskMainStruct != 0)
    {
        currentTask->Stack = currentTask->stackBase + currentTask->stackSize - sizeof(stack_T); //End of Stack
        // currentTask->State = PAUSED; //Set Task state as new
        currentTask->continueInMS = HAL_GetTick() + 5000; //Restart Task in 5 s
        if(currentTask->semVal != NULL){
            if(currentTask->waitingForSemaphore == 0){
                // only execute, if semaphore is actually owned by task (take finished)

                /* normal write access to semaphore is ok in this context, 
                * as no other task may execute during hardFault 
                */
                *(currentTask->semVal) = 1; //Semaphore freigeben
                __CLREX();  // reset exclusive monitor
            }
            else{
                // undefined state, task may or may not own the semaphore
                // assume it didn't own it, as that's more likely?
                // TODO: change this???
                #ifndef UNIT_TEST
                asm("bkpt");  //Zeige debugger
                #endif
            }
        }

        currentTask->waitingForSemaphore = 0;
        currentTask->semVal = 0; //Semaphore von task lösen
        currentTask = taskMainStruct;
        nextTask = taskMainStruct;
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    }
}

void HardFault_Handler()
{
    StallardOSGeneralFaultHandler();
}

void NMI_Handler()
{
    StallardOSGeneralFaultHandler();
}

void MemManage_Handler()
{
    StallardOSGeneralFaultHandler();
}

void BusFault_Handler()
{
    StallardOSGeneralFaultHandler();
}

void UsageFault_Handler()
{
    StallardOSGeneralFaultHandler();
}

#ifdef useFPU
// FPU IRQ Handler
void FPU_IRQHandler()
{
    asm("MOV R0, LR"); // move LR to R0
    asm("MOV R1, SP"); // Save SP to R1 to avoid any modification to the stack pointer from FPU_ExceptionHandler
    asm("MRS r4, MSP");
    asm("MRS r5, PSP");

    asm("VMRS R2, FPSCR"); // dummy read access, to force clear

    asm("CMP LR, #0xFFFFFFE9");
    asm("ITTT EQ"); //Next 3 instructions executed if LR = 0xFFFFFFE9
    asm("MOVEQ r2, r4");
    asm("ADDEQ r2, #0x60");
    asm("MSREQ MSP, r2");

    asm("CMP LR, #0xFFFFFFED");
    asm("ITTT EQ"); //Next 3 instructions executed if LR = 0xFFFFFFED
    asm("MOVEQ r2, r5");
    asm("ADDEQ r2, #0x60");
    asm("MSREQ PSP, r2");

    asm("LDR r3, [r2]");

    //check exception flags
    asm("BIC r3, #0x8F");
    asm("STR r3, [r2]");

    asm("DMB");
    StallardOSGeneralFaultHandler();
}
#endif