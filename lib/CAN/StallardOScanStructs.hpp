#include "stdint.h"
struct STOS_CAN_DAT_AGS1_gearbox_control_unit{
	uint8_t activate_blip;
	uint8_t activate_cut;
	uint8_t blip_state;
	uint8_t cut_level_gcu;
	uint8_t engaged_gear;
	uint8_t gearpot;
	uint8_t shift_state;
	uint8_t state_cut;
	uint8_t target_engine_speed;
};

struct STOS_CAN_DAT_ABS_wheelspeeds{
	uint8_t speedABSfl;
	uint8_t speedABSfr;
	uint8_t speedABSrl;
	uint8_t speedABSrr;
};

struct STOS_CAN_DAT_ABS_switch_state_slip_and_speed{
	uint8_t ax1_Bremse60ABS;
	uint8_t ay1_Bremse60ABS;
	uint8_t blsABS;
	uint8_t p_HzABS;
	uint8_t switchstateABS;
};

struct STOS_CAN_DAT_Injection_1{
	uint8_t ti_1;
	uint8_t ti_2;
	uint8_t ti_3;
	uint8_t ti_4;
	uint8_t ti_5;
	uint8_t ti_6;
	uint8_t ti_7;
	uint8_t ti_8;
};

struct STOS_CAN_DAT_Injection_2{
	uint8_t injang;
	uint8_t injoff;
	uint8_t lamctrl_2k;
	uint8_t lamctrl_k;
	uint8_t tibase;
	uint8_t tibatt_o;
	uint8_t timap;
};

struct STOS_CAN_DAT_Ignition{
	uint8_t ign_1;
	uint8_t ign_2;
	uint8_t ign_3;
	uint8_t ign_4;
	uint8_t ign_5;
	uint8_t ign_6;
	uint8_t ign_7;
	uint8_t ign_8;
};

struct STOS_CAN_DAT_Ignition_Rev_Ath{
	uint8_t ath;
	uint8_t dath;
	uint8_t ignbase;
	uint8_t ignmap;
	uint8_t rev;
	uint8_t tdwell;
};

struct STOS_CAN_DAT_Lambda{
	uint8_t lam;
	uint8_t lam_2;
	uint8_t lami;
	uint8_t lami_2;
	uint8_t lammap;
	uint8_t lammap_2;
	uint8_t lamp;
	uint8_t lamp_2;
};

struct STOS_CAN_DAT_Speed{
	uint8_t speed;
	uint8_t speedfl;
	uint8_t speedfr;
	uint8_t speedrl;
	uint8_t speedrr;
};

struct STOS_CAN_DAT_Lapfunc{
	uint8_t lapdist;
	uint8_t laptime;
	uint8_t laptimediff;
	uint8_t laptimefast;
};

struct STOS_CAN_DAT_Gear_Dashboard_Acceleration{
	uint8_t accx;
	uint8_t accy;
	uint8_t accz;
	uint8_t ddugear;
	uint8_t gcstate;
	uint8_t gear;
	uint8_t gearcut_u;
	uint8_t gearratio;
};

struct STOS_CAN_DAT_Traction_Control{
	uint8_t slipsp;
	uint8_t slra;
	uint8_t tcpfac;
	uint8_t tcsw;
	uint8_t vdraxle;
	uint8_t vref;
};

struct STOS_CAN_DAT_Electronic_Throttle_Control{
	uint8_t aps;
	uint8_t batt_u;
	uint8_t camshaftpos;
	uint8_t etb;
	uint8_t etb_sp;
	uint8_t lap_c;
	uint8_t p1;
};

