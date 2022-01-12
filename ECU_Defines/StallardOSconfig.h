/********************************************
 * User Customization
********************************************/
#define STOS_current_ECU_ID 1 //FCU
// #define STOS_current_ECU_ID 2 //RCU
// #define STOS_current_ECU_ID 3 //PDU
// #define STOS_current_ECU_ID 4 //SWCU

#define useFPU
//#define useMPU
//#define unprotectedBuild
#define countTasks 10
#define defaultSysTickFreq 1000 //[Hz]
#define runFreq 168 //[MHz]

// #define useSystickAltering  //Change the firing rate of Systick to maximize throughput

/////////////////////////////////////////////
//CAN-Network
#ifdef STM32F417xx
#define CAN1_t_pin 0
#define CAN1_r_pin 1
#define CAN1_t_port PORTD
#define CAN1_r_port PORTD
#define CAN2_t_pin 13
#define CAN2_r_pin 12
#define CAN2_t_port PORTB
#define CAN2_r_port PORTB
#endif

#ifdef STM32F415xx
#define CAN2_t_pin 13
#define CAN2_r_pin 12
#define CAN2_t_port PORTB
#define CAN2_r_port PORTB
#endif

#ifdef STM32F407xx
#define CAN1_t_pin 0
#define CAN1_r_pin 1
#define CAN1_t_port PORTD
#define CAN1_r_port PORTD
#define CAN2_t_pin 13
#define CAN2_r_pin 12
#define CAN2_t_port PORTB
#define CAN2_r_port PORTB
#endif

#ifdef STM32F446xx
#define CAN1_t_pin 0
#define CAN1_r_pin 1
#define CAN1_t_port PORTD
#define CAN1_r_port PORTD
#define CAN2_t_pin 13
#define CAN2_r_pin 12
#define CAN2_t_port PORTB
#define CAN2_r_port PORTB
#endif

#define CAN_FIFO_size 200    //[Messages] should be enough for 1 second of storing
/////////////////////////////////////////////

/////////////////////////////////////////////
// External SPI ADC
#define extADCSpiPort SPI2
#define SPI_GPIO_PORT PORTB
#define SPI_GPIO_PIN_MOSI 15
#define SPI_GPIO_PIN_MISO 14
#define SPI_GPIO_PIN_SCK 10 
/////////////////////////////////////////////