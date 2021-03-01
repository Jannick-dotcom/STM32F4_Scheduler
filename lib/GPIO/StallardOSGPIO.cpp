#include "StallardOSGPIO.hpp"

const GPIO_TypeDef *portsToGPIOBase[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI};
extern "C" void StallardOSGeneralFaultHandler();


StallardOSGPIO::StallardOSGPIO()
{
    
}

/**
 * Create a gpio pin.
 *
 * @param number which number on the Port to use
 * @param port   which port to use
 * @param dir    input or output
 * @param pull   internal pull-up or pull-down
 */
StallardOSGPIO::StallardOSGPIO(uint8_t number, ports port, pinDir dir, bool initialState, pullMode pull)
{
    this->sem.take();
    if (number > 31) //Error check
    {
        this->sem.give();
        StallardOSGeneralFaultHandler();
    }

    this->pin = number;
    this->port = port;
    this->dir = dir;
    this->pull = pull;

    this->state = 0;

    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();
    __GPIOF_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();
    __GPIOH_CLK_ENABLE();
    __GPIOI_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = 1 << this->pin;
    GPIO_InitStruct.Mode = this->dir;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = this->pull;

    HAL_GPIO_WritePin((GPIO_TypeDef *)portsToGPIOBase[this->port], 1 << this->pin, GPIO_PinState(initialState));
    HAL_GPIO_Init((GPIO_TypeDef *)portsToGPIOBase[this->port], &GPIO_InitStruct);
    this->sem.give();
}

/**
 * Create a gpio pin.
 *
 * @param number which number on the Port to use
 * @param port   which port to use
 * @param dir    input or output
 * @param pull   internal pull-up or pull-down
 * @param alternate alternative to an normal gpio port
 */
StallardOSGPIO::StallardOSGPIO(uint8_t number, ports port, pinDir dir, pullMode pull, uint32_t alternate)
{
    this->sem.take();
    if (number > 31) //Error check
    {
        this->sem.give();
        StallardOSGeneralFaultHandler();
    }

    this->pin = number;
    this->port = port;
    this->dir = dir;
    this->pull = pull;

    this->state = 0;

    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();
    __GPIOF_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();
    __GPIOH_CLK_ENABLE();
    __GPIOI_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = 1 << this->pin;
    GPIO_InitStruct.Mode = this->dir;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = this->pull;
    GPIO_InitStruct.Alternate = alternate;

    HAL_GPIO_Init((GPIO_TypeDef *)portsToGPIOBase[this->port], &GPIO_InitStruct);
    this->sem.give();
}

StallardOSGPIO::~StallardOSGPIO()
{
    HAL_GPIO_DeInit((GPIO_TypeDef *)portsToGPIOBase[this->port], this->pin);
}

/**
 * Change the pin state.
 *
 * @param state new state, high or low
 * @return new state
 */
bool StallardOSGPIO::operator=(bool state)
{
    return this->write(state);
}

bool StallardOSGPIO::read()
{
    this->sem.take();
    if (this->dir == Input)
    {
        this->sem.give();
        return HAL_GPIO_ReadPin((GPIO_TypeDef *)portsToGPIOBase[this->port], 1 << this->pin);
    }
    else if (this->dir == Output)
    {
        this->sem.give();
        return this->state;
    }
    this->sem.give();
    return 0;
}

bool StallardOSGPIO::write(bool state)
{
    this->sem.take();
    if (this->dir == Output)
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)portsToGPIOBase[this->port], 1 << this->pin, GPIO_PinState(state));
        this->state = state;
        this->sem.give();
        return this->state;
    }
    else if (this->dir == Input)
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = 1 << this->pin;
        GPIO_InitStruct.Mode = this->dir;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Pull = pullMode(int(state)+1);

        HAL_GPIO_Init((GPIO_TypeDef *)portsToGPIOBase[this->port], &GPIO_InitStruct);
        this->sem.give();
        return state;
    }
}

bool StallardOSGPIO::operator!()
{
    return !this->read();
} 

bool StallardOSGPIO::operator&&(StallardOSGPIO &ref)
{
    return this->read() && ref.read();
} 

bool StallardOSGPIO::operator||(StallardOSGPIO &ref)
{
    return this->read() || ref.read();
} 

bool StallardOSGPIO::operator!=(StallardOSGPIO &ref)
{
    return this->write(!ref.read());
} 

bool StallardOSGPIO::operator<(StallardOSGPIO &ref)
{
    return this->read() < ref.read();
}
bool StallardOSGPIO::operator>(StallardOSGPIO &ref)
{
    return this->read() > ref.read();
}
bool StallardOSGPIO::operator<=(StallardOSGPIO &ref)
{
    return this->read() <= ref.read();
}
bool StallardOSGPIO::operator>=(StallardOSGPIO &ref)
{
    return this->read() >= ref.read();
}
bool StallardOSGPIO::operator==(StallardOSGPIO &ref)
{
    return this->read() == ref.read();
}