#include "StallardOSTasks.hpp"
#include "StallardOS.hpp"

#ifdef useSFOC
  #include "SFOC.hpp"
  stack_T taskSFOCStack[256]; /* align to size in Byte */
#endif // useSFOC

// private kernel variable
extern volatile struct function_struct* volatile taskMainStruct;
extern struct function_struct taskArray[];

// public variables (declared in header)
stack_T taskmainStack[256];
stack_T taskPerfmonStack[2048];

/**
 * Waste Time if all tasks are in delay.
 *
 * @param 
 * @return
 */
#ifdef BusyLoop
void taskMain(void)
{
  while (1);
}
#endif

#ifndef notHaveCan
void taskPerfmon(void){

    struct function_struct *task;
    uint64_t total_calc_time_us;
    uint64_t idle_calc_time_us;
    uint8_t cpu_load;

    // pointers to status messages
    CAN_Signal<uint8_t>* load;
    CAN_Signal<uint8_t>* can1_tx;
    CAN_Signal<uint8_t>* can2_tx;
    CAN_Signal<uint8_t>* ecu_tmp;


    // output can messages (defined per ECU)
    #if STOS_current_ECU_ID==ECU_ID_FCU
      STOS_CAN_PDU_FCU_Health health;
      load = &health.FCU_CPU_Load;
      can1_tx = &health.FCU_CAN1_Rx_Fifo_Lvl;
      can2_tx = &health.FCU_CAN2_Rx_Fifo_Lvl;
      ecu_tmp = &health.FCU_Temp;
    #elif STOS_current_ECU_ID==ECU_ID_RCU
      STOS_CAN_PDU_RCU_Health health;
      load = &health.RCU_CPU_Load;
      can1_tx = &health.RCU_CAN1_Rx_Fifo_Lvl;
      can2_tx = &health.RCU_CAN2_Rx_Fifo_Lvl;
      ecu_tmp = &health.RCU_Temp;
    #elif STOS_current_ECU_ID==ECU_ID_PDU
      STOS_CAN_PDU_PDU_Health health;
      load = &health.PDU_CPU_Load;
      can1_tx = &health.PDU_CAN1_Rx_Fifo_Lvl;
      can2_tx = &health.PDU_CAN2_Rx_Fifo_Lvl;
      ecu_tmp = &health.PDU_Temp;
    #elif STOS_current_ECU_ID==ECU_ID_SWCU
      STOS_CAN_PDU_SWCU_Health health;
      load = &health.SWCU_CPU_Load;
      can1_tx = &health.SWCU_CAN1_Rx_Fifo_Lvl;
      can2_tx = &health.SWCU_CAN2_Rx_Fifo_Lvl;
      ecu_tmp = &health.SWCU_Temp;
    #elif STOS_current_ECU_ID==ECU_ID_BMS_HYB
      STOS_CAN_PDU_BMS_HYB_Health health;
      load = &health.BMS_HYB_CPU_Load;
      can1_tx = &health.BMS_HYB_CAN1_Rx_Fifo_Lvl;
      can2_tx = &health.BMS_HYB_CAN2_Rx_Fifo_Lvl;
      ecu_tmp = &health.BMS_HYB_Temp;
    #endif
    

  while(1){
    // get cpu load of the system
    total_calc_time_us = 0;
    idle_calc_time_us = 0;

    // get idle task cpu load and compare this to the total time
    idle_calc_time_us = taskMainStruct->perfmon_exec_time_us;
    taskMainStruct->perfmon_exec_time_us = 0;

    // iterate over all tasks to get used cpu time since last scan
    for(uint16_t i = 0; i < countTasks; i++)
    {
      task = &(taskArray[i]);
      total_calc_time_us += task->perfmon_exec_time_us;
      task->perfmon_exec_time_us = 0;
    }

    cpu_load = (1000*total_calc_time_us) / (idle_calc_time_us + total_calc_time_us);
    *load = cpu_load;
    

    // get temperature values of the system
    // TODO: readout temps
    *ecu_tmp = 42;


    // get can fifo fill levels
    *can1_tx = AD_CAN.getSWFiFoFillLevel()/(float)CAN_FIFO_size; // AD_CAN always present
    #ifdef MS4_CAN_PORT
      *can2_tx = MS4_CAN.getSWFiFoFillLevel()/(float)CAN_FIFO_size; // MS4 not on all devices
    #endif


    // send all collected values to AD_CAN (if present)
    health.build();
    
    AD_CAN.sendMessage(&health);
    StallardOS::yield();
  }
}
#endif // notHaveCan

#ifdef useSFOC
  void taskSFOC(void){
    SFOC_Status ret;
    SFOC::setup(0); // no time-out in OS context

    while(1){
      ret = SFOC::stm_iterate();

      if(ret != SFOC_CONTINUE){
        // exit task
        break;
      }

      StallardOS::yield();
    }
  }
#endif