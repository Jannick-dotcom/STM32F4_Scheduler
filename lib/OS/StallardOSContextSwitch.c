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
volatile uint8_t mpu_subregion_disable;
volatile uint32_t mpu_baseAddress;
volatile uint8_t mpu_size;
volatile uint32_t rasr_content;
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
            if(temp->semVal != NULL && (*(temp->semVal) & 0x0000FFFF) == 0 && ((*(temp->semVal) & 0xFFFF0000) >> 16) != temp->id) //If this task is still waiting for the semaphore
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


__attribute__((always_inline)) inline static void inline_set_mpu(){
    #ifdef useMPU
        /* KEEP THESE ASSIGNMENTS!
        * the "compiler" thinks the subregion struct attr is not used
        * and optimizes it away otherwise.
        * Do not directly assign the struct attrs for this reason.
        */
        mpu_subregion_disable = currentTask->mpu_subregions;
        mpu_size = currentTask->mpu_regionSize;
        mpu_baseAddress = currentTask->mpu_baseAddress;
        
        if(mpu_size > 0){
            // taken from HAL_MPU_ConfigRegion
            rasr_content = ((uint32_t)MPU_INSTRUCTION_ACCESS_DISABLE       << MPU_RASR_XN_Pos)   |
                        ((uint32_t)MPU_REGION_FULL_ACCESS               << MPU_RASR_AP_Pos)   |
                        ((uint32_t)MPU_TEX_LEVEL0                       << MPU_RASR_TEX_Pos)  |
                        ((uint32_t)MPU_ACCESS_SHAREABLE                 << MPU_RASR_S_Pos)    |
                        ((uint32_t)MPU_ACCESS_CACHEABLE                 << MPU_RASR_C_Pos)    |
                        ((uint32_t)MPU_ACCESS_NOT_BUFFERABLE            << MPU_RASR_B_Pos)    |
                        ((uint32_t)mpu_subregion_disable                << MPU_RASR_SRD_Pos)  |
                        ((uint32_t)mpu_size                             << MPU_RASR_SIZE_Pos) |
                        ((uint32_t)MPU_REGION_ENABLE                    << MPU_RASR_ENABLE_Pos);
        }
        else{
            rasr_content = ((uint32_t)MPU_INSTRUCTION_ACCESS_DISABLE       << MPU_RASR_XN_Pos)   |
                        ((uint32_t)MPU_REGION_FULL_ACCESS               << MPU_RASR_AP_Pos)   |
                        ((uint32_t)MPU_TEX_LEVEL0                       << MPU_RASR_TEX_Pos)  |
                        ((uint32_t)MPU_ACCESS_SHAREABLE                 << MPU_RASR_S_Pos)    |
                        ((uint32_t)MPU_ACCESS_CACHEABLE                 << MPU_RASR_C_Pos)    |
                        ((uint32_t)MPU_ACCESS_NOT_BUFFERABLE            << MPU_RASR_B_Pos)    |
                        ((uint32_t)mpu_subregion_disable                << MPU_RASR_SRD_Pos)  |
                        ((uint32_t)mpu_size                             << MPU_RASR_SIZE_Pos) |
                        ((uint32_t)MPU_REGION_DISABLE                    << MPU_RASR_ENABLE_Pos);
        }

        // disable the MPU before write
        __DMB();
        SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;  // disable fault exceptions
        MPU->CTRL = 0U;  // disable and clear CTRL register

        // configure the MPU, most values are static
        // only address, size and disableRegion are dynamic values
        MPU->RNR = MPU_REGION_NUMBER7;
        MPU->RBAR = mpu_baseAddress;
        MPU->RASR = rasr_content;

        // re-enable MPU after configuration is done
        MPU->CTRL = MPU_PRIVILEGED_DEFAULT | MPU_CTRL_ENABLE_Msk;  // enable mpu
        SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;  // re-enable fault exceptions

        __DSB();
        __ISB();
        
    #endif
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

    // HAL_MPU_Disable(); // disable for first task? TODO: apply config for first task in init

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
        volatile struct function_struct *temp = currentTask;
        do
        {
            if(temp->Stack > (temp->stackBase + temp->stackSize) || temp->Stack < temp->stackBase) //Stack overflow and underflow check
            {
                #ifndef UNIT_TEST
                asm("bkpt");  //Zeige debugger STACK OVERFLOW!!!!
                #endif
                temp->executable = 0;
            }

            if(temp->refreshRate > 0 && (temp->lastYield - temp->lastStart) > (1000 / temp->refreshRate)) //Task timeout check
            {
                #ifndef UNIT_TEST
                asm("bkpt");  //Zeige debugger Task too Slow!!!!
                #endif
                temp->executable = 0;
            }
            temp = temp->next;
        }
        while (temp != currentTask); 
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
        inline_set_mpu();
    #endif

    enable_interrupts(); //Enable all interrupts
}