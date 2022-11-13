#include "StallardOS.hpp"
#include "StallardOSMPU.hpp"
#include "sharedParams.hpp"

#include "StallardOSSerial.hpp"
#include "FLASH_SECTOR_DEFINES.h"

#include "StallardOSTasks.hpp"

extern "C" stack_T _sdata;  // sizes of .data and .bss
extern "C" stack_T _edata;  // used for MPU config
extern "C" stack_T _sbss;
extern "C" stack_T _ebss;
extern "C" stack_T _sshared;
extern "C" stack_T _eshared;

//Kontext Switch
volatile struct function_struct* volatile currentTask = nullptr;
volatile struct function_struct* volatile nextTask = nullptr;
volatile struct function_struct* volatile taskMainStruct = nullptr;
struct function_struct taskArray[countTasks];

extern "C" void StallardOS_goBootloader();
extern "C" void enable_interrupts();
extern "C" void disable_interrupts();
extern "C" void findNextFunction();




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
  if(!currentTask->staticAlloc)
  {
    free((uint32_t*)currentTask->stackBase);
  }
  currentTask->executable = 0;
  enable_interrupts();
  findNextFunction();
  CALL_STARTMAIN();
  while(1);
}

/**
 * Signal handler
 * A signal from another task is handled here.
 *
 * @param
 * @return
 */
void StallardOS::signal_handler(signals signal_code, function_struct *receivingTask)
{
  if(receivingTask != nullptr && receivingTask != taskMainStruct)
  {
    if(receivingTask->signalHandlers[signal_code] != nullptr) //if signal handler exists for this signal
    {
      void (*signalHandler)() = (void (*)())(receivingTask->signalHandlers[signal_code]); //call this signal handler
      signalHandler();
    }
    else //Otherwise call the default handler for this signal
    {
      taskOnEnd();
    }
  }
}

uint8_t StallardOS::registerSignalHandler(signals signal_code, void (*signal_handler)())
{
  if(currentTask != nullptr && currentTask->signalHandlers[signal_code] == nullptr) //if signal handler was not assigned yet
  {
    currentTask->signalHandlers[signal_code] = (void *)signal_handler; //save signal handler
    return 1;
  }
  else //otherwise not successful
  {
    return 0;
  }
}

void StallardOS::sendSignal(signals signal_code, uint16_t id)
{
  function_struct *tmp = searchFunction(id);
  if(tmp != nullptr)
  {
    for(auto i = 0U; i < sizeof(tmp->rcvSignal) / sizeof(tmp->rcvSignal[0]); i++)
    {
      if(tmp->rcvSignal[i] == SIG_NONE)
      {
        tmp->rcvSignal[i] = signal_code;
        break;
      }
    }
  }
}


/**
 * Create StallardOS RTOS.
 *
 * @param
 * @return
 */
StallardOS::StallardOS()
{
  NVIC_EnableIRQ(BusFault_IRQn);
  NVIC_EnableIRQ(UsageFault_IRQn);
  NVIC_EnableIRQ(NonMaskableInt_IRQn);
  NVIC_EnableIRQ(MemoryManagement_IRQn);
  
  // Basiswerte Initialisieren
  first_function_struct = nullptr;
  currentTask = nullptr;
  TCBsCreated = 0;
  // //Für Context Switch
  createTCBs();
  SysTick_Config(SystemCoreClock / 1000);
  initShared();

  #if defined(useMPU)
    initMPU();
  #endif // useMPU

  #ifdef BusyLoop
  taskMainStruct = addFunctionStatic(taskMain, -1, taskmainStack, sizeof(taskmainStack));
  if(taskMainStruct == nullptr) 
  {
    DEBUGGER_BREAK();
    while(1);
  };
  #endif
  #ifndef notHaveCan
  addFunctionStatic(taskPerfmon, -2, taskPerfmonStack, sizeof(taskPerfmonStack), 1);
  #endif
  #ifdef useSFOC
     addFunctionStatic(taskSFOC, -3, taskSFOCStack, sizeof(taskSFOCStack), 5);
  #endif
}

/**
 * Create Task control blocks.
 *
 * @param
 * @return
 */
