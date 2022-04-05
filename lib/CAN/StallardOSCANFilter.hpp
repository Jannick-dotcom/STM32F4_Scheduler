#ifndef STALLARDOSCANFILTER_H
#define STALLARDOSCANFILTER_H

#include <stdint.h>
#include "StallardOSHelpers.h"
#include "StallardOScan.hpp"

/*
* A filter is used to filter for specific message IDs
* Defined filter IDs will be received
* 28 Filters can be used
* So that makes 14 per CAN
*/

extern "C" void StallardOSGeneralFaultHandler();

class StallardOSCANFilter
{
public:
    StallardOSCANFilter(uint16_t id1, uint16_t id2, CANports can);
    ~StallardOSCANFilter();
protected:
    /**
     * @brief declare new filter, without applying it to HW
     */
    StallardOSCANFilter(uint16_t id1, uint16_t id2);
    void setup(CANports can);
private:
    static uint8_t countFilters;
    uint8_t n;
    uint16_t id1;
    uint16_t id2;    
};


/**
 * @brief setup a CANfilter which is not immediately applied to the CAN controller
 *        usefull when class must be initialized before Hardware is ready
 * 
 */
class StallardOSCANFilterDelayed: public StallardOSCANFilter
{
    public:
        /**
         * @brief declare the new filter object without applying it to hardware
         * 
         * @param id1 first whitelisted CAN id
         * @param id2 second whitelisted CAN id
         * @param can CAN instance
         */
        StallardOSCANFilterDelayed(uint16_t id1, uint16_t id2, CANports can);

        /**
         * @brief apply the current filter and write it to the hardware
         *        Hardfaults when HW not ready
         * 
         */
        void setup();

    private:
        CANports can;
        bool is_init;
};

#endif