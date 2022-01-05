#include "StallardOS.hpp"
#include "shared_params.hpp"

extern "C" stack_T _sdata;  // sizes of .data and .bss
extern "C" stack_T _edata;  // used for MPU config
extern "C" stack_T _sbss;
extern "C" stack_T _ebss;

//Kontext Switch
volatile struct function_struct* volatile currentTask = nullptr;
volatile struct function_struct* volatile nextTask = nullptr;
volatile struct function_struct* volatile taskMainStruct = nullptr;
stack_T taskmainStack[200];

extern "C" void StallardOS_goBootloader();
extern "C" void enable_interrupts();
extern "C" void disable_interrupts();
extern "C" void findNextFunction();

/**
 * Waste Time if all tasks are in delay.
 *
 * @param 
 * @return
 */
void taskMain(void)
{
  
  while (1)
  {
  }
  
}

/**
 * If a Task Returns, this function gets executed and calls the remove function of this task.
 *
 * @param
 * @return
 */
void taskOnEnd(void)
{
    currentTask->used = 0;
    if(!currentTask->staticAlloc)
    {
      free((uint32_t*)currentTask->stackBase);
    }
    currentTask->prev->next = currentTask->next;
    currentTask->next->prev = currentTask->prev;
    currentTask->executable = 0;
    currentTask = taskMainStruct;
    nextTask = taskMainStruct;
    __ASM volatile("SVC #3");
    while(1);
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
  
  //Basiswerte Initialisieren
  first_function_struct = nullptr;
  currentTask = nullptr;
  TCBsCreated = 0;
  //Für Context Switch
  createTCBs();
  StallardOS_SetSysClock(runFreq);
  if(SystemCoreClock != (runFreq * 1000000))
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
  }

  initShared();

  #ifdef useMPU
  initMPU();
  #endif // useMPU

  taskMainStruct = addFunctionStatic(taskMain, -1, taskmainStack, sizeof(taskmainStack));
  if(taskMainStruct == nullptr) while(1);

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

  for (uint8_t i = 0; i < sizeof(taskArray) / sizeof(function_struct); i++)
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

    temp->State = STOPPED;                        //New Task
    // temp->Stack = temp->vals + sizeStack - sizeof(uint32_t); //End of Stack


    temp->executable = false;
    temp->used = false;
    temp->continueInMS = 0;

    TCBsCreated++;
  }
}

void StallardOS::initShared(void){
  /* init in any case
   * does not re-init if already init 
   */
  SharedParamsInit();

  /* set default parameters at OS boot */

  /* the default parames will make the FlashLoader
   * boot back to the OS, in case a reset handler is hit
   * or in case someone hits the reset button of the controller
   */

  /* first param is "from_OS" */
  SharedParamsWriteByIndex(0, 1);

  /* 2nd param is "reboot" */
  SharedParamsWriteByIndex(1, 1);

}

