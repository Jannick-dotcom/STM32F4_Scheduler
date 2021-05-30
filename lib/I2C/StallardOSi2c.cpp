#include "StallardOSi2c.hpp"
/**
 * Create a i2c insance.
 *
 * @param instance i2c to use
 * @param freq frequency of the transmission
 */
StallardOSi2c::StallardOSi2c(I2C_TypeDef *instance, uint32_t freq)
{
    #ifdef contextSwitch
    this->sem.take();
    #endif
    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_I2C2_CLK_ENABLE();
    __HAL_RCC_I2C3_CLK_ENABLE();
    hi2c.Instance = instance;
    hi2c.Init.ClockSpeed = freq;
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
    #ifdef contextSwitch
    this->sem.give();
    #endif
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
#ifdef contextSwitch
    this->sem.take();
#endif
    if (data == nullptr)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        return;
    }
    HAL_I2C_Master_Transmit(&hi2c, addr, data, bytes, 0);
#ifdef contextSwitch
    this->sem.give();
#endif
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
#ifdef contextSwitch
    this->sem.take();
#endif
    if (data == nullptr)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        return 0;
    }
    HAL_I2C_Master_Receive(&hi2c, addr, data, bytes, 0);
#ifdef contextSwitch
    this->sem.give();
#endif
    return 1;
}
