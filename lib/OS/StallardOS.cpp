#include "StallardOS.hpp"

extern "C" volatile uint64_t usCurrentTimeSinceStart; //about 585 000 years of microsecond counting
// extern "C" volatile uint64_t taskMainTime;

//Kontext Switch
volatile struct function_struct* volatile currentTask = nullptr;
volatile struct function_struct* volatile nextTask = nullptr;
volatile struct function_struct* volatile taskMainStruct = nullptr;

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
        free((uint32_t*)currentTask->vals);
    }
    currentTask = taskMainStruct;
    nextTask = taskMainStruct;
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
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
  countTCBsInUse = 0;
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

  taskMainStruct = addFunction(taskMain, -2, 255, 200);
  if(taskMainStruct == nullptr) while(1);

  TIM_HandleTypeDef htim;
  __TIM6_CLK_ENABLE();
  htim.Instance = TIM6;
  htim.Init.Prescaler = 0; //Because 21 MHz APB1 Clock -> 1 MHz timer interrupts
  htim.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim.Init.Period = 41;
  htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim.Init.RepetitionCounter = 0;
  htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  __HAL_DBGMCU_FREEZE_TIM6();
  HAL_TIM_Base_Init(&htim);
  __HAL_TIM_CLEAR_FLAG(&htim, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim);
  NVIC_SetPriority(TIM6_DAC_IRQn, 0x00);
  HAL_NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
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

    if (first_function_struct == nullptr) //Wenn noch keine funktion hinzugefügt wurde
    {
      first_function_struct = temp; //Funktion als erste setzen
      temp->next = temp;
      temp->prev = temp;
    }
    else //wenn bereits eine funktion hinzugefügt wurde
    {
      temp->next = first_function_struct;
      first_function_struct->prev->next = temp;
      temp->prev = first_function_struct->prev;
      first_function_struct->prev = temp;
    }
    //alle Werte übertragen
    temp->function = nullptr;
    temp->priority = -1;

    temp->id = -1;

    temp->State = STOPPED;                        //New Task
    // temp->Stack = temp->vals + sizeStack - sizeof(uint32_t); //End of Stack


    temp->executable = true;
    temp->used = false;
    temp->continueInUS = 0;

    TCBsCreated++;
  }
}

/**
 * Add a new Task to execute list.
 * Also allocates Stack space for the Task
 *
 * @param function Task to execute.
 * @param id unique id of the task.
 * @param prio priority of the task, lower means higher.
 * @param stackSize amount of Stack words to allocate.
 * @param refreshRate frequency of execution through the normal scheduler. <= 1000 !
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunction(void (*function)(), uint8_t prio, uint32_t stackSize, uint16_t refreshRate)
{
  if (function == nullptr || searchFunction(countTCBsInUse) != nullptr || refreshRate > 1000 || stackSize == 0) //Make sure the parameters are correct
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }

  struct function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct

  function_struct_ptr = searchFreeFunction();
  if (function_struct_ptr == nullptr)
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr; //Aus der Funktion rausspringen
  }

  if (first_function_struct == nullptr) //Wenn noch keine funktionen hinzugefügt wurden
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }
  stack_T *stackPtr = (stack_T*)malloc(sizeof(stack_T) * stackSize); //Stack speicher für funktion allokieren
  if(stackPtr == nullptr) //Wenn kein Stack gefunden
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }

  //alle Werte übertragen
  function_struct_ptr->function = function;
  function_struct_ptr->executable = true;
  function_struct_ptr->priority = prio;
  function_struct_ptr->id = countTCBsInUse;
  countTCBsInUse++;
  function_struct_ptr->staticAlloc = 0;
  // function_struct_ptr->error = 0;

  function_struct_ptr->refreshRate = refreshRate;
  function_struct_ptr->lastYield = 0;
  function_struct_ptr->lastStart = 0;
  function_struct_ptr->State = PAUSED;  //New Task
  function_struct_ptr->Stack = stackPtr + stackSize - sizeof(stack_T); //End of Stack
  function_struct_ptr->vals = function_struct_ptr->Stack; //End of Stack
  function_struct_ptr->stackSize = stackSize;
  function_struct_ptr->waitingForSemaphore = 0;
  function_struct_ptr->used = true;
  
  function_struct_ptr->continueInUS = 0;
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
 * Does not allocate stack space
 *
 * @param function Task to execute.
 * @param id unique id of the task.
 * @param prio priority of the task, lower means higher.
 * @param stackPtr pointer to the stack memory allocated by the user
 * @param stackSize amount of Stack words to allocate.
 * @param refreshRate frequency of execution through the normal scheduler. <= 1000 !
 * @return pointer to the created tcb.
 */
