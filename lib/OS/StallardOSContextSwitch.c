#include "StallardOSconfig.h"
#include "StallardOSHelpers.h"
#include <stdint.h>
#include <stdlib.h>
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

extern volatile struct function_struct* volatile currentTask;
extern volatile struct function_struct* volatile taskMainStruct;
extern volatile struct function_struct* volatile nextTask;

#ifdef useMPU
static MPU_Region_InitTypeDef MPU_StackCfg = {
    /* these values are always the same (for stack)
     * do not assign them at each context switch
     */
    .Enable = MPU_REGION_ENABLE,
    .TypeExtField = MPU_TEX_LEVEL0,
    .SubRegionDisable = 0x00,

    /* stack region is
    * Full access
    * shareable
    * cachable
    * not bufferable
    * not executable
    */
    .AccessPermission = MPU_REGION_FULL_ACCESS,
    .IsShareable = MPU_ACCESS_SHAREABLE,
    .IsCacheable = MPU_ACCESS_CACHEABLE,
    .IsBufferable = MPU_ACCESS_NOT_BUFFERABLE,
    .DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE,

    /* always use MPU region 3 for stack */
    .Number = MPU_REGION_NUMBER3
};
#endif

// volatile uint64_t msCurrentTimeSinceStart = 0; //about 584 942 417 years of millisecond counting
volatile uint64_t usCurrentTimeSinceStart = 0; //about 584 942 years of microsecond counting

volatile uint64_t taskMainTime = 0; //Experimental

/**
 * Jump to Bootloader.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) inline void StallardOS_goBootloader()
{
    // __ASM volatile("MOV R7, #6");
    CALL_BOOTLOADER();
}

/**
 * Enable all interrupts.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) inline void enable_interrupts()
{
    __ASM volatile("CPSIE I"); //Instruction for enabling interrupts
    __ASM volatile("CPSIE F"); //Instruction for enabling interrupts
}

/**
 * Disable all interrupts.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) inline void disable_interrupts() 
{
    __ASM volatile("CPSID I"); //Instruction for disabling interrupts
    __ASM volatile("CPSID F"); //Instruction for disabling interrupts
}

/**
 * Set the pendSV Exception to pending.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) inline void pendPendSV()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
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

void findNextFunction()
{
    nextTask = NULL;
    volatile struct function_struct* volatile temp = currentTask->next;
    uint8_t prioMin = -1;                         //Use only tasks with prio < 255
    if(temp == NULL)
    {
        return;
    }
    do
    {
        if(temp->used == 0) //If the TCB is unused, continue with the next one
        {
            temp = temp->next;
            continue;
        }
        
        if (temp->executable && temp->continueInUS <= usCurrentTimeSinceStart && temp->priority < prioMin) //Get task with lowest prio number -> highest priority
        {
            if(temp->waitingForSemaphore && temp->semVal != NULL && *(temp->semVal) == 0) //If this task is still waiting for the semaphore
            {
                temp = temp->next;
                continue;
            }
            nextTask = temp;          //set nextF to right now highest priority task
            prioMin = temp->priority; //save prio
        }
        temp = temp->next; //Nächsten Task
    }
    while (temp != currentTask);   
}

/**
 * Switching of a Task happens here.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) inline void switchTask(void)
{
    //if (currentTask == NULL) currentTask = taskMainStruct;//make sure Tasks are available
    if (nextTask == NULL) nextTask = taskMainStruct;


    //Pausing Task
    __ASM volatile("MRS r0, PSP");         //Get Process Stack Pointer
    __ASM volatile("ISB");
    __ASM volatile("TST r14, #0x10");       //store vfp registers, if task was using FPU
    __ASM volatile("IT eq");
    __ASM volatile("VSTMDBeq r0!, {s16-s31}");
    
    __ASM volatile("STMDB r0!, {r4-r11, r14}"); //Save additional not yet saved registers


    __ASM volatile("LDR r1, =currentTask"); //Current Task Pointer
    __ASM volatile("LDR r2, [r1]"); //Load Stack pointer from first position of currentTask
    __ASM volatile("STR r0, [r2]"); //Save stack pointer
    __ASM volatile("MOV %0, #2" : "=r"(currentTask->State)); //Set function state to paused
    __ASM volatile("LDR r0, =currentTask");
    __ASM volatile("LDR r1, =nextTask");
    __ASM volatile("LDR r1, [r1]");
    __ASM volatile("STR r1, [r0]");
    __ASM volatile("DSB");
    __ASM volatile("ISB");

    //Resuming process
    __ASM volatile("LDR r1, =currentTask");
    __ASM volatile("LDR r2, [r1]");
    __ASM volatile("LDR r0, [r2]");

    __ASM volatile("LDMIA r0!, {r4-r11, r14}");   //load registers from memory

    __ASM volatile("TST r14, #0x10");
    __ASM volatile("IT eq");
    __ASM volatile("VLDMIAeq r0!, {s16-s31}");
    
    __ASM volatile("MSR PSP, r0");           //set PSP
    __ASM volatile("ISB");
    
    __ASM volatile("MOV r0, #01");      // go into unprivileged mode
    __ASM volatile("MSR control, r0");

    __ASM volatile("MOV %0, #1" : "=r"(currentTask->State)); //Set function state to running
    __ASM volatile("LDR r1, =nextTask");
    __ASM volatile("MOV r2, #0");
    __ASM volatile("STR r2, [r1]");
}

/**
 * @brief exact copy of HAL_MPU_ConfigRegion, but inlined
 * 
 */
