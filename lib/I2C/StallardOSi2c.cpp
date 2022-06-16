#include "StallardOSi2c.hpp"

// GPIO/AFIO Regs
constexpr static uint32_t afioBase = 0x40010000UL;
constexpr static uint32_t mapr = afioBase + 0x004; // alternate pin function mapping

/**
 * Create a i2c insance.
 *
 * @param instance i2c to use
 * @param freq frequency of the transmission
 */
StallardOSi2c::StallardOSi2c(I2C_TypeDef *instance, uint32_t freq):
scl(6, PORTB, AFOD, false, pullup),
sda(7, PORTB, AFOD, false, pullup)
{   
    this->sem.take();
    __HAL_RCC_I2C1_CLK_ENABLE();
    #ifdef STM32F4xxxx
    __HAL_RCC_I2C3_CLK_ENABLE();
    #endif
    hi2c.Instance = instance;
    hi2c.Init.ClockSpeed = freq;
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    hi2c.State = HAL_I2C_STATE_RESET;
    if (HAL_I2C_Init(&hi2c) != HAL_OK)
    {
        this->sem.give();
        StallardOSGeneralFaultHandler();
    }
    
    this->sem.give();
    
}

/**
 * Send i2c data.
 *
 * @param addr  to which address to send
 * @param data  data to send
 * @param bytes size of the data container
 */
uint8_t StallardOSi2c::write(uint16_t addr, uint8_t *data, uint16_t bytes)
{
    bool retVal = false;
    this->sem.take();

    if (data == nullptr)
    {

        this->sem.give();

        return 0;
    }
    retVal = HAL_I2C_Master_Transmit(&hi2c, addr, data, bytes, 100);

    this->sem.give();
    return retVal;
}

/**
 * receive i2c data.
 *
 * @param addr  from which address to receive
 * @param[out] data  received data
 * @param bytes size of the data container
 * @return if data received true, false otherwise
 */
uint8_t StallardOSi2c::read(uint16_t addr, uint8_t *data, uint16_t bytes)
{
    bool retVal = false;
    this->sem.take();

    if (data == nullptr)
    {

        this->sem.give();

        return 0;
    }
    retVal = HAL_I2C_Master_Receive(&hi2c, addr, data, bytes, 1000);

    this->sem.give();

    return retVal;
}