void StallardOS::createTCBs()
{
  if (TCBsCreated >= sizeof(taskArray) / sizeof(function_struct)) //Wenn schon genug TCBs erstellt wurden, nicht nochmal erstellen
  {
    return;
  }

  for (uint16_t i = 0; i < sizeof(taskArray) / sizeof(function_struct); i++)
  {
    struct function_struct *temp;
    temp = &taskArray[i]; //new struct function_struct;
    if (temp == nullptr)  //Wenn kein HEAP Platz mehr frei ist...
    {
      return; //Aus der Funktion rausspringen
    }
    //alle Werte übertragen
    temp->function = nullptr;
    temp->priority = -1;

    temp->id = i;

    temp->executable = false;
    temp->used = false;
    temp->continue_ts = 0;

    TCBsCreated++;
  }
}


/**
 * @brief initialize shared memory for cooperation with Flashloader
 *        MUST NOT be called from unprivileged task context, if the MPU is enabled
 * 
 */
void StallardOS::initShared(void){

  /* constructor will init the struct */
  SharedParams params;

  /* set default parameters at OS boot */

  /* the default parames will make the FlashLoader
   * boot back to the OS, in case a reset handler is hit
   * or in case someone hits the reset button of the controller
   */
  #ifdef useMPU
    //CALL_PRIVILEGED();
  #endif

  params.set_boot_type(SharedParams::boot_type::T_REBOOT);
  params.set_os_version(STOS_VERSION);
  #ifdef SW_VERSION
    params.set_sw_version(SW_VERSION);
  #endif

  #ifdef useMPU
    //CALL_UNPRIVILEGED();
  #endif
}

