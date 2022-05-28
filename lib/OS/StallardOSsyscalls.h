#pragma  once
#include "StallardOSconfig.h"


/* "background" macros used to construct the syscall */
#define _SYM_TO_STR(NUM) #NUM

#define _SV_STR(NUMBER) "SVC #" _SYM_TO_STR(NUMBER)
#define _SVC(NUMBER) __ASM volatile(_SV_STR(NUMBER))


/* syscall definitions */

#define SV_BOOTLOADER 1
#define SV_PENDSV 2
#define SV_STARTMAIN 3
#define SV_SYSRESET 4
#define SV_ACTIVATE_PRIV 5
#define SV_DEACTIVATE_PRIV 6


/* callable c abstractions */
#define CALL_BOOTLOADER() _SVC(SV_BOOTLOADER)
#define CALL_PENDSV() _SVC(SV_PENDSV) 
#define CALL_STARTMAIN() _SVC(SV_STARTMAIN)
#define CALL_SYSRESET() _SVC(SV_SYSRESET)

#ifdef unprotectedBuild
    #define CALL_PRIVILEGED() {}
    #define CALL_UNPRIVILEGED() {}
#else
    #define CALL_PRIVILEGED() if((__get_CONTROL() & CONTROL_nPRIV_Msk)) _SVC(SV_ACTIVATE_PRIV) //if not privileged request privilege
    #define CALL_UNPRIVILEGED() if(!(__get_CONTROL() & CONTROL_nPRIV_Msk)) _SVC(SV_DEACTIVATE_PRIV) //if privileged request unprivilege
#endif