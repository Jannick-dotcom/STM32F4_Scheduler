#include "StallardOSSerial.hpp"
using namespace std;

uint8_t StallardOSSerial::portToAlternateFunc(USART_TypeDef *serPort)
{
    uint8_t alternateFunction = 0;
    if(serPort == USART1)
    {
        __HAL_RCC_USART1_CLK_ENABLE();
        alternateFunction = GPIO_AF7_USART1;
    }
    else if(serPort == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        alternateFunction = GPIO_AF7_USART2;
    }
    else if(serPort == USART3)
    {
        __HAL_RCC_USART3_CLK_ENABLE();
        alternateFunction = GPIO_AF7_USART3;
    }
    else if(serPort == UART4)
    {
        __HAL_RCC_UART4_CLK_ENABLE();
        alternateFunction = GPIO_AF8_UART4;
    }
    else if(serPort == UART5)
    {
        __HAL_RCC_UART5_CLK_ENABLE();
        alternateFunction = GPIO_AF8_UART5;
    }
    else if(serPort == USART6)
    {
        __HAL_RCC_USART6_CLK_ENABLE();
        alternateFunction = GPIO_AF8_USART6;
    }
    return alternateFunction;
}

/**
 * create a serial instance.
 *
 * @param serPort which Serial to use
 * @param baud baud rate
 */
StallardOSSerial::StallardOSSerial(USART_TypeDef *serPort, gpio tx, gpio rx, uint32_t baud) :
    tx(tx.pin,tx.port, AFPP, nopull, portToAlternateFunc(serPort)),
    rx(rx.pin,rx.port, AFPP, nopull, portToAlternateFunc(serPort))
{

    this->sem.take();

    if (baud == 0)
    {

        this->sem.give();

        return;
    }
    
    if(portToAlternateFunc(serPort) == 0) //Not implemented
    {
        #ifndef UNIT_TEST
        asm("bkpt");  //Zeige debugger
        #endif
        this->sem.give();
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

    if (dat == nullptr)
    {

        this->sem.give();

        return;
    }
    HAL_UART_Transmit(&huart, (uint8_t *)dat, bytes, 0xFFFF);

    this->sem.give();

}

void StallardOSSerial::send(std::string str)
{
    send(str.c_str(), (uint16_t)str.size());
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

    if (dat == nullptr)
    {

        this->sem.give();

        return;
    }
    HAL_UART_Receive(&huart, (uint8_t *)dat, bytes, 0xFFFF);

    this->sem.give();

}
