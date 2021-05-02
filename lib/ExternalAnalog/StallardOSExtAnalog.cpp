#include "StallardOSExtAnalog.hpp"

StallardOSExtAnalog::StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber) : 
spihandle(extADCSpiPort, 0)
// cs(3,PORTB, Input),
// drdy(3,PORTB,Input)
{
    cs = StallardOSGPIO(4+channel,PORTB, Output);
    drdy = StallardOSGPIO(6+channel, PORTB, Input);
    this->channel = channel;
}

void StallardOSExtAnalog::registerWrite(uint8_t address, uint8_t value)
{
    uint8_t data[2];
    if(address > 0x9) return; //not valid register!

    data[0] = (0b0110 << 4) | (address & 0x0F);    //'011' -> register Write, '0' ->write multiple, register address 4 Bit
    data[1] = value;
    // this->sem.take();
    this->spihandle.send(data, sizeof(data));
    // this->sem.give();
}

uint8_t StallardOSExtAnalog::registerRead(uint8_t address)
{
    uint8_t data;
    if(address > 0x9) return 0; //Not valid register

    data = (0b0100 << 4) | (address & 0x0F);
    // this->sem.take();
    spihandle.send(&data, sizeof(data));
    spihandle.receive(&data, sizeof(data), 0);
    // this->sem.give();
    return data;
}

uint16_t StallardOSExtAnalog::channelRead()
{
    uint8_t dataout, datain[2];

    dataout = (0b001 << 5);
    // this->sem.take();
    spihandle.send(&dataout, sizeof(dataout));
    spihandle.receive(datain, sizeof(datain), 0);
    // this->sem.give();
    return datain[0] << 8 | datain[1];
}

uint16_t StallardOSExtAnalog::getValue()
{
    this->sem.take();
    if(0 == drdy.read())
    {
        channelRead();
    }
    this->sem.give();
    return 0;
}