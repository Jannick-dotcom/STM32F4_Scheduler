#include <stm32f4xx_hal.h>
#include "TaskScheduler.hpp"
//Kontext Switch
uint8_t switchEnable = 0;
function_struct *currentTask = nullptr;
function_struct *nextTask = nullptr;
function_struct *taskMainStruct = nullptr;
volatile float sysTickFreq = 1000.0; //11Hz - ... how often context switches

#define func (uint32_t)currentTask->function & ~1UL     //Use the function pointer with lowest bit zero
#define sysTickTicks (uint32_t)(SystemCoreClock / sysTickFreq)
#define sysTickMillisPerInt (float)(1000.0 / sysTickFreq)

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
//If a Task Returns call the remove function of this task
////////////////////////////////////////////////////////////////////////////////////////
void taskDeleteOnEnd(void)
{
    function_struct *temp = currentTask->next;
    currentTask->removeFunction();
    currentTask = temp;
    asm("SVC 0x00");
    enable_interrupts();
}

////////////////////////////////////////////////////////////////////////////////////////
//Set all the Interrupts and Values for the OS
////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::startOS(void)
{
    currentTask = first_function_struct;      //The current Task is the first one in the List
    //currentTask->State = NEW;                 //The current Task is a new Task
    setContextSwitch(true);                   //Activate context switching
    SysTick_Config(sysTickTicks);             //Set the frequency of the systick interrupt

    NVIC_SetPriority(PendSV_IRQn, 0xff);      //Lowest possible priority 
    NVIC_SetPriority(SysTick_IRQn, 0x00);     //Highest possible priority

    __set_PSP(__get_MSP());                   //Init the PSP
    __set_CONTROL(0x03);                      // Switch to Unprivilleged Thread Mode with PSP

    asm("ISB");                               //After modifying the control Register flush all instructions (I don't understand why but ok)
    enable_interrupts();  
}

////////////////////////////////////////////////////////////////////////////////////////
//Finding a next Task
////////////////////////////////////////////////////////////////////////////////////////
function_struct *findNextFunction(function_struct *currF)
{
    function_struct *temp = currF->next;
    function_struct *nextF = nullptr;
    uint8_t flagFound = 0;
    do
    {    
        if(temp->executable == true && !flagFound && temp->priority < 255)//Wenn Task Executable ist und noch keine Funktion gefunden wurde
        {
            flagFound = 1;
            nextF = temp;
        }
        temp = temp->next;
    } while(temp != currF);  //Solange ich noch nicht wieder beim ersten angekommen bin 

    if(nextF != nullptr)    //Wenn ein Task ausführbar ist
    {
        return nextF;       //Diesen returnen
    }
    else                    //Ansonsten
    {
        return taskMainStruct;  //Den Task zum Rechenzeit verscherbeln nehmen
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//System Call interrupt (Supervisor Call) from Delay
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void SVC_Handler(void)
{
    nextTask = findNextFunction(currentTask);
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;    //Set the PendSV to pending
    enable_interrupts();                    //enable interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Set the PendSV exception to pending (Systick is a 24 bit counter) minimum 11Hz
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void SysTick_Handler(void)                           //In C Language
{    
    nextTask = nullptr;
    function_struct *temp = currentTask->next;
    uint32_t minDelayT = -1;
    do
    {
        if(temp->continueInMS > 0) //Wenn verbleibende Delay Zeit größer als 0
        {
            if(temp->continueInMS < sysTickMillisPerInt)
            {
                temp->continueInMS = 0;
            }
            else
            {
                temp->continueInMS -= sysTickMillisPerInt;    //dekrementieren
            }
        }
        else
        {
            temp->executable = true;        //Wenn keine Delay Zeit mehr, task auf executable setzen
        }

        if(minDelayT > temp->continueInMS)
        {
            minDelayT = temp->continueInMS;
        }

        temp = temp->next;  //Nächsten Task
    } while (temp != currentTask);
    
    if(minDelayT < 90 && minDelayT > 0) 
    {
        sysTickFreq = 1000.0 / (float)minDelayT;
    }
    else 
    {
        sysTickFreq = 1000.0;
    }
    SysTick_Config(sysTickTicks);             //Set the frequency of the systick interrupt

    if(switchEnable && currentTask->priority > 1) 
    {
        nextTask = findNextFunction(currentTask);
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;       //If switchEnable set, set the PendSV to pending
    }   
    enable_interrupts();                                        //enable all interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Switch the context
////////////////////////////////////////////////////////////////////////////////////////
extern "C" void PendSV_Handler()                                //In C Language
{
    disable_interrupts();
    if ((currentTask->State == RUNNING)) //Hier Task anhalten
    {
        asm("MRS r0, PSP");     //Get Process Stack Pointer
        asm("STMDB r0!, {r4-r11}"); //Save additional not yet saved registers
        asm("MSR PSP, r0");     //Set Modified Stack pointer
        asm("MOV %0, r0" : "=r"(currentTask->Stack));   //Save Stack pointer

        currentTask->State = STOPPED;    //Save function state
        currentTask = nextTask;
    }

    if (currentTask->State == NEW)      //New Task
    {   
        asm("MOV r4, #0");                                  //R0
        asm("MOV r5, #1");                                  //R1
        asm("MOV r6, #2");                                  //R2
        asm("MOV r7, #3");                                  //R3
        asm("MOV r8, #0x12");                               //R12
        asm("MOV r9, %0" : : "r"(taskDeleteOnEnd));         //LR
        asm("MOV r10, %0" : : "r"(func));                   //PC
        asm("MOV r11, #0x01000000");                        //XPSR

        asm("MRS r0, PSP");             //get PSP
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

    if (currentTask->State == STOPPED) //Hier Task fortsetzen
    {
        asm("MOV r0, %0" : : "r"(currentTask->Stack));  //get saved Stack pointer
        asm("LDMIA r0!, {r4-r11}");                     //load registers from memory
        asm("MSR PSP, r0");                             //set PSP
        currentTask->State = RUNNING;                   //Save state as running
    }
    asm("MOV LR, #0xFFFFFFFD");                             //Set the LR to 0xFFFFFFFD to signal Process mode with psp
    enable_interrupts();                                    //Enable all interrupts
    asm("bx LR");                                           //Jump to LR address
}