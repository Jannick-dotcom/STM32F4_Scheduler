#include "../unittest_transport.h"
#include <unity.h>
#include "StallardOS.hpp"
StallardOS StallardOSJanniq;

void setUp(void)
{
    unittest_uart_begin();
}

void tearDown(void)
{
}

void test_PID_p(void)
{
    StallardosPID testPID(1, 0, 0);
    double retVal = testPID.calculate_pid(10, 0);
    TEST_ASSERT_EQUAL(10, retVal);
}

void test_PID_i(void)
{
    double last = 10;
    double retVal = 0;
    StallardosPID testPID(0, 1, 0);
    for (uint8_t i = 0; i < 10; i++)
    {
        retVal = testPID.calculate_pid(10, 0);
        TEST_ASSERT_EQUAL(last, retVal);
        last += 10;
    }
}

void test_PID_d(void)
{
    double retVal = 0;
    StallardosPID testPID(0, 0, 1);
    retVal = testPID.calculate_pid(10, 0);
    TEST_ASSERT_EQUAL(10, retVal);
    retVal = testPID.calculate_pid(0, 0);
    TEST_ASSERT_EQUAL(-10, retVal);
    retVal = testPID.calculate_pid(0,0);
    TEST_ASSERT_EQUAL(0,retVal);
}

int main()
{
    HAL_Init(); // initialize the HAL library
    StallardOS::delay(5000);
    UNITY_BEGIN();

    RUN_TEST(test_PID_p);
    RUN_TEST(test_PID_i);
    RUN_TEST(test_PID_d);

    UNITY_END(); // stop unit testing

    while (1)
    {
    }
}
