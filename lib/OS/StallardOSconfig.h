/********************************************
 * User Customization
********************************************/

#define sizeStack 300      //300 * uint32_t
#define countTasks 2
#define defaultSysTickFreq 1000.0 //[Hz]
#define useSystickAltering
#define functionModifier (uint32_t)0xFFFFFFFE     //Use the function pointer with lowest bit zero
#define sysTickTicks (uint32_t)(SystemCoreClock / sysTickFreq)

#define CAN1_t_pin 1////////////////////!!!!
#define CAN1_r_pin 1
#define CAN2_t_pin 1
#define CAN2_r_pin 1
#define CAN_FIFO_size 20    //[Messages]

/////////////////////////////////////////////