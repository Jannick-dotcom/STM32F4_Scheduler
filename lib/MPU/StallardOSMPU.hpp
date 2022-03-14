#pragma once

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "StallardOSHelpers.h"


class StallardOSMPU{
    public:

        /**
         * @brief apply subregion adjustments to config, based on given start_adress and size
         *        Does NOT write to any MPU registers
         * 
         * @param config[out] MPU configuration, holds affected region aswell
         * @param start_address start addres of memory block, might get shiftet to front to match regions
         * @param size desired size of section, must match subregion sizes
         * @return int negative on invalid config request
         */
        static int fix_config(MPU_Region_InitTypeDef *config, stack_T start_address, stack_T size);


        /**
         * @brief config memory region with automatic subregion arangement, allows sub-aligned memory. 
         *        Will disable MPU for valid configuration, automatic re-enable after config (if it was enabled before).
         *        Will call fix_config to apply start_address and size
         *        WARNING: will HardFault if called from user mode
         * 
         * @param config MPU configuration, holds affected region aswell
         * @param start_address start addres of memory block, might get shiftet to front to match regions
         * @param size desired size of section, must match subregion sizes
         * @param force_write try to set config, even when illegal alignment was detected, likely to cause Hardfault
         * @ref   fix_config
         * @return int - 0 on success, negative if alignment is wrong
         */
        static int write_config(MPU_Region_InitTypeDef *config, stack_T start_address, stack_T size, bool force_write=0);

        /**
         * @brief wraps HAL enable method
         * 
         */
        static void enable(uint32_t MPU_Control);

        /**
         * @brief wraps HAL disable method
         * 
         */
        static void disable();

        /**
         * @brief read if MPU is currently enabled.
         *        WARNING: Hardfault when called unprivileged
         * 
         * @return true MPU is enabled
         * @return false MPU is disabled
         */
        static bool is_enabled();


        /**
         * @brief convert given number into MPU define, must be power of 2
         * 
         * @param bytes region size
         * @return uint8_t, 0 on failure (not pwr of 2 or over 2G)
         */
        static uint8_t bytesToMPUSize(stack_T bytes);


        /**
         * @brief convert the mpu size symbol back to the size in bytes
         * 
         * @param mpu_size MPU define symbol
         * @return uint32_t region size in bytes
         */
        static uint32_t mpuSizeToBytes(uint8_t mpu_size);

    private:

        /**
         * @brief ceil to the next power of 2
         *        only applicable for 32bit
         * 
         * @param n current value to be ceiiled
         * @return uint32_t ceiled value, power of 2
         */
        static uint32_t ceilPow2(uint32_t n);

};