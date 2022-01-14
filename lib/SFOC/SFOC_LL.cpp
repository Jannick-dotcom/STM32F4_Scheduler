#include "SFOC.hpp"

#include <string.h>
#include "stm32f4xx_hal.h"



void SFOC::decode(){
    uint8_t *val = (uint8_t*)&(in_frame.Val);
    uint8_t dlc = in_frame.dlc;
    uint16_t id = in_frame.ID;

    if(dlc == 0){
        // invalid packet, must have opCode
        return;
    }

    // the highest byte is OpCode
    cmd.len = dlc-1;
    for(int i=0; i<cmd.len; i++){
        cmd.data[i] = val[i];
    }
    cmd.opcode = val[cmd.len];
    cmd.id = id;
}


/**
 * @brief encode the current response for CAN transmission
 *        usually called by send
 * 
 */
void SFOC::encode(){
    uint64_t val = 0;
    uint8_t *val_arr = (uint8_t *)&val;

    for(int i=0; i<response.len; i++){
        val_arr[i] = response.data[i];
    }
    val_arr[response.len] = response.opcode;

    out_frame.ID = response.id;
    out_frame.dlc = response.len+1;
    out_frame.Val = val;
}


/**
 * @brief encode the current response for CAN transmission
 *        then send the message
 * 
 */
void SFOC::send(){
    encode();
    AD_CAN.sendMessage(&out_frame);
}