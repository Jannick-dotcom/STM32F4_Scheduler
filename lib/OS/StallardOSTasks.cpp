#include "StallardOSTasks.hpp"
#include "StallardOS.hpp"

// private kernel variable
extern volatile struct function_struct* volatile taskMainStruct;

// public variables (declared in header)
stack_T taskmainStack[256] __attribute__((aligned(1024))); /* align to size in Byte */
stack_T taskPerfmonStack[256] __attribute__((aligned(1024))); /* align to size in Byte */





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

    // output can messages (defined per ECU)
    // ...using dummy messages, until dbc is updated
    #if 0
    #if STOS_current_ECU_ID==ECU_ID_FCU
      STOS_CAN_PDU_Steering_Whl_Angle load;
      STOS_CAN_PDU_SWCU_ECU_Temp temp;
      STOS_CAN_PDU_Whl_Speed_F fifoLvl;
    #elif STOS_current_ECU_ID==2
      STOS_CAN_PDU_Steering_Whl_Angle load;
      STOS_CAN_PDU_SWCU_ECU_Temp temp;
      STOS_CAN_PDU_Whl_Speed_F fifoLvl;
    #elif STOS_current_ECU_ID==3
      STOS_CAN_PDU_Steering_Whl_Angle load;
      STOS_CAN_PDU_SWCU_ECU_Temp temp;
      STOS_CAN_PDU_Whl_Speed_F fifoLvl;
    #endif
    #endif
    



  while(1){
    #if 0
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
    load.ADCAN_SP_Steering_Wheel_Angle = cpu_load;

    // get temperature values of the system
    // TODO: readout temps
    temp.ADCAN_EL_ECU_Temp_SWCU = 42;


    // get can fifo fill levels
    
    fifoLvl.ADCAN_SP_Wheel_Speed_FL = AD_CAN.getSWFiFoFillLevel(); // AD_CAN always present
    #ifdef MS4_CAN_PORT
      fifoLvl.ADCAN_SP_Wheel_Speed_FR = MS4_CAN.getSWFiFoFillLevel(); // MS4 not on all devices
    #endif


    // send all collected values to AD_CAN (if present)
    fifoLvl.build();
    temp.build();
    load.build();
    
    AD_CAN.sendMessage(&fifoLvl);
    AD_CAN.sendMessage(&temp);
    AD_CAN.sendMessage(&load);
    #endif // 0
    StallardOS::yield();
  }
}