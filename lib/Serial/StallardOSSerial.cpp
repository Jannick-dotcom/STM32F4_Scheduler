#include "StallardOSSerial.hpp"

StallardOSSerial::StallardOSSerial(serialPorts serPort, uint32_t baud)
{
    //huart.Instance = serPort;////////////////////////////////
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
    char datSend[] = "Hello World";
    HAL_UART_Transmit(&huart, (uint8_t*)datSend, sizeof(datSend), 0);
}