#include "Jannix.h"

extern uint8_t switchEnable;
extern function_struct *currentTask;
extern function_struct *taskMainStruct;

////////////////////////////////////////////////////////////////////////////////////////
//Just if no other Tasks have to be executed run this
////////////////////////////////////////////////////////////////////////////////////////
void taskMain(void) //Hier wird die Überschüssige Zeit verbraten
{
  while (1)
    ;
}

////////////////////////////////////////////////////////////////////////////////////////
//Constructor - Here we Create a Jannix Object
////////////////////////////////////////////////////////////////////////////////////////
Jannix::Jannix()
{
  //Basiswerte Initialisieren
  first_function_struct = nullptr;
  currentTask = nullptr;
  TCBsCreated = 0;

  //Für Context Switch
  taskMainStruct = addFunction(taskMain, 0, 255, 1);
  createTCBs();
  currentTask = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Adds new Tasks to the List
////////////////////////////////////////////////////////////////////////////////////////
void Jannix::createTCBs()
{
  if (TCBsCreated >= countTasks) //Wenn schon genug TCBs erstellt wurden, nicht nochmal erstellen
  {
    return;
  }

  for (uint8_t i = 0; i < countTasks + 1; i++)
  {
    function_struct *temp;
    temp = new function_struct;
    if (temp == nullptr) //Wenn kein HEAP Platz mehr frei ist...
    {
      break; //Aus der Funktion rausspringen
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
    temp->executable = true;
    temp->priority = -1;
    // function_struct_ptr->frequency = exec_freq;
    temp->id = -1;
    // function_struct_ptr->lastExecTime = 0;

    temp->State = NEW; //New Task
    temp->used = false;
    temp->continueInMS = 0;

    temp->Stack = temp->vals + sizeStack - 4; //End of Stack
    TCBsCreated++;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Adds a new Task to the List of executable ones
////////////////////////////////////////////////////////////////////////////////////////
function_struct *Jannix::addFunction(void (*function)(), uint16_t id, uint8_t prio, float exec_freq, uint16_t Execcount)
{
  if (function == nullptr || exec_freq <= 0 || searchFunction(id) != nullptr) //Make sure the parameters are correct
  {
    return nullptr;
  }

  function_struct *function_struct_ptr = nullptr; //Pointer to the function Struct

  function_struct_ptr = searchFreeFunction();
  if (function_struct_ptr == nullptr)
  {
    function_struct_ptr = new function_struct; //ein neues erstellen
    if (function_struct_ptr == nullptr)        //Wenn kein HEAP Platz mehr frei ist...
    {
      return nullptr; //Aus der Funktion rausspringen
    }
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
  // function_struct_ptr->frequency = exec_freq;
  function_struct_ptr->id = id;
  // function_struct_ptr->lastExecTime = 0;

  function_struct_ptr->State = NEW; //New Task
  function_struct_ptr->used = true;
  function_struct_ptr->continueInMS = 0;

  function_struct_ptr->Stack = function_struct_ptr->vals + sizeStack - 4; //End of Stack

  // function_struct_ptr->lastExecTime = 0; //ab hier wird die nächste ausfürzeit berechnet
  return function_struct_ptr;
}

////////////////////////////////////////////////////////////////////////////////////////
//Here we en/disable a Task from the List
////////////////////////////////////////////////////////////////////////////////////////
void Jannix::changeFunctionEnabled(uint16_t id, bool act)
{
  function_struct *temp = searchFunction(id); //Funktion suchen
  if (temp != nullptr)                        //Wenn die übergebene Funktion gültig ist
  {
    temp->executable = act;
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Sets new Priority of a Task
////////////////////////////////////////////////////////////////////////////////////////
void Jannix::setFunctionPriority(/*Funktion*/ uint16_t id, uint8_t prio)
{
  function_struct *temp = searchFunction(id); //Hier die Funktion speichern von der die Priorität geändert werden soll
  if (temp != nullptr)                        //Wenn die übergebene Funktion gültig ist
  {
    temp->priority = prio; //Die Priorität ändern
  }
}

////////////////////////////////////////////////////////////////////////////////////////
//Search a task in the list of executable ones/*
////////////////////////////////////////////////////////////////////////////////////////
function_struct *Jannix::searchFunction(/*ID*/ uint16_t id)
{
  uint16_t i = 0;
  function_struct *temp = first_function_struct; //temporärer pointer erzeugen

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
  return temp; //Element übergeben
}

////////////////////////////////////////////////////////////////////////////////////////
//Search a free task in the list
////////////////////////////////////////////////////////////////////////////////////////
function_struct *Jannix::searchFreeFunction(void)
{
  uint16_t i = 0;
  function_struct *temp = first_function_struct; //temporärer pointer erzeugen

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
  return temp; //Element übergeben
}

////////////////////////////////////////////////////////////////////////////////////////
//Delay for an amount of milliseconds
////////////////////////////////////////////////////////////////////////////////////////
void Jannix::delay(uint32_t milliseconds)
{
  currentTask->continueInMS = milliseconds; //Speichere anzahl millisekunden bis der Task weiter ausgeführt wird
  currentTask->executable = false;
  asm("SVC #2");
}

////////////////////////////////////////////////////////////////////////////////////////
//Return the State of the Task
////////////////////////////////////////////////////////////////////////////////////////
taskState Jannix::getFunctionState(/*Funktion*/ uint16_t id)
{
  function_struct *temp = searchFunction(id); //Hier die Funktion suchen
  if (temp != nullptr)                        //Wenn die übergebene Funktion gültig ist
  {
    return temp->State;
  }
  else //Ansonsten
  {
    return STOPPED;
  }
}

// function_struct::~function_struct() //Destructor
// {
//   if (this != taskMainStruct)
//   {
//     this->next->prev = this->prev;
//     this->prev->next = this->next;
//   }
// }

// clock source is selected with CLOCK_SOURCE in json config
#define USE_PLL_HSE_EXTC 0x8 // Use external clock (ST Link MCO)
#define USE_PLL_HSE_XTAL 0x4 // Use external xtal (X3 on board - not provided by default)
#define USE_PLL_HSI 0x2      // Use HSI internal clock

uint8_t SetSysClock_PLL_HSE(uint8_t bypass)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  //RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet. */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Get the Clocks configuration according to the internal RCC registers */
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  /* PLL could be already configured by bootlader */
  if (RCC_OscInitStruct.PLL.PLLState != RCC_PLL_ON)
  {

    /* Enable HSE oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    if (bypass == 0)
    {
      RCC_OscInitStruct.HSEState = RCC_HSE_ON; /* External 8 MHz xtal on OSC_IN/OSC_OUT */
    }
    else
    {
      RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS; /* External 8 MHz clock on OSC_IN */
    }
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;             // VCO input clock = 1 MHz (8 MHz / 8)
    RCC_OscInitStruct.PLL.PLLN = 360;           // VCO output clock = 360 MHz (1 MHz * 360)
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 180 MHz (360 MHz / 2)
    RCC_OscInitStruct.PLL.PLLQ = 7;             //
    RCC_OscInitStruct.PLL.PLLR = 2;             //
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      return 0; // FAIL
    }
  }

  // Activate the OverDrive to reach the 180 MHz Frequency
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    return 0; // FAIL
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // 180 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  //  45 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  //  90 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    return 0; // FAIL
  }
  return 1;
}

uint8_t SetSysClock_PLL_HSI(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  //RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet. */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSI oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;            // VCO input clock = 1 MHz (16 MHz / 16)
  RCC_OscInitStruct.PLL.PLLN = 360;           // VCO output clock = 360 MHz (1 MHz * 360)
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLCLK = 180 MHz (360 MHz / 2)
  RCC_OscInitStruct.PLL.PLLQ = 7;             //
  RCC_OscInitStruct.PLL.PLLR = 6;             //
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    return 0; // FAIL
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // 180 MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        // 180 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;         //  45 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;         //  90 MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    return 0; // FAIL
  }

  return 1; // OK
}

void Jannix_SetSysClock(void)
{
  /* 1- Try to start with HSE and external clock */
  //if (SetSysClock_PLL_HSE(1) == 0)
  //{
  /* 2- If fail try to start with HSE and external xtal */
  //  if (SetSysClock_PLL_HSE(0) == 0)
  //{
  /* 3- If fail start with HSI clock */
  if (SetSysClock_PLL_HSI() == 0)
  {
    while (1)
      ;
  }
  //}
  //}
}