void StallardOS::initMPU(void){

  /* for correctly setting up the region attributes
   * for each type of memory, consider
   * 4.2.4 Table 42, of the programming manual PM0214
   */
  MPU_Region_InitTypeDef MPU_Init;

  HAL_MPU_Disable();

  /* setup general settings, which are equal for all regions */
  MPU_Init.Enable = MPU_REGION_ENABLE;
  MPU_Init.TypeExtField = MPU_TEX_LEVEL0;
  MPU_Init.SubRegionDisable = 0x00;

  /* configure FLASH/CODE region 
   * not shareable
   * cachable
   * not bufferable
   * executable
   * RO for all permission levels
   */
  MPU_Init.BaseAddress = FLASH_BASE;
  MPU_Init.Size = MPU_REGION_SIZE_1MB;    // "G" model has 1MB flash
  MPU_Init.AccessPermission = MPU_REGION_PRIV_RO_URO;

  MPU_Init.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER0;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  HAL_MPU_ConfigRegion(&MPU_Init);


  /* configure SRAM .data region 
   * shareable
   * cachable
   * not bufferable
   * not executable
   * RW for privileged tasks
   * 
   * linker script is forcing .data to be 4096 aligned
   */
  MPU_Init.BaseAddress = (stack_T)&_sdata;
  MPU_Init.Size = bytesToMPUSize((&_edata)-(&_sdata));  // size of .data region
  MPU_Init.AccessPermission = MPU_REGION_FULL_ACCESS;

  MPU_Init.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER1;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  HAL_MPU_ConfigRegion(&MPU_Init);

  
  /* configure .bss 
   * same properties as .data settings
   * 
   * linker script is forcing .bss to be 4096 aligned
   */

  MPU_Init.BaseAddress = (stack_T)&_sbss;
  MPU_Init.Size = bytesToMPUSize((&_ebss)-(&_sbss));  // size of .data region
  MPU_Init.AccessPermission = MPU_REGION_FULL_ACCESS;

  MPU_Init.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER2;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  HAL_MPU_ConfigRegion(&MPU_Init);


  /* configure Task stack */
  /* -> is configured at each contextSwitch
   * Region 3 (NUMBER3) is used for stack
   */


  /* configure Peripherals 
   * sharable
   * not cachable
   * bufferable
   */
  MPU_Init.BaseAddress = PERIPH_BASE;
  MPU_Init.Size = MPU_REGION_SIZE_512MB;
  MPU_Init.AccessPermission = MPU_REGION_FULL_ACCESS;

  MPU_Init.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_Init.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_Init.IsBufferable = MPU_ACCESS_BUFFERABLE;

  MPU_Init.Number = MPU_REGION_NUMBER4;
  MPU_Init.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  HAL_MPU_ConfigRegion(&MPU_Init);

  
  /* configure EXT Ram */
  /* EXT Ram not avail */

  /* configure EXT device */
  /* EXT device not avail */
  
  /* configure private peripeheral bus */
  /* no access, only in privileged mode */
  

  /* configure Vendior-specific memory */
  /* not avail */


  /* PRIVILEGED_DEFAULT will allow all access to privileged proceses
   * and to fault handlers
   * only non-privileged tasks are affected by the MPU
   */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

uint8_t StallardOS::bytesToMPUSize(stack_T bytes){
  switch(bytes){
    case 0x20:
      return MPU_REGION_SIZE_32B;
    case 0x40:
      return MPU_REGION_SIZE_64B;
    case 0x80:
      return MPU_REGION_SIZE_128B;
    case 0x100:
      return MPU_REGION_SIZE_256B;
    case 0x200:
      return MPU_REGION_SIZE_512B;
    case 0x400:
      return MPU_REGION_SIZE_1KB;
    case 0x800:
      return MPU_REGION_SIZE_2KB;
    case 0x1000:
      return MPU_REGION_SIZE_4KB;
    case 0x2000:
      return MPU_REGION_SIZE_8KB;
    case 0x4000:
      return MPU_REGION_SIZE_16KB;
    case 0x8000:
      return MPU_REGION_SIZE_32KB;
    case 0x1'0000:
      return MPU_REGION_SIZE_64KB;
    case 0x2'0000:
      return MPU_REGION_SIZE_128KB;
    case 0x4'0000:
      return MPU_REGION_SIZE_256KB;
    case 0x8'0000:
      return MPU_REGION_SIZE_512KB;
    case 0x10'0000:
      return MPU_REGION_SIZE_1MB;
    case 0x20'0000:
      return MPU_REGION_SIZE_2MB;
    case 0x40'0000:
      return MPU_REGION_SIZE_4MB;
    case 0x80'0000:
      return MPU_REGION_SIZE_8MB;
    case 0x100'0000:
      return MPU_REGION_SIZE_16MB;
    case 0x200'0000:
      return MPU_REGION_SIZE_32MB;
    case 0x400'0000:
      return MPU_REGION_SIZE_64MB;
    case 0x800'0000:
      return MPU_REGION_SIZE_128MB;
    case 0x1000'0000:
      return MPU_REGION_SIZE_256MB;
    case 0x2000'0000:
      return MPU_REGION_SIZE_512MB;
    case 0x4000'0000:
      return MPU_REGION_SIZE_1GB;
    case 0x8000'0000:
      return MPU_REGION_SIZE_2GB;
    case (uint32_t)0x1'0000'0000:
      return MPU_REGION_SIZE_4GB;
    default:
      return 0x0;  // invalid reg value, will cause Hardfault
  }
}

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
struct function_struct *StallardOS::initTask(void (*function)(), uint8_t prio, uint32_t *stackPtr, stack_T stackSize, uint16_t refreshRate)
{
  struct function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct

  function_struct_ptr = searchFreeFunction();
  if (function_struct_ptr == nullptr)
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr; //Aus der Funktion rausspringen
  }

  if (first_function_struct == nullptr) //Wenn noch keine funktion hinzugefügt wurde
  {
    first_function_struct = function_struct_ptr; //Funktion als erste setzen
    function_struct_ptr->next = function_struct_ptr;
    function_struct_ptr->prev = function_struct_ptr;
  }
  else //wenn bereits eine funktion hinzugefügt wurde
  {
    function_struct_ptr->next = first_function_struct;
    first_function_struct->prev->next = function_struct_ptr;
    function_struct_ptr->prev = first_function_struct->prev;
    first_function_struct->prev = function_struct_ptr;
  }
  //alle Werte übertragen
  function_struct_ptr->function = function;
  function_struct_ptr->executable = true;
  function_struct_ptr->priority = prio;
  for (uint16_t i = 0; i < countTasks+1; i++)
  {
    if(this->taskArray[i].used == 0)
    {
      function_struct_ptr->id = i;
      break;
    }
  }
  /////////////////////////////////////////////

  function_struct_ptr->refreshRate = refreshRate;
  function_struct_ptr->lastYield = 0;
  function_struct_ptr->lastStart = 0;
  function_struct_ptr->State = PAUSED;                                       //New Task
  function_struct_ptr->stackBase = stackPtr;
  function_struct_ptr->Stack = stackPtr + (stackSize - sizeof(stack_T)); //End of Stack
  function_struct_ptr->stackSize_MPU = bytesToMPUSize(stackSize);
  function_struct_ptr->stackSize = stackSize;
  function_struct_ptr->waitingForSemaphore = 0;
  function_struct_ptr->used = true;
  
  function_struct_ptr->continueInMS = 0;

  //Prepare initial stack trace
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)0x01000000;
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)function & (~1);
  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)taskOnEnd;

  function_struct_ptr->Stack--;
  *function_struct_ptr->Stack = (uint32_t)0x12;
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
  for(uint8_t i = 4; i < 12; i++)
  {
    function_struct_ptr->Stack--;
    *function_struct_ptr->Stack = 0;
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
 * @param stackSize amount of Stack bytes to allocate, stackSize*address_len must be power of 2 in MPU mode.
 * @param refreshRate frequency of execution through the normal scheduler. <= 1000 !
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunction(void (*function)(), uint8_t prio, stack_T stackSize, uint16_t refreshRate)
{
  stack_T *stackPtr;
  if (function == nullptr || searchFreeFunction() == nullptr || refreshRate > 1000 || stackSize == 0 || stackSize > 0x1'0000'0000) //Make sure the parameters are correct
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }

  #ifdef useMPU
  // MPU requires at least 32 Bytes
  // and stack size to be a pwr of 2
  if (stackSizeBytes < 32 ||\
     (stackSizeBytes & (stackSizeBytes-1)) != 0)  // number is not pwr of 2, if more than 1 bit is !=0
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }
  #endif // useMPU

  // get memory aligned (alignment, size)
  #ifdef useMPU
    stackPtr = (stack_T *)memalign(stackSize, stackSize);
  #else
    stackPtr = (stack_T *)malloc(stackSize);
  #endif // useMPU

  if(stackPtr == nullptr) //Wenn kein Stack gefunden
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }
  function_struct *ptr = initTask(function, prio, stackPtr, stackSize, refreshRate);
  ptr->staticAlloc = 0;
  return ptr;
}

