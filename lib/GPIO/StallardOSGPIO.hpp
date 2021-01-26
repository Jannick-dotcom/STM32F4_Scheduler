#ifndef StallardOS_GPIO_h
#define StallardOS_GPIO_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

extern const GPIO_TypeDef *portsToGPIOBase[];

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

typedef enum pinDir
{
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

public:
    StallardOSGPIO(
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Direction*/ pinDir dir,
        /*PullResistor*/ pullMode pull = nopull);
    StallardOSGPIO(
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Direction*/ pinDir dir,
        /*PullResistor*/ pullMode pull,
        uint32_t alternate);
    bool read();
    bool write(bool state);
    bool operator=(bool state);                                                //Operator for writing on the pin
    bool operator!();                                 //Inverting the state
    
    bool operator&&(StallardOSGPIO &ref); //Logical operator
    bool operator||(StallardOSGPIO &ref); //Logical operator
    bool operator!=(StallardOSGPIO &ref); //Comparison
    bool operator<(StallardOSGPIO &ref);
    bool operator>(StallardOSGPIO &ref);
    bool operator<=(StallardOSGPIO &ref);
    bool operator>=(StallardOSGPIO &ref);
    bool operator==(StallardOSGPIO &ref);
};

#endif