#ifdef useMPU
void StallardOS::initMPU(void){

  /* manually disable MPU here
   * to not reenable it at every single configuration step
   */
  HAL_MPU_Disable();

  /* for correctly setting up the region attributes
   * for each type of memory, consider
   * 4.2.4 Table 42, of the programming manual PM0214
   */
  MPU_Region_InitTypeDef MPU_Init;

  /* setup general settings, which are equal for all regions */
  MPU_Init.Enable = MPU_REGION_ENABLE;
  MPU_Init.TypeExtField = MPU_TEX_LEVEL0;

  /* configure FLASH/CODE region 
   * not shareable
   * cachable
   * not bufferable
   * executable
   * RO for all permission levels
   */
  MPU_Init.AccessPermission = MPU_REGION_PRIV_RO_URO;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  MPU_Init.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER0;
  // allow access to entire flash address space (same for all STM32s)
  // "Code" addres region ranges in [0x0..0x1FFF FFFF]
  // only make 
  StallardOSMPU::write_config(&MPU_Init, FLASH_BASE, FLASH_TOTAL_SIZE);  //  flash size defined in flashOps lib


  /* configure SRAM .data region 
   * shareable
   * cachable
   * not bufferable
   * not executable
   * RW for privileged tasks
   * 
   * linker script is forcing .data to be 4096 aligned
   */
  MPU_Init.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  MPU_Init.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER1;
  StallardOSMPU::write_config(&MPU_Init, (stack_T)&_sdata, ((stack_T)&_edata-(stack_T)&_sdata));


  /* configure .bss 
   * same properties as .data settings
   * 
   * linker script is forcing .bss to be 4096 aligned
   */

  MPU_Init.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  MPU_Init.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER2;
  StallardOSMPU::write_config(&MPU_Init, (stack_T)&_sbss, ((stack_T)&_ebss - (stack_T)&_sbss));

  /* configure .shared 
   * same properties as .data settings
   * priv tasks are R/W
   * unpriv tasks are RO
   * 
   */
  MPU_Init.AccessPermission = MPU_REGION_PRIV_RW_URO;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  MPU_Init.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER3;
  StallardOSMPU::write_config(&MPU_Init, (stack_T)&_sshared, ((stack_T)&_eshared - (stack_T)&_sshared));


  /* configure Peripherals 
   * sharable
   * not cachable
   * bufferable
   */
  MPU_Init.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  MPU_Init.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER4;
  StallardOSMPU::write_config(&MPU_Init, PERIPH_BASE, 0x20000000);  /* 512MB for all STM32s*/


  /* configure EXT Ram */
  /* EXT Ram not avail */

  /* configure EXT device */
  /* EXT device not avail */

  /* configure private peripeheral bus */
  /* no access, only in privileged mode */

  /* configure Vendior-specific memory */
  /* not avail */


  /* configure Task stack 
   * sharable
   * cachable
   * not bufferable
   */
  /* -> is configured at each contextSwitch
   * Region 7 (NUMBER7) is used for stack
   * to overlay all other regions
   */

 

  /* PRIVILEGED_DEFAULT will allow all access to privileged proceses
   * and to fault handlers
   * only non-privileged tasks are affected by the MPU
   * so nothing happens until first task switch
   */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
#endif

/**
 * Add a new Task to execute list.
 * Does not allocate stack space
 *
 * @param function Task to execute.
 * @param prio priority of the task, lower means higher.
 * @param stackPtr pointer to the stack memory allocated by the user, must be aligned to stackSize in MPU mode
 * @param stackSizeBytes amount of Stack Bytes to allocate, stackSize*word_len must be power of 2 in MPU mode.
 * @param refreshRate frequency of execution through the normal scheduler. <= 1000 !
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::initTask(void (*function)(), uint8_t prio, uint32_t *stackPtr, stack_T stackSize, uint16_t refreshRate, uint16_t watchdogLimitMs)
{
  struct function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct

  function_struct_ptr = searchFreeFunction();
  if (function_struct_ptr == nullptr)
  {
    DEBUGGER_BREAK();
    return nullptr; //Aus der Funktion rausspringen
  }

  if (first_function_struct == nullptr) //Wenn noch keine funktion hinzugefügt wurde
  {
    first_function_struct = function_struct_ptr; //Funktion als erste setzen
  }
  
  //alle Werte übertragen
  function_struct_ptr->function = function;
  function_struct_ptr->executable = true;
  function_struct_ptr->priority = prio;
  for (uint16_t i = 0; i < countTasks; i++)
  {
    if(taskArray[i].used == 0)
    {
      function_struct_ptr->id = i;
      break;
    }
  }

  for (uint8_t i = 0; i < sizeof(function_struct::signalHandlers) / sizeof(void *); i++)
  {
    function_struct_ptr->signalHandlers[i] = nullptr;
  }


  /////////////////////////////////////////////
  function_struct_ptr->refreshRate = refreshRate;
  function_struct_ptr->lastYield = 0;
  function_struct_ptr->lastStart = StallardOSTime_getTimeMs();
  function_struct_ptr->watchdog_limit = watchdogLimitMs;
  function_struct_ptr->watchdog_exec_time_us = 0;
  function_struct_ptr->watchdog_swapin_ts = 0;
  function_struct_ptr->perfmon_exec_time_us = 0;
  function_struct_ptr->perfmon_swapin_ts = 0;
  // function_struct_ptr->State = PAUSED;                                       //New Task
  function_struct_ptr->stackBase = stackPtr;
  function_struct_ptr->Stack = (stack_T*)((stack_T)stackPtr + (stackSize - sizeof(stack_T))); //End of Stack
  function_struct_ptr->stackSize = stackSize;
  function_struct_ptr->waitingForSemaphore = 0;
  function_struct_ptr->used = true;
  
  function_struct_ptr->continue_ts = 0;

  //Prepare initial stack trace
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)0x01000000;
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)function & (~1);
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)taskOnEnd;

  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)12;
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)3;
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)2;
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)1;
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)0;
  
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = 0xFFFFFFFD;

  #ifndef unprotectedBuild
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (CONTROL_nPRIV_Msk << CONTROL_nPRIV_Pos); //Control register (unprivileged)
  #endif

  for(uint8_t i = 11; i > 3; i--)
  {
    function_struct_ptr->Stack--;
    *function_struct_ptr->Stack = i;
  }
  //////////////////////////////
  return function_struct_ptr;
}

/**
 * Add a new Task to execute list.
 * Also allocates Stack space for the Task
 *
 * @param function Task to execute.
 * @param prio priority of the task, lower means higher.
 * @param stackSize amount of Stack bytes to allocate, must at least be 130 Bytes (FPU ctx switch), for MPU stackSize*address_len must be power of 2 in MPU mode.
 * @param refreshRate frequency of execution through the normal scheduler. 0 > x >= 1000
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunction(void (*function)(), uint8_t prio, stack_T stackSize, uint16_t refreshRate, uint16_t watchdogLimitMs)
{
  stack_T *stackPtr;
  if (function == nullptr || searchFreeFunction() == nullptr || refreshRate > 1000 || stackSize < 256 || stackSize > 0x1'0000'0000) //Make sure the parameters are correct
  {
    DEBUGGER_BREAK();
    return nullptr;
  }

  #ifdef useMPU
    stackPtr = (stack_T *)memalign(stackSize, stackSize);
  #else
    stackPtr = (stack_T *)malloc(stackSize);
  #endif // useMPU


  if(stackPtr == nullptr) //Wenn kein Stack gefunden
  {
    DEBUGGER_BREAK();
    return nullptr;
  }
  function_struct *ptr = initTask(function, prio, stackPtr, stackSize, refreshRate, watchdogLimitMs);
  ptr->staticAlloc = 0;


  /////////////////////////////////////////////
  #ifdef useMPU
    // check if the given addresess can be used for a valid mpu configuartion
    // then store them, to achieve fast reconfigure on context switch
    int mpu_result;
    MPU_Region_InitTypeDef mpu_cfg;
    mpu_result = StallardOSMPU::fix_config(&mpu_cfg, (stack_T)stackPtr, stackSize);
    
    if(mpu_result < 0){
      DEBUGGER_BREAK();
      return nullptr;
    }

    ptr->mpu_regionSize = mpu_cfg.Size;
    ptr->mpu_baseAddress = mpu_cfg.BaseAddress;
    ptr->mpu_subregions = mpu_cfg.SubRegionDisable;
    // the remaining mpu config is thrown away, as it's not configured at this timepoint
    // acutal config is applied in context switch
  #endif // useMPU


  return ptr;
}

/**
 * Add a new Task to execute list.
 * Does not allocate stack space
 *
 * @param function Task to execute.
 * @param prio priority of the task, lower means higher.
 * @param stackPtr pointer to the stack memory allocated by the user, must be aligned to stackSize in MPU mode
 * @param stackSize amount of Stack bytes to allocate, must at least be 130 Bytes (FPU ctx switch)
 * @param refreshRate frequency of execution through the normal scheduler. <= 1000 !
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunctionStatic(void (*function)(), uint8_t prio, stack_T *stackPtr, stack_T stackSize, uint16_t refreshRate, uint16_t watchdogLimitMs)
{
  if (function == nullptr || searchFreeFunction() == nullptr || refreshRate > 1000 || stackSize < 256 || stackSize > 0x1'0000'0000 || stackPtr == nullptr) //Make sure the parameters are correct
  {
    DEBUGGER_BREAK();
    return nullptr;
  }


  function_struct *ptr = initTask(function, prio, stackPtr, stackSize, refreshRate, watchdogLimitMs);
  /////////////////////////////////////////////
  #ifdef useMPU
    // static tasks are already covered by .bss region
    ptr->mpu_regionSize = 0;
    ptr->mpu_baseAddress = 0;
    ptr->mpu_subregions = 0;
  #endif // useMPU
 
  ptr->staticAlloc = 1;
  return ptr;
}


/**
 * remove all tasks from the scheduler
 */
void StallardOS::remove_all_functions()
{
  for (uint16_t i = 0; i < sizeof(taskArray) / sizeof(function_struct); i++)
  {
    taskArray[i].used = false;
  }
}

/**
 * Here we en/disable a Task from the List.
 *
 * @param id unique id of the task.
 * @param act boolean value, activation of task.
 */
void StallardOS::setFunctionEnabled(uint16_t id, bool act)
{
  struct function_struct *temp = searchFunction(id); //Funktion suchen
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    temp->executable = act;
  }
}