/**
 * Add a new Task to execute list.
 * Does not allocate stack space
 *
 * @param function Task to execute.
 * @param prio priority of the task, lower means higher.
 * @param stackPtr pointer to the stack memory allocated by the user, must be aligned to stackSize in MPU mode
 * @param stackSize amount of Stack bytes to allocate, stackSize*word_len must be power of 2 in MPU mode.
 * @param refreshRate frequency of execution through the normal scheduler. <= 1000 !
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunctionStatic(void (*function)(), uint8_t prio, stack_T *stackPtr, stack_T stackSize, uint16_t refreshRate)
{
  if (function == nullptr || searchFreeFunction() == nullptr || refreshRate > 1000 || stackSize == 0 || stackSize > 0x1'0000'0000 || stackPtr == nullptr) //Make sure the parameters are correct
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }

  #ifdef useMPU
  // MPU requires at least 32 Bytes
  // and stack size to be a pwr of 2
  if (stackSize < 32 ||\
     (stackSize & (stackSize-1)) != 0)  // number is not pwr of 2, if more than 1 bit is !=0
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }
  #endif // useMPU
  function_struct *ptr = initTask(function, prio, stackPtr, stackSize, refreshRate);
  ptr->staticAlloc = 1;
  return ptr;
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
  uint16_t i = 0;
  volatile struct function_struct *temp = first_function_struct; //temporärer pointer erzeugen

  if (temp == nullptr)
  {
    return nullptr;
  }

  while (temp->id != id) //Solange Funktion noch nicht gefunden wurde
  {
    if (temp != first_function_struct || i == 0)
    {
      temp = temp->next; //wenn nicht nächstes element anschauen
      i++;
    }
    else
    {
      return nullptr; //wenn am ende der liste angekommen aufhören und zurück in main springen
    }
  }
  //Hier haben wir das richtige element schon gefunden -> temp
  return (function_struct*)temp; //Element übergeben
}

/**
 * search a tcb that is currently not used
 *
 */
