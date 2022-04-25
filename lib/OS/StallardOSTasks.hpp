#pragma once
#include "StallardOSHelpers.h"

// definition in correlated .cpp file
extern stack_T taskmainStack[256];
extern stack_T taskPerfmonStack[256];
#ifdef useSFOC
    extern stack_T taskSFOCStack[256];
#endif


void taskMain(void);
void taskPerfmon(void);

#ifdef useSFOC
    void taskSFOC(void);
#endif