__attribute__((always_inline)) inline static void inline_mpu_configRegion(MPU_Region_InitTypeDef *MPU_Init){
    /* Set the Region number */
    MPU->RNR = MPU_Init->Number;

    if ((MPU_Init->Enable) != RESET)
    {
        /* Check the parameters */
        assert_param(IS_MPU_INSTRUCTION_ACCESS(MPU_Init->DisableExec));
        assert_param(IS_MPU_REGION_PERMISSION_ATTRIBUTE(MPU_Init->AccessPermission));
        assert_param(IS_MPU_TEX_LEVEL(MPU_Init->TypeExtField));
        assert_param(IS_MPU_ACCESS_SHAREABLE(MPU_Init->IsShareable));
        assert_param(IS_MPU_ACCESS_CACHEABLE(MPU_Init->IsCacheable));
        assert_param(IS_MPU_ACCESS_BUFFERABLE(MPU_Init->IsBufferable));
        assert_param(IS_MPU_SUB_REGION_DISABLE(MPU_Init->SubRegionDisable));
        assert_param(IS_MPU_REGION_SIZE(MPU_Init->Size));
        
        MPU->RBAR = MPU_Init->BaseAddress;
        MPU->RASR = ((uint32_t)MPU_Init->DisableExec             << MPU_RASR_XN_Pos)   |
                    ((uint32_t)MPU_Init->AccessPermission        << MPU_RASR_AP_Pos)   |
                    ((uint32_t)MPU_Init->TypeExtField            << MPU_RASR_TEX_Pos)  |
                    ((uint32_t)MPU_Init->IsShareable             << MPU_RASR_S_Pos)    |
                    ((uint32_t)MPU_Init->IsCacheable             << MPU_RASR_C_Pos)    |
                    ((uint32_t)MPU_Init->IsBufferable            << MPU_RASR_B_Pos)    |
                    ((uint32_t)MPU_Init->SubRegionDisable        << MPU_RASR_SRD_Pos)  |
                    ((uint32_t)MPU_Init->Size                    << MPU_RASR_SIZE_Pos) |
                    ((uint32_t)MPU_Init->Enable                  << MPU_RASR_ENABLE_Pos);
    }
    else
    {
        MPU->RBAR = 0x00U;
        MPU->RASR = 0x00U;
    }
}

/**
 * @brief exact copy of HAL_MPU_Disable, but inlined
 * 
 */
__attribute__((always_inline)) inline static void inline_mpu_disable(void){
    __DMB();
    /* Disable fault exceptions */
    SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
    /* Disable the MPU and clear the control register*/
    MPU->CTRL = 0U;
}

/**
 * @brief exact copy of HAL_MPU_Enable, but inlined
 * 
 */
