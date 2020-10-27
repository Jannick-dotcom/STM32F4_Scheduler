#ifndef StallardOSHelpers_H
#define StallardOSHelpers_H

#include <stm32f4xx_hal.h>

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_noTask()
{
    asm("SVC #0");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_sudo()
{
    asm("SVC #3");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_unSudo()
{
    asm("SVC #4");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_start()
{
    asm("SVC #5");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_delay()
{
    asm("SVC #2");
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_endTask()
{
    asm("SVC #1"); 
}

#ifdef __cplusplus
extern "C" 
#endif
inline void StallardOS_goBootloader()
{
    asm("SVC #6");
}

////////////////////////////////////////////////////////////////////////////////////////
//Enables all interrupts
////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
inline void enable_interrupts() 
{
	asm("CPSIE I");     //Instruction for enabling interrupts
}

////////////////////////////////////////////////////////////////////////////////////////
//Disables all interrupts
////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
inline void disable_interrupts() 
{
	asm("CPSID I");     //Instruction for disabling interrupts
}

#ifdef __cplusplus
extern "C" 
#endif
inline void pendPendSV()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

#endif