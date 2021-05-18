#include "StallardOSconfig.h"
#include "StallardOSHelpers.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

extern struct function_struct *currentTask;
extern struct function_struct *taskMainStruct;
extern struct function_struct *nextTask;
volatile uint64_t msCurrentTimeSinceStart = 0; //about 584942417 years of millisecond counting
volatile uint64_t usCurrentTimeSinceStart = 0; //about 585 000 years of microsecond counting
volatile uint32_t sysTickFreq = defaultSysTickFreq; //11Hz - ... how often context switches
volatile uint32_t sysTickMillisPerInt = 1;

volatile uint64_t taskMainTime = 0; //Experimental

/**
 * No Task available.
 *
 * @param
 * @return
 *//* code */
__attribute__((always_inline)) void StallardOS_noTask()
{
    // asm("MOV R7, #0");
    asm("SVC #0");
}

/**
 * Get super Rights
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void StallardOS_sudo()
{
    // asm("MOV R7, #3");
    asm("SVC #3");
}

/**
 * Release super Rights.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void StallardOS_unSudo()
{
    // asm("MOV R7, #4");
    asm("SVC #4");
}

/**
 * Start the OS.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void StallardOS_start()
{
    // asm("MOV R7, #5");
    asm("SVC #5");
}

/**
 * Delay a Task.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void StallardOS_delay()
{
    // asm("MOV R7, #2");
    asm("SVC #2");
}

/**
 * end a Task.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void StallardOS_endTask()
{
    // asm("MOV R7, #1");
    asm("SVC #1");
}

/**
 * Jump to Bootloader.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void StallardOS_goBootloader()
{
    // asm("MOV R7, #6");
    asm("SVC #6");
}

/**
 * Enable all interrupts.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void enable_interrupts()
{
    asm("CPSIE I"); //Instruction for enabling interrupts
}

/**
 * Disable all interrupts.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void disable_interrupts() 
{
    asm("CPSID I"); //Instruction for disabling interrupts
}

/**
 * Set the pendSV Exception to pending.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void pendPendSV()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

/**
 * Configure the systick timer to fire every "ticks".
 *
 * @param
 * @return
 */
__attribute__((always_inline)) void StallardOS_SysTick_Config(uint32_t ticks)
{
    SysTick_Config(ticks);
}

void jumpToBootloader(void) 
{
    void (*SysMemBootJump)(void);
    volatile uint32_t addr = 0x1FFF0000;
#if defined(USE_HAL_DRIVER)
    HAL_RCC_DeInit();
#endif /* defined(USE_HAL_DRIVER) */
#if defined(USE_STDPERIPH_DRIVER)
    RCC_DeInit();
#endif /* defined(USE_STDPERIPH_DRIVER) */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;
    //__disable_irq();
    SYSCFG->MEMRMP = 0x01;
    SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));
    __set_PRIMASK(1);      // Disable interrupts
    __set_PRIMASK(0x20001000);      // Set the main stack pointer to its default value
    __set_MSP(0x20001000);
    SysMemBootJump();
    while(1);
}

#ifdef contextSwitch
void findNextFunction(uint32_t *minDelayT)
{
    nextTask = NULL;
    struct function_struct *temp = currentTask->next;
    uint8_t prioMin = -1;                         //Use only tasks with prio < 255
    while (temp != currentTask && temp != NULL)
    {
        if(temp->used == 0) //If the TCB is unused, continue with the next one
        {
            temp = temp->next;
            continue;
        }

        if (temp->continueInMS < sysTickMillisPerInt)
        {
            temp->continueInMS = 0;
        }
        else
        {
            temp->continueInMS -= sysTickMillisPerInt; //dekrementieren
        }
        
        if (temp->executable && temp->continueInMS == 0 && temp->priority < prioMin) //Get task with lowest prio number -> highest priority
        {
            if(temp->waitingForSemaphore && &temp->semVal != NULL && temp->semVal == 0) //If this task is still waiting for the semaphore
            {
                temp = temp->next;
                continue;
            }
            nextTask = temp;          //set nextF to right now highest priority task
            prioMin = temp->priority; //save prio
        }
#ifdef useSystickAltering
        if(minDelayT != NULL)
        {
            if (*minDelayT > temp->continueInMS)
            {
                *minDelayT = temp->continueInMS;
            }
        }
#endif //useSystickAltering
        temp = temp->next; //Nächsten Task
    }
    if((nextTask == taskMainStruct || nextTask == NULL) && currentTask->executable == 1 && temp->continueInMS == 0) nextTask = currentTask;
}
#endif //contextSwitch


/**
 * If a Task Returns, this function gets executed and calls the remove function of this task.
 *
 * @param
 * @return
 */
#ifdef contextSwitch
void taskOnEnd(void)
{
    disable_interrupts();
    currentTask->used = 0;
    currentTask->executable = 0;
    currentTask->State = NEW; 
    currentTask = taskMainStruct;
    enable_interrupts();
    StallardOS_endTask(); //Create a system call to the SVC Handler
}
#endif

/**
 * Switching of a Task happens here.
 *
 * @param
 * @return
 */
