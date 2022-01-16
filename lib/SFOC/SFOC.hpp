#ifndef _SFOC_H_
#define _SFOC_H_

#include "sharedParams.hpp" 
#include "StallardOScanTypes.hpp"
#include "StallardOScan.hpp"

#ifdef STOS_VERSION
    #define SFOC_OS_DOMAIN
    #include "StallardOS.hpp"  // not sure why we even need this in OS
#else
    #define SFOC_FL_DOMAIN
#endif


#define SFOC_VERSION (0x01) // 0.1

#define ECU_ID 0x123
#define HOST_ID 0x124
#define SFOC_DISCOVERY 0x125


typedef enum sfoc_status{
    SFOC_GENERAL_ERR = -2,
    SFOC_TIMEOUT = -1,
    SFOC_CONTINUE = 0,
    SFOC_EXIT_REBOOT = 1
}SFOC_Status;



class SFOC{
    public:
        SFOC(uint16_t ecu_id, uint16_t host_id, uint16_t discovery_id, uint32_t timeout_ms=30000);
        SFOC_Status stm_iterate();
        void send_flash_hello();

    private:
        /********************** TYPES **************************/

        typedef enum sfoc_opcodes{
            NACK = 0x00,
            ACK = 0x01,
            DISCOVERY_REQUEST = 0x02,
            DISCOVERY_RESPONSE = 0x03,
            VERSION = 0x04,
            ID = 0x05,
            GO_FL = 0x06,
            FL_HELLO = 0x07
        }SFOC_Opcodes;

        typedef enum stm_state{
            BASE
        }STM_State;

        struct sfoc_message{
            uint16_t id;
            uint8_t opcode;
            uint8_t len;
            uint8_t data[8];
        };

        /********************** VARS **************************/

        const uint16_t ecu_id;
        const uint16_t host_id;   // parameter received from OS, may be 0 to accept all
        const uint16_t discovery_id;
    
        const uint32_t timeout_ms;  // up to 136 years
        uint32_t last_activity;  // timestamp of last activity

        const StallardOSCANFilter filter;
        STM_State state;

        StallardOSCanMessage in_frame;
        sfoc_message cmd;
        sfoc_message response;
        StallardOSCanMessage out_frame;

        SharedParams s_params;

        /********************** METHODS *************************/
        void STM_step();
        
        /* processing commands */
        void decode();
        void encode();

        void send();
        void read_cmd();

        /* execute commands */
        void ack_cmd();
        void nack_cmd();

        void send_discovery();
        void send_version();
        void send_id();
        void go_flashloader();
};

#endif // _SFOC_H_