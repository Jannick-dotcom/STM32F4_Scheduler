#include "StallardOSSerial.hpp"
/**
 * create a serial instance.
 *
 * @param serPort which Serial to use
 * @param baud baud rate
 */
StallardOSSerial::StallardOSSerial(USART_TypeDef *serPort, uint32_t baud)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    if (baud == 0)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        return;
    }
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_USART3_CLK_ENABLE();
    __HAL_RCC_USART6_CLK_ENABLE();
    __HAL_RCC_UART4_CLK_ENABLE();
    __HAL_RCC_UART5_CLK_ENABLE();
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
#ifdef contextSwitch
        this->sem.give();
#endif
        StallardOSGeneralFaultHandler();
    }
#ifdef contextSwitch
    this->sem.give();
#endif
}

/**
 * send Data.
 *
 * @param dat Data to be sent
 * @param bytes Number of bytes to send
 */
void StallardOSSerial::send(const char *dat, uint16_t bytes)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    if (dat == nullptr)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        return;
    }
    HAL_UART_Transmit(&huart, (uint8_t *)dat, bytes, 0xFFFF);
#ifdef contextSwitch
    this->sem.give();
#endif
}

/**
 * read Data.
 *
 * @param[out] dat container for the read data
 * @param bytes number of bytes to read
 */
void StallardOSSerial::read(char *dat, uint16_t bytes)
{
#ifdef contextSwitch
    this->sem.take();
#endif
    if (dat == nullptr)
    {
#ifdef contextSwitch
        this->sem.give();
#endif
        return;
    }
    HAL_UART_Receive(&huart, (uint8_t *)dat, bytes, 0xFFFF);
#ifdef contextSwitch
    this->sem.give();
#endif
}
