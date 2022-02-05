#ifndef _SFOC_H_
#define _SFOC_H_

#include <bitset>

#include "sharedParams.hpp" 
#include "StallardOScanTypes.hpp"
#include "StallardOScan.hpp"


#if __has_include("StallardOS.hpp")
    #include "StallardOS.hpp"  // OS define (and some other stuff)
    #define SFOC_OS_DOMAIN
#else
    #define SFOC_FL_DOMAIN
    #include "FLASH_SECTOR_DEFINES.h"
    #include "cmox_crypto.h"
#endif


#define SFOC_VERSION (0x01) // 0.1

#define SFOC_ECU_ID 0x123
#define SFOC_HOST_ID 0x124
#define SFOC_DISCOVERY_ID 0x125


typedef enum sfoc_status{
    SFOC_GENERAL_ERR = -2,
    SFOC_TIMEOUT = -1,
    SFOC_CONTINUE = 0,
    SFOC_EXIT_REBOOT = 1
}SFOC_Status;


/**
 * @brief handle the SFOC protocoll as client
 *        compiler flags decide the used DOMAIN
 *        mutliple domains could be combined
 * 
 *        only a single instance at a time may use 
 *        the stream buffer or perform flash ops
 * 
 *        only stateless operations are supported for parallel instances
 *        (this is done to safe memory on buffer)
 */
class SFOC{
    public:

        enum sfoc_nack_reason{
            UNKNOWN = 0x00,
            UNSUPPORTED_OPCODE = 0x01,
            WRONG_DOMAIN = 0x02,
            WRITE_PROTECTION = 0x03,
            READ_PROTECTION = 0x04,
            GEN_FLASH_ERROR = 0x05,
            INVALID_PARAMETERS = 0x06,
            INVALID_CHECKSUM = 0x07,
            HASH_ERROR = 0x08,
            SECTOR_OCCUPIED = 0x09,
        };


        static void setup(uint32_t timeout_ms=30000);

        /**
         * @brief iterate the internal STM, executing the protocol
         *        per iteration, 1 message is processed (if any is available)
         * 
         * @return SFOC_Status returns SFOC_TIMEOUT on timeout
         * @see SFOC_Status
         */
        static SFOC_Status stm_iterate();

        /**
         * @brief validate a region in flash
         *        send nack if a hash or checksum error occurs 
         * 
         * @param silent if silent, do not send frame on success, else send ack
         */
        static bool validate_hash(bool silent);

        static void nack_cmd(sfoc_nack_reason reason=sfoc_nack_reason::UNKNOWN);

    private:
        /********************** TYPES **************************/
        SFOC(); // force class static

        typedef enum sfoc_opcodes{
            NACK = 0x00,
            ACK = 0x01,
            SNACK = 0x02,

            DISCOVERY_REQUEST = 0x10,
            DISCOVERY_RESPONSE = 0x11,

            VERSION = 0x12,
            ID = 0x13,

            GO_FL = 0x14,
            FL_HELLO = 0x15,
            GO_OS = 0x16,
            OS_HELLO = 0x17,

            ERASE_SECTORS = 0x20,
            WRITE_MEMORY = 0x21,
            FLUSH_BUFFERS = 0x22,

            SET_HASH = 0x30,
            TEST_HASH = 0x31,
            DISABLE_HASH = 0x32
        }SFOC_Opcodes;


        /* stm variables
         *
         * stm holds state and output variable
         * if the state does not change, the old output is repeated
         * only on state change, the output may change
         */
        enum stm_state{
            HELLO,
            BASE,
            DATA_RCV,
            HASH_RCV,
            REBOOT
        };

        struct sfoc_message{
            uint16_t id;
            uint8_t opcode;
            uint8_t len;
            uint8_t data[8];
        };

        /********************** CONSTS ***************************/

        constexpr static uint16_t stream_bytes_in_frame = 6;
        constexpr static uint16_t stream_frame_limit = 254;
        constexpr static uint16_t stream_bytes_limit = 254*6;
        constexpr static uint16_t stream_buffer_slots = stream_bytes_limit/4;
        static_assert(stream_bytes_limit%4==0, "max stream buffer must fit into receive buffer (dividable by 4)");

        constexpr static uint16_t buffer_buffer_slots = stream_buffer_slots * 40;

        /********************** STATICS **************************/
        #ifdef SFOC_FL_DOMAIN
            
            static uint32_t buffer[stream_buffer_slots]; // max 255 frames, 4 bytes per frame
            static std::bitset<stream_frame_limit> buffer_mask; // holds missing frames 

            static uint8_t computed_hash[CMOX_SHA256_SIZE];

            static bool sectorWritable[FLASH_SECTOR_CNT];
            static uint32_t sectorHead[FLASH_SECTOR_CNT];

            static uint32_t flash_addr;  // desired write address
            static uint8_t expected_frames;

            static void (*stream_callback)(); // member ptr, after full stream rcv
        #endif /* SFOC_FL_DOMAIN */



        static uint16_t ecu_id;
        static uint16_t host_id;   // parameter received from OS, may be 0 to accept all
        static uint16_t discovery_id;
    
        static uint32_t timeout_ms;  // up to 136 years
        static uint32_t last_activity;  // timestamp of last activity

        //static StallardOSCANFilter filter;
        static enum stm_state state;
        static sfoc_status state_out;
        

        static StallardOSCanMessage in_frame;
        static sfoc_message cmd;
        static sfoc_message response;
        static StallardOSCanMessage out_frame;

        static SharedParams s_params;


        /********************** METHODS *************************/
        static void STM_step();
        
        /* processing commands */
        static void decode();
        static void encode();

        static void send();
        static void read_cmd();

        /* execute commands */
        static void ack_cmd();
        static void snack_cmd(uint8_t first_frame, uint8_t last_frame);
        

        static void send_discovery();
        static void send_version();
        static void send_id();
        static void go_flashloader();
        static void erase_flash();
        static void write_request();
        static void go_os();
        static void flush_buffers();

        static void set_hash();
        static void rcv_hash();
        static void write_hash();
        static void disable_hash();

        static void send_sfoc_hello();

        /* stream ops and callbacks */
        static void rcv_stream();
        static void flash_buffer();
};

#endif // _SFOC_H_
