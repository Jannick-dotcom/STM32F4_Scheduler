#include "../unittest_transport.h"
#include <unity.h>
#include "StallardOS.hpp"
StallardOS StallardOSJanniq;

ports port = PORTA;
uint8_t pin = 6;
StallardOSGPIO testGPIO; //(pin, port, Output);

void setUp(void)
{
    unittest_uart_begin();
}

void tearDown(void)
{
}

void test_pin_state_high(void)
{
    testGPIO = 1;
    TEST_ASSERT_EQUAL(GPIO_PIN_SET, testGPIO.read());
}

void test_pin_state_low(void)
{
    testGPIO = 0;
    TEST_ASSERT_EQUAL(GPIO_PIN_RESET, testGPIO.read());
}

int main()
{
    HAL_Init(); // initialize the HAL library
    StallardOS::delay(2000);
    // HAL_Delay(2000);    // service delay
    UNITY_BEGIN();

    for (uint8_t iPIN = 0; iPIN < 32; iPIN++)
    {
        for (uint8_t iPORT = 0; iPORT < sizeof(StallardOSGPIO::portsToGPIOBase) / sizeof(GPIO_TypeDef *); iPORT++)
        {
            testGPIO = StallardOSGPIO(iPIN, ports(iPORT), Output, 1);
            RUN_TEST(test_pin_state_high);
            RUN_TEST(test_pin_state_low);
        }
    }

    UNITY_END(); // stop unit testing
    StallardOS::delay(1000);
    HAL_NVIC_SystemReset();
    while (1)
    {
    }
}
