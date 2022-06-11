#ifndef StallardOScanStructs_hpp
#define StallardOScanStructs_hpp
#include "stdint.h"
#include "StallardOScanTypes.hpp"
#include <math.h>
#include "StallardOScanIDs.h"

struct STOS_CAN_PDU_PDU_Relais_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_PDU_Relais_Status;
    const uint16_t _size = 3;
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_1 = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_10 = {0, 1, 1, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_11 = {0, 1, 2, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_12 = {0, 1, 3, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_13 = {0, 1, 4, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_14 = {0, 1, 5, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_15 = {0, 1, 6, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_16 = {0, 1, 7, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_17 = {0, 1, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_18 = {0, 1, 9, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_19 = {0, 1, 10, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_2 = {0, 1, 11, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_3 = {0, 1, 12, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_4 = {0, 1, 13, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_5 = {0, 1, 14, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_6 = {0, 1, 15, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_7 = {0, 1, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_8 = {0, 1, 17, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_9 = {0, 1, 18, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Relais_Status_1 = {0, 1, 19, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ADCAN_EL_Relais_Status_2 = {0, 1, 20, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_PDU_Relais_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= ADCAN_EL_Fuse_Status_1.build();
        Val |= ADCAN_EL_Fuse_Status_10.build();
        Val |= ADCAN_EL_Fuse_Status_11.build();
        Val |= ADCAN_EL_Fuse_Status_12.build();
        Val |= ADCAN_EL_Fuse_Status_13.build();
        Val |= ADCAN_EL_Fuse_Status_14.build();
        Val |= ADCAN_EL_Fuse_Status_15.build();
        Val |= ADCAN_EL_Fuse_Status_16.build();
        Val |= ADCAN_EL_Fuse_Status_17.build();
        Val |= ADCAN_EL_Fuse_Status_18.build();
        Val |= ADCAN_EL_Fuse_Status_19.build();
        Val |= ADCAN_EL_Fuse_Status_2.build();
        Val |= ADCAN_EL_Fuse_Status_3.build();
        Val |= ADCAN_EL_Fuse_Status_4.build();
        Val |= ADCAN_EL_Fuse_Status_5.build();
        Val |= ADCAN_EL_Fuse_Status_6.build();
        Val |= ADCAN_EL_Fuse_Status_7.build();
        Val |= ADCAN_EL_Fuse_Status_8.build();
        Val |= ADCAN_EL_Fuse_Status_9.build();
        Val |= ADCAN_EL_Relais_Status_1.build();
        Val |= ADCAN_EL_Relais_Status_2.build();

    }
    void unbuild()
    {
        ADCAN_EL_Fuse_Status_1.unbuild(Val);
        ADCAN_EL_Fuse_Status_10.unbuild(Val);
        ADCAN_EL_Fuse_Status_11.unbuild(Val);
        ADCAN_EL_Fuse_Status_12.unbuild(Val);
        ADCAN_EL_Fuse_Status_13.unbuild(Val);
        ADCAN_EL_Fuse_Status_14.unbuild(Val);
        ADCAN_EL_Fuse_Status_15.unbuild(Val);
        ADCAN_EL_Fuse_Status_16.unbuild(Val);
        ADCAN_EL_Fuse_Status_17.unbuild(Val);
        ADCAN_EL_Fuse_Status_18.unbuild(Val);
        ADCAN_EL_Fuse_Status_19.unbuild(Val);
        ADCAN_EL_Fuse_Status_2.unbuild(Val);
        ADCAN_EL_Fuse_Status_3.unbuild(Val);
        ADCAN_EL_Fuse_Status_4.unbuild(Val);
        ADCAN_EL_Fuse_Status_5.unbuild(Val);
        ADCAN_EL_Fuse_Status_6.unbuild(Val);
        ADCAN_EL_Fuse_Status_7.unbuild(Val);
        ADCAN_EL_Fuse_Status_8.unbuild(Val);
        ADCAN_EL_Fuse_Status_9.unbuild(Val);
        ADCAN_EL_Relais_Status_1.unbuild(Val);
        ADCAN_EL_Relais_Status_2.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Current_Sensors : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Current_Sensors;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_1 = {0, 8, 0, 0, 0, 0.1568627451, -20};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-20|20.0000000005]
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_2 = {0, 8, 8, 0, 0, 0.1568627451, -20};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-20|20.0000000005]
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_3 = {0, 8, 16, 0, 0, 0.1568627451, -20};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-20|20.0000000005]
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_4 = {0, 8, 24, 0, 0, 0.1568627451, -20};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-20|20.0000000005]
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_5 = {0, 8, 32, 0, 0, 0.2352941176, -30};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-30|29.999999988]
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_6 = {0, 8, 40, 0, 0, 0.2352941176, -30};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-30|29.999999988]
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_7 = {0, 8, 48, 0, 0, 0.2352941176, -30};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-30|29.999999988]
    CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_8 = {0, 8, 56, 0, 0, 0.7843137255, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|200]
    STOS_CAN_PDU_Current_Sensors() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= ADCAN_EL_Current_Sensor_1.build();
        Val |= ADCAN_EL_Current_Sensor_2.build();
        Val |= ADCAN_EL_Current_Sensor_3.build();
        Val |= ADCAN_EL_Current_Sensor_4.build();
        Val |= ADCAN_EL_Current_Sensor_5.build();
        Val |= ADCAN_EL_Current_Sensor_6.build();
        Val |= ADCAN_EL_Current_Sensor_7.build();
        Val |= ADCAN_EL_Current_Sensor_8.build();

    }
    void unbuild()
    {
        ADCAN_EL_Current_Sensor_1.unbuild(Val);
        ADCAN_EL_Current_Sensor_2.unbuild(Val);
        ADCAN_EL_Current_Sensor_3.unbuild(Val);
        ADCAN_EL_Current_Sensor_4.unbuild(Val);
        ADCAN_EL_Current_Sensor_5.unbuild(Val);
        ADCAN_EL_Current_Sensor_6.unbuild(Val);
        ADCAN_EL_Current_Sensor_7.unbuild(Val);
        ADCAN_EL_Current_Sensor_8.unbuild(Val);
    }
};
struct STOS_CAN_PDU_BMS_HYB_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_BMS_HYB_Status;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> SHUTDOWN_BMS_HYB = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_BMS_HYB_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= SHUTDOWN_BMS_HYB.build();

    }
    void unbuild()
    {
        SHUTDOWN_BMS_HYB.unbuild(Val);
    }
};
struct STOS_CAN_PDU_BMS_HOMO_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_BMS_HOMO_Status;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> SHUTDOWN_BMS_HOMO = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_BMS_HOMO_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= SHUTDOWN_BMS_HOMO.build();

    }
    void unbuild()
    {
        SHUTDOWN_BMS_HOMO.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO1_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO1_Shift;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Rx_Shift_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO1_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Shift_ControlWord.build();

    }
    void unbuild()
    {
        Rx_Shift_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO1_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO1_Clutch;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Rx_Clutch_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO1_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Clutch_ControlWord.build();

    }
    void unbuild()
    {
        Rx_Clutch_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO1_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO1_HAL_1;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Rx_HAL_1_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO1_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_HAL_1_ControlWord.build();

    }
    void unbuild()
    {
        Rx_HAL_1_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO1_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO1_HAL_2;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Rx_HAL_2_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO1_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_HAL_2_ControlWord.build();

    }
    void unbuild()
    {
        Rx_HAL_2_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO1_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO1_Airbox;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Rx_Airbox_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO1_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Airbox_ControlWord.build();

    }
    void unbuild()
    {
        Rx_Airbox_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO1_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO1_ARH_1;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Rx_ARH_1_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO1_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_ARH_1_ControlWord.build();

    }
    void unbuild()
    {
        Rx_ARH_1_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO1_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO1_ARH_2;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Rx_ARH_2_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO1_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_ARH_2_ControlWord.build();

    }
    void unbuild()
    {
        Rx_ARH_2_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO1_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO1_Shift;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Tx_Shift_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO1_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Shift_ControlWord.build();

    }
    void unbuild()
    {
        Tx_Shift_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO1_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO1_Clutch;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Tx_Clutch_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO1_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Clutch_ControlWord.build();

    }
    void unbuild()
    {
        Tx_Clutch_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO1_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO1_HAL_1;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Tx_HAL_1_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO1_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_HAL_1_ControlWord.build();

    }
    void unbuild()
    {
        Tx_HAL_1_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO1_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO1_HAL_2;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Tx_HAL_2_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO1_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_HAL_2_ControlWord.build();

    }
    void unbuild()
    {
        Tx_HAL_2_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO1_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO1_Airbox;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Tx_Airbox_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO1_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Airbox_ControlWord.build();

    }
    void unbuild()
    {
        Tx_Airbox_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO1_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO1_ARH_1;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Tx_ARH_1_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO1_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_ARH_1_ControlWord.build();

    }
    void unbuild()
    {
        Tx_ARH_1_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO1_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO1_ARH_2;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Tx_ARH_2_ControlWord = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO1_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_ARH_2_ControlWord.build();

    }
    void unbuild()
    {
        Tx_ARH_2_ControlWord.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO2_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO2_Shift;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_Shift_TargetPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO2_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Shift_TargetPosition.build();

    }
    void unbuild()
    {
        Rx_Shift_TargetPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO2_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO2_Clutch;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_Clutch_TargetPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO2_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Clutch_TargetPosition.build();

    }
    void unbuild()
    {
        Rx_Clutch_TargetPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO2_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO2_HAL_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_HAL_1_TargetPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO2_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_HAL_1_TargetPosition.build();

    }
    void unbuild()
    {
        Rx_HAL_1_TargetPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO2_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO2_HAL_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_HAL_2_TargetPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO2_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_HAL_2_TargetPosition.build();

    }
    void unbuild()
    {
        Rx_HAL_2_TargetPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO2_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO2_Airbox;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_Airbox_TargetPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO2_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Airbox_TargetPosition.build();

    }
    void unbuild()
    {
        Rx_Airbox_TargetPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO2_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO2_ARH_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_ARH_1_TargetPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO2_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_ARH_1_TargetPosition.build();

    }
    void unbuild()
    {
        Rx_ARH_1_TargetPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO2_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO2_ARH_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_ARH_2_TargetPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO2_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_ARH_2_TargetPosition.build();

    }
    void unbuild()
    {
        Rx_ARH_2_TargetPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO2_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO2_Shift;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_Shift_ActualPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO2_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Shift_ActualPosition.build();

    }
    void unbuild()
    {
        Tx_Shift_ActualPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO2_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO2_Clutch;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_Clutch_ActualPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO2_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Clutch_ActualPosition.build();

    }
    void unbuild()
    {
        Tx_Clutch_ActualPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO2_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO2_HAL_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_HAL_1_ActualPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO2_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_HAL_1_ActualPosition.build();

    }
    void unbuild()
    {
        Tx_HAL_1_ActualPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO2_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO2_HAL_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_HAL_2_ActualPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO2_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_HAL_2_ActualPosition.build();

    }
    void unbuild()
    {
        Tx_HAL_2_ActualPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO2_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO2_Airbox;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_Airbox_ActualPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO2_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Airbox_ActualPosition.build();

    }
    void unbuild()
    {
        Tx_Airbox_ActualPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO2_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO2_ARH_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_ARH_1_ActualPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO2_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_ARH_1_ActualPosition.build();

    }
    void unbuild()
    {
        Tx_ARH_1_ActualPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO2_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO2_ARH_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_ARH_2_ActualPosition = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO2_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_ARH_2_ActualPosition.build();

    }
    void unbuild()
    {
        Tx_ARH_2_ActualPosition.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO3_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO3_Shift;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_Shift_TargetVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO3_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Shift_TargetVelocity.build();

    }
    void unbuild()
    {
        Rx_Shift_TargetVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO3_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO3_Clutch;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_Clutch_TargetVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO3_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Clutch_TargetVelocity.build();

    }
    void unbuild()
    {
        Rx_Clutch_TargetVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO3_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO3_HAL_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_HAL_1_TargetVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO3_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_HAL_1_TargetVelocity.build();

    }
    void unbuild()
    {
        Rx_HAL_1_TargetVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO3_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO3_HAL_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_HAL_2_TargetVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO3_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_HAL_2_TargetVelocity.build();

    }
    void unbuild()
    {
        Rx_HAL_2_TargetVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO3_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO3_Airbox;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_Airbox_TargetVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO3_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_Airbox_TargetVelocity.build();

    }
    void unbuild()
    {
        Rx_Airbox_TargetVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO3_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO3_ARH_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_ARH_1_TargetVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO3_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_ARH_1_TargetVelocity.build();

    }
    void unbuild()
    {
        Rx_ARH_1_TargetVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_RxPDO3_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_RxPDO3_ARH_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Rx_ARH_2_TargetVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_RxPDO3_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rx_ARH_2_TargetVelocity.build();

    }
    void unbuild()
    {
        Rx_ARH_2_TargetVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO3_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO3_Shift;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_Shift_ActualVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO3_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Shift_ActualVelocity.build();

    }
    void unbuild()
    {
        Tx_Shift_ActualVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO3_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO3_Clutch;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_Clutch_ActualVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO3_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Clutch_ActualVelocity.build();

    }
    void unbuild()
    {
        Tx_Clutch_ActualVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO3_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO3_HAL_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_HAL_1_ActualVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO3_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_HAL_1_ActualVelocity.build();

    }
    void unbuild()
    {
        Tx_HAL_1_ActualVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO3_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO3_HAL_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_HAL_2_ActualVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO3_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_HAL_2_ActualVelocity.build();

    }
    void unbuild()
    {
        Tx_HAL_2_ActualVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO3_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO3_Airbox;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_Airbox_ActualVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO3_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_Airbox_ActualVelocity.build();

    }
    void unbuild()
    {
        Tx_Airbox_ActualVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO3_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO3_ARH_1;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_ARH_1_ActualVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO3_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_ARH_1_ActualVelocity.build();

    }
    void unbuild()
    {
        Tx_ARH_1_ActualVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_TxPDO3_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_TxPDO3_ARH_2;
    const uint16_t _size = 6;
    CAN_Signal<uint32_t> Tx_ARH_2_ActualVelocity = {0, 32, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_TxPDO3_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Tx_ARH_2_ActualVelocity.build();

    }
    void unbuild()
    {
        Tx_ARH_2_ActualVelocity.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Upload_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Upload_Shift;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Upload_Shift() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Upload_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Upload_Clutch;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Upload_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Upload_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Upload_HAL_1;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Upload_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Upload_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Upload_HAL_2;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Upload_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Upload_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Upload_Airbox;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Upload_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Upload_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Upload_ARH_1;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Upload_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Upload_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Upload_ARH_2;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Upload_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Download_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Download_Shift;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Download_Shift() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Download_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Download_Clutch;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Download_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Download_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Download_HAL_1;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Download_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Download_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Download_HAL_2;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Download_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Download_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Download_Airbox;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Download_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Download_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Download_ARH_1;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Download_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SDO_Download_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SDO_Download_ARH_2;
    const uint16_t _size = 8;
    STOS_CAN_PDU_CanOPEN_SDO_Download_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_SYNC : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_SYNC;
    const uint16_t _size = 0;
    STOS_CAN_PDU_CanOPEN_SYNC() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_NMT : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_NMT;
    const uint16_t _size = 2;
    STOS_CAN_PDU_CanOPEN_NMT() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_CanOPEN_BootUp_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_BootUp_Shift;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> CanOPEN_BOOTUP_Shifting = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_BootUp_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_BOOTUP_Shifting.build();

    }
    void unbuild()
    {
        CanOPEN_BOOTUP_Shifting.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_BootUp_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_BootUp_Clutch;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> CanOPEN_BOOTUP_Clutch = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_BootUp_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_BOOTUP_Clutch.build();

    }
    void unbuild()
    {
        CanOPEN_BOOTUP_Clutch.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_BootUp_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_BootUp_HAL_1;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> CanOPEN_BOOTUP_HAL_1 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_BootUp_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_BOOTUP_HAL_1.build();

    }
    void unbuild()
    {
        CanOPEN_BOOTUP_HAL_1.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_BootUp_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_BootUp_HAL_2;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> CanOPEN_BOOTUP_HAL_2 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_BootUp_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_BOOTUP_HAL_2.build();

    }
    void unbuild()
    {
        CanOPEN_BOOTUP_HAL_2.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_BootUp_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_BootUp_Airbox;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> CanOPEN_BOOTUP_Airbox = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_BootUp_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_BOOTUP_Airbox.build();

    }
    void unbuild()
    {
        CanOPEN_BOOTUP_Airbox.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_BootUp_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_BootUp_ARH_1;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> CanOPEN_BOOTUP_ARH_1 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_BootUp_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_BOOTUP_ARH_1.build();

    }
    void unbuild()
    {
        CanOPEN_BOOTUP_ARH_1.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_BootUp_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_BootUp_ARH_2;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> CanOPEN_BOOTUP_ARH_2 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_BootUp_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_BOOTUP_ARH_2.build();

    }
    void unbuild()
    {
        CanOPEN_BOOTUP_ARH_2.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_Error_Shift : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_Error_Shift;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> CanOPEN_Shift_Error0 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_Shift_Error1 = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_Shift_Error_Reg = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> CanOPEN_Shift_Error_FE = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_Error_Shift() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_Shift_Error0.build();
        Val |= CanOPEN_Shift_Error1.build();
        Val |= CanOPEN_Shift_Error_Reg.build();
        Val |= CanOPEN_Shift_Error_FE.build();

    }
    void unbuild()
    {
        CanOPEN_Shift_Error0.unbuild(Val);
        CanOPEN_Shift_Error1.unbuild(Val);
        CanOPEN_Shift_Error_Reg.unbuild(Val);
        CanOPEN_Shift_Error_FE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_Error_Clutch : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_Error_Clutch;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> CanOPEN_Clutch_Error0 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_Clutch_Error1 = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_Clutch_Error_Reg = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> CanOPEN_Clutch_Error_FE = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_Error_Clutch() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_Clutch_Error0.build();
        Val |= CanOPEN_Clutch_Error1.build();
        Val |= CanOPEN_Clutch_Error_Reg.build();
        Val |= CanOPEN_Clutch_Error_FE.build();

    }
    void unbuild()
    {
        CanOPEN_Clutch_Error0.unbuild(Val);
        CanOPEN_Clutch_Error1.unbuild(Val);
        CanOPEN_Clutch_Error_Reg.unbuild(Val);
        CanOPEN_Clutch_Error_FE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_Error_HAL_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_Error_HAL_1;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> CanOPEN_HAL_1_Error0 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_HAL_1_Error1 = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_HAL_1_Error_Reg = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> CanOPEN_HAL_1_Error_FE = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_Error_HAL_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_HAL_1_Error0.build();
        Val |= CanOPEN_HAL_1_Error1.build();
        Val |= CanOPEN_HAL_1_Error_Reg.build();
        Val |= CanOPEN_HAL_1_Error_FE.build();

    }
    void unbuild()
    {
        CanOPEN_HAL_1_Error0.unbuild(Val);
        CanOPEN_HAL_1_Error1.unbuild(Val);
        CanOPEN_HAL_1_Error_Reg.unbuild(Val);
        CanOPEN_HAL_1_Error_FE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_Error_HAL_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_Error_HAL_2;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> CanOPEN_HAL_2_Error0 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_HAL_2_Error1 = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_HAL_2_Error_Reg = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> CanOPEN_HAL_2_Error_FE = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_Error_HAL_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_HAL_2_Error0.build();
        Val |= CanOPEN_HAL_2_Error1.build();
        Val |= CanOPEN_HAL_2_Error_Reg.build();
        Val |= CanOPEN_HAL_2_Error_FE.build();

    }
    void unbuild()
    {
        CanOPEN_HAL_2_Error0.unbuild(Val);
        CanOPEN_HAL_2_Error1.unbuild(Val);
        CanOPEN_HAL_2_Error_Reg.unbuild(Val);
        CanOPEN_HAL_2_Error_FE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_Error_Airbox : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_Error_Airbox;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> CanOPEN_Airbox_Error0 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_Airbox_Error1 = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_Airbox_Error_Reg = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> CanOPEN_Airbo_xError_FE = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_Error_Airbox() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_Airbox_Error0.build();
        Val |= CanOPEN_Airbox_Error1.build();
        Val |= CanOPEN_Airbox_Error_Reg.build();
        Val |= CanOPEN_Airbo_xError_FE.build();

    }
    void unbuild()
    {
        CanOPEN_Airbox_Error0.unbuild(Val);
        CanOPEN_Airbox_Error1.unbuild(Val);
        CanOPEN_Airbox_Error_Reg.unbuild(Val);
        CanOPEN_Airbo_xError_FE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_Error_ARH_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_Error_ARH_1;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> CanOPEN_ARH_1_Error0 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_ARH_1_Error1 = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_ARH_1_Error_Reg = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> CanOPEN_ARH_1_Error_FE = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_Error_ARH_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_ARH_1_Error0.build();
        Val |= CanOPEN_ARH_1_Error1.build();
        Val |= CanOPEN_ARH_1_Error_Reg.build();
        Val |= CanOPEN_ARH_1_Error_FE.build();

    }
    void unbuild()
    {
        CanOPEN_ARH_1_Error0.unbuild(Val);
        CanOPEN_ARH_1_Error1.unbuild(Val);
        CanOPEN_ARH_1_Error_Reg.unbuild(Val);
        CanOPEN_ARH_1_Error_FE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_CanOPEN_Error_ARH_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_CanOPEN_Error_ARH_2;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> CanOPEN_ARH_2_Error0 = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_ARH_2_Error1 = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> CanOPEN_ARH_2_Error_Reg = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> CanOPEN_ARH_2_Error_FE = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_CanOPEN_Error_ARH_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= CanOPEN_ARH_2_Error0.build();
        Val |= CanOPEN_ARH_2_Error1.build();
        Val |= CanOPEN_ARH_2_Error_Reg.build();
        Val |= CanOPEN_ARH_2_Error_FE.build();

    }
    void unbuild()
    {
        CanOPEN_ARH_2_Error0.unbuild(Val);
        CanOPEN_ARH_2_Error1.unbuild(Val);
        CanOPEN_ARH_2_Error_Reg.unbuild(Val);
        CanOPEN_ARH_2_Error_FE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_ARH_PWM : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_ARH_PWM;
    const uint16_t _size = 2;
    CAN_Signal<uint8_t> ARH_1_PWM = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    CAN_Signal<uint8_t> ARH_2_PWM = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    STOS_CAN_PDU_ARH_PWM() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= ARH_1_PWM.build();
        Val |= ARH_2_PWM.build();

    }
    void unbuild()
    {
        ARH_1_PWM.unbuild(Val);
        ARH_2_PWM.unbuild(Val);
    }
};
struct STOS_CAN_PDU_ARH_Homing : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_ARH_Homing;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> ARH_1_Homing = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> ARH_2_Homing = {0, 1, 1, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_ARH_Homing() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= ARH_1_Homing.build();
        Val |= ARH_2_Homing.build();

    }
    void unbuild()
    {
        ARH_1_Homing.unbuild(Val);
        ARH_2_Homing.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Gear_Sensor : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Gear_Sensor;
    const uint16_t _size = 3;
    CAN_Signal<uint8_t> Gear_Signal_Fake = {0, 3, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> Gear_Signal_Real = {0, 3, 3, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> Gear_Voltage_Fake = {0, 8, 8, 0, 0, 0.0196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.999989]
    CAN_Signal<uint8_t> Gear_Voltage_Real = {0, 8, 16, 0, 0, 0.0196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.999989]
    STOS_CAN_PDU_Gear_Sensor() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Gear_Signal_Fake.build();
        Val |= Gear_Signal_Real.build();
        Val |= Gear_Voltage_Fake.build();
        Val |= Gear_Voltage_Real.build();

    }
    void unbuild()
    {
        Gear_Signal_Fake.unbuild(Val);
        Gear_Signal_Real.unbuild(Val);
        Gear_Voltage_Fake.unbuild(Val);
        Gear_Voltage_Real.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_Discovery : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_Discovery;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_Discovery() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_FCU_Host : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_FCU_Host;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_FCU_Host() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_FCU_Client : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_FCU_Client;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_FCU_Client() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_RCU_Host : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_RCU_Host;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_RCU_Host() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_RCU_Client : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_RCU_Client;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_RCU_Client() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_PCU_Host : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_PCU_Host;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_PCU_Host() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_PCU_Client : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_PCU_Client;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_PCU_Client() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_SWCU_Host : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_SWCU_Host;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_SWCU_Host() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_SWCU_Client : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_SWCU_Client;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_SWCU_Client() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_BMS_HOMO_Host : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_BMS_HOMO_Host;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_BMS_HOMO_Host() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_BMS_HOMO_Client : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_BMS_HOMO_Client;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_BMS_HOMO_Client() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_BMS_HYB_Host : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_BMS_HYB_Host;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_BMS_HYB_Host() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_Flash_Over_Can_BMS_HYB_Client : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Flash_Over_Can_BMS_HYB_Client;
    const uint16_t _size = 8;
    STOS_CAN_PDU_Flash_Over_Can_BMS_HYB_Client() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_FCU_Health : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_FCU_Health;
    const uint16_t _size = 4;
    CAN_Signal<uint8_t> FCU_CPU_Load = {0, 7, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> FCU_CAN1_Tx_Fifo_Lvl = {0, 3, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> FCU_CAN2_Tx_Fifo_Lvl = {0, 3, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> FCU_Temp = {0, 8, 24, 0, 0, 0.5490196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|139.999999989]
    STOS_CAN_PDU_FCU_Health() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= FCU_CPU_Load.build();
        Val |= FCU_CAN1_Tx_Fifo_Lvl.build();
        Val |= FCU_CAN2_Tx_Fifo_Lvl.build();
        Val |= FCU_Temp.build();

    }
    void unbuild()
    {
        FCU_CPU_Load.unbuild(Val);
        FCU_CAN1_Tx_Fifo_Lvl.unbuild(Val);
        FCU_CAN2_Tx_Fifo_Lvl.unbuild(Val);
        FCU_Temp.unbuild(Val);
    }
};
struct STOS_CAN_PDU_RCU_Health : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_RCU_Health;
    const uint16_t _size = 4;
    CAN_Signal<uint8_t> RCU_CPU_Load = {0, 7, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> RCU_CAN1_Tx_Fifo_Lvl = {0, 3, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> RCU_CAN2_Tx_Fifo_Lvl = {0, 3, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> RCU_Temp = {0, 8, 24, 0, 0, 0.5490196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|139.999999989]
    STOS_CAN_PDU_RCU_Health() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= RCU_CPU_Load.build();
        Val |= RCU_CAN1_Tx_Fifo_Lvl.build();
        Val |= RCU_CAN2_Tx_Fifo_Lvl.build();
        Val |= RCU_Temp.build();

    }
    void unbuild()
    {
        RCU_CPU_Load.unbuild(Val);
        RCU_CAN1_Tx_Fifo_Lvl.unbuild(Val);
        RCU_CAN2_Tx_Fifo_Lvl.unbuild(Val);
        RCU_Temp.unbuild(Val);
    }
};
struct STOS_CAN_PDU_PDU_Health : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_PDU_Health;
    const uint16_t _size = 4;
    CAN_Signal<uint8_t> PDU_CPU_Load = {0, 7, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> PDU_CAN1_Tx_Fifo_Lvl = {0, 3, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> PDU_CAN2_Tx_Fifo_Lvl = {0, 3, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> PDU_Temp = {0, 8, 24, 0, 0, 0.5490196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|139.999999989]
    STOS_CAN_PDU_PDU_Health() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= PDU_CPU_Load.build();
        Val |= PDU_CAN1_Tx_Fifo_Lvl.build();
        Val |= PDU_CAN2_Tx_Fifo_Lvl.build();
        Val |= PDU_Temp.build();

    }
    void unbuild()
    {
        PDU_CPU_Load.unbuild(Val);
        PDU_CAN1_Tx_Fifo_Lvl.unbuild(Val);
        PDU_CAN2_Tx_Fifo_Lvl.unbuild(Val);
        PDU_Temp.unbuild(Val);
    }
};
struct STOS_CAN_PDU_SWCU_Health : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_SWCU_Health;
    const uint16_t _size = 4;
    CAN_Signal<uint8_t> SWCU_CPU_Load = {0, 7, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> SWCU_CAN1_Tx_Fifo_Lvl = {0, 3, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> SWCU_CAN2_Tx_Fifo_Lvl = {0, 3, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> SWCU_Temp = {0, 8, 24, 0, 0, 0.5490196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|139.999999989]
    STOS_CAN_PDU_SWCU_Health() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= SWCU_CPU_Load.build();
        Val |= SWCU_CAN1_Tx_Fifo_Lvl.build();
        Val |= SWCU_CAN2_Tx_Fifo_Lvl.build();
        Val |= SWCU_Temp.build();

    }
    void unbuild()
    {
        SWCU_CPU_Load.unbuild(Val);
        SWCU_CAN1_Tx_Fifo_Lvl.unbuild(Val);
        SWCU_CAN2_Tx_Fifo_Lvl.unbuild(Val);
        SWCU_Temp.unbuild(Val);
    }
};
struct STOS_CAN_PDU_BMS_HOMO_Health : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_BMS_HOMO_Health;
    const uint16_t _size = 4;
    CAN_Signal<uint8_t> BMS_HOMO_CPU_Load = {0, 7, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> BMS_HOMO_CAN1_Tx_Fifo_Lvl = {0, 3, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> BMS_HOMO_CAN2_Tx_Fifo_Lvl = {0, 3, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> BMS_HOMO_Temp = {0, 8, 24, 0, 0, 0.5490196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|139.999999989]
    STOS_CAN_PDU_BMS_HOMO_Health() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= BMS_HOMO_CPU_Load.build();
        Val |= BMS_HOMO_CAN1_Tx_Fifo_Lvl.build();
        Val |= BMS_HOMO_CAN2_Tx_Fifo_Lvl.build();
        Val |= BMS_HOMO_Temp.build();

    }
    void unbuild()
    {
        BMS_HOMO_CPU_Load.unbuild(Val);
        BMS_HOMO_CAN1_Tx_Fifo_Lvl.unbuild(Val);
        BMS_HOMO_CAN2_Tx_Fifo_Lvl.unbuild(Val);
        BMS_HOMO_Temp.unbuild(Val);
    }
};
struct STOS_CAN_PDU_BMS_HYB_Health : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_BMS_HYB_Health;
    const uint16_t _size = 4;
    CAN_Signal<uint8_t> BMS_HYB_CPU_Load = {0, 7, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> BMS_HYB_CAN1_Tx_Fifo_Lvl = {0, 3, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> BMS_HYB_CAN2_Tx_Fifo_Lvl = {0, 3, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|7]
    CAN_Signal<uint8_t> BMS_HYB_Temp = {0, 8, 24, 0, 0, 0.5490196078, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|139.999999989]
    STOS_CAN_PDU_BMS_HYB_Health() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= BMS_HYB_CPU_Load.build();
        Val |= BMS_HYB_CAN1_Tx_Fifo_Lvl.build();
        Val |= BMS_HYB_CAN2_Tx_Fifo_Lvl.build();
        Val |= BMS_HYB_Temp.build();

    }
    void unbuild()
    {
        BMS_HYB_CPU_Load.unbuild(Val);
        BMS_HYB_CAN1_Tx_Fifo_Lvl.unbuild(Val);
        BMS_HYB_CAN2_Tx_Fifo_Lvl.unbuild(Val);
        BMS_HYB_Temp.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Airbox_Position : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Airbox_Position;
    const uint16_t _size = 2;
    CAN_Signal<uint8_t> Airbox_Pos = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> Airbox_PWM = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    STOS_CAN_PDU_Airbox_Position() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Airbox_Pos.build();
        Val |= Airbox_PWM.build();

    }
    void unbuild()
    {
        Airbox_Pos.unbuild(Val);
        Airbox_PWM.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Brake_Disc_R : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Brake_Disc_R;
    const uint16_t _size = 4;
    CAN_Signal<uint16_t> Brake_Disc_Temp_RL = {0, 16, 0, 0, 0, 0.01221224, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|800.3291484]
    CAN_Signal<uint16_t> Brake_Disc_Temp_RR = {0, 16, 16, 0, 0, 0.01221224, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|800.3291484]
    STOS_CAN_PDU_Brake_Disc_R() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Brake_Disc_Temp_RL.build();
        Val |= Brake_Disc_Temp_RR.build();

    }
    void unbuild()
    {
        Brake_Disc_Temp_RL.unbuild(Val);
        Brake_Disc_Temp_RR.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Brake_Disc_F : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Brake_Disc_F;
    const uint16_t _size = 4;
    CAN_Signal<uint16_t> Brake_Disc_Temp_FL = {0, 16, 0, 0, 0, 0.01221224, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|800.3291484]
    CAN_Signal<uint16_t> Brake_Disc_Temp_FR = {0, 16, 16, 0, 0, 0.01221224, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|800.3291484]
    STOS_CAN_PDU_Brake_Disc_F() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Brake_Disc_Temp_FL.build();
        Val |= Brake_Disc_Temp_FR.build();

    }
    void unbuild()
    {
        Brake_Disc_Temp_FL.unbuild(Val);
        Brake_Disc_Temp_FR.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Brake_Pressure : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Brake_Pressure;
    const uint16_t _size = 5;
    CAN_Signal<uint16_t> Brake_Pressure_Front = {0, 16, 0, 0, 0, 0.0024414435, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|159.9999997725]
    CAN_Signal<uint16_t> Brake_Pressure_Rear = {0, 16, 16, 0, 0, 0.0024414435, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|159.9999997725]
    CAN_Signal<uint8_t> Brake_Bias = {0, 8, 32, 0, 0, 0.39216, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    STOS_CAN_PDU_Brake_Pressure() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Brake_Pressure_Front.build();
        Val |= Brake_Pressure_Rear.build();
        Val |= Brake_Bias.build();

    }
    void unbuild()
    {
        Brake_Pressure_Front.unbuild(Val);
        Brake_Pressure_Rear.unbuild(Val);
        Brake_Bias.unbuild(Val);
    }
};
struct STOS_CAN_PDU_FDS_Wheel_Signals : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_FDS_Wheel_Signals;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> FDS_Slip_Angle_FL = {0, 8, 0, 0, 0, 0.23529412, -30};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-30|30]
    CAN_Signal<uint8_t> FDS_Slip_Angle_FR = {0, 8, 8, 0, 0, 0.23529412, -30};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-30|30]
    CAN_Signal<uint8_t> FDS_Slip_Angle_RL = {0, 8, 16, 0, 0, 0.23529412, -30};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-30|30]
    CAN_Signal<uint8_t> FDS_Slip_Angle_RR = {0, 8, 24, 0, 0, 0.23529412, -30};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-30|30]
    CAN_Signal<uint8_t> FDS_Whl_Load_FL = {0, 8, 32, 0, 0, 15.6863, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4000]
    CAN_Signal<uint8_t> FDS_Whl_Load_FR = {0, 8, 40, 0, 0, 15.6863, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4000]
    CAN_Signal<uint8_t> FDS_Whl_Load_RL = {0, 8, 48, 0, 0, 15.6863, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4000]
    CAN_Signal<uint8_t> FDS_Whl_Load_RR = {0, 8, 56, 0, 0, 15.6863, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4000]
    STOS_CAN_PDU_FDS_Wheel_Signals() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= FDS_Slip_Angle_FL.build();
        Val |= FDS_Slip_Angle_FR.build();
        Val |= FDS_Slip_Angle_RL.build();
        Val |= FDS_Slip_Angle_RR.build();
        Val |= FDS_Whl_Load_FL.build();
        Val |= FDS_Whl_Load_FR.build();
        Val |= FDS_Whl_Load_RL.build();
        Val |= FDS_Whl_Load_RR.build();

    }
    void unbuild()
    {
        FDS_Slip_Angle_FL.unbuild(Val);
        FDS_Slip_Angle_FR.unbuild(Val);
        FDS_Slip_Angle_RL.unbuild(Val);
        FDS_Slip_Angle_RR.unbuild(Val);
        FDS_Whl_Load_FL.unbuild(Val);
        FDS_Whl_Load_FR.unbuild(Val);
        FDS_Whl_Load_RL.unbuild(Val);
        FDS_Whl_Load_RR.unbuild(Val);
    }
};
struct STOS_CAN_PDU_FDS_Parameters : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_FDS_Parameters;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> FDS_Friction_LC = {0, 8, 0, 0, 0, 0.00980392, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|2.5]
    CAN_Signal<uint8_t> FDS_Swim_VDE = {0, 8, 8, 0, 0, 0.2734375, -34.7265625};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-34.7|35]
    CAN_Signal<uint8_t> FDS_Yaw_VDE = {0, 8, 16, 0, 0, 1.41176471, -180};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-180|180]
    CAN_Signal<uint8_t> FDS_Slip_mue_max = {0, 8, 24, 0, 0, 0.00784314, -1};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-1|1]
    CAN_Signal<uint8_t> FDS_Wheel_Slip_RL = {0, 8, 32, 0, 0, 0.00784314, -1};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-1|1]
    CAN_Signal<uint8_t> FDS_Wheel_Slip_RR = {0, 8, 40, 0, 0, 0.00784314, -1};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-1|1]
    CAN_Signal<uint16_t> FDS_Velo_VDE = {0, 16, 48, 0, 0, 0.50980392, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|130]
    STOS_CAN_PDU_FDS_Parameters() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= FDS_Friction_LC.build();
        Val |= FDS_Swim_VDE.build();
        Val |= FDS_Yaw_VDE.build();
        Val |= FDS_Slip_mue_max.build();
        Val |= FDS_Wheel_Slip_RL.build();
        Val |= FDS_Wheel_Slip_RR.build();
        Val |= FDS_Velo_VDE.build();

    }
    void unbuild()
    {
        FDS_Friction_LC.unbuild(Val);
        FDS_Swim_VDE.unbuild(Val);
        FDS_Yaw_VDE.unbuild(Val);
        FDS_Slip_mue_max.unbuild(Val);
        FDS_Wheel_Slip_RL.unbuild(Val);
        FDS_Wheel_Slip_RR.unbuild(Val);
        FDS_Velo_VDE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Oil_Pressure_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Oil_Pressure_Status;
    const uint16_t _size = 4;
    CAN_Signal<uint8_t> Oil_Level = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> Oil_Temp = {0, 8, 8, 0, 0, 0.9019607843, -55};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-55|174.9999999965]
    CAN_Signal<uint8_t> Oil_Level_RS232 = {0, 1, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> Oil_Pressure = {0, 8, 24, 0, 0, 2, -1};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|10]
    STOS_CAN_PDU_Oil_Pressure_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Oil_Level.build();
        Val |= Oil_Temp.build();
        Val |= Oil_Level_RS232.build();
        Val |= Oil_Pressure.build();

    }
    void unbuild()
    {
        Oil_Level.unbuild(Val);
        Oil_Temp.unbuild(Val);
        Oil_Level_RS232.unbuild(Val);
        Oil_Pressure.unbuild(Val);
    }
};
struct STOS_CAN_PDU_HAL_Status_Control : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_HAL_Status_Control;
    const uint16_t _size = 2;
    CAN_Signal<uint8_t> HAL_Angle = {0, 8, 0, 0, 0, 0.02362205, -3.02362205};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-3|3]
    CAN_Signal<uint8_t> HAL_Homing_R = {0, 1, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> HAL_Homing_L = {0, 1, 9, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_HAL_Status_Control() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= HAL_Angle.build();
        Val |= HAL_Homing_R.build();
        Val |= HAL_Homing_L.build();

    }
    void unbuild()
    {
        HAL_Angle.unbuild(Val);
        HAL_Homing_R.unbuild(Val);
        HAL_Homing_L.unbuild(Val);
    }
};
struct STOS_CAN_PDU_HAL_PWM : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_HAL_PWM;
    const uint16_t _size = 2;
    CAN_Signal<uint8_t> HAL_PWM_L = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> HAL_PWM_R = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_HAL_PWM() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= HAL_PWM_L.build();
        Val |= HAL_PWM_R.build();

    }
    void unbuild()
    {
        HAL_PWM_L.unbuild(Val);
        HAL_PWM_R.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Rocker_R : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Rocker_R;
    const uint16_t _size = 4;
    CAN_Signal<uint16_t> Rocker_RL = {0, 16, 0, 0, 0, 20, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|90]
    CAN_Signal<uint16_t> Rocker_RR = {0, 16, 16, 0, 0, 20, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|90]
    STOS_CAN_PDU_Rocker_R() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rocker_RL.build();
        Val |= Rocker_RR.build();

    }
    void unbuild()
    {
        Rocker_RL.unbuild(Val);
        Rocker_RR.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Rocker_F : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Rocker_F;
    const uint16_t _size = 4;
    CAN_Signal<uint16_t> Rocker_FL = {0, 16, 0, 0, 0, 20, -5};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|90]
    CAN_Signal<uint16_t> Rocker_FR = {0, 16, 16, 0, 0, 20, -5};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|90]
    STOS_CAN_PDU_Rocker_F() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Rocker_FL.build();
        Val |= Rocker_FR.build();

    }
    void unbuild()
    {
        Rocker_FL.unbuild(Val);
        Rocker_FR.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Steering_Whl_Angle : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Steering_Whl_Angle;
    const uint16_t _size = 2;
    CAN_Signal<uint16_t> Steering_Wheel_Angle = {0, 16, 0, 0, 0, 75, -187};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-150|150]
    STOS_CAN_PDU_Steering_Whl_Angle() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Steering_Wheel_Angle.build();

    }
    void unbuild()
    {
        Steering_Wheel_Angle.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Whl_Speed_R : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Whl_Speed_R;
    const uint16_t _size = 4;
    CAN_Signal<uint16_t> Wheel_Speed_RL = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> Wheel_Speed_RR = {0, 16, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Whl_Speed_R() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Wheel_Speed_RL.build();
        Val |= Wheel_Speed_RR.build();

    }
    void unbuild()
    {
        Wheel_Speed_RL.unbuild(Val);
        Wheel_Speed_RR.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Whl_Speed_F : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Whl_Speed_F;
    const uint16_t _size = 4;
    CAN_Signal<uint16_t> Wheel_Speed_FL = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> Wheel_Speed_FR = {0, 16, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Whl_Speed_F() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Wheel_Speed_FL.build();
        Val |= Wheel_Speed_FR.build();

    }
    void unbuild()
    {
        Wheel_Speed_FL.unbuild(Val);
        Wheel_Speed_FR.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Pitot : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Pitot;
    const uint16_t _size = 6;
    CAN_Signal<uint16_t> Pitot_1 = {0, 16, 0, 0, 0, 0.0010681315, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|69.9999978525]
    CAN_Signal<uint16_t> Pitot_2 = {0, 16, 16, 0, 0, 0.0010681315, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|69.9999978525]
    CAN_Signal<uint16_t> Pitot_3 = {0, 16, 32, 0, 0, 0.0010681315, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|69.9999978525]
    STOS_CAN_PDU_Pitot() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Pitot_1.build();
        Val |= Pitot_2.build();
        Val |= Pitot_3.build();

    }
    void unbuild()
    {
        Pitot_1.unbuild(Val);
        Pitot_2.unbuild(Val);
        Pitot_3.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Mode_Selector : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Mode_Selector;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> Car_Mode = {0, 4, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|15]
    CAN_Signal<uint8_t> Backup_Mode = {0, 4, 4, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|15]
    STOS_CAN_PDU_Mode_Selector() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Car_Mode.build();
        Val |= Backup_Mode.build();

    }
    void unbuild()
    {
        Car_Mode.unbuild(Val);
        Backup_Mode.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Water_Oil_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Water_Oil_Status;
    const uint16_t _size = 7;
    CAN_Signal<uint8_t> Oil_Fan_Percent = {0, 7, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> Oil_Fan_PWM = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    CAN_Signal<uint8_t> Water_Fan_1_Percent = {0, 7, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> Water_Fan_1_PWM = {0, 8, 24, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    CAN_Signal<uint8_t> Water_Fan_2_Percent = {0, 7, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint8_t> Water_Fan_2_PWM = {0, 8, 40, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    CAN_Signal<uint8_t> Water_Pump_Percent = {0, 7, 48, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    STOS_CAN_PDU_Water_Oil_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Oil_Fan_Percent.build();
        Val |= Oil_Fan_PWM.build();
        Val |= Water_Fan_1_Percent.build();
        Val |= Water_Fan_1_PWM.build();
        Val |= Water_Fan_2_Percent.build();
        Val |= Water_Fan_2_PWM.build();
        Val |= Water_Pump_Percent.build();

    }
    void unbuild()
    {
        Oil_Fan_Percent.unbuild(Val);
        Oil_Fan_PWM.unbuild(Val);
        Water_Fan_1_Percent.unbuild(Val);
        Water_Fan_1_PWM.unbuild(Val);
        Water_Fan_2_Percent.unbuild(Val);
        Water_Fan_2_PWM.unbuild(Val);
        Water_Pump_Percent.unbuild(Val);
    }
};
struct STOS_CAN_PDU_PDU_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_PDU_Status;
    const uint16_t _size = 2;
    CAN_Signal<uint8_t> SHUTDOWN_HOOP_L = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> SHUTDOWN_HOOP_R = {0, 1, 1, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> SHUTDOWN_HMI = {0, 1, 2, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> SHUTDOWN_BOTS = {0, 1, 3, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> SHUTDOWN_CRASH = {0, 1, 4, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> SHUTDOWN_BSPD = {0, 1, 7, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> COOLING_OVERRIDE = {0, 1, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_PDU_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= SHUTDOWN_HOOP_L.build();
        Val |= SHUTDOWN_HOOP_R.build();
        Val |= SHUTDOWN_HMI.build();
        Val |= SHUTDOWN_BOTS.build();
        Val |= SHUTDOWN_CRASH.build();
        Val |= SHUTDOWN_BSPD.build();
        Val |= COOLING_OVERRIDE.build();

    }
    void unbuild()
    {
        SHUTDOWN_HOOP_L.unbuild(Val);
        SHUTDOWN_HOOP_R.unbuild(Val);
        SHUTDOWN_HMI.unbuild(Val);
        SHUTDOWN_BOTS.unbuild(Val);
        SHUTDOWN_CRASH.unbuild(Val);
        SHUTDOWN_BSPD.unbuild(Val);
        COOLING_OVERRIDE.unbuild(Val);
    }
};
struct STOS_CAN_PDU_SWCU_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_SWCU_Status;
    const uint16_t _size = 1;
    CAN_Signal<uint8_t> Anti_Stall_Active = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> Auto_Shift_Active = {0, 1, 1, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> Neutral_Guard_Active = {0, 1, 2, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_SWCU_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Anti_Stall_Active.build();
        Val |= Auto_Shift_Active.build();
        Val |= Neutral_Guard_Active.build();

    }
    void unbuild()
    {
        Anti_Stall_Active.unbuild(Val);
        Auto_Shift_Active.unbuild(Val);
        Neutral_Guard_Active.unbuild(Val);
    }
};
struct STOS_CAN_PDU_FCU_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_FCU_Status;
    const uint16_t _size = 8;
    STOS_CAN_PDU_FCU_Status() 
    {
        ID = _id;
    }
    void build()
    {
    }
    void unbuild()
    {
    }
};
struct STOS_CAN_PDU_RCU_Status : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_RCU_Status;
    const uint16_t _size = 3;
    CAN_Signal<uint8_t> Auto_Shift_Request = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> Shift_Clutch_Fallback_Mode = {0, 1, 1, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> LaunchControl_State = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> LaunchControl_UI_State = {0, 8, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_RCU_Status() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Auto_Shift_Request.build();
        Val |= Shift_Clutch_Fallback_Mode.build();
        Val |= LaunchControl_State.build();
        Val |= LaunchControl_UI_State.build();

    }
    void unbuild()
    {
        Auto_Shift_Request.unbuild(Val);
        Shift_Clutch_Fallback_Mode.unbuild(Val);
        LaunchControl_State.unbuild(Val);
        LaunchControl_UI_State.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Hybrid_Electr_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Hybrid_Electr_2;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> Bat_Hybrid_U_9 = {0, 8, 0, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_10 = {0, 8, 8, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_11 = {0, 8, 16, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_12 = {0, 8, 24, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_13 = {0, 8, 32, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_14 = {0, 8, 40, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<int16_t> Bat_Hybrid_I = {0, 16, 48, 0, 0, 0.0183111057, 60};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-540.0183115776|660.0000004719]
    STOS_CAN_PDU_Bat_Hybrid_Electr_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Hybrid_U_9.build();
        Val |= Bat_Hybrid_U_10.build();
        Val |= Bat_Hybrid_U_11.build();
        Val |= Bat_Hybrid_U_12.build();
        Val |= Bat_Hybrid_U_13.build();
        Val |= Bat_Hybrid_U_14.build();
        Val |= Bat_Hybrid_I.build();

    }
    void unbuild()
    {
        Bat_Hybrid_U_9.unbuild(Val);
        Bat_Hybrid_U_10.unbuild(Val);
        Bat_Hybrid_U_11.unbuild(Val);
        Bat_Hybrid_U_12.unbuild(Val);
        Bat_Hybrid_U_13.unbuild(Val);
        Bat_Hybrid_U_14.unbuild(Val);
        Bat_Hybrid_I.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Hybrid_Electr_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Hybrid_Electr_1;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> Bat_Hybrid_U_1 = {0, 8, 0, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_2 = {0, 8, 8, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_3 = {0, 8, 16, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_4 = {0, 8, 24, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_5 = {0, 8, 32, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_6 = {0, 8, 40, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_7 = {0, 8, 48, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    CAN_Signal<uint8_t> Bat_Hybrid_U_8 = {0, 8, 56, 0, 0, 0.01686274541, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.30000007955]
    STOS_CAN_PDU_Bat_Hybrid_Electr_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Hybrid_U_1.build();
        Val |= Bat_Hybrid_U_2.build();
        Val |= Bat_Hybrid_U_3.build();
        Val |= Bat_Hybrid_U_4.build();
        Val |= Bat_Hybrid_U_5.build();
        Val |= Bat_Hybrid_U_6.build();
        Val |= Bat_Hybrid_U_7.build();
        Val |= Bat_Hybrid_U_8.build();

    }
    void unbuild()
    {
        Bat_Hybrid_U_1.unbuild(Val);
        Bat_Hybrid_U_2.unbuild(Val);
        Bat_Hybrid_U_3.unbuild(Val);
        Bat_Hybrid_U_4.unbuild(Val);
        Bat_Hybrid_U_5.unbuild(Val);
        Bat_Hybrid_U_6.unbuild(Val);
        Bat_Hybrid_U_7.unbuild(Val);
        Bat_Hybrid_U_8.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Hybrid_Temp_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Hybrid_Temp_1;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> Bat_Hybrid_T_1 = {0, 6, 0, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_2 = {0, 6, 6, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_3 = {0, 6, 12, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_4 = {0, 6, 18, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_5 = {0, 6, 24, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_6 = {0, 6, 30, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_7 = {0, 6, 36, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    STOS_CAN_PDU_Bat_Hybrid_Temp_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Hybrid_T_1.build();
        Val |= Bat_Hybrid_T_2.build();
        Val |= Bat_Hybrid_T_3.build();
        Val |= Bat_Hybrid_T_4.build();
        Val |= Bat_Hybrid_T_5.build();
        Val |= Bat_Hybrid_T_6.build();
        Val |= Bat_Hybrid_T_7.build();

    }
    void unbuild()
    {
        Bat_Hybrid_T_1.unbuild(Val);
        Bat_Hybrid_T_2.unbuild(Val);
        Bat_Hybrid_T_3.unbuild(Val);
        Bat_Hybrid_T_4.unbuild(Val);
        Bat_Hybrid_T_5.unbuild(Val);
        Bat_Hybrid_T_6.unbuild(Val);
        Bat_Hybrid_T_7.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Hybrid_Temp_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Hybrid_Temp_2;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> Bat_Hybrid_T_8 = {0, 6, 0, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_9 = {0, 6, 6, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_10 = {0, 6, 12, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_11 = {0, 6, 18, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_12 = {0, 6, 24, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_13 = {0, 6, 30, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Hybrid_T_14 = {0, 6, 36, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    STOS_CAN_PDU_Bat_Hybrid_Temp_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Hybrid_T_8.build();
        Val |= Bat_Hybrid_T_9.build();
        Val |= Bat_Hybrid_T_10.build();
        Val |= Bat_Hybrid_T_11.build();
        Val |= Bat_Hybrid_T_12.build();
        Val |= Bat_Hybrid_T_13.build();
        Val |= Bat_Hybrid_T_14.build();

    }
    void unbuild()
    {
        Bat_Hybrid_T_8.unbuild(Val);
        Bat_Hybrid_T_9.unbuild(Val);
        Bat_Hybrid_T_10.unbuild(Val);
        Bat_Hybrid_T_11.unbuild(Val);
        Bat_Hybrid_T_12.unbuild(Val);
        Bat_Hybrid_T_13.unbuild(Val);
        Bat_Hybrid_T_14.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Aero_Electr_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Aero_Electr_2;
    const uint16_t _size = 8;
    CAN_Signal<uint16_t> Bat_Aero_U_6 = {0, 9, 0, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_7 = {0, 9, 9, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_8 = {0, 9, 18, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_9 = {0, 9, 27, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_10 = {0, 9, 36, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_I = {0, 16, 48, 0, 0, 0.0045777066, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|300.000002031]
    STOS_CAN_PDU_Bat_Aero_Electr_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Aero_U_6.build();
        Val |= Bat_Aero_U_7.build();
        Val |= Bat_Aero_U_8.build();
        Val |= Bat_Aero_U_9.build();
        Val |= Bat_Aero_U_10.build();
        Val |= Bat_Aero_I.build();

    }
    void unbuild()
    {
        Bat_Aero_U_6.unbuild(Val);
        Bat_Aero_U_7.unbuild(Val);
        Bat_Aero_U_8.unbuild(Val);
        Bat_Aero_U_9.unbuild(Val);
        Bat_Aero_U_10.unbuild(Val);
        Bat_Aero_I.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Aero_Electr_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Aero_Electr_1;
    const uint16_t _size = 6;
    CAN_Signal<uint16_t> Bat_Aero_U_1 = {0, 9, 0, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_2 = {0, 9, 9, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_3 = {0, 9, 18, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_4 = {0, 9, 27, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    CAN_Signal<uint16_t> Bat_Aero_U_5 = {0, 9, 36, 0, 0, 0.0084148728, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.3000000008]
    STOS_CAN_PDU_Bat_Aero_Electr_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Aero_U_1.build();
        Val |= Bat_Aero_U_2.build();
        Val |= Bat_Aero_U_3.build();
        Val |= Bat_Aero_U_4.build();
        Val |= Bat_Aero_U_5.build();

    }
    void unbuild()
    {
        Bat_Aero_U_1.unbuild(Val);
        Bat_Aero_U_2.unbuild(Val);
        Bat_Aero_U_3.unbuild(Val);
        Bat_Aero_U_4.unbuild(Val);
        Bat_Aero_U_5.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Aero_Temp_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Aero_Temp_1;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> Bat_Aero_T_1 = {0, 6, 0, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_2 = {0, 6, 6, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_3 = {0, 6, 12, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_4 = {0, 6, 18, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_5 = {0, 6, 24, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_6 = {0, 6, 30, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_7 = {0, 6, 36, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_8 = {0, 6, 42, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_9 = {0, 6, 48, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_10 = {0, 6, 54, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    STOS_CAN_PDU_Bat_Aero_Temp_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Aero_T_1.build();
        Val |= Bat_Aero_T_2.build();
        Val |= Bat_Aero_T_3.build();
        Val |= Bat_Aero_T_4.build();
        Val |= Bat_Aero_T_5.build();
        Val |= Bat_Aero_T_6.build();
        Val |= Bat_Aero_T_7.build();
        Val |= Bat_Aero_T_8.build();
        Val |= Bat_Aero_T_9.build();
        Val |= Bat_Aero_T_10.build();

    }
    void unbuild()
    {
        Bat_Aero_T_1.unbuild(Val);
        Bat_Aero_T_2.unbuild(Val);
        Bat_Aero_T_3.unbuild(Val);
        Bat_Aero_T_4.unbuild(Val);
        Bat_Aero_T_5.unbuild(Val);
        Bat_Aero_T_6.unbuild(Val);
        Bat_Aero_T_7.unbuild(Val);
        Bat_Aero_T_8.unbuild(Val);
        Bat_Aero_T_9.unbuild(Val);
        Bat_Aero_T_10.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Bat_Aero_Temp_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Bat_Aero_Temp_2;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> Bat_Aero_T_11 = {0, 6, 0, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_12 = {0, 6, 6, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_13 = {0, 6, 12, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_14 = {0, 6, 18, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_15 = {0, 6, 24, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_16 = {0, 6, 30, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_17 = {0, 6, 36, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_18 = {0, 6, 42, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_19 = {0, 6, 48, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    CAN_Signal<uint8_t> Bat_Aero_T_20 = {0, 6, 54, 0, 0, 1, 10};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [10|73]
    STOS_CAN_PDU_Bat_Aero_Temp_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Bat_Aero_T_11.build();
        Val |= Bat_Aero_T_12.build();
        Val |= Bat_Aero_T_13.build();
        Val |= Bat_Aero_T_14.build();
        Val |= Bat_Aero_T_15.build();
        Val |= Bat_Aero_T_16.build();
        Val |= Bat_Aero_T_17.build();
        Val |= Bat_Aero_T_18.build();
        Val |= Bat_Aero_T_19.build();
        Val |= Bat_Aero_T_20.build();

    }
    void unbuild()
    {
        Bat_Aero_T_11.unbuild(Val);
        Bat_Aero_T_12.unbuild(Val);
        Bat_Aero_T_13.unbuild(Val);
        Bat_Aero_T_14.unbuild(Val);
        Bat_Aero_T_15.unbuild(Val);
        Bat_Aero_T_16.unbuild(Val);
        Bat_Aero_T_17.unbuild(Val);
        Bat_Aero_T_18.unbuild(Val);
        Bat_Aero_T_19.unbuild(Val);
        Bat_Aero_T_20.unbuild(Val);
    }
};
struct STOS_CAN_PDU_IMU_Gyro : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_IMU_Gyro;
    const uint16_t _size = 6;
    CAN_Signal<int16_t> IMU_1_GX = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-32768|32767]
    CAN_Signal<int16_t> IMU_1_GY = {0, 16, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-32768|32767]
    CAN_Signal<int16_t> IMU_1_GZ = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_IMU_Gyro() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= IMU_1_GX.build();
        Val |= IMU_1_GY.build();
        Val |= IMU_1_GZ.build();

    }
    void unbuild()
    {
        IMU_1_GX.unbuild(Val);
        IMU_1_GY.unbuild(Val);
        IMU_1_GZ.unbuild(Val);
    }
};
struct STOS_CAN_PDU_IMU_Accel : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_IMU_Accel;
    const uint16_t _size = 6;
    CAN_Signal<int16_t> IMU_1_AX = {0, 16, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int16_t> IMU_1_AY = {0, 16, 16, 0, 0, 0.0002, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-6.5536|6.5534]
    CAN_Signal<int16_t> IMU_1_AZ = {0, 16, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-32768|32767]
    STOS_CAN_PDU_IMU_Accel() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= IMU_1_AX.build();
        Val |= IMU_1_AY.build();
        Val |= IMU_1_AZ.build();

    }
    void unbuild()
    {
        IMU_1_AX.unbuild(Val);
        IMU_1_AY.unbuild(Val);
        IMU_1_AZ.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Aero_Fan : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Aero_Fan;
    const uint16_t _size = 2;
    CAN_Signal<uint8_t> Fan_PWM_L = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    CAN_Signal<uint8_t> Fan_PWM_R = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|255]
    STOS_CAN_PDU_Aero_Fan() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Fan_PWM_L.build();
        Val |= Fan_PWM_R.build();

    }
    void unbuild()
    {
        Fan_PWM_L.unbuild(Val);
        Fan_PWM_R.unbuild(Val);
    }
};
struct STOS_CAN_PDU_SWCU_Switches : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_SWCU_Switches;
    const uint16_t _size = 2;
    CAN_Signal<uint8_t> Switch_1 = {0, 1, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> Switch_Clutch = {0, 1, 1, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> Switch_2 = {0, 1, 2, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> Switch_Mode_A = {0, 4, 3, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|15]
    CAN_Signal<uint8_t> Switch_OhShit = {0, 1, 7, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> Switch_Mode_B = {0, 4, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|15]
    CAN_Signal<uint8_t> Switch_Radio = {0, 1, 12, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_SWCU_Switches() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= Switch_1.build();
        Val |= Switch_Clutch.build();
        Val |= Switch_2.build();
        Val |= Switch_Mode_A.build();
        Val |= Switch_OhShit.build();
        Val |= Switch_Mode_B.build();
        Val |= Switch_Radio.build();

    }
    void unbuild()
    {
        Switch_1.unbuild(Val);
        Switch_Clutch.unbuild(Val);
        Switch_2.unbuild(Val);
        Switch_Mode_A.unbuild(Val);
        Switch_OhShit.unbuild(Val);
        Switch_Mode_B.unbuild(Val);
        Switch_Radio.unbuild(Val);
    }
};
struct STOS_CAN_PDU_AGS1_gearbox_control_unit : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_AGS1_gearbox_control_unit;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> engaged_gear = {0, 8, 0, 0, 0, 0.5, -1.5};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-1.5|126]
    CAN_Signal<uint16_t> gearpot = {0, 10, 8, 0, 0, 4.888, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|5000]
    CAN_Signal<uint8_t> shift_state = {0, 4, 24, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|15]
    CAN_Signal<uint8_t> blip_state = {0, 4, 28, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|15]
    CAN_Signal<uint16_t> target_engine_speed = {0, 14, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|16383]
    CAN_Signal<uint8_t> cut_level_gcu = {0, 8, 48, 0, 0, 0.01960784, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|4.9999992]
    CAN_Signal<uint8_t> state_cut = {0, 4, 56, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|2]
    CAN_Signal<int8_t> activate_blip = {0, 1, 60, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint8_t> activate_cut = {0, 1, 61, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    STOS_CAN_PDU_AGS1_gearbox_control_unit() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= engaged_gear.build();
        Val |= gearpot.build();
        Val |= shift_state.build();
        Val |= blip_state.build();
        Val |= target_engine_speed.build();
        Val |= cut_level_gcu.build();
        Val |= state_cut.build();
        Val |= activate_blip.build();
        Val |= activate_cut.build();

    }
    void unbuild()
    {
        engaged_gear.unbuild(Val);
        gearpot.unbuild(Val);
        shift_state.unbuild(Val);
        blip_state.unbuild(Val);
        target_engine_speed.unbuild(Val);
        cut_level_gcu.unbuild(Val);
        state_cut.unbuild(Val);
        activate_blip.unbuild(Val);
        activate_cut.unbuild(Val);
    }
};
struct STOS_CAN_PDU_ABS_switch_state_slip_and_speed : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_ABS_switch_state_slip_and_speed;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> switchstateABS = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int16_t> p_HzABS = {0, 16, 8, 0, 0, 0.0153, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-42.5|425]
    CAN_Signal<uint8_t> blsABS = {0, 1, 24, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|1]
    CAN_Signal<uint16_t> ax1_Bremse60ABS = {0, 16, 32, 0, 0, 0.00012742, -4.1768};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-4.7168|4.7167]
    CAN_Signal<uint16_t> ay1_Bremse60ABS = {0, 16, 48, 0, 0, 0.00012742, -4.1768};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [-4.7168|4.7167]
    STOS_CAN_PDU_ABS_switch_state_slip_and_speed() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= switchstateABS.build();
        Val |= p_HzABS.build();
        Val |= blsABS.build();
        Val |= ax1_Bremse60ABS.build();
        Val |= ay1_Bremse60ABS.build();

    }
    void unbuild()
    {
        switchstateABS.unbuild(Val);
        p_HzABS.unbuild(Val);
        blsABS.unbuild(Val);
        ax1_Bremse60ABS.unbuild(Val);
        ay1_Bremse60ABS.unbuild(Val);
    }
};
struct STOS_CAN_PDU_ABS_wheelspeeds : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_ABS_wheelspeeds;
    const uint16_t _size = 8;
    CAN_Signal<uint16_t> speedABSfl = {0, 16, 0, 0, 0, 0.015625, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint16_t> speedABSfr = {0, 16, 16, 0, 0, 0.015625, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint16_t> speedABSrl = {0, 16, 32, 0, 0, 0.015625, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    CAN_Signal<uint16_t> speedABSrr = {0, 16, 48, 0, 0, 0.015625, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|100]
    STOS_CAN_PDU_ABS_wheelspeeds() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= speedABSfl.build();
        Val |= speedABSfr.build();
        Val |= speedABSrl.build();
        Val |= speedABSrr.build();

    }
    void unbuild()
    {
        speedABSfl.unbuild(Val);
        speedABSfr.unbuild(Val);
        speedABSrl.unbuild(Val);
        speedABSrr.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Boost_Pressures_Wastegate : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Boost_Pressures_Wastegate;
    const uint16_t _size = 8;
    CAN_Signal<uint16_t> p22_m = {0, 16, 7, 0, 1, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> p22_2m_pwg_m = {0, 16, 23, 0, 1, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> p22_sp = {0, 8, 32, 0, 0, 25.7, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> pwg_sp = {0, 8, 40, 0, 0, 25.7, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> wgdc_wgdcvent = {0, 8, 48, 0, 0, 0.392156862, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> wgdc_2_wgdchold = {0, 8, 56, 0, 0, 0.392156862, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Boost_Pressures_Wastegate() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= p22_m.build();
        Val |= p22_2m_pwg_m.build();
        Val |= p22_sp.build();
        Val |= pwg_sp.build();
        Val |= wgdc_wgdcvent.build();
        Val |= wgdc_2_wgdchold.build();

    }
    void unbuild()
    {
        p22_m.unbuild(Val);
        p22_2m_pwg_m.unbuild(Val);
        p22_sp.unbuild(Val);
        pwg_sp.unbuild(Val);
        wgdc_wgdcvent.unbuild(Val);
        wgdc_2_wgdchold.unbuild(Val);
    }
};
struct STOS_CAN_PDU_States_Temp_Press : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_States_Temp_Press;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> rowcounter_0x77A = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tc_b = {0, 1, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> gearcut_b = {0, 1, 9, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lamctrl_2b = {0, 1, 10, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lamctrl_b = {0, 1, 11, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> injstartphase_b = {0, 1, 12, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> injenrich_b = {0, 1, 13, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> injcutin_b = {0, 1, 14, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> injcut_b = {0, 1, 15, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> speedlimit_b = {0, 1, 16, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> phsokset_b = {0, 1, 17, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> phsok_b = {0, 1, 18, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> oillamp_b_1 = {0, 1, 19, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> mil_b = {0, 1, 20, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> laptrig_b = {0, 1, 21, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lap_b = {0, 1, 22, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> idle_b = {0, 1, 23, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> speedlimitreq_b = {0, 1, 24, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> etbsys_e = {0, 1, 25, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> knockenable_b = {0, 1, 26, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> knockadaptenable_b = {0, 1, 27, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> startend_b = {0, 1, 28, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> revlimit_b = {0, 1, 29, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> rev_b = {0, 1, 30, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ignoff_b = {0, 1, 31, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tmot = {0, 8, 32, 0x5, 0, 1, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tfuel = {0, 8, 32, 0x4, 0, 1, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> fuellap = {0, 16, 39, 0x3, 1, 0.00035791, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> pamb = {0, 16, 39, 0x2, 1, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> pcrank = {0, 8, 32, 0x1, 0, 5, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tex = {0, 8, 40, 0x5, 0, 5, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> toil = {0, 8, 40, 0x4, 0, 1, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> poil = {0, 8, 40, 0x1, 0, 0.0514, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tex_2 = {0, 8, 48, 0x5, 0, 5, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tlam = {0, 8, 48, 0x4, 0, 5, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int16_t> fueltank = {0, 16, 55, 0x3, 1, 0.005726562, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> mappos = {0, 8, 48, 0x2, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> pwat = {0, 8, 48, 0x1, 0, 0.0514, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> shled1_b = {0, 1, 56, 0x5, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tlam_2 = {0, 8, 56, 0x4, 0, 5, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tair = {0, 8, 56, 0x2, 0, 1, -40};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> pfuel = {0, 8, 56, 0x1, 0, 0.0514, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> shled2_b = {0, 1, 57, 0x5, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> shled3_b = {0, 1, 58, 0x5, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> shled4_b = {0, 1, 59, 0x5, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> shled5_b = {0, 1, 60, 0x5, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> battlow_b = {0, 1, 61, 0x5, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> oillamp_b_2 = {0, 1, 62, 0x5, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_States_Temp_Press() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= rowcounter_0x77A.build();
        Val |= tc_b.build();
        Val |= gearcut_b.build();
        Val |= lamctrl_2b.build();
        Val |= lamctrl_b.build();
        Val |= injstartphase_b.build();
        Val |= injenrich_b.build();
        Val |= injcutin_b.build();
        Val |= injcut_b.build();
        Val |= speedlimit_b.build();
        Val |= phsokset_b.build();
        Val |= phsok_b.build();
        Val |= oillamp_b_1.build();
        Val |= mil_b.build();
        Val |= laptrig_b.build();
        Val |= lap_b.build();
        Val |= idle_b.build();
        Val |= speedlimitreq_b.build();
        Val |= etbsys_e.build();
        Val |= knockenable_b.build();
        Val |= knockadaptenable_b.build();
        Val |= startend_b.build();
        Val |= revlimit_b.build();
        Val |= rev_b.build();
        Val |= ignoff_b.build();
        if(rowcounter_0x77A.physValue==0x5){
            Val |= tmot.build();
        }
        if(rowcounter_0x77A.physValue==0x4){
            Val |= tfuel.build();
        }
        if(rowcounter_0x77A.physValue==0x3){
            Val |= fuellap.build();
        }
        if(rowcounter_0x77A.physValue==0x2){
            Val |= pamb.build();
        }
        if(rowcounter_0x77A.physValue==0x1){
            Val |= pcrank.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= tex.build();
        }
        if(rowcounter_0x77A.physValue==0x4){
            Val |= toil.build();
        }
        if(rowcounter_0x77A.physValue==0x1){
            Val |= poil.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= tex_2.build();
        }
        if(rowcounter_0x77A.physValue==0x4){
            Val |= tlam.build();
        }
        if(rowcounter_0x77A.physValue==0x3){
            Val |= fueltank.build();
        }
        if(rowcounter_0x77A.physValue==0x2){
            Val |= mappos.build();
        }
        if(rowcounter_0x77A.physValue==0x1){
            Val |= pwat.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= shled1_b.build();
        }
        if(rowcounter_0x77A.physValue==0x4){
            Val |= tlam_2.build();
        }
        if(rowcounter_0x77A.physValue==0x2){
            Val |= tair.build();
        }
        if(rowcounter_0x77A.physValue==0x1){
            Val |= pfuel.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= shled2_b.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= shled3_b.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= shled4_b.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= shled5_b.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= battlow_b.build();
        }
        if(rowcounter_0x77A.physValue==0x5){
            Val |= oillamp_b_2.build();
        }

    }
    void unbuild()
    {
        rowcounter_0x77A.unbuild(Val);
        tc_b.unbuild(Val);
        gearcut_b.unbuild(Val);
        lamctrl_2b.unbuild(Val);
        lamctrl_b.unbuild(Val);
        injstartphase_b.unbuild(Val);
        injenrich_b.unbuild(Val);
        injcutin_b.unbuild(Val);
        injcut_b.unbuild(Val);
        speedlimit_b.unbuild(Val);
        phsokset_b.unbuild(Val);
        phsok_b.unbuild(Val);
        oillamp_b_1.unbuild(Val);
        mil_b.unbuild(Val);
        laptrig_b.unbuild(Val);
        lap_b.unbuild(Val);
        idle_b.unbuild(Val);
        speedlimitreq_b.unbuild(Val);
        etbsys_e.unbuild(Val);
        knockenable_b.unbuild(Val);
        knockadaptenable_b.unbuild(Val);
        startend_b.unbuild(Val);
        revlimit_b.unbuild(Val);
        rev_b.unbuild(Val);
        ignoff_b.unbuild(Val);
        if(rowcounter_0x77A.physValue==0x5){
            tmot.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x4){
            tfuel.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x3){
            fuellap.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x2){
            pamb.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x1){
            pcrank.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            tex.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x4){
            toil.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x1){
            poil.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            tex_2.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x4){
            tlam.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x3){
            fueltank.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x2){
            mappos.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x1){
            pwat.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            shled1_b.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x4){
            tlam_2.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x2){
            tair.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x1){
            pfuel.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            shled2_b.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            shled3_b.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            shled4_b.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            shled5_b.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            battlow_b.unbuild(Val);
        }
        if(rowcounter_0x77A.physValue==0x5){
            oillamp_b_2.unbuild(Val);
        }
    }
};
struct STOS_CAN_PDU_Electronic_Throttle_Control : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Electronic_Throttle_Control;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> etb = {0, 8, 0, 0, 0, 0.5, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> etb_sp = {0, 8, 8, 0, 0, 0.5, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> aps = {0, 8, 16, 0, 0, 0.5, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> p1 = {0, 16, 31, 0, 1, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> camshaftpos = {0, 8, 40, 0, 0, 0.5, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> batt_u = {0, 8, 48, 0, 0, 0.070694901961, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lap_c = {0, 8, 56, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Electronic_Throttle_Control() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= etb.build();
        Val |= etb_sp.build();
        Val |= aps.build();
        Val |= p1.build();
        Val |= camshaftpos.build();
        Val |= batt_u.build();
        Val |= lap_c.build();

    }
    void unbuild()
    {
        etb.unbuild(Val);
        etb_sp.unbuild(Val);
        aps.unbuild(Val);
        p1.unbuild(Val);
        camshaftpos.unbuild(Val);
        batt_u.unbuild(Val);
        lap_c.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Traction_Control : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Traction_Control;
    const uint16_t _size = 8;
    CAN_Signal<int8_t> tcpfac = {0, 8, 0, 0, 0, 0.78125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tcsw = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> slipsp = {0, 8, 16, 0, 0, 0.078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> slra = {0, 8, 24, 0, 0, 0.078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> vdraxle = {0, 16, 39, 0, 1, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> vref = {0, 16, 55, 0, 1, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Traction_Control() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= tcpfac.build();
        Val |= tcsw.build();
        Val |= slipsp.build();
        Val |= slra.build();
        Val |= vdraxle.build();
        Val |= vref.build();

    }
    void unbuild()
    {
        tcpfac.unbuild(Val);
        tcsw.unbuild(Val);
        slipsp.unbuild(Val);
        slra.unbuild(Val);
        vdraxle.unbuild(Val);
        vref.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Gear_Dashboard_Acceleration : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Gear_Dashboard_Acceleration;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> gear = {0, 8, 0, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> gcstate = {0, 8, 8, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> gearratio = {0, 8, 16, 0, 0, 0.0625, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> gearcut_u = {0, 8, 24, 0, 0, 0.019607843, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ddugear = {0, 8, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> accx = {0, 8, 40, 0, 0, 0.03125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> accy = {0, 8, 48, 0, 0, 0.03125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> accz = {0, 8, 56, 0, 0, 0.03125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Gear_Dashboard_Acceleration() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= gear.build();
        Val |= gcstate.build();
        Val |= gearratio.build();
        Val |= gearcut_u.build();
        Val |= ddugear.build();
        Val |= accx.build();
        Val |= accy.build();
        Val |= accz.build();

    }
    void unbuild()
    {
        gear.unbuild(Val);
        gcstate.unbuild(Val);
        gearratio.unbuild(Val);
        gearcut_u.unbuild(Val);
        ddugear.unbuild(Val);
        accx.unbuild(Val);
        accy.unbuild(Val);
        accz.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Lapfunc : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Lapfunc;
    const uint16_t _size = 8;
    CAN_Signal<uint16_t> lapdist = {0, 16, 7, 0, 1, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> laptime = {0, 16, 23, 0, 1, 0.01, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> laptimediff = {0, 16, 39, 0, 1, 0.01, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> laptimefast = {0, 16, 55, 0, 1, 0.01, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Lapfunc() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= lapdist.build();
        Val |= laptime.build();
        Val |= laptimediff.build();
        Val |= laptimefast.build();

    }
    void unbuild()
    {
        lapdist.unbuild(Val);
        laptime.unbuild(Val);
        laptimediff.unbuild(Val);
        laptimefast.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Speed : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Speed;
    const uint16_t _size = 8;
    CAN_Signal<uint16_t> speed = {0, 16, 7, 0, 1, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> speedfl = {0, 8, 16, 0, 0, 2, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> speedfr = {0, 8, 24, 0, 0, 2, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> speedrl = {0, 8, 32, 0, 0, 2, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> speedrr = {0, 8, 40, 0, 0, 2, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Speed() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= speed.build();
        Val |= speedfl.build();
        Val |= speedfr.build();
        Val |= speedrl.build();
        Val |= speedrr.build();

    }
    void unbuild()
    {
        speed.unbuild(Val);
        speedfl.unbuild(Val);
        speedfr.unbuild(Val);
        speedrl.unbuild(Val);
        speedrr.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Lambda : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Lambda;
    const uint16_t _size = 8;
    CAN_Signal<int8_t> lami = {0, 8, 0, 0, 0, 0.25, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> lami_2 = {0, 8, 8, 0, 0, 0.25, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> lamp = {0, 8, 16, 0, 0, 0.25, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> lamp_2 = {0, 8, 24, 0, 0, 0.25, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lam = {0, 8, 32, 0, 0, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lam_2 = {0, 8, 40, 0, 0, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lammap = {0, 8, 48, 0, 0, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lammap_2 = {0, 8, 56, 0, 0, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Lambda() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= lami.build();
        Val |= lami_2.build();
        Val |= lamp.build();
        Val |= lamp_2.build();
        Val |= lam.build();
        Val |= lam_2.build();
        Val |= lammap.build();
        Val |= lammap_2.build();

    }
    void unbuild()
    {
        lami.unbuild(Val);
        lami_2.unbuild(Val);
        lamp.unbuild(Val);
        lamp_2.unbuild(Val);
        lam.unbuild(Val);
        lam_2.unbuild(Val);
        lammap.unbuild(Val);
        lammap_2.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Ignition_Rev_Ath : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Ignition_Rev_Ath;
    const uint16_t _size = 8;
    CAN_Signal<int8_t> ignbase = {0, 8, 0, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ignmap = {0, 8, 8, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tdwell = {0, 8, 16, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint16_t> rev = {0, 16, 31, 0, 1, 0.5, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ath = {0, 8, 40, 0, 0, 0.390625, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> dath = {0, 8, 48, 0, 0, 12, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Ignition_Rev_Ath() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= ignbase.build();
        Val |= ignmap.build();
        Val |= tdwell.build();
        Val |= rev.build();
        Val |= ath.build();
        Val |= dath.build();

    }
    void unbuild()
    {
        ignbase.unbuild(Val);
        ignmap.unbuild(Val);
        tdwell.unbuild(Val);
        rev.unbuild(Val);
        ath.unbuild(Val);
        dath.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Ignition : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Ignition;
    const uint16_t _size = 8;
    CAN_Signal<int8_t> ign_1 = {0, 8, 0, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ign_2 = {0, 8, 8, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ign_3 = {0, 8, 16, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ign_4 = {0, 8, 24, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ign_5 = {0, 8, 32, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ign_6 = {0, 8, 40, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ign_7 = {0, 8, 48, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<int8_t> ign_8 = {0, 8, 56, 0, 0, 0.75, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Ignition() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= ign_1.build();
        Val |= ign_2.build();
        Val |= ign_3.build();
        Val |= ign_4.build();
        Val |= ign_5.build();
        Val |= ign_6.build();
        Val |= ign_7.build();
        Val |= ign_8.build();

    }
    void unbuild()
    {
        ign_1.unbuild(Val);
        ign_2.unbuild(Val);
        ign_3.unbuild(Val);
        ign_4.unbuild(Val);
        ign_5.unbuild(Val);
        ign_6.unbuild(Val);
        ign_7.unbuild(Val);
        ign_8.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Injection_2 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Injection_2;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> tibase = {0, 8, 0, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> tibatt_o = {0, 8, 8, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> timap = {0, 8, 16, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> injang = {0, 8, 24, 0, 0, 2.8125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> injoff = {0, 8, 32, 0, 0, 1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lamctrl_k = {0, 8, 40, 0, 0, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> lamctrl_2k = {0, 8, 48, 0, 0, 0.0078125, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Injection_2() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= tibase.build();
        Val |= tibatt_o.build();
        Val |= timap.build();
        Val |= injang.build();
        Val |= injoff.build();
        Val |= lamctrl_k.build();
        Val |= lamctrl_2k.build();

    }
    void unbuild()
    {
        tibase.unbuild(Val);
        tibatt_o.unbuild(Val);
        timap.unbuild(Val);
        injang.unbuild(Val);
        injoff.unbuild(Val);
        lamctrl_k.unbuild(Val);
        lamctrl_2k.unbuild(Val);
    }
};
struct STOS_CAN_PDU_Injection_1 : public StallardOSCanMessage 
{
public:
    static constexpr uint16_t _id = STOS_CAN_ID_Injection_1;
    const uint16_t _size = 8;
    CAN_Signal<uint8_t> ti_1 = {0, 8, 0, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ti_2 = {0, 8, 8, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ti_3 = {0, 8, 16, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ti_4 = {0, 8, 24, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ti_5 = {0, 8, 32, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ti_6 = {0, 8, 40, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ti_7 = {0, 8, 48, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    CAN_Signal<uint8_t> ti_8 = {0, 8, 56, 0, 0, 0.1, 0};  // {init,bitcount,startbit,rowcount,isMotorola,factor,offset}  [0|0]
    STOS_CAN_PDU_Injection_1() 
    {
        ID = _id;
    }
    void build()
    {
        Val = 0;
        Val |= ti_1.build();
        Val |= ti_2.build();
        Val |= ti_3.build();
        Val |= ti_4.build();
        Val |= ti_5.build();
        Val |= ti_6.build();
        Val |= ti_7.build();
        Val |= ti_8.build();

    }
    void unbuild()
    {
        ti_1.unbuild(Val);
        ti_2.unbuild(Val);
        ti_3.unbuild(Val);
        ti_4.unbuild(Val);
        ti_5.unbuild(Val);
        ti_6.unbuild(Val);
        ti_7.unbuild(Val);
        ti_8.unbuild(Val);
    }
};
#endif  // StallardOScanStructs_hpp