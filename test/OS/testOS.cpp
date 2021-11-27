#include "../unittest_transport.h"

#include <unity.h>
#include "StallardOS.hpp"
StallardOS StallardOSJanniq;
function_struct *ref;

void setUp(void)
{
    unittest_uart_begin();
}

void tearDown(void)
{
}

void testfunction() {}

void test_addFunction()
{
    uint32_t stack[512];
    function_struct *temp;
    temp = StallardOSJanniq.addFunction(testfunction, 1, 3, 128); //This should not return a nullptr
    TEST_ASSERT_NOT_EQUAL_MESSAGE(nullptr, temp, "normal dynamic function add");
    temp = StallardOSJanniq.addFunction(testfunction, 1, 1, 128); //This should return a nullptr because already given id
    TEST_ASSERT_EQUAL_MESSAGE(nullptr, temp, "dynamic add function with same id");
    temp = StallardOSJanniq.addFunction(testfunction, 2, 3, (uint32_t)(0x1<<31)); //Try allocating a lot of stack space (but x^2)
    TEST_ASSERT_EQUAL_MESSAGE(nullptr, temp, "dynamic add function with too much stack");

    temp = StallardOSJanniq.addFunctionStatic(testfunction, 3, 1, stack, sizeof(stack));
    TEST_ASSERT_NOT_EQUAL_MESSAGE(nullptr, temp, "normal static function add");
    ref = temp; //Save the function_struct
    temp = StallardOSJanniq.addFunctionStatic(testfunction, 4, 1, nullptr, sizeof(stack));
    TEST_ASSERT_EQUAL_MESSAGE(nullptr, temp, "nullptr static function add");
    temp = StallardOSJanniq.addFunctionStatic(testfunction, 5, 1, stack, 0);
    TEST_ASSERT_EQUAL_MESSAGE(nullptr, temp, "zero size static function add");
}

void test_functionModifiers()
{
    StallardOSJanniq.setFunctionEnabled(ref->id,0);
    TEST_ASSERT_EQUAL_MESSAGE(false, ref->executable, "Disable function");
    StallardOSJanniq.setFunctionEnabled(ref->id,1);
    TEST_ASSERT_EQUAL_MESSAGE(true, ref->executable, "Enable function");

    StallardOSJanniq.setFunctionPriority(ref->id, 34);
    TEST_ASSERT_EQUAL_MESSAGE(34, ref->priority, "Change prio");

    StallardOSJanniq.setFunctionFrequency(ref->id, 1234);
    TEST_ASSERT_EQUAL_MESSAGE(1234, ref->refreshRate, "change frequency");
}

int main()
{
    HAL_Init(); // initialize the HAL library
    StallardOS::delay(5000);
    unittest_uart_begin();
    unittest_uart_putchar(countTasks);
    UNITY_BEGIN();

    RUN_TEST(test_addFunction);
    RUN_TEST(test_functionModifiers);

    UNITY_END(); // stop unit testing

    while (1)
    {
    }
}
