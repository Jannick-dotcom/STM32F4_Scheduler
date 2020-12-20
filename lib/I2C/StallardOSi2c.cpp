#include "StallardOSi2c.hpp"
/**
 * Create a i2c insance.
 *
 * @param instance i2c to use
 */
StallardOSi2c::StallardOSi2c(I2C_TypeDef *instance)
{
    hi2c.Instance = instance;
    hi2c.Init.ClockSpeed = 100000; //100 kHz
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }
}

/**
 * Send i2c data.
 *
 * @param addr  to which address to send
 * @param data  data to send
 * @param bytes size of the data container
 */
void StallardOSi2c::write(uint16_t addr, uint8_t *data, uint16_t bytes)
{
    if(data == nullptr)
    {
        return;
    }
    HAL_I2C_Master_Transmit(&hi2c, addr, data, bytes, 0);
}

uint8_t StallardOSi2c::read(uint16_t addr, uint8_t *data, uint16_t bytes)
{
    if(data == nullptr)
    {
        return 0;
    }
    HAL_I2C_Master_Receive(&hi2c, addr, data, bytes, 0);
    return 1;
}
