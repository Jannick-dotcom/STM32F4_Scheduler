#include "StallardOSconfig.h"
#include "StallardOSHelpers.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

extern struct function_struct *currentTask;
extern struct function_struct *taskMainStruct;
extern struct function_struct *nextTask;
volatile uint64_t msCurrentTimeSinceStart = 0; //about 585 000 years of microsecond counting
volatile uint32_t sysTickFreq = defaultSysTickFreq; //11Hz - ... how often context switches
volatile uint32_t sysTickMillisPerInt = 1;

/**
 * No Task available.
 *
 * @param
 * @return
 *//* code */
void StallardOS_noTask()
{
    asm("MOV r7, #0");
    asm("SVC #0");
}

/**
 * Get super Rights
 *
 * @param
 * @return
 */
void StallardOS_sudo()
{
    asm("MOV r7, #3");
    asm("SVC #3");
}

/**
 * Release super Rights.
 *
 * @param
 * @return
 */
void StallardOS_unSudo()
{
    asm("MOV r7, #4");
    asm("SVC #4");
}

/**
 * Start the OS.
 *
 * @param
 * @return
 */
void StallardOS_start()
{
    asm("MOV r7, #5");
    asm("SVC #5");
}

/**
 * Delay a Task.
 *
 * @param
 * @return
 */
void StallardOS_delay()
{
    asm("MOV r7, #2");
    asm("SVC #2");
}

/**
 * end a Task.
 *
 * @param
 * @return
 */
void StallardOS_endTask()
{
    asm("MOV r7, #1");
    asm("SVC #1");
}

/**
 * Jump to Bootloader.
 *
 * @param
 * @return
 */
void StallardOS_goBootloader()
{
    asm("MOV r7, #6");
    asm("SVC #6");
}

/**
 * Enable all interrupts.
 *
 * @param
 * @return
 */
void enable_interrupts()
{
    asm("CPSIE I"); //Instruction for enabling interrupts
}

/**
 * Disable all interrupts.
 *
 * @param
 * @return
 */
void disable_interrupts()
{
    asm("CPSID I"); //Instruction for disabling interrupts
}

/**
 * Set the pendSV Exception to pending.
 *
 * @param
 * @return
 */
void pendPendSV()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

/**
 * Configure the systick timer to fire every "ticks".
 *
 * @param
 * @return
 */
void StallardOS_SysTick_Config(uint32_t ticks)
{
    SysTick_Config(ticks);
}

/**
 * If a Task Returns, this function gets executed and calls the remove function of this task.
 *
 * @param
 * @return
 */
void taskOnEnd(void)
{
    disable_interrupts();
    currentTask->used = 0;
    currentTask->executable = 0;
    currentTask = taskMainStruct;
    enable_interrupts();
    StallardOS_endTask(); //Create a system call to the SVC Handler
}

/**
 * Switching of a Task happens here.
 *
 * @param
 * @return
 */
static inline void switchTask(void)
{
    if (currentTask == NULL) currentTask = taskMainStruct;//make sure Tasks are available
    if (nextTask == NULL) nextTask = taskMainStruct;

    if ((currentTask->State == RUNNING)) //Hier Task anhalten
    {
        asm("MRS r0, PSP");         //Get Process Stack Pointer
        asm("STMDB r0!, {r4-r11}"); //Save additional not yet saved registers
        asm("TST lr, #0x10");
        asm("IT EQ");
        asm("VSTMDBEQ r0!, {s16-s31}");
        asm("MSR PSP, r0"); //Set Modified Stack pointer
        asm("MOV %0, r0" : "=r"(currentTask->Stack)); //Save Stack pointer

        currentTask->State = PAUSED; //Save function state
        currentTask = nextTask;
    }

    if (currentTask->State == NEW) //New Task
    {
        asm("MOV r4, #0");  //R0
        asm("MOV r5, #1");  //R1
        asm("MOV r6, #2");  //R2
        asm("MOV r7, #3");  //R3
        asm("MOV r8, #12"); //R12
        asm("MOV r9, %0"  : : "r"(taskOnEnd)); //LR
        asm("MOV r10, %0" : : "r"((uint32_t)currentTask->function & functionModifier)); //PC
        asm("MOV r11, #0x01000000");                                    //XPSR

        asm("MOV r0, %0"  : : "r"(currentTask->Stack)); //get saved Stack pointer
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

        currentTask->State = RUNNING; //Save state as running
    }

    if (currentTask->State == PAUSED) //Hier Task fortsetzen
    {
        asm("MOV r0, %0" : : "r"(currentTask->Stack)); //get saved Stack pointer
        asm("VLDMIA r0!, {s16-s31}");
        asm("LDMIA r0!, {r4-r11}");   //load registers from memory
        asm("MSR PSP, r0");           //set PSP
        currentTask->State = RUNNING; //Save state as running
        nextTask = NULL;
    }
}

