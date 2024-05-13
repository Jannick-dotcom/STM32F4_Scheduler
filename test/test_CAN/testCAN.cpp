#include "../unittest_transport.h"
#include <unity.h>
#include <iostream>
#include "StallardOS.hpp"
StallardOS StallardOSJanniq;

StallardOSCAN can1(gpio(CAN1_t_port,CAN1_t_pin),gpio(CAN1_r_port,CAN1_r_pin),StallardOSCAN1, CAN500k, true);

void setUp(void)
{
    unittest_uart_begin();
}

void tearDown(void)
{
}

void testSendMessage()
{
    StallardOSCanMessage msg;
    TEST_ASSERT_EQUAL(-1, can1.sendMessage(nullptr));
    TEST_ASSERT_EQUAL(-1, can1.sendMessage(nullptr, 0));
    TEST_ASSERT_EQUAL(-1, can1.sendMessage(nullptr, 9));
    TEST_ASSERT_EQUAL(-1, can1.sendMessage(&msg));
    TEST_ASSERT_EQUAL(-1, can1.sendMessage(&msg, 0));
    TEST_ASSERT_EQUAL(-1, can1.sendMessage(&msg, 9));
    TEST_ASSERT_EQUAL(0, can1.sendMessage(&msg, 3));
    msg.dlc = 3;
    TEST_ASSERT_EQUAL(0, can1.sendMessage(&msg));
}

void testReceiveMessage()
{
    StallardOSCanMessage msg;
    TEST_ASSERT_EQUAL(false, can1.receiveMessage(nullptr));
    TEST_ASSERT_EQUAL(false, can1.receiveMessage(nullptr));
    msg.ID = 125;
    TEST_ASSERT_EQUAL(false, can1.receiveMessage(&msg));
    msg.ID = 0;
    TEST_ASSERT_EQUAL(true, can1.receiveMessage(&msg));
    TEST_ASSERT_EQUAL(true, can1.receiveMessage(&msg));
    TEST_ASSERT_EQUAL(false, can1.receiveMessage(&msg));
}

int main()
{
    HAL_Init(); // initialize the HAL library
    unittest_uart_begin();
    StallardOS::delay(500);
    // HAL_Delay(2000);    // service delay
    UNITY_BEGIN();

    

    UNITY_END(); // stop unit testing
    StallardOS::delay(1000);
    // HAL_NVIC_SystemReset();
    while (1)
    {
    }
}
