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

void test_stackSizeValid()
{
    uint32_t stack[32];
    function_struct *tmp;

    uint16_t id = 1;
    uint16_t mpu_iter = 4;

    //TODO: make sure OS has enough structs for allocation
    #ifdef useMPU
    for(int i=32; i<=0x1'0000'0000; (i=i<<2), id++, mpu_iter++){
        // use static allocation to not overflow the heap
        // it's not actually important if the given stack size is the actual stack isze
        tmp = StallardOSJanniq.addFunctionStatic(testfunction, id, 1, stack, i);
        TEST_ASSERT_NOT_EQUAL_MESSAGE(nullptr, tmp, "accepted correct stack size");

        // WARN: if the mpu defines change their layout
        // this method is no longer valid, a LUT must be used then
        TEST_ASSERT_EQUAL_MESSAGE(tmp->stackSize_MPU, mpu_iter, "correct mpu-size config");
    }
    #endif
}

void test_stackSizeOutOfRange()
{
    function_struct *tmp;

    #ifdef useMPU
    tmp = StallardOSJanniq.addFunction(testfunction, 1, 3, 16); //This should return a nullptr
    TEST_ASSERT_EQUAL_MESSAGE(nullptr, tmp, "Too small stack size");
    #endif

    tmp = StallardOSJanniq.addFunction(testfunction, 1, 3, 0x2'0000'0000); //This should return a nullptr
    TEST_ASSERT_EQUAL_MESSAGE(nullptr, tmp, "Too large stack size");
}

int main()
{
    HAL_Init(); // initialize the HAL library
    StallardOS::delay(5000);
    unittest_uart_begin();
    unittest_uart_putchar(countTasks);
    UNITY_BEGIN();

    RUN_TEST(test_stackSizeValid);
    RUN_TEST(test_stackSizeOutOfRange);

    UNITY_END(); // stop unit testing

    while (1)
    {
    }
}
