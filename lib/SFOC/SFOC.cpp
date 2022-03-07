#include "SFOC.hpp"

#include <string.h>
#include "stm32f4xx_hal.h"


#ifdef SFOC_FL_DOMAIN
    /* protect FL sectors */
    extern "C" const uint32_t __bootrom_start__;
    extern "C" const uint32_t __bootrom_size__;

    uint32_t SFOC::buffer[stream_buffer_slots];
    /* 254=stream_frame_limit, not sure why not compiling */
    std::bitset<254> SFOC::buffer_mask{0};

    uint8_t SFOC::computed_hash[CMOX_SHA256_SIZE];

    bool SFOC::sectorWritable[FLASH_SECTOR_CNT] = {0}; // sets first to 0, and all others to 0
    uint32_t SFOC::sectorHead[FLASH_SECTOR_CNT];

    uint32_t SFOC::flash_addr;
    uint8_t SFOC::expected_frames;

    void (*SFOC::stream_callback)() = nullptr;
#endif /* SFOC_FL_DOMAIN */


uint16_t SFOC::ecu_id = SFOC_ECU_ID;
uint16_t SFOC::host_id = SFOC_HOST_ID;   // parameter received from OS, may be 0 to accept all
uint16_t SFOC::discovery_id = SFOC_DISCOVERY_ID;
uint32_t SFOC::timeout_ms;  // up to 136 years
uint32_t SFOC::last_activity;  // timestamp of last activity

enum SFOC::stm_state SFOC::state = stm_state::HELLO;
sfoc_status SFOC::state_out = SFOC_CONTINUE;

StallardOSCanMessage SFOC::in_frame;
SFOC::sfoc_message SFOC::cmd;
SFOC::sfoc_message SFOC::response;
StallardOSCanMessage SFOC::out_frame;

SharedParams SFOC::s_params;

StallardOSCANFilterDelayed SFOC::filter(SFOC_ECU_ID, SFOC_DISCOVERY_ID, AD_CAN_PORT);
StallardOSCANFilterDelayed SFOC::ms4EngRPM(STOS_CAN_ID_States_Temp_Press, 0, MS4_CAN_PORT);


void SFOC::setup(uint32_t timeout_ms){
    filter.setup();
    SFOC::timeout_ms = timeout_ms;
    last_activity = HAL_GetTick();
}


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


void SFOC::snack_cmd(uint8_t first_frame, uint8_t last_frame){
    response.id = host_id;
    response.opcode = sfoc_opcodes::SNACK;
    response.len = 2;

    response.data[0] = first_frame;
    response.data[1] = last_frame;
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
    response.id = SFOC_DISCOVERY_ID;
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

    response.len = 4;


    #if defined(SFOC_OS_DOMAIN)
        #ifdef SW_VERSION
            response.data[0] = SW_VERSION;
        #else
            response.data[0] = 0;
        #endif
        response.data[1] = STOS_VERSION;
        response.data[2] = s_params.get_fl_version();
    #elif defined(SFOC_FL_DOMAIN)
        response.data[0] = s_params.get_sw_version();
        response.data[1] = s_params.get_os_version();
        response.data[2] = FL_VERSION;
    #else
        send_nack(sfoc_nack_reason::WRONG_DOMAIN);
        #ifndef UNIT_TEST
        asm("bkpt");  //Zeige debugger
        #endif
        return;
    #endif

    response.data[3] = SFOC_VERSION;
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
    
    // select chip id based on the used uC
    #if defined(STM32F417IG)
        response.data[1] = 1;
    #else
        response.data[1] = 0;
    #endif

    send();
}

/**
 * @brief send the current domain to the host
 * 
 */
void SFOC::send_domain(){
    response.id = host_id;
    response.opcode = sfoc_opcodes::DOMAIN_ID;
    response.len=1;

    #ifdef SFOC_OS_DOMAIN
        response.data[0] = sfoc_domains::OS;
    #elif defined(SFOC_FL_DOMAIN)
        response.data[0] = sfoc_domains::FL;
    #else
        response.data[0] = sfoc_domains::RESERVED;
    #endif

    send();
}

/**
 * @brief checks if CU is allowed to switch to flashloader
 * 
 *        if allowed, will reboot an method will not return
 *        sends NACK otherwise
 */
