#include "sharedParams.hpp"
#include "shared_params.hpp"

/* static semaphore */
//StallardOSSemaphore SharedParams::sem;
/**
 * @brief Construct a new Shared Params:: Shared Params object
 *        initialize the shared buffer if not already done
 * 
 */
SharedParams::SharedParams(){
    // initializing multiple times is not an issue
    // in case of multiple class instances
    //sem.take();
    SharedParamsInit();
    //sem.give();
}


bool SharedParams::write_locked(uint32_t pos, uint8_t val){
    bool ret;
    //sem.take();
    ret = SharedParamsWriteByIndex(pos, val);
    //sem.take();

    return ret;
}

bool SharedParams::read_locked(uint32_t pos, uint8_t *val){
    bool ret;
    //sem.take();
    ret = SharedParamsReadByIndex(pos, val);
    //sem.take();

    return ret;
}


bool SharedParams::set_fl_version(uint8_t ver){
    return write_locked(shared_pos::FL_VER, ver);
}
uint8_t SharedParams::get_fl_version(){
    uint8_t ret;
    read_locked(shared_pos::FL_VER, &ret);
    return ret;
}

bool SharedParams::set_os_version(uint8_t ver){
    return write_locked(shared_pos::OS_VER, ver);
}
uint8_t SharedParams::get_os_version(){
    uint8_t ret;
    read_locked(shared_pos::OS_VER, &ret);
    return ret;
}

bool SharedParams::set_sw_version(uint8_t ver){
    return write_locked(shared_pos::SW_VER, ver);
}
uint8_t SharedParams::get_sw_version(){
    uint8_t ret;
    read_locked(shared_pos::SW_VER, &ret);
    return ret;
}

bool SharedParams::set_boot_type(enum boot_type type){
    return write_locked(shared_pos::BOOT_TYPE, (uint8_t)type);
}
enum SharedParams::boot_type SharedParams::get_boot_type(){
    uint8_t ret;
    read_locked(shared_pos::BOOT_TYPE, &ret);
    return (enum SharedParams::boot_type)ret;
}

