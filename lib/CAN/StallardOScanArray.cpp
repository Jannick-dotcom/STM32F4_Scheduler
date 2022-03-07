#include "StallardOScanStructs.hpp"
struct STOS_CAN_PDU_AGS1_gearbox_control_unit AGS1_gearbox_control_unit;
struct STOS_CAN_PDU_ABS_wheelspeeds ABS_wheelspeeds;
struct STOS_CAN_PDU_ABS_switch_state_slip_and_speed ABS_switch_state_slip_and_speed;
struct STOS_CAN_PDU_Injection_1 Injection_1;
struct STOS_CAN_PDU_Injection_2 Injection_2;
struct STOS_CAN_PDU_Ignition Ignition;
struct STOS_CAN_PDU_Ignition_Rev_Ath Ignition_Rev_Ath;
struct STOS_CAN_PDU_Lambda Lambda;
struct STOS_CAN_PDU_Speed Speed;
struct STOS_CAN_PDU_Lapfunc Lapfunc;
struct STOS_CAN_PDU_Gear_Dashboard_Acceleration Gear_Dashboard_Acceleration;
struct STOS_CAN_PDU_Traction_Control Traction_Control;
struct STOS_CAN_PDU_Electronic_Throttle_Control Electronic_Throttle_Control;
struct STOS_CAN_PDU_States_Temp_Press States_Temp_Press;
struct STOS_CAN_PDU_Boost_Pressures_Wastegate Boost_Pressures_Wastegate;
struct STOS_CAN_PDU_Acceleration_1 Acceleration_1;
struct STOS_CAN_PDU_Acceleration_2 Acceleration_2;
struct STOS_CAN_PDU_Aero_Fan_PWM Aero_Fan_PWM;
struct STOS_CAN_PDU_Aero_Fan_Telemetry Aero_Fan_Telemetry;
struct STOS_CAN_PDU_Aero_Fan_Warnings Aero_Fan_Warnings;
struct STOS_CAN_PDU_Airbox_Position Airbox_Position;
struct STOS_CAN_PDU_ARH_Homing ARH_Homing;
struct STOS_CAN_PDU_ARH_PWM ARH_PWM;
struct STOS_CAN_PDU_Battery_Temp_48V Battery_Temp_48V;
struct STOS_CAN_PDU_Brake_Disc_F Brake_Disc_F;
struct STOS_CAN_PDU_Brake_Disc_R Brake_Disc_R;
struct STOS_CAN_PDU_Brake_Pressure Brake_Pressure;
struct STOS_CAN_PDU_Current_Sensors Current_Sensors;
struct STOS_CAN_PDU_FCU_ECU_Bat_Temp FCU_ECU_Bat_Temp;
struct STOS_CAN_PDU_FCU_Switches FCU_Switches;
struct STOS_CAN_PDU_FDS_Parameters FDS_Parameters;
struct STOS_CAN_PDU_FDS_Wheel_Signals FDS_Wheel_Signals;
struct STOS_CAN_PDU_Flash_Over_Can Flash_Over_Can;
struct STOS_CAN_PDU_Frame_Pressure Frame_Pressure;
struct STOS_CAN_PDU_Gyroscope_1 Gyroscope_1;
struct STOS_CAN_PDU_Gyroscope_2 Gyroscope_2;
struct STOS_CAN_PDU_Niveau_F Niveau_F;
struct STOS_CAN_PDU_Niveau_Front_Status Niveau_Front_Status;
struct STOS_CAN_PDU_Niveau_R Niveau_R;
struct STOS_CAN_PDU_Niveau_Rear_Status Niveau_Rear_Status;
struct STOS_CAN_PDU_Oil_Pressure Oil_Pressure;
struct STOS_CAN_PDU_Oil_Pressure_Status Oil_Pressure_Status;
struct STOS_CAN_PDU_PDU_ECU_Temp PDU_ECU_Temp;
struct STOS_CAN_PDU_PDU_Status PDU_Status;
struct STOS_CAN_PDU_Pitot Pitot;
struct STOS_CAN_PDU_RAS_PWM RAS_PWM;
struct STOS_CAN_PDU_RAS_Status_Control RAS_Status_Control;
struct STOS_CAN_PDU_RCU_ECU_Temp RCU_ECU_Temp;
struct STOS_CAN_PDU_RCU_Test_A RCU_Test_A;
struct STOS_CAN_PDU_RCU_Test_B RCU_Test_B;
struct STOS_CAN_PDU_RCU_Test_C RCU_Test_C;
struct STOS_CAN_PDU_Rocker_F Rocker_F;
struct STOS_CAN_PDU_Rocker_R Rocker_R;
struct STOS_CAN_PDU_Shift_Clutch Shift_Clutch;
struct STOS_CAN_PDU_Steering_Whl_Angle Steering_Whl_Angle;
struct STOS_CAN_PDU_SWCU_ECU_Temp SWCU_ECU_Temp;
struct STOS_CAN_PDU_SWCU_Oh_Shit SWCU_Oh_Shit;
struct STOS_CAN_PDU_SWCU_Switches SWCU_Switches;
struct STOS_CAN_PDU_Test_FCU_A Test_FCU_A;
struct STOS_CAN_PDU_Test_FCU_B Test_FCU_B;
struct STOS_CAN_PDU_Water_Oil_Status_Control Water_Oil_Status_Control;
struct STOS_CAN_PDU_Whl_Speed_F Whl_Speed_F;
struct STOS_CAN_PDU_Whl_Speed_R Whl_Speed_R;
struct StallardOSCanMessage *canarray[] = {
	&AGS1_gearbox_control_unit,
	&ABS_wheelspeeds,
	&ABS_switch_state_slip_and_speed,
	&Injection_1,
	&Injection_2,
	&Ignition,
	&Ignition_Rev_Ath,
	&Lambda,
	&Speed,
	&Lapfunc,
	&Gear_Dashboard_Acceleration,
	&Traction_Control,
	&Electronic_Throttle_Control,
	&States_Temp_Press,
	&Boost_Pressures_Wastegate,
	&Acceleration_1,
	&Acceleration_2,
	&Aero_Fan_PWM,
	&Aero_Fan_Telemetry,
	&Aero_Fan_Warnings,
	&Airbox_Position,
	&ARH_Homing,
	&ARH_PWM,
	&Battery_Temp_48V,
	&Brake_Disc_F,
	&Brake_Disc_R,
	&Brake_Pressure,
	&Current_Sensors,
	&FCU_ECU_Bat_Temp,
	&FCU_Switches,
	&FDS_Parameters,
	&FDS_Wheel_Signals,
	&Flash_Over_Can,
	&Frame_Pressure,
	&Gyroscope_1,
	&Gyroscope_2,
	&Niveau_F,
	&Niveau_Front_Status,
	&Niveau_R,
	&Niveau_Rear_Status,
	&Oil_Pressure,
	&Oil_Pressure_Status,
	&PDU_ECU_Temp,
	&PDU_Status,
	&Pitot,
	&RAS_PWM,
	&RAS_Status_Control,
	&RCU_ECU_Temp,
	&RCU_Test_A,
	&RCU_Test_B,
	&RCU_Test_C,
	&Rocker_F,
	&Rocker_R,
	&Shift_Clutch,
	&Steering_Whl_Angle,
	&SWCU_ECU_Temp,
	&SWCU_Oh_Shit,
	&SWCU_Switches,
	&Test_FCU_A,
	&Test_FCU_B,
	&Water_Oil_Status_Control,
	&Whl_Speed_F,
	&Whl_Speed_R
};
uint16_t idarray[] = {
	AGS1_gearbox_control_unit.ID,
	ABS_wheelspeeds.ID,
	ABS_switch_state_slip_and_speed.ID,
	Injection_1.ID,
	Injection_2.ID,
	Ignition.ID,
	Ignition_Rev_Ath.ID,
	Lambda.ID,
	Speed.ID,
	Lapfunc.ID,
	Gear_Dashboard_Acceleration.ID,
	Traction_Control.ID,
	Electronic_Throttle_Control.ID,
	States_Temp_Press.ID,
	Boost_Pressures_Wastegate.ID,
	Acceleration_1.ID,
	Acceleration_2.ID,
	Aero_Fan_PWM.ID,
	Aero_Fan_Telemetry.ID,
	Aero_Fan_Warnings.ID,
	Airbox_Position.ID,
	ARH_Homing.ID,
	ARH_PWM.ID,
	Battery_Temp_48V.ID,
	Brake_Disc_F.ID,
	Brake_Disc_R.ID,
	Brake_Pressure.ID,
	Current_Sensors.ID,
	FCU_ECU_Bat_Temp.ID,
	FCU_Switches.ID,
	FDS_Parameters.ID,
	FDS_Wheel_Signals.ID,
	Flash_Over_Can.ID,
	Frame_Pressure.ID,
	Gyroscope_1.ID,
	Gyroscope_2.ID,
	Niveau_F.ID,
	Niveau_Front_Status.ID,
	Niveau_R.ID,
	Niveau_Rear_Status.ID,
	Oil_Pressure.ID,
	Oil_Pressure_Status.ID,
	PDU_ECU_Temp.ID,
	PDU_Status.ID,
	Pitot.ID,
	RAS_PWM.ID,
	RAS_Status_Control.ID,
	RCU_ECU_Temp.ID,
	RCU_Test_A.ID,
	RCU_Test_B.ID,
	RCU_Test_C.ID,
	Rocker_F.ID,
	Rocker_R.ID,
	Shift_Clutch.ID,
	Steering_Whl_Angle.ID,
	SWCU_ECU_Temp.ID,
	SWCU_Oh_Shit.ID,
	SWCU_Switches.ID,
	Test_FCU_A.ID,
	Test_FCU_B.ID,
	Water_Oil_Status_Control.ID,
	Whl_Speed_F.ID,
	Whl_Speed_R.ID
};
uint16_t idToOffset(uint16_t id) {
	for(uint16_t i = 0; i < sizeof(idarray) / sizeof(uint16_t); i++) {
		if(idarray[i] == id) return i;
	}
	return -1;
	}
void copyToBuffer(const StallardOSCanMessage *msg){
	if(msg == nullptr) return;
	uint16_t offset = idToOffset(msg->ID);
	*(canarray[offset]) = *(msg);
}
