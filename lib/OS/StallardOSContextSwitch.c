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
    nextTask = taskMainStruct;
    volatile struct function_struct* temp = currentTask->next;
    uint8_t prioMin = -1;                         //Use only tasks with prio < 255
    if(temp == NULL)
    {
        #ifndef UNIT_TEST
        asm("bkpt");  //Zeige debugger
        #endif
        return;
    }
    do
    {
        if(temp->used == 0) //If the TCB is unused, continue with the next one
        {
            #ifndef UNIT_TEST
            asm("bkpt");  //Zeige debugger
            #endif
            temp = temp->next;
            continue;
        }
        
        if (temp->executable && temp->continueInMS <= HAL_GetTick() && temp->priority < prioMin) //Get task with lowest prio number -> highest priority
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
    while (temp != currentTask->next);   
}

/**
 * Switching of a Task happens here.
 *
 * @param
 * @return
 */
__attribute__((always_inline)) inline void switchTask(void)
{
    //Pausing Task
    __ASM volatile("MRS r0, PSP\n"         //Get Process Stack Pointer
                    "ISB\n"

                    #ifdef useFPU
                    "TST r14, #0x10\n"  //store vfp registers, if task was using FPU
                    "IT eq\n"
                    "VSTMDBeq r0!, {s16-s31}\n"
                    #endif

                    #ifndef unprotectedBuild
                    "MRS r12, CONTROL\n"                    
                    "STMDB r0!, {r4-r12, r14}\n" //Save additional not yet saved registers
                    #else
                    "STMDB r0!, {r4-r11, r14}\n" //Save additional not yet saved registers
                    #endif

                    "LDR r3, =currentTask\n" //Current Task Pointer
                    "LDR r2, [r3]\n" //Load Stack pointer from first position of currentTask
                    "STR r0, [r2]\n" //Save stack pointer
                    "LDR r1, =nextTask\n"
                    "LDR r2, [r1]\n"
                    "STR r2, [r3]\n"
                    "DSB\n"
                    "ISB\n"

                    // Resuming process
                    "LDR r0, [r2]\n"

                    #ifndef unprotectedBuild
                    "LDMIA r0!, {r4-r12, r14}\n"   //load registers from memory
                    "MSR CONTROL, r12\n"
                    #else
                    "LDMIA r0!, {r4-r11, r14}\n"   //load registers from memory
                    #endif

                    #ifdef useFPU
                    "TST r14, #0x10\n"
                    "IT eq\n"
                    "VLDMIAeq r0!, {s16-s31}\n"
                    #endif
                    "MSR PSP, r0\n"           //set PSP
                    "ISB\n"
                    
                    "LDR r1, =nextTask\n"
                    "MOV r2, #0\n"
                    "STR r2, [r1]\n");
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
 * @brief enables privileges for the current task
 *        by setting the nPriv bit
 * 
 */
__attribute__((always_inline)) inline void enable_privilege(){
    /* registers do not need to be preserved, 
     * compiler preserves used registers
     */
    __ASM volatile("MRS r1, control\n"
                    "BIC r1, #1\n"
                    "MSR control, r1\n");
}

/**
 * @brief disables privileges of the current task
 *        by clearing the nPriv bit
 * 
 */
__attribute__((always_inline)) inline void disable_privilege(){
    /* registers do not need to be preserved, 
     * compiler preserves used registers
     */
    __ASM volatile("MRS r1, control\n"
    "ORR r1, #1\n"
    "MSR control, r1\n");
}


/**
 * @brief starts the currentTask as maintask
 *        only called from boot procedure
 *        MUST be inlinend, to allow bx command to work
 */
__attribute__((always_inline)) inline void start_mainTask(){
    __ASM volatile("LDR r1, =currentTask\n"
    "LDR r2, [r1]\n"
    "LDR r0, [r2]\n"

    #ifndef unprotectedBuild
    "LDMIA r0!, {r4-r12, r14}\n"   //load registers from memory
    "MSR CONTROL, r12\n"
    #else
    "LDMIA r0!, {r4-r11, r14}\n"   //load registers from memory
    #endif
    
    "MSR PSP, r0\n"           //set PSP
    "ISB\n"
    
    // "MOV %0, #1" //Set function state to running
    "LDR r1, =nextTask\n"
    "MOV r2, #0\n"
    "STR r2, [r1]\n"
    "MOV lr, #0xfffffffd\n"
    "bx lr\n" /*: "=r"(currentTask->State)*/);
}


__attribute__( (__used__ , optimize("-O2")) ) void SVC_Handler_Main( unsigned int *svc_args ) //Optimize Attribute makes sure no frame pointer is used
{
    unsigned int svc_number;

    /*
    * Stack contains:
    * r0, r1, r2, r3, r12, r14, the return address and xPSR
    * First argument (r0) is svc_args[0]
    */
    svc_number = ( ( char * )svc_args[ 6 ] )[ -2 ] ;
    switch( svc_number )
    {
    case SV_BOOTLOADER:  /* EnablePrivilegedMode */
        jumpToBootloader();
        break;
    case SV_PENDSV:
        pendPendSV();
        break;
    case SV_STARTMAIN:
        start_mainTask();
        break;
    case SV_SYSRESET:
        NVIC_SystemReset();
        break;
    #ifndef unprotectedBuild
    case SV_ACTIVATE_PRIV:
        enable_privilege();
        break;
    case SV_DEACTIVATE_PRIV:
        disable_privilege();
        break;
    #endif
    default:    /* unknown SVC */
        break;
    }
}

/**
 * @brief SVC_Handler routine
 * @see https://developer.arm.com/documentation/ka004005/latest
 */
__attribute__( (__used__ , optimize("-O2")) ) void SVC_Handler(void) //Optimize Attribute makes sure no frame pointer is used
{
  __asm(
    ".global SVC_Handler_Main\n"
    "TST lr, #4\n"
    "ITE EQ\n"
    "MRSEQ r0, MSP\n"
    "MRSNE r0, PSP\n"
    "B SVC_Handler_Main\n"
  ) ;
}


/**
 * Systick Handler for an Exception every x ms. Minimum is 11 Hz
 *
 * @param
 * @return
 */
__attribute__( (__used__) ) void SysTick_Handler(void) //In C Language
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
        if(currentTask != nextTask && !(currentTask == taskMainStruct && nextTask == NULL))
        {
            pendPendSV(); //If nextTask is not this task, set the PendSV to pending
        }
    }
    enable_interrupts(); //enable all interrupts
}

/**
 * PendSV Exception Handler.
 * MUST NOT call any functions, only always_inline functions allowed
 *
 * @param
 * @return
 */
__attribute__( (__used__ , optimize("-O2")) ) void PendSV_Handler() //Optimize Attribute makes sure no frame pointer is used
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
}