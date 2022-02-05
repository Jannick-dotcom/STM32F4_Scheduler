#ifndef StallardOS_h
#define StallardOS_h

#include <stdint.h>
#include <malloc.h>
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

#define STOS_VERSION 0x10

#endif //StallardOS_h
