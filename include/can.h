#ifndef JannixCAN_h
#define JannixCAN_h

#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

extern const GPIO_TypeDef *portsToGPIOBase[];
typedef enum ports
{
    PORTA = 0,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF,
    PORTG
} ports;

typedef enum pinDir
{
    Input = GPIO_MODE_INPUT,
    Output = GPIO_MODE_OUTPUT_PP,
    Analog = GPIO_MODE_ANALOG
} pinMode;

typedef enum pullMode
{
    nopull = GPIO_NOPULL,
    pullup = GPIO_PULLUP,
    pulldown = GPIO_PULLDOWN
} pullMode;

class JannixCAN
{
private:
    uint8_t state;
    uint32_t pin;
    ports port;
    pinDir dir;
    pullMode pull;

public:
    JannixCAN(
        /*Portnumber*/ uint8_t number,
        /*Portname*/ ports port,
        /*Direction*/ pinDir dir,
        /*PullResistor*/ pullMode pull = nopull);

    uint16_t operator=(bool state);                                            //Operator for writing on the pin
    uint16_t operator!() { return !this->state; };                             //Inverting the state
    uint16_t operator&&(JannixCAN &ref) { return this->state && ref.state; }; //Logical operator
    uint16_t operator||(JannixCAN &ref) { return this->state || ref.state; }; //Logical operator
    uint16_t operator!=(JannixCAN &ref) { return this->state != ref.state; }; //Comparison
    uint16_t operator<(JannixCAN &ref) { return this->state < ref.state; };
    uint16_t operator>(JannixCAN &ref) { return this->state > ref.state; };
    uint16_t operator<=(JannixCAN &ref) { return this->state <= ref.state; };
    uint16_t operator>=(JannixCAN &ref) { return this->state >= ref.state; };
    uint16_t operator==(JannixCAN &ref) { return this->state == ref.state; };
};

#endif