struct function_struct *StallardOS::searchFreeFunction(void)
{
  for(uint8_t i = 0; i < sizeof(this->taskArray) / sizeof(function_struct); i++)
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
    currentTask->continueInMS = StallardOSTime_getTimeMs() + (uint64_t)milliseconds; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird
    // nextTask = taskMainStruct;
    findNextFunction();
    CALL_PENDSV();
  }
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
  currentTask->lastYield = StallardOSTime_getTimeMs();
  if (currentTask->refreshRate != 0)
  {
    if(currentTask != nullptr)
    {
      currentTask->continueInMS = StallardOSTime_getTimeMs() + (1000 / currentTask->refreshRate) - (currentTask->lastYield - currentTask->lastStart); //Calculate next execution time so we can hold the refresh rate
      if(currentTask->continueInMS > (1000 / currentTask->refreshRate) + StallardOSTime_getTimeMs())
      {
        currentTask->continueInMS = StallardOSTime_getTimeMs();
      }
      else
      {
        findNextFunction();
        CALL_PENDSV();
      }
    }
    currentTask->lastStart = StallardOSTime_getTimeMs();
  }
}


/**
 * Check the state of a task
 *
 * @param id unique id of the task.
 * @return state of the task, see taskstate enum
 */
taskState StallardOS::getFunctionState(/*Funktion*/ uint16_t id)
{
  struct function_struct *temp = searchFunction(id); //Hier die Funktion suchen
  if (temp != nullptr)                               //Wenn die übergebene Funktion gültig ist
  {
    return temp->State;
  }
  else //Ansonsten
  {
    return STOPPED;
  }
}

/**
 * Start the StallardOS operating system
 *
 */
void StallardOS::startOS(void)
{
  enable_interrupts();
  if (first_function_struct != nullptr)
  {
    currentTask = first_function_struct; //The current Task is the first one in the List
    FLASH->ACR |= (1 << FLASH_ACR_PRFTEN_Pos) | (1 << FLASH_ACR_ICEN_Pos) | (1 << FLASH_ACR_DCEN_Pos); //Enable the Flash ART-Accelerator
    // SCB->CCR |= 1 << SCB_CCR_DIV_0_TRP_Pos | 1 << SCB_CCR_UNALIGN_TRP_Pos;
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  //Set the FPU to full access
    #endif
    __ASM volatile("DSB");
    __ASM volatile("ISB");

    SysTick_Config(SystemCoreClock / (uint32_t)1000); //Counting every processor clock
    NVIC_SetPriority(SysTick_IRQn, 0xFF);
    NVIC_SetPriority(PendSV_IRQn, 0xFF);

    NVIC_EnableIRQ(PendSV_IRQn);
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(SVCall_IRQn);
    NVIC_EnableIRQ(FPU_IRQn);
    __ASM volatile("MRS R0, MSP");
    __ASM volatile("SUB R0, #200"); //Reserve some space for Handlers (200 Byte)
    __ASM volatile("MSR PSP, R0");
    // asm("mov r0, #0");
    // asm("msr control, r0");
    // SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    __ASM volatile("dsb");
    __ASM volatile("isb");
    CALL_STARTMAIN();
  }
}

/**
 * Search a task in the list
 *
 * @param id unique id of the task.
 * @param exec_freq new execution frequency of the task
 */
void StallardOS::setFunctionFrequency(/*Funktion*/ uint16_t id, float exec_freq)
{
  if (exec_freq <= 0) //Make sure the parameters are correct
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
  CALL_FLASHLOADER();
}