void SFOC::go_flashloader(){
    if(SFOC::RPM == 0)
    {
    #ifdef SFOC_OS_DOMAIN
        /* set arguments for Flashloader */
        s_params.set_boot_type(SharedParams::boot_type::T_FLASH);
        // command is not ACKED, only FL_HELLO after reboot
        CALL_SYSRESET();
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif  // STOS_VERSION
    // do nothing if in FL
    }
    else
    {
        nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
    }
}


/**
 * @brief sends the FLASH_HELLO or OS_HELLO Opcode
 *        is automatically send on library start
 * 
 */
void SFOC::send_sfoc_hello(){
    response.id = host_id;
    response.len = 0;

    #if defined(SFOC_FL_DOMAIN)
        response.opcode = sfoc_opcodes::FL_HELLO;
    #elif defined(SFOC_OS_DOMAIN)
        response.opcode = sfoc_opcodes::OS_HELLO;
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
        return;
    #endif

    send();
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
        
        if(start>end || end > FLASH_SECTOR_CNT-1){
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            return;
        }

        ret = Flash_Erase_Sectors(start, end);

        if(ret == HAL_FLASH_ERROR_NONE){
            for(int i=start; i<=end; i++){
                /* reset write head for all sectors */
                sectorWritable[i] = true;
                sectorHead[i] = GetSectorToAddress(i);
            }
            ack_cmd();
        }
        else if(ret == HAL_FLASH_ERROR_WRP){
            nack_cmd(sfoc_nack_reason::WRITE_PROTECTION);
        }
        else{
            nack_cmd(sfoc_nack_reason::GEN_FLASH_ERROR);
        }
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif

}

/**
 * @brief write to flash
 *
 */
void SFOC::write_request(){
    #ifdef SFOC_FL_DOMAIN

        uint8_t n_frames;
        uint32_t n_bytes;
        uint32_t ret;

        uint16_t start_sector;
        uint16_t end_sector;


        n_frames = cmd.data[0];
        n_bytes = n_frames*stream_bytes_in_frame;

        flash_addr = cmd.data[1];
        flash_addr |= cmd.data[2] << 8;
        flash_addr |= cmd.data[3] << 16;
        flash_addr |= cmd.data[4] << 24;
        
        /* test if the write would hit the flashloader sectors */
        if(flash_addr < (uint32_t)(&__bootrom_start__) + (uint32_t)(&__bootrom_size__)){
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            return;
        }
        /* test if the requested write would exceed the flash memory */
        else if(flash_addr+(n_bytes) >= (FLASH_BASE + FLASH_TOTAL_SIZE)){
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            return;
        }
        /* test if buffer is large enough */
        else if(n_bytes > sizeof(buffer)){
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            return;
        }
        else if(n_frames == 0){
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            return;
        }
        /* at this point, flash_address is guaranteed to fit into the flash */


        /* erase all sectors where a write is planned
         * if the write head is behind, do not erase flash
         */
        start_sector = GetSector(flash_addr);
        end_sector = GetSector(flash_addr + n_frames*stream_bytes_in_frame);

        /* first sector got a change to already have data on it */
        if(!sectorWritable[start_sector] || flash_addr < sectorHead[start_sector]){
            ret = Flash_Erase_Sectors(start_sector, start_sector);
            if(ret){
                nack_cmd(ret==HAL_FLASH_ERROR_WRP ? sfoc_nack_reason::WRITE_PROTECTION : sfoc_nack_reason::GEN_FLASH_ERROR);
                return;
            }

            sectorWritable[start_sector] = true;
            sectorHead[start_sector] = GetSectorToAddress(start_sector);
        }

        /* any following sector needs erase in any case */
        if(end_sector > start_sector){
            ret = Flash_Erase_Sectors(start_sector+1, end_sector);
            if(ret){
                nack_cmd(ret==HAL_FLASH_ERROR_WRP ? sfoc_nack_reason::WRITE_PROTECTION : sfoc_nack_reason::GEN_FLASH_ERROR);
                return;
            }

            /* update status vars for erased sectors */
            for(int i=start_sector+1; i<=end_sector; i++){
                sectorWritable[i] = true;
                sectorHead[i] = GetSectorToAddress(i);
            }
        }   

        /* set stm into read data mode */
        expected_frames = n_frames;
        state = stm_state::DATA_RCV;
        stream_callback = &SFOC::flash_buffer;

        buffer_mask.set();  
        for(size_t b=n_frames; b<buffer_mask.size(); b++){
            /* pretend all frames above n_frames have already arrived */
            buffer_mask.reset(b);
        }

        memset(buffer, 0, sizeof(buffer));

        /* agree on parameters */
        ack_cmd();
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif
}