/**
 * SuperVisorCall Handler for the supervisor Exception.
 *
 * @param
 * @return
 */
void SVC_Handler(void)
{
    disable_interrupts();
    uint8_t handleMode;
    asm("MOV %0, r7" : "=r"(handleMode));

    switch (handleMode)
    {
    case 0: //No Task
        currentTask = NULL;
        nextTask = NULL;
        pendPendSV();
        break;

    case 1: //Task has Ended
        currentTask = NULL;
        nextTask = NULL;
        switchTask();
        break;

    case 2: //Delay
        nextTask = NULL;
        switchTask();
        break;

    case 3: //Switch to privileged mode
        asm("MRS R0, CONTROL");
        asm("AND R0, #-2");
        asm("MSR CONTROL, R0");
        asm("ISB"); //After modifying the control Register flush all instructions (I don't understand why but ok)
        break;

    case 4: //Switch to unprivileged mode
        asm("MRS R0, CONTROL");
        asm("ORR R0, #1");
        asm("MSR CONTROL, R0");
        asm("ISB"); //After modifying the control Register flush all instructions (I don't understand why but ok)
        break;

    case 5: //Start the os
        SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  //Set the FPU to full access
        while (SysTick_Config(sysTickTicks));

        NVIC_SetPriority(SysTick_IRQn, 0x00);
        NVIC_SetPriority(PendSV_IRQn, 0x00);
        NVIC_EnableIRQ(PendSV_IRQn);
        NVIC_EnableIRQ(SysTick_IRQn);
        NVIC_EnableIRQ(SVCall_IRQn);
        
        //Start the FPU (s.257 prog man)
        // asm("LDR.W r0, =0xE000ED88");
        // asm("LDR r1, [r0]");
        // asm("ORR r1, r1, #(0xF << 20)");
        // asm("STR r1, [r0]");
        // asm("DSB");
        // asm("ISB");
        //FPU Started

        pendPendSV();
        break;

    case 6: //Enter Bootloader
        *((uint32_t *)0x2001FFF0) = 0xDEADBEEF; // End of RAM
        NVIC_SystemReset();
        break;

    default:
        break;
    }

    enable_interrupts(); //Enable all interrupts
}

/**
 * Systick Handler for an Exception every x ms. Minimum is 11 Hz
 *
 * @param
 * @return
 */
void SysTick_Handler(void) //In C Language
{
    disable_interrupts();
#ifdef contextSwitch
    nextTask = NULL;
    struct function_struct *temp = taskMainStruct->next;
    uint32_t minDelayT = -1;
    uint8_t prioMin = -1;                         //Use only tasks with prio < 255
    while (temp != taskMainStruct && temp != NULL)
    {   
        if (temp->continueInMS < sysTickMillisPerInt)
        {
            temp->continueInMS = 0;
            temp->executable = 1; //Wenn keine Delay Zeit mehr, task auf executable setzen
        }
        else
        {
            temp->continueInMS -= sysTickMillisPerInt; //dekrementieren
        }
        
        if (temp->used && temp->executable && temp->priority < prioMin) //Get task with lowest prio number -> highest priority
        {
            nextTask = temp;          //set nextF to right now highest priority task
            prioMin = temp->priority; //save prio
        }

#ifdef useSystickAltering
        if (minDelayT > temp->continueInMS)
        {
            minDelayT = temp->continueInMS;
        }
#endif
        temp = temp->next; //Nächsten Task
    }

#ifdef useSystickAltering
    if (minDelayT >= 90 || minDelayT < 1)
    {
        minDelayT = 1;
    }
    SysTick_Config((uint32_t)(SystemCoreClock / (1000 * minDelayT))); //Set the frequency of the systick interrupt
#endif

    if (currentTask->priority > 0)
    {
        pendPendSV(); //If switchEnable set, set the PendSV to pending
    }
#endif
    msCurrentTimeSinceStart += sysTickMillisPerInt;
    HAL_IncTick();
    sysTickMillisPerInt = minDelayT;
    enable_interrupts(); //enable all interrupts
}

/**
 * PendSV Exception Handler.
 *
 * @param
 * @return
 */
void PendSV_Handler()
{
    disable_interrupts();
    switchTask();
    //asm("MOV LR, #0xFFFFFFFD");                             //Set the LR to 0xFFFFFFFD to signal Process mode with psp
    enable_interrupts(); //Enable all interrupts
}