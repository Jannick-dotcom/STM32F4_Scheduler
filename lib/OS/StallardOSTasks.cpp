#include "StallardOSTasks.hpp"
#include "StallardOS.hpp"

// private kernel variable
extern volatile struct function_struct* volatile taskMainStruct;

// public variables (declared in header)
stack_T taskmainStack[256] __attribute__((aligned(1024))); /* align to size in Byte */
stack_T taskPerfmonStack[256] __attribute__((aligned(1024))); /* align to size in Byte */


STOS_CAN_PDU_Whl_Speed_F wSpeed;


/**
 * Waste Time if all tasks are in delay.
 *
 * @param 
 * @return
 */
void taskMain(void)
{
  
  while (1)
  {
  }
  
}



void taskPerfmon(void){

    volatile struct function_struct *task;
    uint64_t total_calc_time_us;
    uint64_t idle_calc_time_us;
    uint8_t cpu_load;

    uint16_t adcan_fill_lvl;
    uint16_t ms4can_fill_lvl;


  while(1){

    // get cpu load of the system
    total_calc_time_us = 0;
    idle_calc_time_us = 0;

    // iterate over all tasks to get used cpu time since last scan
    task = taskMainStruct;
    do{
      total_calc_time_us += task->perfmon_exec_time_us;
      task->perfmon_exec_time_us = 0;
      task = task->next;
    }
    while(task != taskMainStruct);

    // get idle task cpu load and compare this to the total time
    idle_calc_time_us = taskMainStruct->perfmon_exec_time_us;
    cpu_load = 100 - (idle_calc_time_us*100/total_calc_time_us);


    // get temperature values of the system
    // TODO: readout temps


    // get can fifo fill levels
    adcan_fill_lvl = AD_CAN.getSWFiFoFillLevel();
    ms4can_fill_lvl = MS4_CAN.getSWFiFoFillLevel();


    // send all collected values to AD_CAN (if present)
    wSpeed.build();
    // AD_CAN.sendMessage(&wSpeed); // cpu load
    // AD_CAN.sendMessage(&wSpeed); // temp
    // AD_CAN.sendMessage(&wSpeed); // FIFO levels (AD/MS4)

    StallardOS::yield();
  }
}