/**
 * Sets new Priority of a Task
 *
 * @param id unique id of the task.
 * @param prio new priority, lower means higher
 */
void StallardOS::setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio)
{
  struct function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio; //Die Priorität ändern
  }
}

/**
 * Search a task in the list
 *
 * @param id unique id of the task.
 * @return pointer to the tcb with the task
 */
struct function_struct *StallardOS::searchFunction(/*ID*/ uint16_t id)
{
  volatile struct function_struct *temp = nullptr; //temporärer pointer erzeugen

  if (temp == nullptr)
  {
    return nullptr;
  }
  for (uint16_t i = 0; i < countTasks; i++)
  {
    if (taskArray[i].id == id)
    {
      return (struct function_struct *)&taskArray[i];
    }
  }
  return nullptr; //Nicht gefunden
}

/**
 * search a tcb that is currently not used
 *
 */
struct function_struct *StallardOS::searchFreeFunction(void)
{
  for(uint16_t i = 0; i < countTasks; i++)
  {
    if(taskArray[i].used == 0)
    {
      return &taskArray[i];
    }
  }
  //Hier haben wir das richtige element schon gefunden -> temp
  return nullptr; //Element übergeben
}

/**
 * delay for an amount of milliseconds
 *
 * @param milliseconds the amount of msec to wait.
 */
