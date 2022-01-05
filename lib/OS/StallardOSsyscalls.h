#pragma  once


/* "background" macros used to construct the syscall */
#define _SYM_TO_STR(NUM) #NUM

#define _SV_STR(NUMBER) "SVC #" _SYM_TO_STR(NUMBER)
#define _SVC(NUMBER) __ASM volatile(_SV_STR(NUMBER))


/* syscall definitions */

#define SV_NOP 0
#define SV_BOOTLOADER 1
#define SV_PENDSV 2
#define SV_STARTMAIN 3
#define SV_FLASHLOADER 4
#define SV_ACTIVATE_PRIV 5
#define SV_DEACTIVATE_PRIV 6


/* callable c abstractions */
#define CALL_NOP() _SVC(SV_NOP)
#define CALL_BOOTLOADER() _SVC(SV_BOOTLOADER)
#define CALL_PENDSV() _SVC(SV_PENDSV) 
#define CALL_STARTMAIN() _SVC(SV_STARTMAIN)
#define CALL_FLASHLOADER() _SVC(SV_FLASHLOADER)
#define CALL_PRIVILEGED() _SVC(SV_ACTIVATE_PRIV)
#define CALL_UNPRIVILEGED() _SVC(SV_DEACTIVATE_PRIV)