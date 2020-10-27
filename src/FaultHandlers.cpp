#include "StallardOS.hpp"

extern uint8_t switchEnable;
extern function_struct *currentTask;
extern function_struct *taskMainStruct;
extern function_struct *nextTask;

inline void StallardOSGeneralFaultHandler() //restarts a Task when a fault occurs
{
    disable_interrupts();
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
    enable_interrupts();
}

extern "C" void HardFault_Handler()
{
    StallardOSGeneralFaultHandler();
}

extern "C" void NMI_Handler()
{
    StallardOSGeneralFaultHandler();
}

extern "C" void MemManage_Handler()
{
    StallardOSGeneralFaultHandler();
}

extern "C" void BusFault_Handler()
{
    StallardOSGeneralFaultHandler();
}

extern "C" void UsageFault_Handler()
{
    StallardOSGeneralFaultHandler();
}