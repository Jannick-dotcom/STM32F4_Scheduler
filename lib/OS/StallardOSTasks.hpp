#pragma once
#include "StallardOSHelpers.h"

// definition in correlated .cpp file
extern stack_T taskmainStack[256];
extern stack_T taskPerfmonStack[256];


void taskMain(void);
void taskPerfmon(void);