struct STOS_CAN_DAT_States_Temp_Press{
	uint8_t battlow_b;
	uint8_t etbsys_e;
	uint8_t fuellap;
	uint8_t fueltank;
	uint8_t gearcut_b;
	uint8_t idle_b;
	uint8_t ignoff_b;
	uint8_t injcut_b;
	uint8_t injcutin_b;
	uint8_t injenrich_b;
	uint8_t injstartphase_b;
	uint8_t knockadaptenable_b;
	uint8_t knockenable_b;
	uint8_t lamctrl_2b;
	uint8_t lamctrl_b;
	uint8_t lap_b;
	uint8_t laptrig_b;
	uint8_t mappos;
	uint8_t mil_b;
	uint8_t oillamp_b;
	// uint8_t oillamp_b;
	uint8_t pamb;
	uint8_t pcrank;
	uint8_t pfuel;
	uint8_t phsok_b;
	uint8_t phsokset_b;
	uint8_t poil;
	uint8_t pwat;
	uint8_t rev_b;
	uint8_t revlimit_b;
	uint8_t rowcounter_0x77A;
	uint8_t shled1_b;
	uint8_t shled2_b;
	uint8_t shled3_b;
	uint8_t shled4_b;
	uint8_t shled5_b;
	uint8_t speedlimit_b;
	uint8_t speedlimitreq_b;
	uint8_t startend_b;
	uint8_t tair;
	uint8_t tc_b;
	uint8_t tex;
	uint8_t tex_2;
	uint8_t tfuel;
	uint8_t tlam;
	uint8_t tlam_2;
	uint8_t tmot;
	uint8_t toil;
};

struct STOS_CAN_DAT_Boost_Pressures_Wastegate{
	uint8_t p22_2m_pwg_m;
	uint8_t p22_m;
	uint8_t p22_sp;
	uint8_t pwg_sp;
	uint8_t wgdc_2_wgdchold;
	uint8_t wgdc_wgdcvent;
};

struct STOS_CAN_DAT_Acceleration_1{
	uint8_t ADCAN_SP_Accel_1_X;
	uint8_t ADCAN_SP_Accel_1_Y;
	uint8_t ADCAN_SP_Accel_1_Z;
};

struct STOS_CAN_DAT_Acceleration_2{
	uint8_t ADCAN_SP_Accel_2_X;
	uint8_t ADCAN_SP_Accel_2_Y;
	uint8_t ADCAN_SP_Accel_2_Z;
};

struct STOS_CAN_DAT_Aero_Fan_PWM{
	uint8_t ADCAN_AE_Fan_L_PWM;
	uint8_t ADCAN_AE_Fan_R_PWM;
};

struct STOS_CAN_DAT_Aero_Fan_Telemetry{
	uint8_t ADCAN_AE_Fan_Telemetry_1;
	uint8_t ADCAN_AE_Fan_Telemetry_2;
};

struct STOS_CAN_DAT_Aero_Fan_Warnings{
	uint8_t ADCAN_AE_Warnings;
};

struct STOS_CAN_DAT_Airbox_Position{
	uint8_t ADCAN_PT_Airbox_Pos;
};

struct STOS_CAN_DAT_ARH_Homing{
	uint8_t ADCAN_SP_ARH_1_Homing;
	uint8_t ADCAN_SP_ARH_2_Homing;
};

struct STOS_CAN_DAT_ARH_PWM{
	uint8_t ADCAN_SP_ARH_1_PWM;
	uint8_t ADCAN_SP_ARH_2_PWM;
};

struct STOS_CAN_DAT_Battery_Temp_48V{
	uint8_t ADCAN_EL_Battery_48V_Temp_1;
	uint8_t ADCAN_EL_Battery_48V_Temp_2;
	uint8_t ADCAN_EL_Battery_48V_Temp_3;
};

struct STOS_CAN_DAT_Brake_Disc_F{
	uint8_t ADCAN_SP_Brake_Disc_Temp_FL;
	uint8_t ADCAN_SP_Brake_Disc_Temp_FR;
};

struct STOS_CAN_DAT_Brake_Disc_R{
	uint8_t ADCAN_SP_Brake_Disc_Temp_RL;
	uint8_t ADCAN_SP_Brake_Disc_Temp_RR;
};

struct STOS_CAN_DAT_Brake_Pressure{
	uint8_t ADCAN_SP_Brake_Pressure_Front;
	uint8_t ADCAN_SP_Brake_Pressure_Rear;
};

