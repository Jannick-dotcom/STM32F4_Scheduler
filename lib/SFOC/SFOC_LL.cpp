#include "SFOC.hpp"

#include <string.h>
#include "stm32f4xx_hal.h"



void SFOC::decode(){
    uint8_t *val = (uint8_t*)&(in_frame.Val);
    uint8_t dlc = in_frame.dlc;
    uint16_t id = in_frame.ID;

    if(dlc != 8){
        // invalid packet, must have 8 Byte
        return;
    }

    // the highest byte is OpCode
    cmd.len = dlc-1;
    for(int i=0; i<cmd.len; i++){
        cmd.data[i] = val[i+1]; // assymetr. opcode offset
    }
    cmd.opcode = val[0];
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

    val_arr[0] = response.opcode;
    for(int i=0; i<response.len; i++){
        val_arr[i+1] = response.data[i]; // assymetr. opcode offset
    }
    /* remaining bytes in frame are used as padding
     * will hold old data, in this case
     * NOTE: for future implementation changes;
     *       set to 0 if sensitive data is transmitted 
     *       at any point during communication
     */

    out_frame.ID = response.id;
    out_frame.dlc = 8;
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