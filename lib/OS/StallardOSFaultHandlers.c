#include "StallardOSHelpers.h"
#include <stdint.h>

extern struct function_struct *currentTask;
extern struct function_struct *taskMainStruct;
extern struct function_struct *nextTask;

void StallardOSGeneralFaultHandler() //restarts a Task when a fault occurs
{
    disable_interrupts();
#ifdef contextSwitch
    currentTask->Stack = currentTask->vals + sizeStack - 4; //End of Stack
    asm("MOV r4, #0");                                  //R0
    asm("MOV r5, #1");                                  //R1
    asm("MOV r6, #2");                                  //R2
    asm("MOV r7, #3");                                  //R3
    asm("MOV r8, #12");                                 //R12
    asm("MOV r9, %0" : : "r"(taskMainStruct->function));//LR
    asm("MOV r10, %0" : : "r"((uint32_t)currentTask->function & functionModifier));   //PC
    asm("MOV r11, #0x01000000");                        //XPSR

    asm("MOV r0, %0" : : "r"(currentTask->Stack));  //get saved Stack pointer
    asm("STMDB r0!, {r4-r11}");     //Store prepared initial Data for R0-R3, R12, LR, PC, XPSR
    asm("MSR PSP, r0");             //set PSP

    asm("MOV r4, #4");
    asm("MOV r5, #5");
    asm("MOV r6, #6");
    asm("MOV r7, #7");
    asm("MOV r8, #8");
    asm("MOV r9, #9");
    asm("MOV r10, #10");
    asm("MOV r11, #11");

    currentTask->State = RUNNING;   //Save state as running
#endif
    enable_interrupts();
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

// FPU IRQ Handler
void FPU_IRQHandler(void)
{
    //asm("IMPORT FPU_ExceptionHandler");
    asm("MOV R0, LR");                  // move LR to R0
    asm("MOV R1, SP");                  // Save SP to R1 to avoid any modification to
                                        // the stack pointer from FPU_ExceptionHandler
    asm("MRS r4, MSP");
    asm("MRS r5, PSP");

    asm("VMRS R2, FPSCR");              // dummy read access, to force clear
    // register uint32_t fpscr_val;
    
    //if(lr == 0xFFFFFFE9)
    //{
        asm("CMP LR, #0xFFFFFFE9");
        asm("ITTT EQ"); //Next 3 instructions executed if LR = 0xFFFFFFE9
        //sp = sp + 0x60;
        asm("MOVEQ r2, r4");
        asm("ADDEQ r2, #0x60");
        asm("MSREQ PSP, r2");
    //}
    // else if(lr == 0xFFFFFFED)
    // {
        asm("CMP LR, #0xFFFFFFED");
        asm("ITTT EQ"); //Next 3 instructions executed if LR = 0xFFFFFFED
        //sp = __get_PSP() + 0x60 ;
        asm("MRSEQ r2, PSP");
        asm("ADDEQ r2, #0x60");
        asm("MSREQ PSP, r2");
    // }
    //fpscr_val = *(uint32_t*)sp;
    asm("LDR r3, [r2]");

    //{ check exception flags }
    //fpscr_val &= (uint32_t)~0x8F ; // Clear all exception flags
    asm("BIC r3, #0x8F");

    //*(uint32_t*)sp = fpscr_val;
    asm("STR r3, [r2]");

    asm("DMB");
    StallardOSGeneralFaultHandler();
    asm("BX LR");
}