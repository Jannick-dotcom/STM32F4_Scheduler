#ifndef StallardOSHelpers_H
#define StallardOSHelpers_H

#include "stdint.h"

#include "StallardOSconfig.h"
#include "StallardOSsyscalls.h"

#if defined STM32F4xxxx
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#elif defined STM32F1xxxx
#include <stm32f1xx_hal.h>
#include <system_stm32f1xx.h>
#endif

#ifndef UNIT_TEST
#define DEBUGGER_BREAK() //asm("bkpt")
#else
#define DEBUGGER_BREAK()
#endif

#define GEN_HARDFAULT() \
  DEBUGGER_BREAK();     \
  StallardOSGeneralFaultHandler()

#define functionModifier (uint32_t)0xFFFFFFFE // Use the function pointer with lowest bit zero
// #define sysTickTicks (uint32_t)(SystemCoreClock / 1000)
typedef enum oscillatorType
  {
    internal = RCC_OSCILLATORTYPE_HSI,
    external = RCC_OSCILLATORTYPE_HSE
  } oscillatorType;
#ifdef __cplusplus
extern "C"
{
#endif
  void StallardOS_SetSysClock(uint8_t clockspeed, oscillatorType oscType);
  void StallardOS_goBootloader();
  void enable_interrupts();
  void disable_interrupts();
  void taskOnEnd(void);
#ifdef __cplusplus
}
#endif

typedef enum
{
  // NEW = 0,
  RUNNING = 1,
  PAUSED,
  STOPPED
} taskState;

typedef uint32_t stack_T;

struct function_struct
{
  volatile stack_T *Stack;     // Stack pointer
  volatile stack_T *stackBase; // lowest address of stack allocation, used for MPU config
  uint32_t stackSize;          // Number of elements possible to store on stack, NOT size in bytes
  uint8_t staticAlloc;         // Is the stack static or dynamically allocated?

#ifdef useMPU
  uint8_t mpu_regionSize;   // might be offset from atcual stack pointer, if subregions are used
  uint32_t mpu_baseAddress; // might be offset from actual size, if subregions are used
  uint8_t mpu_subregions;
#endif // useMPU

  volatile struct function_struct *prev; // für verkettete liste
  volatile struct function_struct *next; // für verkettete liste

  // Must have Variablen
  void (*function)();          // Auszuführende Funktion
  volatile uint8_t priority;   // Priorität 0 wird nicht unterbrochen außer Prozess wünscht es durch ein Delay
  volatile uint16_t id;        // ID des Tasks
  volatile uint8_t used;       // Ist dieser TCB schon belegt?
  volatile uint8_t executable; // Funktion ausführen?

  // volatile uint8_t error; //Error in Task scheduling has happened

  // nur für KontextSwitch
  volatile uint16_t refreshRate;
  volatile uint64_t lastYield;
  volatile uint64_t lastStart;                  // used for yield/frequency violation detection

  // SW watchdog
  volatile uint64_t watchdog_limit;           // user defined limit
  volatile uint64_t watchdog_exec_time_us;    // exec time since last kick
  volatile uint64_t watchdog_swapin_ts;       // last swapin OR time since last kick (whicever is later), in us

  // cpu load estimation
  volatile uint64_t perfmon_exec_time_us;       // accumulated exec time of task since last reset
  volatile uint64_t perfmon_swapin_ts;          // last swapIn, helper for exec time, ts in us

  // volatile uint32_t stackUsage;
  // volatile taskState State;             //Status des Tasks
  volatile uint8_t waitingForSemaphore; // Is task waiting for a semaphore
  volatile uint32_t *semVal;            // First 16bit - ID-of-Task
                             // Last  16bit - Semaphore Value
  volatile uint64_t continue_ts; //Timestamp of continuation
};

#endif