struct STOS_CAN_DAT_Current_Sensors{
	uint8_t ADCAN_EL_Current_Sensor_1;
	uint8_t ADCAN_EL_Current_Sensor_2;
	uint8_t ADCAN_EL_Current_Sensor_3;
	uint8_t ADCAN_EL_Current_Sensor_4;
	uint8_t ADCAN_EL_Current_Sensor_5;
	uint8_t ADCAN_EL_Current_Sensor_6;
	uint8_t ADCAN_EL_Current_Sensor_7;
	uint8_t ADCAN_EL_Current_Sensor_8;
};

struct STOS_CAN_DAT_FCU_ECU_Bat_Temp{
	uint8_t ADCAN_EL_Battery_24V_Temp;
	uint8_t ADCAN_EL_ECU_Temp_FCU_1;
	uint8_t ADCAN_EL_ECU_Temp_FCU_2;
};

struct STOS_CAN_DAT_FCU_Switches{
	uint8_t ADCAN_SP_ARB_Switch;
	uint8_t ADCAN_SP_LaunchC_Activated;
	uint8_t ADCAN_SP_LaunchC_Switch;
	uint8_t ADCAN_SP_RAS_Switch;
};

struct STOS_CAN_DAT_FDS_Parameters{
	uint8_t ADCAN_SP_FDS_Friction_LC;
	uint8_t ADCAN_SP_FDS_Slip_mue_max;
	uint8_t ADCAN_SP_FDS_Swim_VDE;
	uint8_t ADCAN_SP_FDS_Velo_VDE;
	uint8_t ADCAN_SP_FDS_Wheel_Slip_RL;
	uint8_t ADCAN_SP_FDS_Wheel_Slip_RR;
	uint8_t ADCAN_SP_FDS_Yaw_VDE;
};

struct STOS_CAN_DAT_FDS_Wheel_Signals{
	uint8_t ADCAN_SP_FDS_Slip_Angle_FL;
	uint8_t ADCAN_SP_FDS_Slip_Angle_FR;
	uint8_t ADCAN_SP_FDS_Slip_Angle_RL;
	uint8_t ADCAN_SP_FDS_Slip_Angle_RR;
	uint8_t ADCAN_SP_FDS_Whl_Load_FL;
	uint8_t ADCAN_SP_FDS_Whl_Load_FR;
	uint8_t ADCAN_SP_FDS_Whl_Load_RL;
	uint8_t ADCAN_SP_FDS_Whl_Load_RR;
};

struct STOS_CAN_DAT_Flash_Over_Can{
	uint8_t ADCAN_EL_FoC_1;
	uint8_t ADCAN_EL_FoC_2;
};

struct STOS_CAN_DAT_Frame_Pressure{
	uint8_t ADCAN_CH_Frame_Pressure;
};

struct STOS_CAN_DAT_Gyroscope_1{
	uint8_t ADCAN_SP_Gyro_1_X;
	uint8_t ADCAN_SP_Gyro_1_Y;
	uint8_t ADCAN_SP_Gyro_1_Z;
};

struct STOS_CAN_DAT_Gyroscope_2{
	uint8_t ADCAN_SP_Gyro_2_X;
	uint8_t ADCAN_SP_Gyro_2_Y;
	uint8_t ADCAN_SP_Gyro_2_Z;
};

struct STOS_CAN_DAT_Niveau_F{
	uint8_t ADCAN_SP_Niveau_FL_Niveau;
	uint8_t ADCAN_SP_Niveau_FR_Niveau;
};

struct STOS_CAN_DAT_Niveau_Front_Status{
	uint8_t ADCAN_SP_Niveau_FL_Error;
	uint8_t ADCAN_SP_Niveau_FL_Function;
	uint8_t ADCAN_SP_Niveau_FL_on_off;
	uint8_t ADCAN_SP_Niveau_FR_Error;
	uint8_t ADCAN_SP_Niveau_FR_Function;
	uint8_t ADCAN_SP_Niveau_FR_on_off;
};

struct STOS_CAN_DAT_Niveau_R{
	uint8_t ADCAN_SP_Niveau_R_Niveau;
};

