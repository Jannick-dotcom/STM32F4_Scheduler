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

void test_addFunction()
{

}

void test_delay()
{

}

void test_yield()
{

}

void test_functionModifiers()
{

}

void test_timing()
{
    
}

int main()
{
    HAL_Init(); // initialize the HAL library
    StallardOS::delay(2000);
    UNITY_BEGIN();

    RUN_TEST(test_addFunction);

    UNITY_END(); // stop unit testing

    while (1)
    {
    }
}
