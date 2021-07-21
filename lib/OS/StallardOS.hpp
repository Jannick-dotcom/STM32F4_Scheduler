#ifndef StallardOS_h
#define StallardOS_h

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <system_stm32f4xx.h>

#include "StallardOSClass.hpp"
#include "StallardOSsem.hpp"
#include "StallardOSGPIO.hpp"
#include "StallardOSpwm.hpp"
#include "StallardOSanalog.hpp"
#include "StallardOSExtAnalog.hpp"
#include "StallardOScan.hpp"
#include "StallardOSSerial.hpp"
#include "StallardOSi2c.hpp"
#include "StallardOSPID.hpp"
#include "StallardOSSPI.hpp"
#include "StallardOSDAC.hpp"


#ifdef STM32F417xx
static StallardOSCAN MS4_CAN(StallardOSCAN2, CAN1M);
static StallardOSCAN AD_CAN(StallardOSCAN1, CAN500k);
#endif
#ifdef STM32F415xx
static StallardOSCAN AD_CAN(StallardOSCAN2, CAN500k);
#endif

#endif //StallardOS_h