void SFOC::go_os(){
    #ifdef SFOC_FL_DOMAIN
        bool ret;
        /* send nack/ack to host */
        ret = validate_hash(false);
        if(ret){
            s_params.set_boot_type(SharedParams::boot_type::T_REBOOT);
            state = stm_state::REBOOT;
            state_out = SFOC_EXIT_REBOOT;
            /* no ACK, only OS_HELLO */
        }
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif
}


void SFOC::flush_buffers(){
    #ifdef SFOC_FL_DOMAIN
        /* buffer not implemented 
         * writes are always instant
         */
        ack_cmd();
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif
}


void SFOC::set_hash(){
    #ifdef SFOC_FL_DOMAIN
        // calculate offset for hash location
        // block holds hash itself, address and length of checksum area
        uint8_t seq;
    
        /* receive data */
        state = stm_state::HASH_RCV;

        /* write first data into buffer */
        seq = cmd.data[0];
        buffer[seq] = cmd.data[1];
        buffer[seq] |= cmd.data[2] << 8;
        buffer[seq] |= cmd.data[3] << 16;
        buffer[seq] |= cmd.data[4] << 24;
    #else
        nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
    #endif
}

void SFOC::rcv_hash(){
    #ifdef SFOC_FL_DOMAIN
        uint8_t seq;

        seq = cmd.data[0];
        buffer[seq] = cmd.data[1];
        buffer[seq] |= cmd.data[2] << 8;
        buffer[seq] |= cmd.data[3] << 16;
        buffer[seq] |= cmd.data[4] << 24;

        if(seq == 9){
            write_hash();
        }
    #endif
}

void SFOC::write_hash(){
    #ifdef SFOC_FL_DOMAIN
        state = stm_state::BASE; // return to normal ops in any case

        uint32_t ret;
        uint32_t hash_base = (FLASH_BASE+FLASH_TOTAL_SIZE) - 32 - 4 - 4;
        uint8_t sector = GetSector(hash_base);

        uint32_t addr = buffer[0];
        uint32_t len = buffer[1];


        /* do not allow to check bootloader */
        if(addr < (uint32_t)(&__bootrom_start__) + (uint32_t)(&__bootrom_size__)){
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            return;
        }
        /* test if the requested write would exceed the flash memory */
        else if(addr+(len) >= (FLASH_BASE + FLASH_TOTAL_SIZE)){
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            return;
        }

        /* next check if the hash can be written to 
        * it fails if:
        *      the protected area is in the last sector
        *  AND the last sector wasn't erased before
        */
        if(!sectorWritable[sector] || sectorHead[sector] > hash_base){
            /* erase if sector not used */
            if(GetSector(addr+len) < sector){
                ret = Flash_Erase_Sectors(sector, sector);
                if(ret){
                    nack_cmd(ret==HAL_FLASH_ERROR_WRP ? sfoc_nack_reason::WRITE_PROTECTION : sfoc_nack_reason::GEN_FLASH_ERROR);
                    return;
                }
            }
            /* else error */
            else{
                nack_cmd(sfoc_nack_reason::SECTOR_OCCUPIED); 
                return;
            }
        }

        /* write hash to flash and validate entry */
        ret = Flash_Write_Data(hash_base, buffer, 10);
        sectorHead[sector] = hash_base+(10*4); // int arithmetic
        if(ret){
            nack_cmd(ret==HAL_FLASH_ERROR_WRP ? sfoc_nack_reason::WRITE_PROTECTION : sfoc_nack_reason::GEN_FLASH_ERROR);
        }

        /* will send ack or nack */
        validate_hash(false);
    #endif
}


