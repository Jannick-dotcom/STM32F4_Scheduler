#include "SFOC.hpp"

#include <string.h>
#include "stm32f4xx_hal.h"

//#include "FLASH_SECTOR_F4.h"

/*
uint32_t data[64];
//Flash_Write_Data(0x8008000, data, 64);
    memset(data, 0, 64);
    memset(data, 0x42, 32);
*/

/**
 * @brief Construct a new SFOC::SFOC object
 *        initialised required CAN interfac(es)
 * 
 */
SFOC::SFOC(uint16_t ecu_id, uint16_t host_id, uint16_t discovery_id, uint32_t timeout_ms):
    ecu_id(ecu_id),
    host_id(host_id),
    discovery_id(discovery_id),
    timeout_ms(timeout_ms),
    last_activity(HAL_GetTick()),
    filter(ecu_id, discovery_id, AD_CAN_PORT),
    state(BASE){}

/**
 * @brief send a single ack message to the host
 * 
 */
void SFOC::ack_cmd(){
    response.id = host_id;
    response.opcode = sfoc_opcodes::ACK;
    response.len = 0;
    send();
}

/**
 * @brief send a single nack to the host, denying the request
 * 
 */
void SFOC::nack_cmd(){
    response.id = host_id;
    response.opcode = sfoc_opcodes::NACK;
    response.len = 0;
    send();
}


/**
 * @brief send a discovery response to the global discovery ID
 * 
 */
void SFOC::send_discovery(){
    response.id = SFOC_DISCOVERY;
    response.opcode = sfoc_opcodes::DISCOVERY_RESPONSE;

    response.len = 4;
    response.data[0] = ecu_id & 0xFF;
    response.data[1] = (ecu_id & 0xFF00) >> 8;

    response.data[2] = host_id & 0xFF;
    response.data[3] = (host_id & 0xFF00) >> 8;

    send();
}


/**
 * @brief send the used SFOC to the host
 * 
 */
void SFOC::send_version(){
    response.id = host_id;
    response.opcode = sfoc_opcodes::VERSION;

    response.len = 3;
    response.data[0] = OS_VERSION;
    response.data[1] = FLASH_LOADER_VERSION;
    response.data[2] = SFOC_VERSION;
    send();
}


/**
 * @brief send the used hardware to the host
 * 
 */
void SFOC::send_id(){
    response.id = host_id;
    response.opcode = sfoc_opcodes::ID;

    response.len = 2;

    // defines are in line with protocol definition
    response.data[0] = STOS_current_ECU_ID;
    response.data[1] = 0; /* TODO: implement */

    send();
}

/**
 * @brief checks if CU is allowed to switch to flashloader
 * 
 *        if allowed, will reboot an method will not return
 *        sends NACK otherwise
 */
void SFOC::go_flashloader(){
    nack_cmd();
    return;

    /* set arguments for Flashloader */
    CALL_SYSRESET();
}


/**
 * @brief interpret the cmd and act based on it
 * 
 */
void SFOC::read_cmd(){

    switch(cmd.opcode){
        case sfoc_opcodes::DISCOVERY_REQUEST:
            send_discovery();
            return;
        case sfoc_opcodes::VERSION:
            send_version();
            return;
        case sfoc_opcodes::ID:
            send_id();
            return;
        case sfoc_opcodes::GO_FL:
            go_flashloader();
            return;
        default:
            break;
    }
}


/**
 * @brief core of the protocoll state machine
 * 
 * @param data trigger condition (CAN received bytes)
 */
void SFOC::STM_step(){

    /* not all states interpret the new message as command
     * it might be a payload message
     */
    switch(state){
        case BASE:
            decode();
            read_cmd();
            break;
        default:
            break;
    }
}


/**
 * @brief start handler loop for SFOC protocoll
 *        respects timeout of object
 * 
 * @return int 
 */
SFOC_Status SFOC::stm_iterate(){

    /* basic read-loop, SFOC never actively starts a CAN transmission
     * and acts purely reactive
     *
     * therefore loops is structured in simple
     *      read_can -> filter -> process -> respond
     * 
     * where respond might be any of:
     *      * ACK
     *      * NACK
     *      * DATA (+ ACK)
     */
 
    bool ret;
    uint32_t tick;
    
    ret = AD_CAN.receiveMessage(&in_frame, ecu_id);
    if(!ret){
        // query discovery ids
        ret = AD_CAN.receiveMessage(&in_frame, discovery_id);
    }

    if(!ret){
        tick = HAL_GetTick();
        if(timeout_ms > 0 && (tick-last_activity) > timeout_ms){
            // flashLoader is timed out with error
            return SFOC_TIMEOUT;
        }
        return SFOC_CONTINUE;
    }


    /* we've got a valid frame */
    STM_step();
    last_activity = HAL_GetTick();

    return SFOC_CONTINUE;
}
