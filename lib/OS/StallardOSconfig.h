/********************************************
 * User Customization
********************************************/

#define sizeStack 300      //300 * uint32_t (Stack size for Tasks)
#define countTasks 2    //Autmatically counted by countfunctions.sh (only on linux)
#define defaultSysTickFreq 1000.0 //[Hz]
#define useSystickAltering  //Change the firing rate of Systick to maximize throughput
#define functionModifier (uint32_t)0xFFFFFFFE     //Use the function pointer with lowest bit zero
#define sysTickTicks (uint32_t)(SystemCoreClock / sysTickFreq)

#define CAN1_t_pin 12
#define CAN1_r_pin 11
#define CAN1_t_port PORTA
#define CAN1_r_port PORTA

#define CAN2_t_pin 1
#define CAN2_r_pin 1
#define CAN2_t_port PORTB
#define CAN2_r_port PORTB

#define CAN_FIFO_size 20    //[Messages]

/////////////////////////////////////////////