#ifdef contextSwitch
__attribute__((always_inline)) void switchTask(void)
{
    if (currentTask == NULL) currentTask = taskMainStruct;//make sure Tasks are available
    if (nextTask == NULL) nextTask = taskMainStruct;

    if ((currentTask->State == RUNNING)) //Hier Task anhalten
    {
        asm("MRS r0, PSP");         //Get Process Stack Pointer
        // asm("MRS r3, CONTROL");
        asm("STMDB r0!, {r4-r11}"); //Save additional not yet saved registers
        asm("VSTMDB r0!, {s16-s31}");
        asm("MSR PSP, r0"); //Set Modified Stack pointer
        asm("MOV %0, r0" : "=r"(currentTask->Stack)); //Save Stack pointer

        currentTask->State = PAUSED; //Save function state
        // if(&currentTask->vals[sizeStack] - currentTask->Stack > currentTask->stackUsage) 
        // {
        //     currentTask->stackUsage = &currentTask->vals[sizeStack] - currentTask->Stack;
        // }
        currentTask = nextTask;
    }

    if (currentTask->State == NEW) //New Task
    {
        asm("MOV r4, #0");  //R0
        asm("MOV r5, #1");  //R1
        asm("MOV r6, #2");  //R2
        asm("MOV r7, #3");  //R3
        asm("MOV r8, #12"); //R12
        asm("MOV r9, %0"  : : "r"((uint32_t)taskOnEnd)); //LR
        asm("MOV r10, %0" : : "r"((uint32_t)currentTask->function & functionModifier)); //PC
        asm("MOV r11, #0x01000000");                                    //XPSR

        asm("MOV r0, %0"  : : "r"(currentTask->Stack)); //get saved Stack pointer
        asm("STMDB r0!, {r4-r11}");     //Store prepared initial Data for R0-R3, R12, LR, PC, XPSR
        asm("MSR PSP, r0");             //set PSP

        currentTask->State = RUNNING; //Save state as running
    }

    if (currentTask->State == PAUSED) //Hier Task fortsetzen
    {
        asm("MOV r0, %0" : : "r"(currentTask->Stack)); //get saved Stack pointer
        asm("VLDMIA r0!, {s16-s31}");
        asm("LDMIA r0!, {r4-r11}");   //load registers from memory
        asm("MSR PSP, r0");           //set PSP
        // asm("MSR CONTROL, r3");
        currentTask->State = RUNNING; //Save state as running
        nextTask = NULL;
    }
}
#endif

/**
 * SuperVisorCall Handler for the supervisor Exception.
 *
 * @param
 * @return
 */
#ifdef contextSwitch
void SVC_Handler()
{
    disable_interrupts();
    uint8_t handleMode;
    uint32_t temp;

    asm("TST    LR, #4");
    asm("ITE    EQ");
	asm("MRSEQ	R0, MSP");
	asm("MRSNE	R0, PSP");

	asm("LDR	R0, [R0, #24]");
	asm("LDRB	R0, [R0, #-2]");
    asm("MOV    %0, r0" : "=r"(handleMode));

    switch (handleMode)
    {
    case 0: //No Task
        currentTask = NULL;
        //findNextFunction(NULL);
        pendPendSV();
        break;

    case 1: //Task has Ended
        currentTask = NULL;
        //findNextFunction(NULL);
        switchTask();
        break;

    case 2: //Delay
        findNextFunction(&temp);
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
        StallardOS_SetSysClock(168);
        SysTick_Config(sysTickTicks);
        SystemCoreClockUpdate();
        NVIC_SetPriority(SysTick_IRQn, 0x00);
        NVIC_SetPriority(PendSV_IRQn, 0xFF);
        NVIC_EnableIRQ(PendSV_IRQn);
        NVIC_EnableIRQ(SysTick_IRQn);
        NVIC_EnableIRQ(SVCall_IRQn);
        NVIC_EnableIRQ(FPU_IRQn);
        pendPendSV();
        break;

    case 6: //Enter Bootloader
        jumpToBootloader();
        break;

    default:
        break;
    }

    enable_interrupts(); //Enable all interrupts
}
#endif


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
    usCurrentTimeSinceStart++;
    if(usCurrentTimeSinceStart % (defaultSysTickFreq / 1000) == 0) //Every millisecond
    {
        msCurrentTimeSinceStart++;//sysTickMillisPerInt;
        HAL_IncTick();
        uint32_t minDelayT = -1;
        if(currentTask == taskMainStruct) 
        {
            taskMainTime += sysTickMillisPerInt; //Auslastungsberechnung
        }
        findNextFunction(&minDelayT);
        if(currentTask != nextTask)
        {
            pendPendSV(); //If nextTask is not this task, set the PendSV to pending
        }
    }
#ifdef useSystickAltering
    if (minDelayT >= 90 || minDelayT < 1)
    {
        minDelayT = 1;
    }
    SysTick_Config((uint32_t)(SystemCoreClock / (1000 * minDelayT))); //Set the frequency of the systick interrupt
    sysTickMillisPerInt = minDelayT;
#endif //useSystickAltering

#endif //contextSwitch
    
    enable_interrupts(); //enable all interrupts
}

/**
 * PendSV Exception Handler.
 *
 * @param
 * @return
 */
#ifdef contextSwitch
void PendSV_Handler()
{
    disable_interrupts();
    switchTask();
    //asm("MOV LR, #0xFFFFFFFD");                             //Set the LR to 0xFFFFFFFD to signal Process mode with psp
    enable_interrupts(); //Enable all interrupts
}
#endif