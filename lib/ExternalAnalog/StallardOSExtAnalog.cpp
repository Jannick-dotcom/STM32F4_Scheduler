#include "StallardOSExtAnalog.hpp"

// StallardOSSPI StallardOSExtAnalog::spihandle(extADCSpiPort, Normal, gpio(PORTB, 15), gpio(PORTB, 14), gpio(PORTB, 10));
uint8_t StallardOSExtAnalog::adcInitialized = 0;
// StallardOSSemaphore StallardOSExtAnalog::sem;
extern "C" volatile uint64_t usCurrentTimeSinceStart; //about 585 000 years of microsecond counting

StallardOSGPIO StallardOSExtAnalog::reset1(4, PORTD, Output, false);
StallardOSGPIO StallardOSExtAnalog::reset2(3, PORTD, Output, false);

StallardOSGPIO StallardOSExtAnalog::cs1(5, PORTB, Output, false);
StallardOSGPIO StallardOSExtAnalog::cs2(6, PORTB, Output, false);

StallardOSGPIO StallardOSExtAnalog::drdy1(7, PORTB, Output, false);
StallardOSGPIO StallardOSExtAnalog::drdy2(8, PORTB, Output, false);

StallardOSExtAnalog::StallardOSExtAnalog(uint8_t channel, uint8_t adcNumber) : spihandle(extADCSpiPort, Normal, gpio(PORTB, 15), gpio(PORTB, 14), gpio(PORTB, 10))
{
    if (adcNumber > 2 || channel > 15 || adcNumber == 0)
        return;
    this->channel = channel;
    this->adcNumber = adcNumber;

    //Setup of the ADC, without channel setting
    if ((adcInitialized & adcNumber) != 0)
        return;
    if (adcNumber == 1)
        reset1 = 1;
    else if (adcNumber == 2)
        reset2 = 1;
    StallardOS::delay(100);
    registerWrite(0x00, 0b00000000); //Page 34f //CONFIG0
    registerWrite(0x01, 0b00000011); //Page 36  //CONFIG1

    // volatile uint16_t test;
    // for(uint8_t i = 0; i < 10; i++)
    // {
    //     test = registerRead(i);
    // }
    for (uint8_t i = 0; i < 16; i++) //Fix start pin with only reading from all channels
    {
        channelRead(i);
    }
    offset = channelRead(16);
    adcInitialized |= adcNumber;
}

void StallardOSExtAnalog::registerWrite(uint8_t address, uint8_t value)
{
    uint8_t data[2];
    if (address > 0x9)
        return; //not valid register!

    data[0] = (0b0110 << 4) | (address & 0x0F); //'011' -> register Write, '0' ->write single, register address 4 Bit
    data[1] = value;
    if (adcNumber == 1)
        cs1 = 0;
    else if (adcNumber == 2)
        cs2 = 0;
    spihandle.send(data, sizeof(data));
    if (adcNumber == 1)
        cs1 = 1;
    else if (adcNumber == 2)
        cs2 = 1;
}

uint8_t StallardOSExtAnalog::registerRead(uint8_t address)
{
    uint8_t data;
    if (address > 0x9)
        return 0; //Not valid register

    data = (0b0100 << 4) | (address & 0x0F); //'010' -> register Read, '0' -> write singular register, register address
    if (adcNumber == 1)
        cs1 = 0;
    else if (adcNumber == 2)
        cs2 = 0;
    spihandle.send(&data, sizeof(data));
    spihandle.receive(&data, sizeof(data), HAL_MAX_DELAY);
    if (adcNumber == 1)
        cs1 = 1;
    else if (adcNumber == 2)
        cs2 = 1;
    return data;
}

uint16_t StallardOSExtAnalog::channelRead(uint8_t channel)
{
    uint8_t dataout, datain[3];
    dataout = (0b100 << 5); //Pulse convert command byte
    if (channel >= 0 && channel < 8)
    {
        registerWrite(0x04, 1 << channel); //Select channel 0-7
        registerWrite(0x05, 0);
        registerWrite(0x06, 0);
    }
    else if (channel >= 8 && channel < 16)
    {
        registerWrite(0x05, 1 << (channel - 8)); //Select channel 8-15
        registerWrite(0x04, 0);
        registerWrite(0x06, 0);
    }
    else //offset Reading
    {
        registerWrite(0x04, 0);
        registerWrite(0x05, 0);
        registerWrite(0x06, 0x01);
    }
    if (adcNumber == 1)
        cs1 = 0;
    else if (adcNumber == 2)
        cs2 = 0;
    spihandle.send(&dataout, sizeof(dataout)); //Send pulse convert command
    if (adcNumber == 1)
        cs1 = 1;
    else if (adcNumber == 2)
        cs2 = 1;
    uint64_t timestart = usCurrentTimeSinceStart;

    if (adcNumber == 1)
    {
        while (drdy1 == true) //Wait for the drdy pin or timeout
        {
            if ((usCurrentTimeSinceStart - timestart) > 100000)
            {
                return 0; //No reading error!!!!
            }
        }
    }
    else if(adcNumber == 2)
    {
        while (drdy2 == true) //Wait for the drdy pin or timeout
        {
            if ((usCurrentTimeSinceStart - timestart) > 100000)
            {
                return 0; //No reading error!!!!
            }
        }
    }
    if (adcNumber == 1)
        cs1 = 0;
    else if (adcNumber == 2)
        cs2 = 0;
    dataout = 0b00110000; //channel read command
    spihandle.send(&dataout, sizeof(dataout));
    spihandle.receive(datain, sizeof(datain), HAL_MAX_DELAY); //Receive a 2 byte Analog Value
    if (adcNumber == 1)
        cs1 = 1;
    else if (adcNumber == 2)
        cs2 = 1;
    // cs = 0; //Toggle to reset spi interface of ADC
    // cs = 1;
    // registerWrite(0x04, 0);
    // registerWrite(0x05, 0);
    // registerWrite(0x06, 0);
    return datain[1] << 8 | datain[2];
}

int16_t StallardOSExtAnalog::getValue()
{
    int16_t buf;
#ifdef contextSwitch
    sem.take();
#endif
    buf = channelRead(this->channel);
#ifdef contextSwitch
    sem.give();
#endif
    return buf - offset;
}