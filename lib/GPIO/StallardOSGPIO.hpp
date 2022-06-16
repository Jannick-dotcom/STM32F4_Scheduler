#ifndef StallardOS_GPIO_h
#define StallardOS_GPIO_h

#include "StallardOSHelpers.h"
#include <stdint.h>
#include "StallardOSsem.hpp"
#include "StallardOSClass.hpp"
#include "math.h"

extern "C" void StallardOSGeneralFaultHandler();

typedef enum ports
{
    PORTA = 0,
    PORTB,
    PORTC,
    PORTD,
    PORTE
    #ifdef STM32F4xxxx
    ,
    PORTF,
    PORTG,
    PORTH,
    PORTI
    #endif
} ports;

typedef enum interruptNumber
{
    P0 = EXTI0_IRQn,
    P1 = EXTI1_IRQn,
    P2 = EXTI2_IRQn,
    P3 = EXTI3_IRQn,
    P4 = EXTI4_IRQn,
    P5 = EXTI9_5_IRQn,
    P6 = EXTI9_5_IRQn,
    P7 = EXTI9_5_IRQn,
    P8 = EXTI9_5_IRQn,
    P9 = EXTI9_5_IRQn,
    P10 = EXTI15_10_IRQn,
    P11 = EXTI15_10_IRQn,
    P12 = EXTI15_10_IRQn,
    P13 = EXTI15_10_IRQn,
    P14 = EXTI15_10_IRQn,
    P15 = EXTI15_10_IRQn
} interruptNumber;

struct gpio
{
    gpio(ports po, uint8_t pi)
    {
        port = po;
        pin = pi;
    }
    ports port;
    uint8_t pin;
};

typedef enum pinDir
{
    Analog = GPIO_MODE_ANALOG,
    Input = GPIO_MODE_INPUT,
    Output = GPIO_MODE_OUTPUT_PP,
    OutputOD = GPIO_MODE_OUTPUT_OD,
    AFOD = GPIO_MODE_AF_OD,
    AFPP = GPIO_MODE_AF_PP,
    InputITFalling = GPIO_MODE_IT_FALLING,
    InputITRising = GPIO_MODE_IT_RISING,
    InputITChange = GPIO_MODE_IT_RISING_FALLING
} pinDir;

typedef enum pullMode
{
    nopull = GPIO_NOPULL,
    pulldown = GPIO_PULLDOWN,
    pullup = GPIO_PULLUP
} pullMode;

class StallardOSGPIO : public NonAssignable
{
private:
    bool state;
    uint32_t pin;
    ports port;
    pinDir dir;
    pullMode pull;
    StallardOSSemaphore sem;
    // static uint32_t functions[16];

public:
    #ifdef STM32F417xx
    const GPIO_TypeDef *portsToGPIOBase[9] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI};
    #elif defined(STM32F4xxxx)
    const GPIO_TypeDef *portsToGPIOBase[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
    #elif defined(STM32F1xxxx)
    const GPIO_TypeDef *portsToGPIOBase[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};
    #endif

    StallardOSGPIO(
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Direction*/ pinDir dir,
        /*InitialState*/ bool initialState = 0,
        /*PullResistor*/ pullMode pull = nopull
        );
    StallardOSGPIO(
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Direction*/ pinDir dir,
        /*PullResistor*/ pullMode pull,
        /*AlternateFunction*/ uint32_t alternate);
    ~StallardOSGPIO(); //Destructor

    void setISR(void (*function)());
    bool read();
    bool write(bool state);
    bool operator=(bool state);           //Operator for writing on the pin
    bool operator!();                     //Inverting the state
    
    bool operator&&(StallardOSGPIO &ref); //Logical operator
    bool operator||(StallardOSGPIO &ref); //Logical operator
    bool operator!=(StallardOSGPIO &ref); //Comparison
    bool operator==(StallardOSGPIO &ref);

    bool operator&&(bool ref); //Logical operator
    bool operator||(bool ref); //Logical operator
    bool operator!=(bool ref); //Comparison
    bool operator==(bool ref);
};

#endif