bool SFOC::validate_hash(bool silent){

    #ifdef SFOC_FL_DOMAIN
        cmox_hash_retval_t retval;
        size_t computed_size;

        uint32_t hash_base = (uint32_t)((FLASH_BASE+FLASH_TOTAL_SIZE) - 32 - 4 - 4); // int arithemtic (not ptr)

        uint32_t addr = ((uint32_t*)hash_base)[0];
        uint32_t len =  ((uint32_t*)hash_base)[1];

        uint8_t *hash = ((uint8_t*)hash_base) + 8;


        if(addr == 0 && len == 0){
            /* hash is disabled, always suceed */
            if(!silent)
                ack_cmd();
            return true;
        }


        if(addr < (uint32_t)(&__bootrom_start__) + (uint32_t)(&__bootrom_size__)){
            if(!silent)
                nack_cmd(sfoc_nack_reason::HASH_ERROR);
            return false;
        }
        /* test if the requested write would exceed the flash memory */
        else if(addr+(len) >= (FLASH_BASE + FLASH_TOTAL_SIZE)){
            if(!silent)
                nack_cmd(sfoc_nack_reason::HASH_ERROR);
            return false;
        }

        

        retval = cmox_hash_compute(CMOX_SHA256_ALGO,         /* Use SHA256 algorithm */
                                (uint8_t*)addr, len, /* Message to digest */
                                computed_hash,            /* Data buffer to receive digest data */
                                CMOX_SHA256_SIZE,         /* Expected digest size */
                                &computed_size);          /* Size of computed digest */


        if(retval != CMOX_HASH_SUCCESS){
            if(!silent)
                nack_cmd(sfoc_nack_reason::HASH_ERROR);
            return false;
        }
        if (computed_size != CMOX_SHA256_SIZE)
        {
            if(!silent)
                nack_cmd(sfoc_nack_reason::HASH_ERROR);
            return false;
        }

        if (memcmp(hash, computed_hash, computed_size) != 0)
        {
            if(!silent)
                nack_cmd(sfoc_nack_reason::INVALID_CHECKSUM);
            return false;
        }

        if(!silent){
            ack_cmd();
        }
        return true;
    #else
        if(!silent){
            nack_cmd(sfoc_nack_reason::WRONG_DOMAIN);
        }
        return false;
    #endif
}


void SFOC::disable_hash(){
    #ifdef SFOC_FL_DOMAIN
   
        uint32_t hash_base = (uint32_t)((FLASH_BASE+FLASH_TOTAL_SIZE) - 32 - 4 - 4); // int arithemtic (not ptr)
        uint32_t addr = ((uint32_t*)hash_base)[0];
        uint32_t len =  ((uint32_t*)hash_base)[1];

        uint8_t sector = GetSector(hash_base);
        uint32_t ret;

        /* setting flash to 0 is always possible
         * no matter the write-state of this region
         * therfore flash index is ignored and not updated
         */
        memset(buffer, 0, 10*4);
        ret = Flash_Write_Data(hash_base, buffer, 10);

        if(ret){
            nack_cmd(ret==HAL_FLASH_ERROR_WRP ? sfoc_nack_reason::WRITE_PROTECTION : sfoc_nack_reason::GEN_FLASH_ERROR);
            return;
        }
        ack_cmd();
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
        case sfoc_opcodes::DOMAIN_ID:
            send_domain();
            return;
        case sfoc_opcodes::GO_FL:
            go_flashloader();
            return;
        case sfoc_opcodes::ERASE_SECTORS:
            erase_flash();
            return;
        case sfoc_opcodes::WRITE_MEMORY:
            write_request();
            return;
        case sfoc_opcodes::GO_OS:
            go_os();
            return;
        case sfoc_opcodes::FLUSH_BUFFERS:
            flush_buffers();
            return;
        case sfoc_opcodes::SET_HASH:
            set_hash();
            return;
        case sfoc_opcodes::TEST_HASH:
            validate_hash(false);
            return;
        case sfoc_opcodes::DISABLE_HASH:
            disable_hash();
            return;
        default:
            nack_cmd(sfoc_nack_reason::UNSUPPORTED_OPCODE);
            break;
    }
}


