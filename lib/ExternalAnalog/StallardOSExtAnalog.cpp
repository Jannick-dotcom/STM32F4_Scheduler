#include "StallardOSExtAnalog.hpp"

StallardOSExtAnalog::StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber) : 
spihandle(extADCSpiPort, 0)
// cs(3,PORTB, Input),
// drdy(3,PORTB,Input)
{
    if(adcNumber > 2 || channel > 15) return;
    cs = StallardOSGPIO(4+adcNumber,PORTB, Output, true);
    drdy = StallardOSGPIO(6+adcNumber, PORTB, Input);
    this->channel = channel;
    this->adcNumber = adcNumber;

    //Setup of the ADC, without channel setting
    registerWrite(0x00, 0b01000000); //Page 34f //CONFIG0
    registerWrite(0x01, 0b00000010); //Page 36  //CONFIG1
}

void StallardOSExtAnalog::registerWrite(uint8_t address, uint8_t value)
{
    uint8_t data[2];
    if(address > 0x9) return; //not valid register!

    data[0] = (0b0110 << 4) | (address & 0x0F);    //'011' -> register Write, '0' ->write single, register address 4 Bit
    data[1] = value;
    cs = 0;
    spihandle.send(data, sizeof(data));
    cs = 1;
}

uint8_t StallardOSExtAnalog::registerRead(uint8_t address)
{
    uint8_t data;
    if(address > 0x9) return 0; //Not valid register

    data = (0b0100 << 4) | (address & 0x0F);    //'010' -> register Read, '0' -> write singular register, register address
    cs = 0;
    spihandle.send(&data, sizeof(data));
    spihandle.receive(&data, sizeof(data), 0);
    cs = 1;
    return data;
}

uint16_t StallardOSExtAnalog::channelRead()
{
    uint8_t dataout, datain[2];
    dataout = (0b100 << 5); //Pulse convert command byte
    
    if(channel >= 0 && channel <= 7)
    {
        registerWrite(0x04, 1 << channel); //Select channel 0-7
    }
    else if(channel >= 8 && channel <= 15)
    {
        registerWrite(0x05, 1 << (channel - 7)); //Select channel 8-15
    }
    cs = 0;
    spihandle.send(&dataout, sizeof(dataout));  //Send pulse convert command
    cs = 1;
    while(drdy == true);   //Wait for conversion to be finished
    cs = 0;
    spihandle.receive(datain, sizeof(datain), 0); //Receive a 2 byte Analog Value
    cs = 1;
    return datain[0] << 8 | datain[1];
}

uint16_t StallardOSExtAnalog::getValue()
{
    uint16_t buf;
    this->sem.take();
    buf = channelRead();
    this->sem.give();
    return buf;
}