void StallardOS::delay(uint32_t milliseconds)
{
  if(currentTask == nullptr) //wenn im bootup
  {
    uint64_t continueTimeStamp = StallardOSTime_getTimeMs() + milliseconds;
    while (StallardOSTime_getTimeMs() < continueTimeStamp);
  }
  else
  {
    currentTask->continue_ts = StallardOSTime_getTimeMs() + (uint64_t)milliseconds; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird
    // nextTask = taskMainStruct;
    findNextFunction();
    CALL_PENDSV();
    for(uint8_t i = 0; i < sizeof(currentTask->rcvSignal)/sizeof(signals); i++)
    {
      if(currentTask->rcvSignal[i] != SIG_NONE)
      {
        if(currentTask->signalHandlers[currentTask->rcvSignal[i]] != NULL) //if signal handler exists for this signal
        {
          void (*signalHandler)() = (void (*)())(currentTask->signalHandlers[currentTask->rcvSignal[i]]); //call this signal handler
          signalHandler();
        }
        else //Otherwise call the default handler for this signal
        {
          taskOnEnd();
        }
        break;
      }
    }
  }
}

/**
 * delay for an amount of microseconds
 *
 * @param microseconds the amount of usec to wait.
 */
void StallardOS::delay_us(uint16_t microseconds)
{
  uint64_t continueTimeStamp;
  if(microseconds >= 1000)
  {
    delay(microseconds / 1000);
    continueTimeStamp = microseconds - ((microseconds / 1000) * 1000);
  }
  else
  {
    continueTimeStamp = StallardOSTime_getTimeUs() + microseconds;
  }
  while (StallardOSTime_getTimeUs() < continueTimeStamp);
}

/**
 * Make sure the Task has a predefined refresh rate that must be held
 * The Task gets executed every (1 / refreshRate) seconds
 *
 * @param id unique id of the task.
 * @param prio new priority, lower means higher
 */

void StallardOS::yield()
{
  if (currentTask != nullptr)
  {
    currentTask->lastYield = StallardOSTime_getTimeMs();
    if(currentTask->refreshRate != 0)
    {
      delay((1000 / currentTask->refreshRate) - (currentTask->lastYield - currentTask->lastStart));
      currentTask->lastStart = StallardOSTime_getTimeMs();
    }
  }
}

/**
 * @brief Reset the Software Watchdog
 *        If Watchdog is not reset within the given window, the task is restarted
 *        
 */
void StallardOS::kickTheDog(){
  if(currentTask != nullptr){
    // do not check if watchdog is enabled for this task or not
    currentTask->watchdog_exec_time_us = 0;
    currentTask->watchdog_swapin_ts = StallardOSTime_getTimeUs(); // fake a "swapin" of the task
  }
}

