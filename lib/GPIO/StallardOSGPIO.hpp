#ifndef StallardOS_GPIO_h
#define StallardOS_GPIO_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>
#include "StallardOSsem.hpp"

extern "C" void StallardOSGeneralFaultHandler();

typedef enum ports
{
    PORTA = 0,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF,
    PORTG,
    PORTH,
    PORTI
} ports;

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
    AFPP = GPIO_MODE_AF_PP
} pinDir;

typedef enum pullMode
{
    nopull = GPIO_NOPULL,
    pulldown = GPIO_PULLDOWN,
    pullup = GPIO_PULLUP
} pullMode;

class StallardOSGPIO
{
private:
    bool state;
    uint32_t pin;
    ports port;
    pinDir dir;
    pullMode pull;
    StallardOSSemaphore sem;

public:
    #ifdef STM32F417xx
    const GPIO_TypeDef *portsToGPIOBase[9] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI};
    #else
    const GPIO_TypeDef *portsToGPIOBase[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
    #endif

    StallardOSGPIO();
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
    bool read();
    bool write(bool state);
    bool operator=(bool state);           //Operator for writing on the pin
    bool operator!();                     //Inverting the state
    
    bool operator&&(StallardOSGPIO &ref); //Logical operator
    bool operator||(StallardOSGPIO &ref); //Logical operator
    bool operator!=(StallardOSGPIO &ref); //Comparison
    // bool operator<(StallardOSGPIO &ref);
    // bool operator>(StallardOSGPIO &ref);
    // bool operator<=(StallardOSGPIO &ref);
    // bool operator>=(StallardOSGPIO &ref);
    bool operator==(StallardOSGPIO &ref);

    bool operator&&(bool ref); //Logical operator
    bool operator||(bool ref); //Logical operator
    bool operator!=(bool ref); //Comparison
    // bool operator<(bool ref);
    // bool operator>(bool ref);
    // bool operator<=(bool ref);
    // bool operator>=(bool ref);
    bool operator==(bool ref);
};

#endif