__attribute__((always_inline)) inline static void inline_mpu_enable(uint32_t MPU_Control){
    /* Enable the MPU */
    MPU->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;
    
    /* Enable fault exceptions */
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
    
    /* Ensure MPU setting take effects */
    __DSB();
    __ISB();
}

/**
 * SuperVisorCall Handler for the supervisor Exception.
 *
 * @param
 * @return
 */
__attribute__((naked, __used__)) void SVC_Handler()
{
    // disable_interrupts();
    // uint8_t handleMode;

    __ASM volatile("TST    LR, #4");
    __ASM volatile("ITE    EQ");
	__ASM volatile("MRSEQ	R0, MSP"); //Warum pusht er den exception entry IMMER auf den Prozess stack pointer? Bei startOS müsste er doch auf den MSP pushen?????
	__ASM volatile("MRSNE	R0, PSP");
    // __ASM volatile("MRS	R0, PSP");

	__ASM volatile("LDR	R0, [R0, #24]");
	__ASM volatile("LDRB	R0, [R0, #-2]");
    // __ASM volatile("MOV    %0, r0" : "=r"(handleMode));

    //SV_PENDSV
    __ASM volatile("CMP r0, #2");
    __ASM volatile("ITTTT eq");
    __ASM volatile("MOVeq r1, #0xED04");
    __ASM volatile("MOVTeq r1, #0xE000");
    __ASM volatile("MOVeq r2, #0x10000000");
    __ASM volatile("STReq r2, [r1]");
    // SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

    //Start first task
    __ASM volatile("CMP r0, #3");
    __ASM volatile("IT NE");
    __ASM volatile("BXne lr");
    __ASM volatile("LDR r1, =currentTask");
    __ASM volatile("LDR r2, [r1]");
    __ASM volatile("LDR r0, [r2]");

    __ASM volatile("LDMIA r0!, {r4-r11, r14}");   //load registers from memory

    __ASM volatile("TST r14, #0x10");
    __ASM volatile("IT eq");
    __ASM volatile("VLDMIAeq r0!, {s16-s31}");
    
    __ASM volatile("MSR PSP, r0");           //set PSP
    __ASM volatile("ISB");
    
    __ASM volatile("MOV %0, #1" : "=r"(currentTask->State)); //Set function state to running
    __ASM volatile("LDR r1, =nextTask");
    __ASM volatile("MOV r2, #0");
    __ASM volatile("STR r2, [r1]");
    __ASM volatile("MOV lr, #0xfffffffd");
    __ASM volatile("bx lr");
    // enable_interrupts(); //Enable all interrupts
}


/**
 * Systick Handler for an Exception every x ms. Minimum is 11 Hz
 *
 * @param
 * @return
 */
__attribute__((used)) void SysTick_Handler(void) //In C Language
{
    disable_interrupts();
    HAL_IncTick();
    if(currentTask != NULL)
    {
        if(currentTask->Stack > (currentTask->stackBase + currentTask->stackSize) || currentTask->Stack < currentTask->stackBase)
        {
            #ifndef UNIT_TEST
            asm("bkpt");  //Zeige debugger
            #endif
            currentTask->executable = 0;
        }
        findNextFunction();
        if(currentTask != nextTask)
        {
            pendPendSV(); //If nextTask is not this task, set the PendSV to pending
        }
    }
    enable_interrupts(); //enable all interrupts
}

__attribute__((__used__)) void TIM6_DAC_IRQHandler(void) {
    TIM6->SR &= ~TIM_SR_UIF; //Reset interrupt
    usCurrentTimeSinceStart += 1;
}

/**
 * PendSV Exception Handler.
 * MUST NOT call any functions, only always_inline functions allowed
 *
 * @param
 * @return
 */
__attribute__( (__used__ ) ) void PendSV_Handler()
{
    disable_interrupts();

    switchTask();

    #ifdef useMPU
        inline_mpu_disable();
        MPU_StackCfg.BaseAddress = (stack_T)currentTask->stackBase;
        MPU_StackCfg.Size = currentTask->stackSize_MPU;
        inline_mpu_configRegion(&MPU_StackCfg);
        inline_mpu_enable(MPU_PRIVILEGED_DEFAULT);
    #endif

    enable_interrupts(); //Enable all interrupts
    __ASM volatile("bx r14");  //perform Exception return
}