void StallardOS::restartTask(function_struct *task)
{
  if(task == nullptr || task->used == false) 
  {
    return;
  }
  disable_interrupts();
  currentTask->Stack = (stack_T*)((stack_T)currentTask->stackBase + (currentTask->stackSize - sizeof(stack_T))); //End of Stack
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
  if(currentTask->semVal != NULL){
      if(currentTask->waitingForSemaphore == 0){
          // only execute, if semaphore is actually owned by task (take finished)

          /* normal write access to semaphore is ok in this context, 
          * as no other task may execute during hardFault 
          */
          *(currentTask->semVal) = 1; //Semaphore freigeben
          __CLREX();  // reset exclusive monitor
      }
      else{
          // undefined state, task may or may not own the semaphore
          // assume it didn't own it, as that's more likely?
          // TODO: change this???
          DEBUGGER_BREAK();
      }
  }
  currentTask->waitingForSemaphore = 0;
  currentTask->semVal = 0; //Semaphore von task lösen
  task->continue_ts = HAL_GetTick();
  task->executable = 1;
  enable_interrupts();
}

/**
 * Check the state of a task
 *
 * @param id unique id of the task.
 * @return state of the task, see taskstate enum
 */
// taskState StallardOS::getFunctionState(/*Funktion*/ uint16_t id)
// {
//   struct function_struct *temp = searchFunction(id); //Hier die Funktion suchen
//   if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
//   {
//     return temp->State;
//   }
//   else //Ansonsten
//   {
//     return STOPPED;
//   }
// }

bool StallardOS::getPrivilegeLevel()
{
  if(__get_CONTROL() & CONTROL_nPRIV_Msk) return true;
  else return false;
}

/**
 * Start the StallardOS operating system
 *
 */
void StallardOS::startOS(void)
{
  StallardOS_SetSysClock(runFreq, external);
  if(SystemCoreClock != (runFreq * 1000000))
  {
      DEBUGGER_BREAK();
  }

  if (first_function_struct != nullptr)
  {
    currentTask = first_function_struct; //The current Task is the first one in the List
    #ifdef STM32F4xxxx
    FLASH->ACR |= (1 << FLASH_ACR_PRFTEN_Pos) | (1 << FLASH_ACR_ICEN_Pos) | (1 << FLASH_ACR_DCEN_Pos); //Enable the Flash ART-Accelerator
    #endif
    SCB->CCR |= 1 << SCB_CCR_DIV_0_TRP_Pos | 1 << SCB_CCR_UNALIGN_TRP_Pos;
    #ifdef useFPU
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  //Set the FPU to full access
    #endif
    #endif
    __ASM volatile("DSB");
    __ASM volatile("ISB");

    SysTick_Config(SystemCoreClock / (uint32_t)1000); //Counting every processor clock
    NVIC_SetPriority(SysTick_IRQn, 0xFF);
    NVIC_SetPriority(PendSV_IRQn, 0xFF);

    NVIC_EnableIRQ(PendSV_IRQn);
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(SVCall_IRQn);
    #if defined(useFPU) && (__FPU_PRESENT == 1)
    NVIC_EnableIRQ(FPU_IRQn);
    #endif
    __ASM volatile("MRS R0, MSP\n"
                   "SUB R0, #200\n" //Reserve some space for Handlers (200 Byte)
                   "MSR PSP, R0");
    __ASM volatile("dsb");
    __ASM volatile("isb");
    enable_interrupts();
    CALL_STARTMAIN();
  }
}

/**
 * Search a task in the list
 *
 * @param id unique id of the task.
 * @param exec_freq new execution frequency of the task in Hz. 0 > x >= 1000
 */
void StallardOS::setFunctionFrequency(/*Funktion*/ uint16_t id, float exec_freq)
{
  if (exec_freq <= 0 || exec_freq > 1000) //Make sure the parameters are correct
  {
    return;
  }

  function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                        //Wenn die übergebene Funktion gültig ist
  {
    temp->refreshRate = exec_freq; 
  }
}

void StallardOS::goBootloader()
{
  CALL_BOOTLOADER();
}

void StallardOS::goFlashloader(){
  CALL_SYSRESET();
}
