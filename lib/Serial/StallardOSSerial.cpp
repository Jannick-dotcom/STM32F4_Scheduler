#include "StallardOSSerial.hpp"
/**
 * create a serial instance.
 *
 * @param serPort which Serial to use
 * @param baud baud rate
 */
StallardOSSerial::StallardOSSerial(USART_TypeDef *serPort, uint32_t baud)
{
    this->sem.take();
    if(baud == 0)
    {
        return;
    }
    huart.Instance = serPort;
    huart.Init.BaudRate = baud;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        this->sem.give();
        StallardOSGeneralFaultHandler();
    }
    this->sem.give();
}

/**
 * send Data.
 *
 * @param dat Data to be sent
 * @param bytes Number of bytes to send
 */
void StallardOSSerial::send(const char *dat, uint16_t bytes)
{
    this->sem.take();
    if(dat == nullptr)
    {
        this->sem.give();
        return;
    }
    HAL_UART_Transmit(&huart, (uint8_t*)dat, bytes, 0xFFFF);
    this->sem.give();
}

/**
 * read Data.
 *
 * @param[out] dat container for the read data
 * @param bytes number of bytes to read
 */
void StallardOSSerial::read(char *dat, uint16_t bytes)
{
    this->sem.take();
    if(dat == nullptr)
    {
        this->sem.give();
        return;
    }
    HAL_UART_Receive(&huart, (uint8_t*)dat, bytes, 0xFFFF);
    this->sem.give();
}
