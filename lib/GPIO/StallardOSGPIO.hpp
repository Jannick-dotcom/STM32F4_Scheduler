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
    Output = GPIO_MODE_OUTPUT_PP
} pinDir;

typedef enum pullMode
{
    nopull = GPIO_NOPULL,
    pullup = GPIO_PULLUP,
    pulldown = GPIO_PULLDOWN
} pullMode;


class StallardOSGPIO
{
private:
    uint8_t state;
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
    operator int() {return state;};
    uint16_t operator=(bool state);                                            //Operator for writing on the pin
    uint16_t operator!() { return !this->state; };                             //Inverting the state
    uint16_t operator&&(StallardOSGPIO &ref) { return this->state && ref.state; }; //Logical operator
    uint16_t operator||(StallardOSGPIO &ref) { return this->state || ref.state; }; //Logical operator
    uint16_t operator!=(StallardOSGPIO &ref) { return this->state != ref.state; }; //Comparison
    uint16_t operator<(StallardOSGPIO &ref) { return this->state < ref.state; };
    uint16_t operator>(StallardOSGPIO &ref) { return this->state > ref.state; };
    uint16_t operator<=(StallardOSGPIO &ref) { return this->state <= ref.state; };
    uint16_t operator>=(StallardOSGPIO &ref) { return this->state >= ref.state; };
    uint16_t operator==(StallardOSGPIO &ref) { return this->state == ref.state; };
};

#endif