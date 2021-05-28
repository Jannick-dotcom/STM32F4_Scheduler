/********************************************
 * User Customization
********************************************/
#define STOS_current_ECU_ID 2
#define contextSwitch

#define sizeStack 512      //300 * 4 Byte (Stack size for Tasks)
#define countTasks 3
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

#define CAN_debug

#define extADCSpiPort SPI2
#define SPI_GPIO_PORT PORTB
#define SPI_GPIO_PIN_MOSI 15
#define SPI_GPIO_PIN_MISO 14
#define SPI_GPIO_PIN_SCK 10 

/////////////////////////////////////////////