void SFOC::rcv_stream(){

    #ifdef SFOC_FL_DOMAIN
        uint64_t val = in_frame.Val;
        uint16_t id = in_frame.ID;
        uint8_t seq;
        uint16_t buffer_idx;

        if(id != ecu_id){
            /* we do not serve discovery messages
            * in data mode, ignore the frame
            */
            return;
        }

        seq = (uint8_t)(val&0xFF);
        if(seq != 0xFF){
            

            if(seq < expected_frames){
                /* frames of 6 byte must be split into two buffer slots */
                buffer_idx = (uint16_t)(seq*stream_bytes_in_frame/4);
                if(seq%2==0){
                    buffer[buffer_idx] = (uint32_t)((val & 0xFFFFFFFF00) >> 8);
                    buffer[buffer_idx+1] |= (uint32_t)((val & 0xFFFF0000000000) >> 40);  // lower 2 bytes
                }else{
                    buffer[buffer_idx] |= (uint32_t)((val&0xFFFF00) << 8);  // upper 2 bytes
                    buffer[buffer_idx+1] = (uint32_t)((val&0xFFFFFFFF000000)>>24);
                }
                buffer_mask.reset(seq);
            }
            else{
                nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
            }
        }
        else if(seq==0xFF){
            /* end of stream frame 
             *
             * check for missing frames 
             * and request those
             * on complete stream, flash memory 
             */
            if(buffer_mask.count() == 0){
                ack_cmd();

                state = stm_state::BASE;
                /* flash if all frames have been transmitted */
                if(stream_callback != nullptr){
                    (*(stream_callback))();
                    stream_callback = nullptr;
                }
                else{
                    // something went wrong
                    nack_cmd();
                    #ifndef UNIT_TEST
                    asm("bkpt");  //Zeige debugger
                    #endif
                }                
                return;
            }

            /* at least one frame is missing
             * when this part is reached */
            uint8_t s_f = 0xFF; // terminator val
            uint8_t e_f = 0xFF-1; // highest val
            for(int b=0; b<expected_frames; b++){
                // first missing bit
                if(buffer_mask[b] && (s_f == 0xFF)){
                    s_f = b;
                }
                else if(!buffer_mask[b] && (s_f != 0xFF)){
                    e_f = b-1;
                    break;
                }
            }
            snack_cmd(s_f, e_f);
        }
        else{
            nack_cmd(sfoc_nack_reason::INVALID_PARAMETERS);
        }

    #endif  // SFOC_FL_DOMAIN
    /* this state is never hit in the wrong domain
     * so no else defined required 
     */
}


void SFOC::flash_buffer(){
    #ifdef SFOC_FL_DOMAIN
        uint32_t ret;
        uint16_t sector_start;
        uint16_t sector_end;
        uint32_t end_addr;

        uint32_t n_word = expected_frames*6/4; // convert frames to words

        ret = Flash_Write_Data(flash_addr, buffer, n_word);

        /* update all write heads (in case of sector overlap)*/
        end_addr = flash_addr + (n_word*4);
        sector_start = GetSector(flash_addr);
        sector_end = GetSector(end_addr);

        for(int i=sector_start; i<=sector_end; i++){
            /* on sector overlap, the head is in the next sector */
            if(i<sector_end){
                /* disable sector writability if end is reached */
                sectorWritable[i] = false;
            }
            else{
                sectorHead[i] = end_addr;
            }
        }


        if(ret == HAL_FLASH_ERROR_NONE){
            ack_cmd();
        }
        else if(ret == HAL_FLASH_ERROR_WRP){
            nack_cmd(sfoc_nack_reason::WRITE_PROTECTION);
        }
        else{
            nack_cmd();
        }

        /* go back to normal stm operations
        * even on error state
        */
        state = stm_state::BASE;
    #endif // SFOC_FL_DOMAIN
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
        case stm_state::DATA_RCV:
            rcv_stream();
            break;
        case stm_state::HASH_RCV:
            decode();
            rcv_hash();
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

    if(state == stm_state::HELLO){
        send_sfoc_hello();
        state = stm_state::BASE;
    }
    
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

    ret = MS4_CAN.receiveMessage(&SFOC::ms4Message);
    if(ret){
        ms4Message.unbuild();
        SFOC::RPM = ms4Message.rev;
    }
    /* we've got a valid frame */
    STM_step();
    last_activity = HAL_GetTick();

    return state_out;
}