struct STOS_CAN_DAT_Niveau_Rear_Status{
	uint8_t ADCAN_SP_Niveau_R_Error;
	uint8_t ADCAN_SP_Niveau_R_Function;
};

struct STOS_CAN_DAT_Oil_Pressure{
	uint8_t ADCAN_PT_Oil_Pressure;
};

struct STOS_CAN_DAT_Oil_Pressure_Status{
	uint8_t ADCAN_PT_Oil_Level;
	uint8_t ADCAN_PT_Oil_Level_RS232;
	uint8_t ADCAN_PT_Oil_Temp;
};

struct STOS_CAN_DAT_PDU_ECU_Temp{
	uint8_t ADCAN_EL_ECU_Temp_PDU_1;
	uint8_t ADCAN_EL_ECU_Temp_PDU_2;
	uint8_t ADCAN_EL_ECU_Temp_PDU_3;
	uint8_t ADCAN_EL_ECU_Temp_PDU_4;
};

struct STOS_CAN_DAT_PDU_Status{
	uint8_t ADCAN_CH_Mainhoop_Diag_L_1;
	uint8_t ADCAN_CH_Mainhoop_Diag_R_1;
	uint8_t ADCAN_EL_BOTS_Diag_1;
	uint8_t ADCAN_EL_BSPD_Shutdown_Out;
	uint8_t ADCAN_EL_Cockpit_Diag_1;
	uint8_t ADCAN_EL_Crash_Diag;
	uint8_t ADCAN_EL_Fuse_Status_1;
	uint8_t ADCAN_EL_Fuse_Status_10;
	uint8_t ADCAN_EL_Fuse_Status_11;
	uint8_t ADCAN_EL_Fuse_Status_12;
	uint8_t ADCAN_EL_Fuse_Status_13;
	uint8_t ADCAN_EL_Fuse_Status_14;
	uint8_t ADCAN_EL_Fuse_Status_15;
	uint8_t ADCAN_EL_Fuse_Status_16;
	uint8_t ADCAN_EL_Fuse_Status_17;
	uint8_t ADCAN_EL_Fuse_Status_18;
	uint8_t ADCAN_EL_Fuse_Status_19;
	uint8_t ADCAN_EL_Fuse_Status_2;
	uint8_t ADCAN_EL_Fuse_Status_3;
	uint8_t ADCAN_EL_Fuse_Status_4;
	uint8_t ADCAN_EL_Fuse_Status_5;
	uint8_t ADCAN_EL_Fuse_Status_6;
	uint8_t ADCAN_EL_Fuse_Status_7;
	uint8_t ADCAN_EL_Fuse_Status_8;
	uint8_t ADCAN_EL_Fuse_Status_9;
	uint8_t ADCAN_EL_Relais_Status_1;
	uint8_t ADCAN_EL_Relais_Status_2;
	uint8_t ADCAN_EL_Shutdown_Cockpit;
	uint8_t ADCAN_PT_Fuel_Pump_Signal;
	uint8_t ADCAN_PT_Reserve_Signal_L;
	uint8_t ADCAN_PT_Reserve_Signal_R;
	uint8_t ADCAN_PT_Water_Pump_Signal;
};

struct STOS_CAN_DAT_Pitot{
	uint8_t ADCAN_AE_Pitot_1;
	uint8_t ADCAN_AE_Pitot_2;
	uint8_t ADCAN_AE_Pitot_3;
};

struct STOS_CAN_DAT_RAS_PWM{
	uint8_t ADCAN_SP_RAS_PWM_L;
	uint8_t ADCAN_SP_RAS_PWM_R;
};

struct STOS_CAN_DAT_RAS_Status_Control{
	uint8_t ADCAN_SP_RAS_Angle;
	uint8_t ADCAN_SP_RAS_Homing_L;
	uint8_t ADCAN_SP_RAS_Homing_R;
};

struct STOS_CAN_DAT_RCU_ECU_Temp{
	uint8_t ADCAN_EL_ECU_Temp_RCU_1;
	uint8_t ADCAN_EL_ECU_Temp_RCU_2;
};

