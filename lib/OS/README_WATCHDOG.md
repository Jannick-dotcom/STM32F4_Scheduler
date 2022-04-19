## **Stallardo Operating System**
**StallardOS_Watchdog**

StallardOS supports Software Watchdogs.
Each task can be configured with a watchdog interval, given in ms.

```
addFunction(void (*function)(), uint8_t prio, stack_T stackSize, uint16_t refreshRate = 0, uint16_t watchdogLimitMs=0);
```

The watchdog must be kicked every `watchdogLimitMS` milliseconds, by calling `STOS.kicktheDog()` or `StallardOS::kickTheDog()`.

If the watchdog is not kicked, a breakpoint is triggered and the task will not be executed anymore (might be changed to restart in the future).

-----

### Implementation

The watchdog timer is incremented at each swapOut in `PendSV`, by the time the task was running. On each systick, the task is additionally checked for a watchdog violation within the current execution window.

All interal values are stored in us, while the user gives the watchdog limit in milliseconds.

Only the currently running task is checked for watchdog violations. A non-executing task would not be affected by a restart/abortion anyway.

