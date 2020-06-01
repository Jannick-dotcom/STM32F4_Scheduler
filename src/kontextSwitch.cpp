#include "TaskScheduler.h"

//Kontext Switch
uint8_t switchEnable = 0;
function_struct *currentTask = nullptr;
Ticker systemSwitchEvent;

__attribute__((isr, naked)) void systemSwitchEvent_Handler(void) //interrupt von Ticker
{
    if (switchEnable)
    {
        if ((currentTask != NULL) && (currentTask->State == RUNNING))       //Hier Task anhalten
        {
            asm("MOV %0, r11" :"=r" (*(currentTask->arr)));    //Move value from r11
            asm("MOV %0, r10" :"=r" (*(currentTask->arr+1)));  //Move value from r10
            asm("MOV %0, r9" :"=r"  (*(currentTask->arr+2)));  //Move value from r9
            asm("MOV %0, r8" :"=r"  (*(currentTask->arr+3)));  //Move value from r8
            asm("MOV %0, r7" :"=r"  (*(currentTask->arr+4)));  //Move value from r7
            asm("MOV %0, r6" :"=r"  (*(currentTask->arr+5)));  //Move value from r6
            asm("MOV %0, r5" :"=r"  (*(currentTask->arr+6)));  //Move value from r5
            asm("MOV %0, r4" :"=r"  (*(currentTask->arr+7)));  //Move value from r4
            asm("MOV %0, r3" :"=r"  (*(currentTask->arr+8)));  //Move value from r3
            asm("MOV %0, r2" :"=r"  (*(currentTask->arr+9)));  //Move value from r2
            asm("MOV %0, r1" :"=r"  (*(currentTask->arr+10))); //Move value from r1
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+11))); //Move value from r0

            ///R14 ist das LinkRegister  -- Bei interrupt wird die Adresse hier gespeichert an die zurückgesprungen werden soll!!!!!

            asm("MOV %0, r14" :"=r"  (*(currentTask->arr+12))); //Move value from r14 / LR

            asm("MRS r0, APSR");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+13))); //Move value from r0
            asm("MRS r0, IPSR");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+14))); //Move value from r0
            asm("MRS r0, IEPSR");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+15))); //Move value from r0
            asm("MRS r0, IAPSR");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+16))); //Move value from r0
            asm("MRS r0, EAPSR");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+17))); //Move value from r0
            asm("MRS r0, PSR");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+18))); //Move value from r0
            asm("MRS r0, MSP");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+19))); //Move value from r0
            asm("MRS r0, PSP");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+20))); //Move value from r0
            asm("MRS r0, PRIMASK");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+21))); //Move value from r0
            asm("MRS r0, BASEPRI");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+22))); //Move value from r0
            asm("MRS r0, BASEPRI_MAX");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+23))); //Move value from r0
            asm("MRS r0, FAULTMASK");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+24))); //Move value from r0
            asm("MRS r0, CONTROL");
            asm("MOV %0, r0" :"=r"  (*(currentTask->arr+25))); //Move value from r0

            //currentTask->State = STOPPED;   //Komplett angehalten!

            //Noch den r0 Registerinhalt wiederherstellen
            //Dann können wir den Task auch zur Not wieder weiterlaufen lassen als wäre nichts gewesen
            asm("MOV r0, %0" : : "r" (*(currentTask->arr+11))); //Move value to r0
        }

        /*******************************************************************************/
        //currentTask = currentTask->next;    //Nächsten Task

        if (currentTask->State == STOPPED)     //Hier Task fortsetzen
        {
            asm("MOV r14, %0" : :"r"  (*(currentTask->arr+12))); //Move value from r14 / LR
            asm("MSR APSR, r0");
            asm("MOV r0, %0" : : "r"  (*(currentTask->arr+13))); //Move value to r0
            asm("MSR IPSR, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+14))); //Move value from r0
            asm("MSR IEPSR, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+15))); //Move value from r0
            asm("MSR IAPSR, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+16))); //Move value from r0
            asm("MSR EAPSR, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+17))); //Move value from r0
            asm("MSR PSR, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+18))); //Move value from r0            
            asm("MSR MSP, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+19))); //Move value from r0            
            asm("MSR PSP, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+20))); //Move value from r0           
            asm("MSR PRIMASK, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+21))); //Move value from r0
            asm("MSR BASEPRI, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+22))); //Move value from r0
            asm("MSR BASEPRI_MAX, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+23))); //Move value from r0
            asm("MSR FAULTMASK, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+24))); //Move value from r0
            asm("MSR CONTROL, r0");
            asm("MOV r0, %0" : :"r"  (*(currentTask->arr+25))); //Move value from r0


            asm("MOV r11, %0" : : "r" (*(currentTask->arr))); //Move value to r0
            asm("MOV r10, %0" : : "r" (*(currentTask->arr+1))); //Move value to r0
            asm("MOV r9, %0" : : "r" (*(currentTask->arr+2))); //Move value to r0
            asm("MOV r8, %0" : : "r" (*(currentTask->arr+3))); //Move value to r0
            asm("MOV r7, %0" : : "r" (*(currentTask->arr+4))); //Move value to r0
            asm("MOV r6, %0" : : "r" (*(currentTask->arr+5))); //Move value to r0
            asm("MOV r5, %0" : : "r" (*(currentTask->arr+6))); //Move value to r0
            asm("MOV r4, %0" : : "r" (*(currentTask->arr+7))); //Move value to r0
            asm("MOV r3, %0" : : "r" (*(currentTask->arr+8))); //Move value to r0
            asm("MOV r2, %0" : : "r" (*(currentTask->arr+9))); //Move value to r0
            asm("MOV r1, %0" : : "r" (*(currentTask->arr+10))); //Move value to r0
            asm("MOV r0, %0" : : "r" (*(currentTask->arr+11))); //Move value to r0

            currentTask->State = RUNNING;
        }
    }
}

/*
// port.c
void xPortPendSVHandler( void )
{
    // This is a naked function. //

    asm("MRS r0, PSP");
    asm("ISB");

    asm("LDR r3, %0":"=r"(currentTask->Stackpointer)); // Get the location of the current TCB. //
    //asm("LDR r2, [r3]");

    asm("TST r14, #16"); // Is the task using the FPU context?  If so, push high vfp registers. //
    asm("IT eq");
    asm("VSTMDBEQ r0!, {s16-s31}");

    asm("STMDB r0!, {r4-r11, r14}"); //Save the core registers. //
    //asm("STR r0, [r2]"); // Save the new top of stack into the first member of the TCB. //

    asm("STMDB sp!, {r0, r3}");
    asm("MOV r0, %0": "=r"(currentTask->Stackpointer));
    asm("MSR BASEPRI, r0");
    asm("DSB");
    asm("ISB");

    currentTask = currentTask->next;
    asm("LDR r3, %0":"=r"(currentTask->Stackpointer)); // Get the location of the current TCB. //
    asm("MOV r0, #0");
    asm("MSR BASEPRI, r0");
    asm("LDMIA sp!, {r0, r3}");

    //asm("LDR r1, [r3]"); // The first item in pxCurrentTCB is the task top of stack. //
    //asm("LDR r0, [r1]");

    asm("LDMIA r0!, {r4-r11, r14}"); // Pop the core registers. //

    asm("TST r14, #16"); // Is the task using the FPU context?  If so, pop the high vfp registers too. //
    asm("IT eq");
    asm("VLDMIAEQ r0!, {s16-s31}");

    asm("MSR PSP, r0");
    asm("ISB");

    asm("BX r14");
    asm(".align 4");
}*/