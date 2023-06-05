#include "StallardOSconfig.h"
#include "StallardOSHelpers.h"
#include <stdint.h>

extern volatile struct function_struct* volatile currentTask;
extern volatile struct function_struct* volatile taskMainStruct;
extern volatile struct function_struct* volatile nextTask;
extern struct function_struct taskArray[countTasks];

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

void findNextFunction()
{
    #ifdef BusyLoop
    nextTask = taskMainStruct;
    #endif
    volatile struct function_struct* temp;
    uint8_t prioMin = (uint8_t)-1U;                         //Use only tasks with prio < 255
    uint64_t earliestDeadline = -1ULL;
    nextTask = NULL;
    for (uint16_t i = 0; i < countTasks; i++)
    {
        temp = &(taskArray[i]);
        if(temp == NULL)    //Somethin is wrong with the Task list
        {
            DEBUGGER_BREAK();  //Zeige debugger
            return;
        }
        if(temp->used == 0 || temp->executable == 0) //If the TCB is unused or not executable
        {
            continue;
        }
        if(temp->semVal != NULL && (*(temp->semVal) & 0x0000FFFF) == 0 && ((*(temp->semVal) & 0xFFFF0000) >> 16) != temp->id) //If this task is waiting for the semaphore
        {
            continue;
        }
        if(temp->continue_ts > uwTick) //If the task is not ready to continue
        {
            continue;
        }
        if(temp->priority >= prioMin) //If lower priority than the current minimum
        {
            continue;
        }
        if(temp->refreshRate > 0 && (temp->lastStart + (1000 / temp->refreshRate)) > earliestDeadline) //if task doesn't have the earliest deadline
        {
            continue;
        }
        if(temp->refreshRate == 0 && earliestDeadline < (uint64_t)-1) //If the task has no deadline and the current minimum has a deadline
        {
            continue;
        }

        nextTask = temp;
        prioMin = temp->priority;
        if(temp->refreshRate > 0) //set earliest deadline to current tasks deadline
        {
            earliestDeadline = temp->lastStart + (1000 / temp->refreshRate);
        }
    }
}


/**
 * @brief restarts the given task
 *        sets executble bit to 1
 *        the lastly held semaphore is freed (not all!!!!!)
 *        sets executable to 1
 * 
 *        INFO: does NOT disable interrupts, only to be called in disabled interrupts context
 */
__attribute__((always_inline)) inline void restartTask(struct function_struct *task)
{
  if(task == NULL || task->used == 0) 
  {
    return;
  }
  task->Stack = (stack_T*)((stack_T)task->stackBase + (task->stackSize - sizeof(stack_T))); //End of Stack
  //Prepare initial stack trace
  task->Stack--;
  *task->Stack = (uint32_t)0x01000000;
  task->Stack--;
  *task->Stack = (uint32_t)currentTask->function & (~1);
  task->Stack--;
  *task->Stack = (uint32_t)taskOnEnd;

  task->Stack--;
  *task->Stack = (uint32_t)12;
  task->Stack--;
  *task->Stack = (uint32_t)3;
  task->Stack--;
  *task->Stack = (uint32_t)2;
  task->Stack--;
  *task->Stack = (uint32_t)1;
  task->Stack--;
  *task->Stack = (uint32_t)0;
  
  task->Stack--;
  *task->Stack = 0xFFFFFFFD;

  #ifndef unprotectedBuild
  task->Stack--;
  *task->Stack = (CONTROL_nPRIV_Msk << CONTROL_nPRIV_Pos); //Control register (unprivileged)
  #endif

  for(uint8_t i = 11; i > 3; i--)
  {
    task->Stack--;
    *task->Stack = i;
  }
  //////////////////////////////
  if(task->semVal != NULL){
    /* normal write access to semaphore is ok in this context, 
    * as no other task may execute during hardFault 
    */
    *(task->semVal) = 1; //Semaphore freigeben
    __CLREX();  // reset exclusive monitor

  }
  task->semVal = 0; //Semaphore von task lösen
  task->continue_ts = HAL_GetTick();
  task->executable = 1;
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

                    #ifdef __FPU_PRESENT
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
                    "STR r2, [r3]\n" //Save next Task to currentTask
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

                    #ifdef __FPU_PRESENT
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
    
    "LDR r1, =nextTask\n"
    "MOV r2, #0\n"
    "STR r2, [r1]\n"
    
    "MOV lr, #0xfffffffd\n"
    "bx lr\n");
}