struct STOS_CAN_DAT_RCU_Test_A{
	uint8_t ADCAN_ZZ_Test_RCU_1;
	uint8_t ADCAN_ZZ_Test_RCU_2;
	uint8_t ADCAN_ZZ_Test_RCU_3;
	uint8_t ADCAN_ZZ_Test_RCU_4;
};

struct STOS_CAN_DAT_RCU_Test_B{
	uint8_t ADCAN_ZZ_Test_RCU_5;
	uint8_t ADCAN_ZZ_Test_RCU_6;
	uint8_t ADCAN_ZZ_Test_RCU_7;
	uint8_t ADCAN_ZZ_Test_RCU_8;
};

struct STOS_CAN_DAT_RCU_Test_C{
	uint8_t ADCAN_ZZ_Test_RCU_10;
	uint8_t ADCAN_ZZ_Test_RCU_9;
};

struct STOS_CAN_DAT_Rocker_F{
	uint8_t ADCAN_SP_Rocker_FL;
	uint8_t ADCAN_SP_Rocker_FR;
};

struct STOS_CAN_DAT_Rocker_R{
	uint8_t ADCAN_SP_Rocker_RL;
	uint8_t ADCAN_SP_Rocker_RR;
};

struct STOS_CAN_DAT_Shift_Clutch{
	uint8_t ADCAN_PT_Gearshift_DigIn;
	uint8_t ADCAN_PT_Gearshift_LaunchC;
	uint8_t ADCAN_PT_Shift_Power_on_off;
	uint8_t ADCAN_PT_Shift_Power_Sensor;
	uint8_t ADCAN_SP_Clutch_DigIn;
	uint8_t ADCAN_SP_Clutch_LaunchC;
};

struct STOS_CAN_DAT_Steering_Whl_Angle{
	uint8_t ADCAN_SP_Steering_Wheel_Angle;
};

struct STOS_CAN_DAT_SWCU_ECU_Temp{
	uint8_t ADCAN_EL_ECU_Temp_SWCU;
};

struct STOS_CAN_DAT_SWCU_Oh_Shit{
	uint8_t ADCAN_EL_INCR_1;
	uint8_t ADCAN_EL_INCR_2;
	uint8_t ADCAN_EL_Oh_Shit;
};

struct STOS_CAN_DAT_SWCU_Switches{
	uint8_t ADCAN_AE_Switch_1;
	uint8_t ADCAN_EL_Radio_Switch;
	uint8_t ADCAN_PT_Shift_Down;
	uint8_t ADCAN_PT_Shift_Up;
	uint8_t ADCAN_SP_ARH_switch_1;
	uint8_t ADCAN_SP_Clutch_Signal;
};

struct STOS_CAN_DAT_Test_FCU_A{
	uint8_t ADCAN_ZZ_Test_FCU_1;
	uint8_t ADCAN_ZZ_Test_FCU_2;
	uint8_t ADCAN_ZZ_Test_FCU_3;
};

struct STOS_CAN_DAT_Test_FCU_B{
	uint8_t ADCAN_ZZ_Test_FCU_4;
	uint8_t ADCAN_ZZ_Test_FCU_5;
	uint8_t ADCAN_ZZ_Test_FCU_6;
};

struct STOS_CAN_DAT_Water_Oil_Status_Control{
	uint8_t ADCAN_PT_Oil_Fan_Percent;
	uint8_t ADCAN_PT_Oil_PWM;
	uint8_t ADCAN_PT_Water_1_PWM;
	uint8_t ADCAN_PT_Water_2_PWM;
	uint8_t ADCAN_PT_Water_Fan_1_Percent;
	uint8_t ADCAN_PT_Water_Fan_2_Percent;
};

struct STOS_CAN_DAT_Whl_Speed_F{
	uint8_t ADCAN_SP_Wheel_Speed_FL;
	uint8_t ADCAN_SP_Wheel_Speed_FR;
};

struct STOS_CAN_DAT_Whl_Speed_R{
	uint8_t ADCAN_SP_Wheel_Speed_RL;
	uint8_t ADCAN_SP_Wheel_Speed_RR;
};