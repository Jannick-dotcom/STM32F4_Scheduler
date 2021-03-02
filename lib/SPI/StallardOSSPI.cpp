#include "StallardOSSPI.hpp"

StallardOSSPI::StallardOSSPI(SPI_TypeDef *inst, uint32_t baud)
{
    handle.Instance = inst;
    handle.Init.Mode = SPI_MODE_MASTER; //SPI_MODE_SLAVE
    handle.Init.Direction = SPI_DIRECTION_2LINES; //SPI_DIRECTION_1LINE, SPI_DIRECTION_2LINES_RXONLY
    handle.Init.DataSize = SPI_DATASIZE_8BIT; //SPI_DATASIZE_16BIT
    handle.Init.CLKPolarity = SPI_POLARITY_LOW; //SPI_POLARITY_HIGH
    handle.Init.CLKPhase = SPI_PHASE_1EDGE; //SPI_PHASE_2EDGE
    handle.Init.NSS = SPI_NSS_HARD_OUTPUT;
    handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; //SPI_BAUDRATEPRESCALER
    handle.Init.FirstBit = SPI_FIRSTBIT_MSB; //SPI_FIRSTBIT_LSB
    handle.Init.TIMode = SPI_TIMODE_DISABLE; //SPI_TIMODE_ENABLE
    handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; //SPI_CRCCALCULATION_ENABLE
    handle.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&handle) != HAL_OK)
    {
        StallardOSGeneralFaultHandler();
    }
}

void StallardOSSPI::send(uint8_t *data, uint16_t size)
{
    sem.take();
    HAL_SPI_Transmit(&handle, data, size, 0);
    sem.give();
}

void StallardOSSPI::receive(uint8_t *data, uint16_t size, uint16_t timeout)
{
    sem.take();
    HAL_SPI_Receive(&handle, data, size, timeout);
    sem.give();
}