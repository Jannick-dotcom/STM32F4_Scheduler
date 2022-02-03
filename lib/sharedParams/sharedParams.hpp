#ifndef _SHARED_PARAMS_CLASS_H_
#define _SHARED_PARAMS_CLASS_H_

#include <stdint.h>
//#include "StallardOSsem.hpp"

class SharedParams{
    public:
        enum boot_type{
            T_STARTUP=0x0, // implicitly set at first boot (with init)
            T_REBOOT=0x1,
            T_FLASH=0x2
        };

        SharedParams();

        bool set_fl_version(uint8_t ver);
        uint8_t get_fl_version();

        bool set_os_version(uint8_t ver);
        uint8_t get_os_version();

        bool set_sw_version(uint8_t ver);
        uint8_t get_sw_version();

        bool set_boot_type(enum boot_type type);
        enum boot_type get_boot_type();


    private:
        //static StallardOSSemaphore sem;

        bool write_locked(uint32_t pos, uint8_t val);
        bool read_locked(uint32_t pos, uint8_t *val);

        enum shared_pos{
            FL_VER=0x0,
            OS_VER=0x1,
            SW_VER=0x2,
            BOOT_TYPE=0x3
        };

};

#endif // _SHARED_PARAMS_CLASS_H_