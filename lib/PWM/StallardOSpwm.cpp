#include "StallardOSpwm.hpp"

StallardOSpwm::StallardOSpwm(uint8_t number, ports port, uint16_t freq)
{
    this->gpio = new StallardOSGPIO(number, port, Output);
    this->freq = freq;
}

StallardOSpwm::~StallardOSpwm()
{
    delete this->gpio;
}

uint32_t StallardOSpwm::operator=(uint32_t duty)
{
    this->duty = duty;
    return duty;
}