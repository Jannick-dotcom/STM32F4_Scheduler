#ifndef StallardOS_h
#define StallardOS_h

#include <stdint.h>
#include <malloc.h>
#include "StallardOSHelpers.h"
#include "StallardOSVersion.hpp"

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
#include "StallardOSAvg.hpp"
#include "AlphaBeta.hpp"
#ifdef STM32F4xxxx
#include "ili9341.h"
#include "fatfs.h"
#endif
#endif //StallardOS_h
