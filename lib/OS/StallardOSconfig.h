/********************************************
 * User Customization
********************************************/

#define contextSwitch

#define sizeStack 300      //300 * 4 Byte (Stack size for Tasks)
#define countTasks 10
#define defaultSysTickFreq 100000 //[Hz] -> 100kHz for 10µs time quantum
#define externalOszillator 25 //[MHz]
// #define useSystickAltering  //Change the firing rate of Systick to maximize throughput

#define CAN1_t_pin 12
#define CAN1_r_pin 11
#define CAN1_t_port PORTA
#define CAN1_r_port PORTA

#define CAN2_t_pin 12
#define CAN2_r_pin 11
#define CAN2_t_port PORTB
#define CAN2_r_port PORTB

#define CAN_FIFO_size 200    //[Messages] should be enough for 1 second of storing

/////////////////////////////////////////////