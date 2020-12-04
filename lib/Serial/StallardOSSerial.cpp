#include "StallardOSSerial.hpp"

StallardOSSerial::StallardOSSerial(USART_TypeDef *serPort, uint32_t baud)
{
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
        StallardOSGeneralFaultHandler();
    }
}

void StallardOSSerial::send(const char *dat, uint16_t bytes)
{
    if(dat == nullptr)
    {
        return;
    }
    HAL_UART_Transmit(&huart, (uint8_t*)dat, bytes, 0);
}

void StallardOSSerial::read(char *dat, uint16_t bytes)
{
    if(dat == nullptr)
    {
        return;
    }
    HAL_UART_Receive(&huart, (uint8_t*)dat, bytes, 0);
}