struct function_struct *StallardOS::addFunctionStatic(void (*function)(), uint8_t prio, uint32_t *stackPtr, uint32_t stackSize, uint16_t refreshRate)
{
  if (function == nullptr || searchFunction(countTCBsInUse) != nullptr || refreshRate > 1000 || stackSize == 0 || stackPtr == nullptr) //Make sure the parameters are correct
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }

  struct function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct

  function_struct_ptr = searchFreeFunction();
  if (function_struct_ptr == nullptr)
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr; //Aus der Funktion rausspringen
  }

  if (first_function_struct == nullptr) //Wenn schon funktionen hinzugefügt wurden
  {
    #ifndef UNIT_TEST
    asm("bkpt");  //Zeige debugger
    #endif
    return nullptr;
  }

  //alle Werte übertragen
  function_struct_ptr->function = function;
  function_struct_ptr->executable = true;
  function_struct_ptr->priority = prio;
  function_struct_ptr->id = countTCBsInUse;
  countTCBsInUse++;
  // function_struct_ptr->error = 0;

  function_struct_ptr->refreshRate = refreshRate;
  function_struct_ptr->lastYield = 0;
  function_struct_ptr->lastStart = 0;
  function_struct_ptr->State = PAUSED;                                       //New Task
  function_struct_ptr->Stack = function_struct_ptr->vals = stackPtr + stackSize - sizeof(stack_T); //End of Stack
  function_struct_ptr->stackSize = stackSize;
  function_struct_ptr->waitingForSemaphore = 0;
  function_struct_ptr->used = true;
  function_struct_ptr->staticAlloc = 1;
  
  function_struct_ptr->continueInUS = 0;
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
  uint16_t i = 0;
  volatile struct function_struct *temp = first_function_struct; //temporärer pointer erzeugen

  if (temp == nullptr)
  {
    return nullptr;
  }

  while (temp->used) //Solange Funktion noch nicht gefunden wurde
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
 * delay for an amount of milliseconds
 *
 * @param milliseconds the amount of msec to wait.
 */
void StallardOS::delay(uint32_t milliseconds)
{
  if(currentTask == nullptr) //wenn im bootup
  {
    uint64_t continueTimeStamp = usCurrentTimeSinceStart + (milliseconds * 1000);
    while (usCurrentTimeSinceStart < continueTimeStamp);
  }
  else
  {
    currentTask->continueInUS = (uint64_t)milliseconds * 1000; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird
    // nextTask = taskMainStruct;
    findNextFunction();
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
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
  currentTask->lastYield = usCurrentTimeSinceStart;
  if (currentTask->refreshRate != 0)
  {
      if(currentTask != nullptr)
      {
        currentTask->continueInUS = (1000000 / currentTask->refreshRate) - (currentTask->lastYield - currentTask->lastStart); //Calculate next execution time so we can hold the refresh rate
        if(currentTask->continueInUS > (1000000 / currentTask->refreshRate))
          currentTask->continueInUS = 0;
        else
        {
          findNextFunction();
          SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
        }
      }
    currentTask->lastStart = usCurrentTimeSinceStart;
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

// uint8_t StallardOS::getCPUload()
// {
//   float val;
//   val = (1.0 - float(taskMainTime) / float(getRuntimeMs())) * 100.0;
//   return val;
// }

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
    asm("DSB");
    asm("ISB");

    SysTick_Config(SystemCoreClock / (uint32_t)1000);
    NVIC_SetPriority(SysTick_IRQn, 0xFF);
    NVIC_SetPriority(PendSV_IRQn, 0xFF);

    NVIC_EnableIRQ(PendSV_IRQn);
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(SVCall_IRQn);
    NVIC_EnableIRQ(FPU_IRQn);
    asm("MRS R0, MSP");
    asm("SUB R0, #200"); //Reserve some space for Handlers (200 Byte)
    asm("MSR PSP, R0");
    asm("mov r0, #0");
    asm("msr control, r0");
    // SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    asm("dsb");
    asm("isb");
    asm("SVC 2");
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

uint64_t StallardOS::getRuntimeMs()
{
  return usCurrentTimeSinceStart / 1000;
}

uint64_t StallardOS::getRuntimeUs()
{
  return usCurrentTimeSinceStart;
}

void StallardOS::goBootloader()
{
  StallardOS_goBootloader();
}