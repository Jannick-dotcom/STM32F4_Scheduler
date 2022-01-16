#include "SFOC.hpp"

#include "stm32f4xx_hal.h"

#ifdef SFOC_FL_DOMAIN
    #include "FLASH_SECTOR_F4.h"
#endif

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
    state(stm_state::BASE),
    state_out(SFOC_CONTINUE ){}

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
void SFOC::nack_cmd(sfoc_nack_reason reason){
    response.id = host_id;
    response.opcode = sfoc_opcodes::NACK;
    response.len = 1;
    response.data[0] = reason;

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

    #if defined(SFOC_OS_DOMAIN)
        response.data[0] = STOS_VERSION;
        response.data[1] = s_params.get_fl_version();
    #elif defined(SFOC_FL_DOMAIN)
        response.data[0] = s_params.get_os_version();
        response.data[1] = FL_VERSION;
    #else
        response.data[0] = 0;
        response.data[1] = 0;
        #ifndef UNIT_TEST
        asm("bkpt");  //Zeige debugger
        #endif
    #endif

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
    #ifdef SFOC_OS_DOMAIN
        /* set arguments for Flashloader */
        s_params.set_boot_type(SharedParams::boot_type::T_FLASH);
        ack_cmd();
        // TODO: wait until message is send
        CALL_SYSRESET();
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif  // STOS_VERSION
    // do nothing if in FL
}


/**
 * @brief sends the FLASH_HELLO Opcode to the host
 *        send after switch from OS->FL to signal readyness
 * 
 */
void SFOC::send_flash_hello(){
    #ifdef SFOC_FL_DOMAIN
        response.opcode = sfoc_opcodes::FL_HELLO;
        response.id = this->host_id;
        response.len = 0;

        send();
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif
}

/**
 * @brief erase the specified sectors from flash
 *        refuses to erase FL sectors
 * 
 */
void SFOC::erase_flash(){
    #ifdef SFOC_FL_DOMAIN
        uint16_t start;
        uint16_t end;
        uint32_t ret;

        start = cmd.data[0] | cmd.data[1]<<8;
        end = cmd.data[2] | cmd.data[3]<<8;
        
        ret = Flash_Erase_Sectors(start, end);

        if(ret == HAL_FLASH_ERROR_NONE){
            ack_cmd();
        }
        else if(ret == HAL_FLASH_ERROR_WRP){
            nack_cmd(sfoc_nack_reason::WRITE_PROTECTION);
        }
        else{
            nack_cmd();
        }
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif

}

/**
 * @brief write to flash
 *
 * 
 */
void SFOC::write_flash(){
    #ifdef SFOC_FL_DOMAIN
        uint32_t data[4];
        uint32_t ret;

        data[0] = 0xDE;
        data[1] = 0xAD;
        data[2] = 0xBE;
        data[3] = 0xEF;

        ret = Flash_Write_Data(0x800C000, data, 4);

        if(!ret){
            ack_cmd();
        }
        else{
            nack_cmd();
        }
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif
}


void SFOC::go_os(){
    #ifdef SFOC_FL_DOMAIN
        s_params.set_boot_type(SharedParams::boot_type::T_REBOOT);
        state = stm_state::REBOOT;
        state_out = SFOC_EXIT_REBOOT;
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif
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
        case sfoc_opcodes::ERASE_SECTORS:
            erase_flash();
            return;
        case sfoc_opcodes::WRITE_MEMORY:
            write_flash();
            return;
        case sfoc_opcodes::GO_OS:
            go_os();
            return;
        default:
            nack_cmd(sfoc_nack_reason::UNSUPPORTED_OPCODE);
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
        case stm_state::BASE:
            decode();
            read_cmd();
            break;
        case stm_state::REBOOT:
            // nop state
            break;
        default:
            /* state shouldn't be reachable */
            state_out = SFOC_GENERAL_ERR;
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
            state_out = SFOC_TIMEOUT;
        }
        return state_out;
    }

    /* we've got a valid frame */
    STM_step();
    last_activity = HAL_GetTick();

    return state_out;
}
