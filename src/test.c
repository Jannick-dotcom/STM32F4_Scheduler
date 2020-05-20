#include <inttypes.h>

void PendSV_Handler(void)
{
    uint32_t Task_SP;

    asm("mrs r0, msp");

    asm("mrs r1, psp");
    asm("msr msp, r1");
    asm("isb");

    asm("push {r11}");
    asm("push {r10}");
    asm("push {r9}");
    asm("push {r8}");
    asm("push {r7}");
    asm("push {r6}");
    asm("push {r5}");
    asm("push {r4}");

    asm("mrs %0, msp" : "=r"(Task_SP));

    asm("msr msp, r0");
    asm("isb");

    asm("mrs r0, msp");
    asm("msr msp, %0" : : "r"(Task_SP));
    asm("isb");

    asm("pop {r4}");
    asm("pop {r5}");
    asm("pop {r6}");
    asm("pop {r7}");
    asm("pop {r8}");
    asm("pop {r9}");
    asm("pop {r10}");
    asm("pop {r11}");

    asm("mrs %0, msp" : "=r"(Task_SP));

    asm("msr msp, r0");
    asm("isb");

    asm("msr psp, %0" : : "r"(Task_SP));
    asm("isb");
}