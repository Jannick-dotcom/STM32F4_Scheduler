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
    bool operator=(bool state);                                            //Operator for writing on the pin
    bool operator!() { return !this->state; };                             //Inverting the state
    bool operator&&(const StallardOSGPIO &ref) { return this->state && ref.state; }; //Logical operator
    bool operator||(const StallardOSGPIO &ref) { return this->state || ref.state; }; //Logical operator
    bool operator!=(const StallardOSGPIO &ref) { return this->state != ref.state; }; //Comparison
    bool operator<(const StallardOSGPIO &ref) { return this->state < ref.state; };
    bool operator>(const StallardOSGPIO &ref) { return this->state > ref.state; };
    bool operator<=(const StallardOSGPIO &ref) { return this->state <= ref.state; };
    bool operator>=(const StallardOSGPIO &ref) { return this->state >= ref.state; };
    bool operator==(const StallardOSGPIO &ref) { return this->state == ref.state; };
};

#endif