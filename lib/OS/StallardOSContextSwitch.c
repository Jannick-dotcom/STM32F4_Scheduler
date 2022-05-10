#include "StallardOSconfig.h"
#include "StallardOSHelpers.h"
#include <stdint.h>

extern volatile struct function_struct* volatile currentTask;
extern volatile struct function_struct* volatile taskMainStruct;
extern volatile struct function_struct* volatile nextTask;

const stack_T watchdog_swapin_offset = offsetof(struct function_struct, watchdog_swapin_ts);
const stack_T perfmon_swapin_offset = offsetof(struct function_struct, perfmon_swapin_ts);
const stack_T watchdog_exec_offset = offsetof(struct function_struct, watchdog_exec_time_us);
const stack_T perfmon_exec_offset = offsetof(struct function_struct, perfmon_exec_time_us);

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
        DEBUGGER_BREAK();  //Zeige debugger
        return;
    }
    do
    {
        if(temp->used == 0) //If the TCB is unused, continue with the next one
        {
            DEBUGGER_BREAK();  //Zeige debugger
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

                    #ifdef STM32F4xxxx
                    #ifdef useFPU
                    "TST r14, #0x10\n"  //store vfp registers, if task was using FPU
                    "IT eq\n"
                    "VSTMDBeq r0!, {s16-s31}\n"
                    #endif
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

                    #ifdef STM32F4xxxx
                    #ifdef useFPU
                    "TST r14, #0x10\n"
                    "IT eq\n"
                    "VLDMIAeq r0!, {s16-s31}\n"
                    #endif
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

    // HAL_MPU_Disable(); // first task is always in .bss, therefore has stack access by default

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
            if((stack_T)temp->Stack > (((stack_T)temp->stackBase + temp->stackSize)) || temp->Stack < temp->stackBase) //Stack overflow and underflow check
            {
                DEBUGGER_BREAK();  //Zeige debugger STACK OVERFLOW!!!!
                temp->executable = 0;
            }

            if(temp->refreshRate > 0 && (temp->lastYield - temp->lastStart) > (1000 / temp->refreshRate)) //Task timeout check
            {
                DEBUGGER_BREAK();  //Zeige debugger Task too Slow!!!!
                // task is not prevented from further execution
                // as it's not corrupting/influencing any higher prio tasks
            }
            temp = temp->next;
        }
        while (temp != currentTask); 

        // test if the currently executing task is already exceeding the watchdog
        // as watchdog calc time is only updated on task swapOut/swapIn, 
        // a high prio task could slip through the detection if it never releases control
        // 
        // as the watchdog resolution is on ms base, this check is performed in ms aswell
        // therefore only ms*1000 is used, instead of us readout
        if(currentTask->watchdog_limit > 0 && currentTask->watchdog_exec_time_us/1000 + (HAL_GetTick() - currentTask->watchdog_swapin_ts/1000) > currentTask->watchdog_limit){
            DEBUGGER_BREAK();  //Zeige debugger Watchdog timeout!!!!
            temp->executable = 0;
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

    // DO NOT USE C
    // the compiler doesn't properly restore all registers

    // uint32_t *SysTick_VAL = (uint32_t*)(SysTick_BASE + 0x08);
    // uint64_t us_ts = (uwTick* 1000) + (*SysTick_VAL / (SystemCoreClock / 1000000));

    // currentTask->watchdog_exec_time_us += (us_ts - currentTask->watchdog_swapin_ts);
    // currentTask->perfmon_exec_time_us += (us_ts - currentTask->perfmon_swapin_ts);

    // // watchdog can be reset independently of perfmon
    // // therefore 2 vars are required
    // nextTask->watchdog_swapin_ts = us_ts;
    // nextTask->perfmon_swapin_ts = us_ts;


    __ASM volatile(
        "PUSH {r4-r6}\n"

        "LDR r0, =#0xe000e018\n" // load &SysTick_VAL into r0
        "LDR r0, [r0]\n" // load SysTick_VAL

        // load the divisor for the systick counter (SystemCoreClock/1000000)
        "LDR r1, =SystemCoreClock\n" // load address of SystemCoreCLok
        "LDR r1, [r1]\n" // load value of SystemCoreClock
        "LDR r2, =#1000000\n"
        "UDIV r1, r2\n" // SystemCoreClock/1000000
        "UDIV r2, r0, r1\n" // div Systick value with sysclock divisor
        // r2 holds current ns of Systick register

        // next get uwTick [ms] counter into r0
        "LDR r0, =uwTick\n" // load address of HAL systick value
        "LDR r0, [r0]\n" // load value of systick in ms

        // and multiply with 1000 to convert to ns
        "LDR r1, =#1000\n"
        "UMULL r0, r1, r0, r1\n" // multiply uwTick*1000, result is r0=lowerH and r1=upperH
        "ADDS r0, r2\n" // lowerH of 64bit + 32bit number
        "ADC r1, #0\n" // take over carry bit
        //===================================
        // us_ts is now in r0 and r1

        // update watchdog variables next
        // first load required offsets
        // currentTask into r2
        // watchdog_exec_time_us into r3
        // watchdog_swapin_ts into r4

        "LDR r2, =currentTask\n" // **currentTask
        "LDR r2, [r2]\n" // load pointer to currentTask

        "LDR r3, =watchdog_exec_offset\n"
        "LDR r3, [r3]\n" // offset of watchdog_exec_time_us
        "ADD r3, r2\n" // load addr of exec_time_us

        "LDR r4, =watchdog_swapin_offset\n"
        "LDR r4, [r4]\n" // offset value of watchdog_swapin_ts
        "ADD r4, r2\n" // load addr of swapin_ts

        // // load the last swapin_ts and substract it from us_ts
        // // then save it back to exec_offset
        "LDM r4, {r5, r6}\n"

        
        // substraction of us_ts-sapin_ts into r5=low, r6=high
        "SUBS r5, r0, r5\n" // 64bit sub of us_ts-watchdog_swapin
        "SBC r6, r1, r6\n"
        "STM r3, {r5, r6}\n" // write back to watchdog_exec_time_us

        // load us_ts into watchdog_swapin_ts
        // addr of swapin_ts is still stored in r4
        "STM r4, {r0, r1}\n"

        //==========================================
        // repeat the same calculation for perfmon_* instead of watchdog_*
        "LDR r3, =perfmon_exec_offset\n"
        "LDR r3, [r3]\n"
        "ADD r3, r2\n"
        "LDR r4, =perfmon_swapin_offset\n"
        "LDR r4, [r4]\n"
        "ADD r4, r2\n"
        "LDM r4, {r5, r6}\n"
        "SUBS r5, r0, r5\n"
        "SBC r6, r1, r6\n"
        "STM r3, {r5, r6}\n"
        "STM r4, {r0, r1}\n"

        "POP {r4-r6}"
    );
    


    switchTask();

    #ifdef useMPU
        inline_set_mpu();
    #endif

    enable_interrupts(); //Enable all interrupts
}