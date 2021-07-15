#include "StallardOSHelpers.h"
#include <stdint.h>

extern struct function_struct *currentTask;
extern struct function_struct *taskMainStruct;
extern struct function_struct *nextTask;

void StallardOSGeneralFaultHandler() //restarts a Task when a fault occurs
{
#ifdef contextSwitch
    asm("TST    LR, #4");//firstly, find the PC
    asm("ITE    EQ");
	asm("MRSEQ	R0, MSP");
	asm("MRSNE	R0, PSP");

	asm("LDR	R0, [R0, #24]"); //PC is in R0
    if (taskMainStruct != 0)
    {
        if (currentTask == 0)
            currentTask = taskMainStruct;
        currentTask->Stack = currentTask->vals + sizeStack - 4; //End of Stack
        asm("MOV r4, #0");  //R0
        asm("MOV r5, #1");  //R1
        asm("MOV r6, #2");  //R2
        asm("MOV r7, #3");  //R3
        asm("MOV r8, #12"); //R12
        asm("MOV r9, %0" : : "r"(taskMainStruct->function)); //LR
        asm("MOV r10, %0" : : "r"((uint32_t)currentTask->function & functionModifier)); //PC
        asm("MOV r11, #0x01000000");                                    //XPSR
        asm("MOV r14, #0xFFFFFFFD");                                    //Default return value

        asm("MOV r0, %0" : : "r"(currentTask->Stack)); //get saved Stack pointer
        asm("STMDB r0!, {r4-r11}");     //Store prepared initial Data for R0-R3, R12, LR, PC, XPSR
        asm("MSR PSP, r0");             //set PSP
        currentTask->waitingForSemaphore = 0;
        currentTask->semVal = 0;
        currentTask->State = RUNNING; //Save state as running
    }
#endif
}

void HardFault_Handler()
{
    asm("TST    LR, #4");//firstly, find the PC
    asm("ITE    EQ");
	asm("MRSEQ	R0, MSP");
	asm("MRSNE	R0, PSP");

	asm("LDR	R0, [R0, #24]"); //PC is in R0
    if (taskMainStruct != 0)
    {
        if (currentTask == 0)
            currentTask = taskMainStruct;
        currentTask->Stack = currentTask->vals + sizeStack - 4; //End of Stack
        asm("MOV r4, #0");  //R0
        asm("MOV r5, #1");  //R1
        asm("MOV r6, #2");  //R2
        asm("MOV r7, #3");  //R3
        asm("MOV r8, #12"); //R12
        asm("MOV r9, %0" : : "r"(taskMainStruct->function)); //LR
        asm("MOV r10, %0" : : "r"((uint32_t)currentTask->function & functionModifier)); //PC
        asm("MOV r11, #0x01000000");                                    //XPSR
        asm("MOV r14, #0xFFFFFFFD");                                    //Default return value

        asm("MOV r0, %0" : : "r"(currentTask->Stack)); //get saved Stack pointer
        asm("STMDB r0!, {r4-r11}");     //Store prepared initial Data for R0-R3, R12, LR, PC, XPSR
        asm("MSR PSP, r0");             //set PSP
        currentTask->waitingForSemaphore = 0;
        currentTask->semVal = 0;
        currentTask->State = RUNNING; //Save state as running
    }
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

// FPU IRQ Handler
void FPU_IRQHandler()
{
    // asm("MOV R0, LR"); // move LR to R0
    // asm("MOV R1, SP"); // Save SP to R1 to avoid any modification to the stack pointer from FPU_ExceptionHandler
    // asm("MRS r4, MSP");
    // asm("MRS r5, PSP");

    // asm("VMRS R2, FPSCR"); // dummy read access, to force clear

    // asm("CMP LR, #0xFFFFFFE9");
    // asm("ITTT EQ"); //Next 3 instructions executed if LR = 0xFFFFFFE9
    // asm("MOVEQ r2, r4");
    // asm("ADDEQ r2, #0x60");
    // asm("MSREQ PSP, r2");

    // asm("CMP LR, #0xFFFFFFED");
    // asm("ITTT EQ"); //Next 3 instructions executed if LR = 0xFFFFFFED
    // asm("MRSEQ r2, PSP");
    // asm("ADDEQ r2, #0x60");
    // asm("MSREQ PSP, r2");
    // asm("LDR r3, [r2]");

    // //check exception flags
    // asm("BIC r3, #0x8F");
    // asm("STR r3, [r2]");

    // asm("DMB");
    StallardOSGeneralFaultHandler();
    // asm("BX LR");
}