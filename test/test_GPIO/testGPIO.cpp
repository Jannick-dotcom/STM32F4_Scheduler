#include "../unittest_transport.h"
#include <unity.h>
#include <iostream>
#include "StallardOS.hpp"
StallardOS StallardOSJanniq;

// ports port = PORTA;
// uint8_t pin = 6;
StallardOSGPIO *ptestGPIO;
std::string temp;

void setUp(void)
{
    unittest_uart_begin();
}

void tearDown(void)
{
}

void test_pin_state_high(void)
{
    ptestGPIO->write(1);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_PIN_SET, ptestGPIO->read(), temp.c_str());
}

void test_pin_state_low(void)
{
    ptestGPIO->write(0);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_PIN_RESET, ptestGPIO->read(), temp.c_str());
}

int main()
{
    HAL_Init(); // initialize the HAL library
    unittest_uart_begin();
    StallardOS::delay(500);
    // HAL_Delay(2000);    // service delay
    UNITY_BEGIN();

    for (uint8_t iPORT = 0; iPORT < sizeof(StallardOSGPIO::portsToGPIOBase) / sizeof(GPIO_TypeDef *); iPORT++)
    {
        for (uint8_t iPIN = 0; iPIN < 16; iPIN++)
        {
            if ((iPORT == PORTA && iPIN == 13) || (iPORT == PORTA && iPIN == 14) || (iPORT == PORTA && iPIN == 9) || (iPORT == PORTA && iPIN == 10)) // Please don't mess with SWD pins
            {
                continue;
            }
            StallardOSGPIO testgpio(iPIN, ports(iPORT), Output, 1);
            ptestGPIO = &testgpio;
            temp = std::string("Pin ") + std::to_string(iPIN) + " on port " + std::to_string(iPORT) + " is tested";
            RUN_TEST(test_pin_state_high);
            RUN_TEST(test_pin_state_low);
            testgpio.~StallardOSGPIO();
        }
    }

    UNITY_END(); // stop unit testing
    StallardOS::delay(1000);
    // HAL_NVIC_SystemReset();
    while (1)
    {
    }
}
