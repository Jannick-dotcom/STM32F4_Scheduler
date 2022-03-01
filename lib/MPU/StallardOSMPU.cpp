#include "StallardOSMPU.hpp"

int StallardOSMPU::fix_config(MPU_Region_InitTypeDef *config, stack_T start_address, stack_T size){

  /* for correctly setting up the region attributes
   * for each type of memory, consider
   * 4.2.4 Table 42, of the programming manual PM0214
   */

    uint8_t sub_mask = 0;
    uint8_t start_section;
    uint8_t end_section;

    // check for valid region size
    // but ignore 0
    // due to limits of 32bit variable, no upper limit needs to be checked
    if((size > 0 && size < 32)){
        return -1;
    }

    // manage sub sections
    // only if resulting alignment size is larger equal to 256
    if(start_address != 0 && size != 0 && size > 128){

        // first get the next biggest section size
        uint32_t align_size = ceilPow2(size);

        // next test, if a valid config is still possible
        // for this, the base address must start at a subregion
        // and the length must end at another (or the same) subregion
        uint32_t sub_size = align_size/8;
        if(size%sub_size){
            // yields non-zero when sizes are not compatible
            return -1;
        }

        // test if the start address is aligned to size
        // or if it needs to be aligned to a subsection
        uint32_t addr_misalign = start_address%align_size;
        if(addr_misalign == 0){
            start_section = 0;  // good alignment
        }
        else{
            // determin in which subsection the start address is laying
            if(addr_misalign%sub_size == 0){
                start_section = addr_misalign/sub_size;
            }
            else{
                // no sub-alignment possible
                return -1;
            }
        }

        // in case we have a start_section, the start_address needs to be updated
        if(start_section){
            start_address = start_address - (start_section*sub_size);
        }

        // next get the end section, 
        // based on the prev. selected start_section
        end_section = start_section + (size/sub_size)-1;

        // memory does not fit into selected region
        // align_size must be increased
        if(end_section > 7){
            return -1;
        }

        // disable all sections not within the selected limits        
        for(int i=0; i<8; i++){
            if(i < start_section || i > end_section){
                sub_mask |= (1<<i);
            }
        }

        config->SubRegionDisable = sub_mask;
        config->BaseAddress = start_address;
        config->Size = bytesToMPUSize(align_size);
    }
    else if(start_address > 0 || size > 0){
        // subregions not possible, due to missing information
        // or not desired by calle (as parameters are already set to config struct manually)
        // only perform basic alignment checks for 'simple' configuration

        if(start_address == 0){
            start_address = config->BaseAddress;
        }

        // if user provided,
        if(size == 0){
            // extract for align calculation
            size = mpuSizeToBytes(config->Size);
        } 
        if((size & (size-1)) != 0){
            // filter out non pow2 numbers
            return -1;
        }
        else{
            // size is valid pow2
            config->Size = bytesToMPUSize(size);
        }

        // base address alignment check is remaining
        if(start_address%size != 0){
            return -1;
        }
        
        // might get double-assign, but easiest way
        config->BaseAddress = start_address;
        config->SubRegionDisable = 0x0;  // no subregioning supported
    }

    return 0;
}


int StallardOSMPU::write_config(MPU_Region_InitTypeDef *config, stack_T start_address, stack_T size, bool force_write){
    bool was_enabled = is_enabled();
    int config_result;

    if(was_enabled){
        disable();
    }

    config_result = fix_config(config, start_address, size);

    if(config_result < 0){
        return config_result;
    }
    config->SubRegionDisable=0; // TODO: lolol
    HAL_MPU_ConfigRegion(config);

    if(was_enabled){
        enable(MPU_PRIVILEGED_DEFAULT);
    }
    return 0;
}

void StallardOSMPU::enable(uint32_t MPU_Control){
    HAL_MPU_Enable(MPU_Control);
}

void StallardOSMPU::disable(){
    HAL_MPU_Disable();
}

bool StallardOSMPU::is_enabled(){
    return MPU->CTRL != 0;
}



uint8_t StallardOSMPU::bytesToMPUSize(stack_T bytes){
  switch(bytes){
    case 0x20:
      return MPU_REGION_SIZE_32B;
    case 0x40:
      return MPU_REGION_SIZE_64B;
    case 0x80:
      return MPU_REGION_SIZE_128B;
    case 0x100:
      return MPU_REGION_SIZE_256B;
    case 0x200:
      return MPU_REGION_SIZE_512B;
    case 0x400:
      return MPU_REGION_SIZE_1KB;
    case 0x800:
      return MPU_REGION_SIZE_2KB;
    case 0x1000:
      return MPU_REGION_SIZE_4KB;
    case 0x2000:
      return MPU_REGION_SIZE_8KB;
    case 0x4000:
      return MPU_REGION_SIZE_16KB;
    case 0x8000:
      return MPU_REGION_SIZE_32KB;
    case 0x1'0000:
      return MPU_REGION_SIZE_64KB;
    case 0x2'0000:
      return MPU_REGION_SIZE_128KB;
    case 0x4'0000:
      return MPU_REGION_SIZE_256KB;
    case 0x8'0000:
      return MPU_REGION_SIZE_512KB;
    case 0x10'0000:
      return MPU_REGION_SIZE_1MB;
    case 0x20'0000:
      return MPU_REGION_SIZE_2MB;
    case 0x40'0000:
      return MPU_REGION_SIZE_4MB;
    case 0x80'0000:
      return MPU_REGION_SIZE_8MB;
    case 0x100'0000:
      return MPU_REGION_SIZE_16MB;
    case 0x200'0000:
      return MPU_REGION_SIZE_32MB;
    case 0x400'0000:
      return MPU_REGION_SIZE_64MB;
    case 0x800'0000:
      return MPU_REGION_SIZE_128MB;
    case 0x1000'0000:
      return MPU_REGION_SIZE_256MB;
    case 0x2000'0000:
      return MPU_REGION_SIZE_512MB;
    case 0x4000'0000:
      return MPU_REGION_SIZE_1GB;
    case 0x8000'0000:
      return MPU_REGION_SIZE_2GB;
    case (uint32_t)0x1'0000'0000:
      return MPU_REGION_SIZE_4GB;
    default:
      return 0x0;  // invalid reg value, will cause Hardfault
  }
}


uint32_t StallardOSMPU::mpuSizeToBytes(uint8_t mpu_size){
    return 2<<mpu_size;
}

uint32_t StallardOSMPU::ceilPow2(uint32_t n){

    n--;  // in case n is already pow2

    // set all bits below the MSB to 1
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

    // adding 1 will result in only 1 bit set
    // which in turn is pow2
    n++;
    return n;
}