__attribute__((always_inline)) inline void clc_cpu_usage()
{
    asm("stmdb sp!, {r4-r11}");
    uint64_t us_ts = (uwTick * 1000) + SysTick->LOAD - (SysTick->VAL / (SystemCoreClock / 1000000));

    currentTask->watchdog_exec_time_us += (us_ts - currentTask->watchdog_swapin_ts);
    currentTask->perfmon_exec_time_us += (us_ts - currentTask->perfmon_swapin_ts);

    // watchdog can be reset independently of perfmon
    // therefore 2 vars are required
    nextTask->watchdog_swapin_ts = us_ts;
    nextTask->perfmon_swapin_ts = us_ts;
    asm("ldmia sp!, {r4-r11}");
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
        // jumpToBootloader();
        break;
    case SV_PENDSV:
        if(nextTask != NULL) 
        {
            #ifndef BusyLoop
            HAL_PWR_DisableSleepOnExit();
            #endif
            pendPendSV();
        }
        else 
        {
            #ifndef BusyLoop
            HAL_PWR_EnableSleepOnExit();
            #else
            nextTask = taskMainStruct;
            #endif
        }
        break;
    case SV_STARTMAIN:
        findNextFunction();
        if(nextTask == NULL)
        {
            #ifndef BusyLoop
            HAL_PWR_EnableSleepOnExit();
            #else
            currentTask = taskMainStruct;
            #endif
            // start_mainTask();
        }
        else 
        {
            currentTask = nextTask;
            #ifndef BusyLoop
            HAL_PWR_DisableSleepOnExit();
            #endif
            start_mainTask();
        }
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
    case SV_USAGE_CALC:
        clc_cpu_usage();
        break;
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
        
        if((stack_T)currentTask->Stack > (((stack_T)currentTask->stackBase + currentTask->stackSize)) || currentTask->Stack < currentTask->stackBase) //Stack overflow and underflow check
        {
            DEBUGGER_BREAK();  //Zeige debugger STACK OVERFLOW!!!!
            enable_interrupts();
            CALL_SYSRESET();    //System might be damaged too much to continue, so reset
        }

        if(currentTask->refreshRate > 0 && currentTask->used && currentTask->lastYield > currentTask->lastStart && (currentTask->lastYield - currentTask->lastStart) > (1000 / currentTask->refreshRate)) //Task timeout check
        {
            DEBUGGER_BREAK();  //Zeige debugger Task too Slow!!!!
            // task is not prevented from further execution
            // as it's not corrupting/influencing any higher prio tasks
        }

        // test if the currently executing task is already exceeding the watchdog
        // as watchdog calc time is only updated on task swapOut/swapIn, 
        // a high prio task could slip through the detection if it never releases control
        // 
        // as the watchdog resolution is on ms base, this check is performed in ms aswell
        // therefore only ms*1000 is used, instead of us readout
        if(currentTask->watchdog_limit > 0 && currentTask->watchdog_exec_time_us/1000 + (HAL_GetTick() - currentTask->watchdog_swapin_ts/1000) > currentTask->watchdog_limit){
            DEBUGGER_BREAK();  //Zeige debugger Watchdog timeout!!!!
            restartTask(currentTask);
        }

        findNextFunction();
        if(currentTask != nextTask && nextTask != NULL)
        {
            #ifndef BusyLoop
            HAL_PWR_DisableSleepOnExit();
            #endif
            pendPendSV(); //If nextTask is not this task, set the PendSV to pending
        }
        else if(nextTask == NULL)
        {
            #ifndef BusyLoop
            HAL_PWR_EnableSleepOnExit();
            #else
            nextTask = taskMainStruct;
            #endif
        }
        else
        {
            HAL_PWR_DisableSleepOnExit();
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
    switchTask();

    #ifdef useMPU
        inline_set_mpu();
    #endif

    enable_interrupts(); //Enable all interrupts
}