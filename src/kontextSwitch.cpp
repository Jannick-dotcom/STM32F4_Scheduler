#include "TaskScheduler.h"
#include <stm32f4xx_hal.h>
//Kontext Switch
function_struct *currentTask = nullptr;
function_struct *nextTask = nullptr;
function_struct *taskMainStruct;

#define defaultSysTickFreq 1000.0
#define functionModifier (uint32_t)0xFFFFFFFE     //Use the function pointer with lowest bit zero
#define sysTickTicks (uint32_t)(SystemCoreClock / sysTickFreq)

volatile uint32_t sysTickFreq = defaultSysTickFreq; //11Hz - ... how often context switches
volatile uint32_t sysTickMillisPerInt = (uint32_t)(1000.0 / sysTickFreq);

extern "C" inline void pendPendSV()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

extern "C" inline void Jannix_SysTick_Config(uint32_t ticks)
{
    SysTick_Config(ticks);
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
//Set all the Interrupts and Values for the OS
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::startOS(void)
{
    if(first_function_struct != nullptr)
    {
        currentTask = first_function_struct;      //The current Task is the first one in the List

        asm("MOV R0, #2");
        asm("MSR CONTROL, R0");
        asm("ISB");

        asm("MRS R0, MSP");
        asm("MSR PSP, R0");

        enable_interrupts();
        asm("SVC #5");
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//Finding a next Task
////////////////////////////////////////////////////////////////////////////////////////
inline void findNextFunction(void)
{
    function_struct *temp = taskMainStruct;    //Start with task after current one
    uint8_t prioMin = 255;  //Use only tasks with prio < 255
    do
    {    
        if(temp->executable == true && temp->priority < prioMin) //Get task with lowest prio number -> highest priority
        {
            nextTask = temp;                   //set nextF to right now highest priority task
            prioMin = temp->priority;       //save prio
        }
        temp = temp->next;
    } while(temp != taskMainStruct);  //Solange ich noch nicht wieder beim ersten angekommen bin 

    if(nextTask == nullptr)    //Wenn ein Task ausführbar ist
    {
        nextTask = taskMainStruct;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//If a Task Returns, this function gets executed and calls the remove function of this task
////////////////////////////////////////////////////////////////////////////////////////
void taskOnEnd(void)
{
    disable_interrupts();
    //delete currentTask;                         //Remove the returned function
    currentTask->used = 0;
    currentTask = taskMainStruct;
    enable_interrupts();
    asm("SVC #1");                                       //Create a system call to the SVC Handler
}

////////////////////////////////////////////////////////////////////////////////////////
//Here the magic happens
//Depending on the Task state, switching happens
////////////////////////////////////////////////////////////////////////////////////////
extern "C" inline void switchTask(void)
{
    if(currentTask == nullptr) //make sure Tasks are available
    {
        currentTask = taskMainStruct;
    }
    if(nextTask == nullptr)
    {
        nextTask = taskMainStruct;
    }

    if ((currentTask->State == RUNNING)) //Hier Task anhalten
    {
        asm("MRS r0, PSP");     //Get Process Stack Pointer
        asm("STMDB r0!, {r4-r11}"); //Save additional not yet saved registers
        //asm("VSTMDB r0!, {s16-s31}");
        asm("MSR PSP, r0");     //Set Modified Stack pointer
        asm("MOV %0, r0" : "=r"(currentTask->Stack));   //Save Stack pointer

        currentTask->State = PAUSED;    //Save function state
        currentTask = nextTask;
    }

    if (currentTask->State == NEW)      //New Task
    {   
        asm("MOV r4, #0");                                  //R0
        asm("MOV r5, #1");                                  //R1
        asm("MOV r6, #2");                                  //R2
        asm("MOV r7, #3");                                  //R3
        asm("MOV r8, #12");                                 //R12
        asm("MOV r9, %0" : : "r"(taskOnEnd));               //LR
        asm("MOV r10, %0" : : "r"((uint32_t)currentTask->function));   //PC
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
    }

    if (currentTask->State == PAUSED) //Hier Task fortsetzen
    {
        asm("MOV r0, %0" : : "r"(currentTask->Stack));  //get saved Stack pointer
        //asm("VLDMIA r0!, {s16-s31}");
        asm("LDMIA r0!, {r4-r11}");                     //load registers from memory
        asm("MSR PSP, r0");                             //set PSP
        currentTask->State = RUNNING;                   //Save state as running
        nextTask = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//System Call (Supervisor Call) from Delay or after a task finishes
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void SVC_Handler(void)
{
    disable_interrupts();
    uint32_t handleMode;
    asm("MRS r0, PSP");
    asm("LDR r0, [r0, #24]");
    asm("LDR r0, [r0, #-2]");
    asm("AND r0, #0xff");
    asm("MOV %0, r0" : "=r"(handleMode)); 
    switch (handleMode)
    {
    case 0:
        currentTask = nullptr;
        nextTask = nullptr;
        pendPendSV();
        break;
    
    case 1: //Task has Ended
        currentTask = nullptr;
        nextTask = nullptr;
        switchTask();
        break;
    
    case 2: //Delay
        nextTask = nullptr;
        switchTask();
        break;

    case 3: //Switch to privileged mode
        asm("MRS R0, CONTROL");
        asm("AND R0, #-2");
        asm("MSR CONTROL, R0");
        asm("ISB");                               //After modifying the control Register flush all instructions (I don't understand why but ok)
        break;

    case 4: //Switch to unprivileged mode
        asm("MRS R0, CONTROL");
        asm("ORR R0, #1");
        asm("MSR CONTROL, R0");
        asm("ISB");                               //After modifying the control Register flush all instructions (I don't understand why but ok)
        break;

    case 5:                                       //Start the os
        while(SysTick_Config(sysTickTicks));

        NVIC_SetPriority(SysTick_IRQn, 0x00);
        NVIC_SetPriority(PendSV_IRQn, 0x00);
        NVIC_EnableIRQ(PendSV_IRQn);
        NVIC_EnableIRQ(SysTick_IRQn);
        NVIC_EnableIRQ(SVCall_IRQn);
        pendPendSV();
        break;

    default:
        break;
    }

    enable_interrupts();                                    //Enable all interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Set the PendSV exception to pending (Systick is a 24 bit counter) minimum 11Hz
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void SysTick_Handler(void)                           //In C Language
{    
    disable_interrupts();
    nextTask = nullptr;
    function_struct *temp = taskMainStruct;
    uint32_t minDelayT = -1;
    do
    {
        if(temp == nullptr)
        {
            minDelayT = 0;
            break;
        }

        if(temp->continueInMS < sysTickMillisPerInt)
        {
            temp->continueInMS = 0;
            temp->executable = true;        //Wenn keine Delay Zeit mehr, task auf executable setzen
        }
        else
        {
            temp->continueInMS -= sysTickMillisPerInt;    //dekrementieren
        }
        if(minDelayT > temp->continueInMS)
        {
            minDelayT = temp->continueInMS;
        }
        temp = temp->next;  //Nächsten Task
    } while (temp != taskMainStruct);
    
    #ifdef useSystickAltering
        if(minDelayT < 90 && minDelayT > 0) 
        {
            sysTickFreq = 1000.0 / (float)minDelayT;
        }
        else 
        {
            sysTickFreq = defaultSysTickFreq;
        }
        sysTickMillisPerInt = (uint32_t)(1000.0 / sysTickFreq)
        SysTick_Config(sysTickTicks);             //Set the frequency of the systick interrupt
    #endif

    if(currentTask->priority > 0) 
    {
        function_struct *temp = taskMainStruct;    //Start with task after current one
        uint8_t prioMin = 255;  //Use only tasks with prio < 255
        do
        {    
            if(temp->executable == true && temp->priority < prioMin) //Get task with lowest prio number -> highest priority
            {
                nextTask = temp;                   //set nextF to right now highest priority task
                prioMin = temp->priority;       //save prio
            }
            temp = temp->next;
        } while(temp != taskMainStruct);  //Solange ich noch nicht wieder beim ersten angekommen bin 

        if(nextTask == nullptr)    //Wenn ein Task ausführbar ist
        {
            nextTask = taskMainStruct;
        }
        pendPendSV();       //If switchEnable set, set the PendSV to pending
    }
    enable_interrupts();                                        //enable all interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Switch the context
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void PendSV_Handler()                                //In C Language
{
    disable_interrupts();
    switchTask();
    //asm("MOV LR, #0xFFFFFFFD");                             //Set the LR to 0xFFFFFFFD to signal Process mode with psp
    enable_interrupts();                                    //Enable all interrupts
}