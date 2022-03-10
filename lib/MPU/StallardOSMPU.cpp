#include "StallardOSMPU.hpp"

#include "StallardOSSerial.hpp"


int StallardOSMPU::fix_config(MPU_Region_InitTypeDef *config, stack_T start_address, stack_T size){

  /* for correctly setting up the region attributes
   * for each type of memory, consider
   * 4.2.4 Table 42, of the programming manual PM0214
   */

    uint8_t sub_mask = 0;
    uint8_t start_subsection;
    uint8_t end_subsection;

    // check for valid region size
    // but ignore 0
    // due to limits of 32bit variable, no upper limit needs to be checked
    if((size > 0 && size < 32)){
        DEBUGGER_BREAK();
        return -1;
    }

    // manage sub sections
    // only if resulting alignment size is larger equal to 256
    // otherwise subregions are not supported
    if(start_address != 0 && size != 0 && size >= 256){

        // round up the requested region size
        // to the next possible size (using full regions)
        uint32_t aligned_size = ceilPow2(size);


        // test 1st condition
        // requisted address must exactly fit into any number of subregions
        // combination, if not, config not possible
        uint32_t sub_size = aligned_size/8;
        if(size%sub_size){
            DEBUGGER_BREAK();
            return -1;
        }

        // 2nd condition
        // start address must be aligned to size of entire region
        // misalignmend can be fixed with a subregion offsett
        uint32_t addr_misalign = start_address%aligned_size;
        if(addr_misalign == 0){
            start_subsection = 0;  // good alignment
        }
        else{
            // determin in which subsection the start address is laying
            if(addr_misalign%sub_size == 0){
                start_subsection = addr_misalign/sub_size;
            }
            else{
                // start address doesn't fit any subregion start address
                DEBUGGER_BREAK();
                return -1;
            }
        }

        // in case we have a start_section, the start_address needs to be updated
        if(start_subsection){
            // calculate the mpu region start address based on the subregion offset
            // (reverse the calculation)
            start_address = start_address - (start_subsection*sub_size);
        }

        // next calc how many subregions are required to fit the requested size, 
        // the end section is calculated by taking the prev. determined start subregion
        // adding the amount of subregions
        // -> incr. steps are size of subregion length
        end_subsection = start_subsection + (size/sub_size)-1;

        // there cannot be more than 8 subregions
        if(end_subsection > 7){
            DEBUGGER_BREAK();
            return -1;
        }

        // disable all sections not within the selected limits        
        for(int i=0; i<8; i++){
            if(i < start_subsection || i > end_subsection){
                sub_mask |= (1<<i);
            }
        }

        config->SubRegionDisable = sub_mask;
        config->BaseAddress = start_address;
        config->Size = bytesToMPUSize(aligned_size);  // this may be larger than the requested size
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
            DEBUGGER_BREAK();
            return -1;
        }
        else{
            // size is valid pow2
            config->Size = bytesToMPUSize(size);
        }

        // base address alignment check is remaining
        if(start_address%size != 0){
            DEBUGGER_BREAK();
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
        DEBUGGER_BREAK();
        return config_result;
    }

    //TODO: remove debug excemption
    config->SubRegionDisable=0;
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