#ifndef StallardOScanStructs_hpp
#define StallardOScanStructs_hpp
#include "stdint.h"
#include "StallardOScanTypes.hpp"
#include <math.h>

struct STOS_CAN_PDU_AGS1_gearbox_control_unit : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_AGS1_gearbox_control_unit;
	uint16_t _size;
	CAN_Signal<int8_t> activate_blip = {0, 1, 60, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> activate_cut = {0, 1, 61, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> blip_state = {0, 4, 28, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> cut_level_gcu = {0, 8, 48, 0, 0, 0.0196078, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> engaged_gear = {0, 8, 0, 0, 0, 0.5, -1.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> gearpot = {0, 10, 8, 0, 0, 4888, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> shift_state = {0, 4, 24, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> state_cut = {0, 4, 56, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> target_engine_speed = {0, 14, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_AGS1_gearbox_control_unit() 
	{
		ID = _id;
		uint8_t temp = activate_blip.countOfBits + activate_cut.countOfBits + blip_state.countOfBits + cut_level_gcu.countOfBits + engaged_gear.countOfBits + gearpot.countOfBits + shift_state.countOfBits + state_cut.countOfBits + target_engine_speed.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = activate_blip.build() | activate_cut.build() | blip_state.build() | cut_level_gcu.build() | engaged_gear.build() | gearpot.build() | shift_state.build() | state_cut.build() | target_engine_speed.build();
		ID = _id;
	}
	void unbuild()
	{
		activate_blip.unbuild(Val);
		activate_cut.unbuild(Val);
		blip_state.unbuild(Val);
		cut_level_gcu.unbuild(Val);
		engaged_gear.unbuild(Val);
		gearpot.unbuild(Val);
		shift_state.unbuild(Val);
		state_cut.unbuild(Val);
		target_engine_speed.unbuild(Val);
	}

};
struct STOS_CAN_PDU_ABS_wheelspeeds : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_ABS_wheelspeeds;
	uint16_t _size;
	CAN_Signal<uint16_t> speedABSfl = {0, 16, 0, 0, 0, 0.015625, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> speedABSfr = {0, 16, 16, 0, 0, 0.015625, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> speedABSrl = {0, 16, 32, 0, 0, 0.015625, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> speedABSrr = {0, 16, 48, 0, 0, 0.015625, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_ABS_wheelspeeds() 
	{
		ID = _id;
		uint8_t temp = speedABSfl.countOfBits + speedABSfr.countOfBits + speedABSrl.countOfBits + speedABSrr.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = speedABSfl.build() | speedABSfr.build() | speedABSrl.build() | speedABSrr.build();
		ID = _id;
	}
	void unbuild()
	{
		speedABSfl.unbuild(Val);
		speedABSfr.unbuild(Val);
		speedABSrl.unbuild(Val);
		speedABSrr.unbuild(Val);
	}

};
struct STOS_CAN_PDU_ABS_switch_state_slip_and_speed : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_ABS_switch_state_slip_and_speed;
	uint16_t _size;
	CAN_Signal<uint16_t> ax1_Bremse60ABS = {0, 16, 32, 0, 0, 0.00012742, -41768};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ay1_Bremse60ABS = {0, 16, 48, 0, 0, 0.00012742, -41768};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> blsABS = {0, 1, 24, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int16_t> p_HzABS = {0, 16, 8, 0, 0, 0.0153, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> switchstateABS = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_ABS_switch_state_slip_and_speed() 
	{
		ID = _id;
		uint8_t temp = ax1_Bremse60ABS.countOfBits + ay1_Bremse60ABS.countOfBits + blsABS.countOfBits + p_HzABS.countOfBits + switchstateABS.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ax1_Bremse60ABS.build() | ay1_Bremse60ABS.build() | blsABS.build() | p_HzABS.build() | switchstateABS.build();
		ID = _id;
	}
	void unbuild()
	{
		ax1_Bremse60ABS.unbuild(Val);
		ay1_Bremse60ABS.unbuild(Val);
		blsABS.unbuild(Val);
		p_HzABS.unbuild(Val);
		switchstateABS.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Injection_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Injection_1;
	uint16_t _size;
	CAN_Signal<uint8_t> ti_1 = {0, 8, 0, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ti_2 = {0, 8, 8, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ti_3 = {0, 8, 16, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ti_4 = {0, 8, 24, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ti_5 = {0, 8, 32, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ti_6 = {0, 8, 40, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ti_7 = {0, 8, 48, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ti_8 = {0, 8, 56, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Injection_1() 
	{
		ID = _id;
		uint8_t temp = ti_1.countOfBits + ti_2.countOfBits + ti_3.countOfBits + ti_4.countOfBits + ti_5.countOfBits + ti_6.countOfBits + ti_7.countOfBits + ti_8.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ti_1.build() | ti_2.build() | ti_3.build() | ti_4.build() | ti_5.build() | ti_6.build() | ti_7.build() | ti_8.build();
		ID = _id;
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
struct STOS_CAN_PDU_Injection_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Injection_2;
	uint16_t _size;
	CAN_Signal<uint8_t> injang = {0, 8, 24, 0, 0, 28125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> injoff = {0, 8, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lamctrl_2k = {0, 8, 48, 0, 0, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lamctrl_k = {0, 8, 40, 0, 0, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tibase = {0, 8, 0, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tibatt_o = {0, 8, 8, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> timap = {0, 8, 16, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Injection_2() 
	{
		ID = _id;
		uint8_t temp = injang.countOfBits + injoff.countOfBits + lamctrl_2k.countOfBits + lamctrl_k.countOfBits + tibase.countOfBits + tibatt_o.countOfBits + timap.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = injang.build() | injoff.build() | lamctrl_2k.build() | lamctrl_k.build() | tibase.build() | tibatt_o.build() | timap.build();
		ID = _id;
	}
	void unbuild()
	{
		injang.unbuild(Val);
		injoff.unbuild(Val);
		lamctrl_2k.unbuild(Val);
		lamctrl_k.unbuild(Val);
		tibase.unbuild(Val);
		tibatt_o.unbuild(Val);
		timap.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Ignition : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Ignition;
	uint16_t _size;
	CAN_Signal<int8_t> ign_1 = {0, 8, 0, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ign_2 = {0, 8, 8, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ign_3 = {0, 8, 16, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ign_4 = {0, 8, 24, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ign_5 = {0, 8, 32, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ign_6 = {0, 8, 40, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ign_7 = {0, 8, 48, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ign_8 = {0, 8, 56, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Ignition() 
	{
		ID = _id;
		uint8_t temp = ign_1.countOfBits + ign_2.countOfBits + ign_3.countOfBits + ign_4.countOfBits + ign_5.countOfBits + ign_6.countOfBits + ign_7.countOfBits + ign_8.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ign_1.build() | ign_2.build() | ign_3.build() | ign_4.build() | ign_5.build() | ign_6.build() | ign_7.build() | ign_8.build();
		ID = _id;
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
struct STOS_CAN_PDU_Ignition_Rev_Ath : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Ignition_Rev_Ath;
	uint16_t _size;
	CAN_Signal<uint8_t> ath = {0, 8, 40, 0, 0, 0.390625, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> dath = {0, 8, 48, 0, 0, 12, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ignbase = {0, 8, 0, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> ignmap = {0, 8, 8, 0, 0, 0.75, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> rev = {0, 16, 24, 0, 1, 0.5, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tdwell = {0, 8, 16, 0, 0, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Ignition_Rev_Ath() 
	{
		ID = _id;
		uint8_t temp = ath.countOfBits + dath.countOfBits + ignbase.countOfBits + ignmap.countOfBits + rev.countOfBits + tdwell.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ath.build() | dath.build() | ignbase.build() | ignmap.build() | rev.build() | tdwell.build();
		ID = _id;
	}
	void unbuild()
	{
		ath.unbuild(Val);
		dath.unbuild(Val);
		ignbase.unbuild(Val);
		ignmap.unbuild(Val);
		rev.unbuild(Val);
		tdwell.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Lambda : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Lambda;
	uint16_t _size;
	CAN_Signal<uint8_t> lam = {0, 8, 32, 0, 0, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lam_2 = {0, 8, 40, 0, 0, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> lami = {0, 8, 0, 0, 0, 0.25, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> lami_2 = {0, 8, 8, 0, 0, 0.25, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lammap = {0, 8, 48, 0, 0, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lammap_2 = {0, 8, 56, 0, 0, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> lamp = {0, 8, 16, 0, 0, 0.25, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> lamp_2 = {0, 8, 24, 0, 0, 0.25, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Lambda() 
	{
		ID = _id;
		uint8_t temp = lam.countOfBits + lam_2.countOfBits + lami.countOfBits + lami_2.countOfBits + lammap.countOfBits + lammap_2.countOfBits + lamp.countOfBits + lamp_2.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = lam.build() | lam_2.build() | lami.build() | lami_2.build() | lammap.build() | lammap_2.build() | lamp.build() | lamp_2.build();
		ID = _id;
	}
	void unbuild()
	{
		lam.unbuild(Val);
		lam_2.unbuild(Val);
		lami.unbuild(Val);
		lami_2.unbuild(Val);
		lammap.unbuild(Val);
		lammap_2.unbuild(Val);
		lamp.unbuild(Val);
		lamp_2.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Speed : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Speed;
	uint16_t _size;
	CAN_Signal<uint16_t> speed = {0, 16, 0, 0, 1, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> speedfl = {0, 8, 16, 0, 0, 2, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> speedfr = {0, 8, 24, 0, 0, 2, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> speedrl = {0, 8, 32, 0, 0, 2, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> speedrr = {0, 8, 40, 0, 0, 2, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Speed() 
	{
		ID = _id;
		uint8_t temp = speed.countOfBits + speedfl.countOfBits + speedfr.countOfBits + speedrl.countOfBits + speedrr.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = speed.build() | speedfl.build() | speedfr.build() | speedrl.build() | speedrr.build();
		ID = _id;
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
struct STOS_CAN_PDU_Lapfunc : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Lapfunc;
	uint16_t _size;
	CAN_Signal<uint16_t> lapdist = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> laptime = {0, 16, 16, 0, 1, 0.01, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> laptimediff = {0, 16, 32, 0, 1, 0.01, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> laptimefast = {0, 16, 48, 0, 1, 0.01, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Lapfunc() 
	{
		ID = _id;
		uint8_t temp = lapdist.countOfBits + laptime.countOfBits + laptimediff.countOfBits + laptimefast.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = lapdist.build() | laptime.build() | laptimediff.build() | laptimefast.build();
		ID = _id;
	}
	void unbuild()
	{
		lapdist.unbuild(Val);
		laptime.unbuild(Val);
		laptimediff.unbuild(Val);
		laptimefast.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Gear_Dashboard_Acceleration : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Gear_Dashboard_Acceleration;
	uint16_t _size;
	CAN_Signal<int8_t> accx = {0, 8, 40, 0, 0, 0.03125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> accy = {0, 8, 48, 0, 0, 0.03125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> accz = {0, 8, 56, 0, 0, 0.03125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ddugear = {0, 8, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> gcstate = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> gear = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> gearcut_u = {0, 8, 24, 0, 0, 0.0196078, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> gearratio = {0, 8, 16, 0, 0, 0.0625, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Gear_Dashboard_Acceleration() 
	{
		ID = _id;
		uint8_t temp = accx.countOfBits + accy.countOfBits + accz.countOfBits + ddugear.countOfBits + gcstate.countOfBits + gear.countOfBits + gearcut_u.countOfBits + gearratio.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = accx.build() | accy.build() | accz.build() | ddugear.build() | gcstate.build() | gear.build() | gearcut_u.build() | gearratio.build();
		ID = _id;
	}
	void unbuild()
	{
		accx.unbuild(Val);
		accy.unbuild(Val);
		accz.unbuild(Val);
		ddugear.unbuild(Val);
		gcstate.unbuild(Val);
		gear.unbuild(Val);
		gearcut_u.unbuild(Val);
		gearratio.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Traction_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Traction_Control;
	uint16_t _size;
	CAN_Signal<uint8_t> slipsp = {0, 8, 16, 0, 0, 0.078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> slra = {0, 8, 24, 0, 0, 0.078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int8_t> tcpfac = {0, 8, 0, 0, 0, 0.78125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tcsw = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> vdraxle = {0, 16, 32, 0, 1, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> vref = {0, 16, 48, 0, 1, 0.0078125, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Traction_Control() 
	{
		ID = _id;
		uint8_t temp = slipsp.countOfBits + slra.countOfBits + tcpfac.countOfBits + tcsw.countOfBits + vdraxle.countOfBits + vref.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = slipsp.build() | slra.build() | tcpfac.build() | tcsw.build() | vdraxle.build() | vref.build();
		ID = _id;
	}
	void unbuild()
	{
		slipsp.unbuild(Val);
		slra.unbuild(Val);
		tcpfac.unbuild(Val);
		tcsw.unbuild(Val);
		vdraxle.unbuild(Val);
		vref.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Electronic_Throttle_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Electronic_Throttle_Control;
	uint16_t _size;
	CAN_Signal<uint8_t> aps = {0, 8, 16, 0, 0, 0.5, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> batt_u = {0, 8, 48, 0, 0, 0.0706949, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> camshaftpos = {0, 8, 40, 0, 0, 0.5, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> etb = {0, 8, 0, 0, 0, 0.5, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> etb_sp = {0, 8, 8, 0, 0, 0.5, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lap_c = {0, 8, 56, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> p1 = {0, 16, 24, 0, 1, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Electronic_Throttle_Control() 
	{
		ID = _id;
		uint8_t temp = aps.countOfBits + batt_u.countOfBits + camshaftpos.countOfBits + etb.countOfBits + etb_sp.countOfBits + lap_c.countOfBits + p1.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = aps.build() | batt_u.build() | camshaftpos.build() | etb.build() | etb_sp.build() | lap_c.build() | p1.build();
		ID = _id;
	}
	void unbuild()
	{
		aps.unbuild(Val);
		batt_u.unbuild(Val);
		camshaftpos.unbuild(Val);
		etb.unbuild(Val);
		etb_sp.unbuild(Val);
		lap_c.unbuild(Val);
		p1.unbuild(Val);
	}

};
struct STOS_CAN_PDU_States_Temp_Press : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_States_Temp_Press;
	uint16_t _size;
	CAN_Signal<uint8_t> battlow_b = {0, 1, 61, 0x5, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> etbsys_e = {0, 1, 25, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> fuellap = {0, 16, 32, 0x3, 1, 0.00035791, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int16_t> fueltank = {0, 16, 48, 0x3, 1, 0.00572656, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> gearcut_b = {0, 1, 9, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> idle_b = {0, 1, 23, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ignoff_b = {0, 1, 31, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> injcut_b = {0, 1, 15, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> injcutin_b = {0, 1, 14, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> injenrich_b = {0, 1, 13, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> injstartphase_b = {0, 1, 12, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> knockadaptenable_b = {0, 1, 27, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> knockenable_b = {0, 1, 26, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lamctrl_2b = {0, 1, 10, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lamctrl_b = {0, 1, 11, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> lap_b = {0, 1, 22, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> laptrig_b = {0, 1, 21, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> mappos = {0, 8, 48, 0x2, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> mil_b = {0, 1, 20, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> oillamp_b = {0, 1, 19, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> pamb = {0, 16, 32, 0x2, 1, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> pcrank = {0, 8, 32, 0x1, 0, 5, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> pfuel = {0, 8, 56, 0x1, 0, 0.0514, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> phsok_b = {0, 1, 18, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> phsokset_b = {0, 1, 17, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> poil = {0, 8, 40, 0x1, 0, 0.0514, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> pwat = {0, 8, 48, 0x1, 0, 0.0514, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> rev_b = {0, 1, 30, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> revlimit_b = {0, 1, 29, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> rowcounter_0x77A = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> shled1_b = {0, 1, 56, 0x5, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> shled2_b = {0, 1, 57, 0x5, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> shled3_b = {0, 1, 58, 0x5, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> shled4_b = {0, 1, 59, 0x5, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> shled5_b = {0, 1, 60, 0x5, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> speedlimit_b = {0, 1, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> speedlimitreq_b = {0, 1, 24, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> startend_b = {0, 1, 28, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tair = {0, 8, 56, 0x2, 0, 1, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tc_b = {0, 1, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tex = {0, 8, 40, 0x5, 0, 5, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tex_2 = {0, 8, 48, 0x5, 0, 5, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tfuel = {0, 8, 32, 0x4, 0, 1, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tlam = {0, 8, 48, 0x4, 0, 5, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tlam_2 = {0, 8, 56, 0x4, 0, 5, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> tmot = {0, 8, 32, 0x5, 0, 1, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> toil = {0, 8, 40, 0x4, 0, 1, -40};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_States_Temp_Press() 
	{
		ID = _id;
		uint8_t temp = battlow_b.countOfBits + etbsys_e.countOfBits + fuellap.countOfBits + fueltank.countOfBits + gearcut_b.countOfBits + idle_b.countOfBits + ignoff_b.countOfBits + injcut_b.countOfBits + injcutin_b.countOfBits + injenrich_b.countOfBits + injstartphase_b.countOfBits + knockadaptenable_b.countOfBits + knockenable_b.countOfBits + lamctrl_2b.countOfBits + lamctrl_b.countOfBits + lap_b.countOfBits + laptrig_b.countOfBits + mappos.countOfBits + mil_b.countOfBits + oillamp_b.countOfBits + pamb.countOfBits + pcrank.countOfBits + pfuel.countOfBits + phsok_b.countOfBits + phsokset_b.countOfBits + poil.countOfBits + pwat.countOfBits + rev_b.countOfBits + revlimit_b.countOfBits + rowcounter_0x77A.countOfBits + shled1_b.countOfBits + shled2_b.countOfBits + shled3_b.countOfBits + shled4_b.countOfBits + shled5_b.countOfBits + speedlimit_b.countOfBits + speedlimitreq_b.countOfBits + startend_b.countOfBits + tair.countOfBits + tc_b.countOfBits + tex.countOfBits + tex_2.countOfBits + tfuel.countOfBits + tlam.countOfBits + tlam_2.countOfBits + tmot.countOfBits + toil.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = battlow_b.build() | etbsys_e.build() | fuellap.build() | fueltank.build() | gearcut_b.build() | idle_b.build() | ignoff_b.build() | injcut_b.build() | injcutin_b.build() | injenrich_b.build() | injstartphase_b.build() | knockadaptenable_b.build() | knockenable_b.build() | lamctrl_2b.build() | lamctrl_b.build() | lap_b.build() | laptrig_b.build() | mappos.build() | mil_b.build() | oillamp_b.build() | pamb.build() | pcrank.build() | pfuel.build() | phsok_b.build() | phsokset_b.build() | poil.build() | pwat.build() | rev_b.build() | revlimit_b.build() | rowcounter_0x77A.build() | shled1_b.build() | shled2_b.build() | shled3_b.build() | shled4_b.build() | shled5_b.build() | speedlimit_b.build() | speedlimitreq_b.build() | startend_b.build() | tair.build() | tc_b.build() | tex.build() | tex_2.build() | tfuel.build() | tlam.build() | tlam_2.build() | tmot.build() | toil.build();
		ID = _id;
	}
	void unbuild()
	{
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			battlow_b.unbuild(Val);
		etbsys_e.unbuild(Val);
		if((Val & 0xFF) == 0x3) //If the rowcounter points to this row 
			fuellap.unbuild(Val);
		if((Val & 0xFF) == 0x3) //If the rowcounter points to this row 
			fueltank.unbuild(Val);
		gearcut_b.unbuild(Val);
		idle_b.unbuild(Val);
		ignoff_b.unbuild(Val);
		injcut_b.unbuild(Val);
		injcutin_b.unbuild(Val);
		injenrich_b.unbuild(Val);
		injstartphase_b.unbuild(Val);
		knockadaptenable_b.unbuild(Val);
		knockenable_b.unbuild(Val);
		lamctrl_2b.unbuild(Val);
		lamctrl_b.unbuild(Val);
		lap_b.unbuild(Val);
		laptrig_b.unbuild(Val);
		if((Val & 0xFF) == 0x2) //If the rowcounter points to this row 
			mappos.unbuild(Val);
		mil_b.unbuild(Val);
		oillamp_b.unbuild(Val);
		if((Val & 0xFF) == 0x2) //If the rowcounter points to this row 
			pamb.unbuild(Val);
		if((Val & 0xFF) == 0x1) //If the rowcounter points to this row 
			pcrank.unbuild(Val);
		if((Val & 0xFF) == 0x1) //If the rowcounter points to this row 
			pfuel.unbuild(Val);
		phsok_b.unbuild(Val);
		phsokset_b.unbuild(Val);
		if((Val & 0xFF) == 0x1) //If the rowcounter points to this row 
			poil.unbuild(Val);
		if((Val & 0xFF) == 0x1) //If the rowcounter points to this row 
			pwat.unbuild(Val);
		rev_b.unbuild(Val);
		revlimit_b.unbuild(Val);
		rowcounter_0x77A.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			shled1_b.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			shled2_b.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			shled3_b.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			shled4_b.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			shled5_b.unbuild(Val);
		speedlimit_b.unbuild(Val);
		speedlimitreq_b.unbuild(Val);
		startend_b.unbuild(Val);
		if((Val & 0xFF) == 0x2) //If the rowcounter points to this row 
			tair.unbuild(Val);
		tc_b.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			tex.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			tex_2.unbuild(Val);
		if((Val & 0xFF) == 0x4) //If the rowcounter points to this row 
			tfuel.unbuild(Val);
		if((Val & 0xFF) == 0x4) //If the rowcounter points to this row 
			tlam.unbuild(Val);
		if((Val & 0xFF) == 0x4) //If the rowcounter points to this row 
			tlam_2.unbuild(Val);
		if((Val & 0xFF) == 0x5) //If the rowcounter points to this row 
			tmot.unbuild(Val);
		if((Val & 0xFF) == 0x4) //If the rowcounter points to this row 
			toil.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Boost_Pressures_Wastegate : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Boost_Pressures_Wastegate;
	uint16_t _size;
	CAN_Signal<uint16_t> p22_2m_pwg_m = {0, 16, 16, 0, 1, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> p22_m = {0, 16, 0, 0, 1, 0.1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> p22_sp = {0, 8, 32, 0, 0, 44402, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> pwg_sp = {0, 8, 40, 0, 0, 44402, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> wgdc_2_wgdchold = {0, 8, 56, 0, 0, 0.392157, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> wgdc_wgdcvent = {0, 8, 48, 0, 0, 0.392157, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Boost_Pressures_Wastegate() 
	{
		ID = _id;
		uint8_t temp = p22_2m_pwg_m.countOfBits + p22_m.countOfBits + p22_sp.countOfBits + pwg_sp.countOfBits + wgdc_2_wgdchold.countOfBits + wgdc_wgdcvent.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = p22_2m_pwg_m.build() | p22_m.build() | p22_sp.build() | pwg_sp.build() | wgdc_2_wgdchold.build() | wgdc_wgdcvent.build();
		ID = _id;
	}
	void unbuild()
	{
		p22_2m_pwg_m.unbuild(Val);
		p22_m.unbuild(Val);
		p22_sp.unbuild(Val);
		pwg_sp.unbuild(Val);
		wgdc_2_wgdchold.unbuild(Val);
		wgdc_wgdcvent.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Acceleration_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Acceleration_1;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_X = {0, 16, 0, 0, 1, 3, -7.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Y = {0, 16, 16, 0, 1, 3, -7.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Z = {0, 16, 32, 0, 1, 5, -12.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Acceleration_1() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Accel_1_X.countOfBits + ADCAN_SP_Accel_1_Y.countOfBits + ADCAN_SP_Accel_1_Z.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Accel_1_X.build() | ADCAN_SP_Accel_1_Y.build() | ADCAN_SP_Accel_1_Z.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Accel_1_X.unbuild(Val);
		ADCAN_SP_Accel_1_Y.unbuild(Val);
		ADCAN_SP_Accel_1_Z.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Acceleration_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Acceleration_2;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_X = {0, 16, 0, 0, 1, 3, -7.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Y = {0, 16, 16, 0, 1, 3, -7.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Z = {0, 16, 32, 0, 1, 5, -12.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Acceleration_2() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Accel_2_X.countOfBits + ADCAN_SP_Accel_2_Y.countOfBits + ADCAN_SP_Accel_2_Z.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Accel_2_X.build() | ADCAN_SP_Accel_2_Y.build() | ADCAN_SP_Accel_2_Z.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Accel_2_X.unbuild(Val);
		ADCAN_SP_Accel_2_Y.unbuild(Val);
		ADCAN_SP_Accel_2_Z.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_Fan_PWM : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_Fan_PWM;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_AE_Fan_L_PWM = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_AE_Fan_R_PWM = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_Fan_PWM() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Fan_L_PWM.countOfBits + ADCAN_AE_Fan_R_PWM.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Fan_L_PWM.build() | ADCAN_AE_Fan_R_PWM.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_Fan_L_PWM.unbuild(Val);
		ADCAN_AE_Fan_R_PWM.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_Fan_Telemetry : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_Fan_Telemetry;
	uint16_t _size;
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_1 = {0, 32, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_2 = {0, 32, 32, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_Fan_Telemetry() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Fan_Telemetry_1.countOfBits + ADCAN_AE_Fan_Telemetry_2.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Fan_Telemetry_1.build() | ADCAN_AE_Fan_Telemetry_2.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_Fan_Telemetry_1.unbuild(Val);
		ADCAN_AE_Fan_Telemetry_2.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_Fan_Warnings : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_Fan_Warnings;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_AE_Warnings = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_Fan_Warnings() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Warnings.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Warnings.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_Warnings.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Airbox_Position : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Airbox_Position;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Airbox_Pos = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Airbox_Position() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Airbox_Pos.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Airbox_Pos.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_PT_Airbox_Pos.unbuild(Val);
	}

};
struct STOS_CAN_PDU_ARH_Homing : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_ARH_Homing;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_Homing = {0, 1, 7, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_Homing = {0, 1, 6, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_ARH_Homing() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_ARH_1_Homing.countOfBits + ADCAN_SP_ARH_2_Homing.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_ARH_1_Homing.build() | ADCAN_SP_ARH_2_Homing.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_ARH_1_Homing.unbuild(Val);
		ADCAN_SP_ARH_2_Homing.unbuild(Val);
	}

};
struct STOS_CAN_PDU_ARH_PWM : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_ARH_PWM;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_PWM = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_PWM = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_ARH_PWM() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_ARH_1_PWM.countOfBits + ADCAN_SP_ARH_2_PWM.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_ARH_1_PWM.build() | ADCAN_SP_ARH_2_PWM.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_ARH_1_PWM.unbuild(Val);
		ADCAN_SP_ARH_2_PWM.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Battery_Temp_48V : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Battery_Temp_48V;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_1 = {0, 8, 0, 0, 0, 100, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_2 = {0, 8, 8, 0, 0, 100, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_3 = {0, 8, 16, 0, 0, 100, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Battery_Temp_48V() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_Battery_48V_Temp_1.countOfBits + ADCAN_EL_Battery_48V_Temp_2.countOfBits + ADCAN_EL_Battery_48V_Temp_3.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_Battery_48V_Temp_1.build() | ADCAN_EL_Battery_48V_Temp_2.build() | ADCAN_EL_Battery_48V_Temp_3.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_EL_Battery_48V_Temp_1.unbuild(Val);
		ADCAN_EL_Battery_48V_Temp_2.unbuild(Val);
		ADCAN_EL_Battery_48V_Temp_3.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Brake_Disc_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Brake_Disc_F;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_FL = {0, 16, 0, 0, 1, 200, -100};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_FR = {0, 16, 16, 0, 1, 200, -100};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Brake_Disc_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Brake_Disc_Temp_FL.countOfBits + ADCAN_SP_Brake_Disc_Temp_FR.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Brake_Disc_Temp_FL.build() | ADCAN_SP_Brake_Disc_Temp_FR.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Brake_Disc_Temp_FL.unbuild(Val);
		ADCAN_SP_Brake_Disc_Temp_FR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Brake_Disc_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Brake_Disc_R;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_RL = {0, 16, 0, 0, 1, 200, -100};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_RR = {0, 16, 16, 0, 1, 200, -100};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Brake_Disc_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Brake_Disc_Temp_RL.countOfBits + ADCAN_SP_Brake_Disc_Temp_RR.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Brake_Disc_Temp_RL.build() | ADCAN_SP_Brake_Disc_Temp_RR.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Brake_Disc_Temp_RL.unbuild(Val);
		ADCAN_SP_Brake_Disc_Temp_RR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Brake_Pressure : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Brake_Pressure;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Pressure_Front = {0, 16, 0, 0, 1, 40, -20};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Pressure_Rear = {0, 16, 16, 0, 1, 40, -20};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Bias = {0, 8, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Brake_Pressure() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Brake_Pressure_Front.countOfBits + ADCAN_SP_Brake_Pressure_Rear.countOfBits + ADCAN_SP_Brake_Bias.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Brake_Pressure_Front.build() | ADCAN_SP_Brake_Pressure_Rear.build() | ADCAN_SP_Brake_Bias.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Brake_Pressure_Front.unbuild(Val);
		ADCAN_SP_Brake_Pressure_Rear.unbuild(Val);
		ADCAN_SP_Brake_Bias.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Current_Sensors : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Current_Sensors;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_1 = {0, 8, 0, 0, 0, 10, -25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_2 = {0, 8, 8, 0, 0, 10, -25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_3 = {0, 8, 16, 0, 0, 10, -25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_4 = {0, 8, 24, 0, 0, 10, -25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_5 = {0, 8, 32, 0, 0, 15.1515, -37.8787};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_6 = {0, 8, 40, 0, 0, 15.1515, -37.8787};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_7 = {0, 8, 48, 0, 0, 15.1515, -37.8787};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_8 = {0, 8, 56, 0, 0, 50, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Current_Sensors() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_Current_Sensor_1.countOfBits + ADCAN_EL_Current_Sensor_2.countOfBits + ADCAN_EL_Current_Sensor_3.countOfBits + ADCAN_EL_Current_Sensor_4.countOfBits + ADCAN_EL_Current_Sensor_5.countOfBits + ADCAN_EL_Current_Sensor_6.countOfBits + ADCAN_EL_Current_Sensor_7.countOfBits + ADCAN_EL_Current_Sensor_8.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_Current_Sensor_1.build() | ADCAN_EL_Current_Sensor_2.build() | ADCAN_EL_Current_Sensor_3.build() | ADCAN_EL_Current_Sensor_4.build() | ADCAN_EL_Current_Sensor_5.build() | ADCAN_EL_Current_Sensor_6.build() | ADCAN_EL_Current_Sensor_7.build() | ADCAN_EL_Current_Sensor_8.build();
		ID = _id;
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
struct STOS_CAN_PDU_FCU_ECU_Bat_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_FCU_ECU_Bat_Temp;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_24V_Temp = {0, 8, 0, 0, 0, 100, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_1 = {0, 8, 8, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_2 = {0, 8, 16, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_FCU_ECU_Bat_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_Battery_24V_Temp.countOfBits + ADCAN_EL_ECU_Temp_FCU_1.countOfBits + ADCAN_EL_ECU_Temp_FCU_2.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_Battery_24V_Temp.build() | ADCAN_EL_ECU_Temp_FCU_1.build() | ADCAN_EL_ECU_Temp_FCU_2.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_EL_Battery_24V_Temp.unbuild(Val);
		ADCAN_EL_ECU_Temp_FCU_1.unbuild(Val);
		ADCAN_EL_ECU_Temp_FCU_2.unbuild(Val);
	}

};
struct STOS_CAN_PDU_FCU_Switches : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_FCU_Switches;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_ARB_Switch = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Activated = {0, 1, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Switch = {0, 8, 31, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Switch = {0, 8, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_FCU_Switches() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_ARB_Switch.countOfBits + ADCAN_SP_LaunchC_Activated.countOfBits + ADCAN_SP_LaunchC_Switch.countOfBits + ADCAN_SP_RAS_Switch.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_ARB_Switch.build() | ADCAN_SP_LaunchC_Activated.build() | ADCAN_SP_LaunchC_Switch.build() | ADCAN_SP_RAS_Switch.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_ARB_Switch.unbuild(Val);
		ADCAN_SP_LaunchC_Activated.unbuild(Val);
		ADCAN_SP_LaunchC_Switch.unbuild(Val);
		ADCAN_SP_RAS_Switch.unbuild(Val);
	}

};
struct STOS_CAN_PDU_FDS_Parameters : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_FDS_Parameters;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Friction_LC = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_mue_max = {0, 8, 56, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Swim_VDE = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_FDS_Velo_VDE = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RL = {0, 8, 40, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RR = {0, 8, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Yaw_VDE = {0, 8, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_FDS_Parameters() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_FDS_Friction_LC.countOfBits + ADCAN_SP_FDS_Slip_mue_max.countOfBits + ADCAN_SP_FDS_Swim_VDE.countOfBits + ADCAN_SP_FDS_Velo_VDE.countOfBits + ADCAN_SP_FDS_Wheel_Slip_RL.countOfBits + ADCAN_SP_FDS_Wheel_Slip_RR.countOfBits + ADCAN_SP_FDS_Yaw_VDE.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_FDS_Friction_LC.build() | ADCAN_SP_FDS_Slip_mue_max.build() | ADCAN_SP_FDS_Swim_VDE.build() | ADCAN_SP_FDS_Velo_VDE.build() | ADCAN_SP_FDS_Wheel_Slip_RL.build() | ADCAN_SP_FDS_Wheel_Slip_RR.build() | ADCAN_SP_FDS_Yaw_VDE.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_FDS_Friction_LC.unbuild(Val);
		ADCAN_SP_FDS_Slip_mue_max.unbuild(Val);
		ADCAN_SP_FDS_Swim_VDE.unbuild(Val);
		ADCAN_SP_FDS_Velo_VDE.unbuild(Val);
		ADCAN_SP_FDS_Wheel_Slip_RL.unbuild(Val);
		ADCAN_SP_FDS_Wheel_Slip_RR.unbuild(Val);
		ADCAN_SP_FDS_Yaw_VDE.unbuild(Val);
	}

};
struct STOS_CAN_PDU_FDS_Wheel_Signals : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_FDS_Wheel_Signals;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FL = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FR = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RL = {0, 8, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RR = {0, 8, 24, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FL = {0, 8, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FR = {0, 8, 40, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RL = {0, 8, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RR = {0, 8, 56, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_FDS_Wheel_Signals() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_FDS_Slip_Angle_FL.countOfBits + ADCAN_SP_FDS_Slip_Angle_FR.countOfBits + ADCAN_SP_FDS_Slip_Angle_RL.countOfBits + ADCAN_SP_FDS_Slip_Angle_RR.countOfBits + ADCAN_SP_FDS_Whl_Load_FL.countOfBits + ADCAN_SP_FDS_Whl_Load_FR.countOfBits + ADCAN_SP_FDS_Whl_Load_RL.countOfBits + ADCAN_SP_FDS_Whl_Load_RR.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_FDS_Slip_Angle_FL.build() | ADCAN_SP_FDS_Slip_Angle_FR.build() | ADCAN_SP_FDS_Slip_Angle_RL.build() | ADCAN_SP_FDS_Slip_Angle_RR.build() | ADCAN_SP_FDS_Whl_Load_FL.build() | ADCAN_SP_FDS_Whl_Load_FR.build() | ADCAN_SP_FDS_Whl_Load_RL.build() | ADCAN_SP_FDS_Whl_Load_RR.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_FDS_Slip_Angle_FL.unbuild(Val);
		ADCAN_SP_FDS_Slip_Angle_FR.unbuild(Val);
		ADCAN_SP_FDS_Slip_Angle_RL.unbuild(Val);
		ADCAN_SP_FDS_Slip_Angle_RR.unbuild(Val);
		ADCAN_SP_FDS_Whl_Load_FL.unbuild(Val);
		ADCAN_SP_FDS_Whl_Load_FR.unbuild(Val);
		ADCAN_SP_FDS_Whl_Load_RL.unbuild(Val);
		ADCAN_SP_FDS_Whl_Load_RR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Flash_Over_Can : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Flash_Over_Can;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_FoC_1 = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_FoC_2 = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Flash_Over_Can() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_FoC_1.countOfBits + ADCAN_EL_FoC_2.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_FoC_1.build() | ADCAN_EL_FoC_2.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_EL_FoC_1.unbuild(Val);
		ADCAN_EL_FoC_2.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Frame_Pressure : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Frame_Pressure;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_CH_Frame_Pressure = {0, 8, 0, 0, 0, 2.5, -1.25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Frame_Pressure() 
	{
		ID = _id;
		uint8_t temp = ADCAN_CH_Frame_Pressure.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_CH_Frame_Pressure.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_CH_Frame_Pressure.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Gyroscope_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Gyroscope_1;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_X = {0, 16, 0, 0, 1, 25, -62.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Y = {0, 16, 16, 0, 1, 25, -62.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Z = {0, 16, 32, 0, 1, 50, -125};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Gyroscope_1() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Gyro_1_X.countOfBits + ADCAN_SP_Gyro_1_Y.countOfBits + ADCAN_SP_Gyro_1_Z.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Gyro_1_X.build() | ADCAN_SP_Gyro_1_Y.build() | ADCAN_SP_Gyro_1_Z.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Gyro_1_X.unbuild(Val);
		ADCAN_SP_Gyro_1_Y.unbuild(Val);
		ADCAN_SP_Gyro_1_Z.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Gyroscope_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Gyroscope_2;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_X = {0, 16, 0, 0, 1, 25, -62.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Y = {0, 16, 16, 0, 1, 25, -62.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Z = {0, 16, 32, 0, 1, 50, -125};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Gyroscope_2() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Gyro_2_X.countOfBits + ADCAN_SP_Gyro_2_Y.countOfBits + ADCAN_SP_Gyro_2_Z.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Gyro_2_X.build() | ADCAN_SP_Gyro_2_Y.build() | ADCAN_SP_Gyro_2_Z.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Gyro_2_X.unbuild(Val);
		ADCAN_SP_Gyro_2_Y.unbuild(Val);
		ADCAN_SP_Gyro_2_Z.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Niveau_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Niveau_F;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Niveau = {0, 8, 0, 0, 0, 25, 25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Niveau = {0, 8, 8, 0, 0, 25, 25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Niveau_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_FL_Niveau.countOfBits + ADCAN_SP_Niveau_FR_Niveau.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_FL_Niveau.build() | ADCAN_SP_Niveau_FR_Niveau.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_FL_Niveau.unbuild(Val);
		ADCAN_SP_Niveau_FR_Niveau.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Niveau_Front_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Niveau_Front_Status;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Error = {0, 1, 23, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Function = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_on_off = {0, 1, 22, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Error = {0, 1, 18, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Function = {0, 8, 21, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_on_off = {0, 1, 20, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Niveau_Front_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_FL_Error.countOfBits + ADCAN_SP_Niveau_FL_Function.countOfBits + ADCAN_SP_Niveau_FL_on_off.countOfBits + ADCAN_SP_Niveau_FR_Error.countOfBits + ADCAN_SP_Niveau_FR_Function.countOfBits + ADCAN_SP_Niveau_FR_on_off.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_FL_Error.build() | ADCAN_SP_Niveau_FL_Function.build() | ADCAN_SP_Niveau_FL_on_off.build() | ADCAN_SP_Niveau_FR_Error.build() | ADCAN_SP_Niveau_FR_Function.build() | ADCAN_SP_Niveau_FR_on_off.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_FL_Error.unbuild(Val);
		ADCAN_SP_Niveau_FL_Function.unbuild(Val);
		ADCAN_SP_Niveau_FL_on_off.unbuild(Val);
		ADCAN_SP_Niveau_FR_Error.unbuild(Val);
		ADCAN_SP_Niveau_FR_Function.unbuild(Val);
		ADCAN_SP_Niveau_FR_on_off.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Niveau_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Niveau_R;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Niveau = {0, 8, 0, 0, 0, 25, 25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Niveau_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_R_Niveau.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_R_Niveau.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_R_Niveau.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Niveau_Rear_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Niveau_Rear_Status;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Error = {0, 1, 15, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Function = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Niveau_Rear_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_R_Error.countOfBits + ADCAN_SP_Niveau_R_Function.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_R_Error.build() | ADCAN_SP_Niveau_R_Function.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_R_Error.unbuild(Val);
		ADCAN_SP_Niveau_R_Function.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Oil_Pressure : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Oil_Pressure;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Pressure = {0, 8, 0, 0, 0, 2.5, -1.25};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Oil_Pressure() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Oil_Pressure.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Oil_Pressure.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_PT_Oil_Pressure.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Oil_Pressure_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Oil_Pressure_Status;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level_RS232 = {0, 1, 23, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Temp = {0, 8, 8, 0, 0, 57.5, -83.75};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Oil_Pressure_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Oil_Level.countOfBits + ADCAN_PT_Oil_Level_RS232.countOfBits + ADCAN_PT_Oil_Temp.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Oil_Level.build() | ADCAN_PT_Oil_Level_RS232.build() | ADCAN_PT_Oil_Temp.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_PT_Oil_Level.unbuild(Val);
		ADCAN_PT_Oil_Level_RS232.unbuild(Val);
		ADCAN_PT_Oil_Temp.unbuild(Val);
	}

};
struct STOS_CAN_PDU_PDU_ECU_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_PDU_ECU_Temp;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_1 = {0, 8, 0, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_2 = {0, 8, 8, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_3 = {0, 8, 16, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_4 = {0, 8, 24, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_PDU_ECU_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_ECU_Temp_PDU_1.countOfBits + ADCAN_EL_ECU_Temp_PDU_2.countOfBits + ADCAN_EL_ECU_Temp_PDU_3.countOfBits + ADCAN_EL_ECU_Temp_PDU_4.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_ECU_Temp_PDU_1.build() | ADCAN_EL_ECU_Temp_PDU_2.build() | ADCAN_EL_ECU_Temp_PDU_3.build() | ADCAN_EL_ECU_Temp_PDU_4.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_PDU_1.unbuild(Val);
		ADCAN_EL_ECU_Temp_PDU_2.unbuild(Val);
		ADCAN_EL_ECU_Temp_PDU_3.unbuild(Val);
		ADCAN_EL_ECU_Temp_PDU_4.unbuild(Val);
	}

};
struct STOS_CAN_PDU_PDU_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_PDU_Status;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_CH_Mainhoop_Diag_L_1 = {0, 1, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_CH_Mainhoop_Diag_R_1 = {0, 1, 1, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_BOTS_Diag_1 = {0, 1, 2, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_BSPD_Shutdown_Out = {0, 1, 3, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Cockpit_Diag_1 = {0, 1, 4, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Crash_Diag = {0, 1, 5, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_1 = {0, 1, 6, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_10 = {0, 1, 7, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_11 = {0, 1, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_12 = {0, 1, 9, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_13 = {0, 1, 10, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_14 = {0, 1, 11, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_15 = {0, 1, 12, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_16 = {0, 1, 13, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_17 = {0, 1, 14, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_18 = {0, 1, 15, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_19 = {0, 1, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_2 = {0, 1, 17, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_3 = {0, 1, 18, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_4 = {0, 1, 19, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_5 = {0, 1, 20, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_6 = {0, 1, 21, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_7 = {0, 1, 22, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_8 = {0, 1, 23, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_9 = {0, 1, 24, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Relais_Status_1 = {0, 1, 25, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Relais_Status_2 = {0, 1, 26, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Shutdown_Cockpit = {0, 1, 27, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Fuel_Pump_Signal = {0, 1, 28, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Reserve_Signal_L = {0, 1, 29, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Reserve_Signal_R = {0, 1, 30, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Pump_Signal = {0, 1, 31, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_PDU_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_CH_Mainhoop_Diag_L_1.countOfBits + ADCAN_CH_Mainhoop_Diag_R_1.countOfBits + ADCAN_EL_BOTS_Diag_1.countOfBits + ADCAN_EL_BSPD_Shutdown_Out.countOfBits + ADCAN_EL_Cockpit_Diag_1.countOfBits + ADCAN_EL_Crash_Diag.countOfBits + ADCAN_EL_Fuse_Status_1.countOfBits + ADCAN_EL_Fuse_Status_10.countOfBits + ADCAN_EL_Fuse_Status_11.countOfBits + ADCAN_EL_Fuse_Status_12.countOfBits + ADCAN_EL_Fuse_Status_13.countOfBits + ADCAN_EL_Fuse_Status_14.countOfBits + ADCAN_EL_Fuse_Status_15.countOfBits + ADCAN_EL_Fuse_Status_16.countOfBits + ADCAN_EL_Fuse_Status_17.countOfBits + ADCAN_EL_Fuse_Status_18.countOfBits + ADCAN_EL_Fuse_Status_19.countOfBits + ADCAN_EL_Fuse_Status_2.countOfBits + ADCAN_EL_Fuse_Status_3.countOfBits + ADCAN_EL_Fuse_Status_4.countOfBits + ADCAN_EL_Fuse_Status_5.countOfBits + ADCAN_EL_Fuse_Status_6.countOfBits + ADCAN_EL_Fuse_Status_7.countOfBits + ADCAN_EL_Fuse_Status_8.countOfBits + ADCAN_EL_Fuse_Status_9.countOfBits + ADCAN_EL_Relais_Status_1.countOfBits + ADCAN_EL_Relais_Status_2.countOfBits + ADCAN_EL_Shutdown_Cockpit.countOfBits + ADCAN_PT_Fuel_Pump_Signal.countOfBits + ADCAN_PT_Reserve_Signal_L.countOfBits + ADCAN_PT_Reserve_Signal_R.countOfBits + ADCAN_PT_Water_Pump_Signal.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_CH_Mainhoop_Diag_L_1.build() | ADCAN_CH_Mainhoop_Diag_R_1.build() | ADCAN_EL_BOTS_Diag_1.build() | ADCAN_EL_BSPD_Shutdown_Out.build() | ADCAN_EL_Cockpit_Diag_1.build() | ADCAN_EL_Crash_Diag.build() | ADCAN_EL_Fuse_Status_1.build() | ADCAN_EL_Fuse_Status_10.build() | ADCAN_EL_Fuse_Status_11.build() | ADCAN_EL_Fuse_Status_12.build() | ADCAN_EL_Fuse_Status_13.build() | ADCAN_EL_Fuse_Status_14.build() | ADCAN_EL_Fuse_Status_15.build() | ADCAN_EL_Fuse_Status_16.build() | ADCAN_EL_Fuse_Status_17.build() | ADCAN_EL_Fuse_Status_18.build() | ADCAN_EL_Fuse_Status_19.build() | ADCAN_EL_Fuse_Status_2.build() | ADCAN_EL_Fuse_Status_3.build() | ADCAN_EL_Fuse_Status_4.build() | ADCAN_EL_Fuse_Status_5.build() | ADCAN_EL_Fuse_Status_6.build() | ADCAN_EL_Fuse_Status_7.build() | ADCAN_EL_Fuse_Status_8.build() | ADCAN_EL_Fuse_Status_9.build() | ADCAN_EL_Relais_Status_1.build() | ADCAN_EL_Relais_Status_2.build() | ADCAN_EL_Shutdown_Cockpit.build() | ADCAN_PT_Fuel_Pump_Signal.build() | ADCAN_PT_Reserve_Signal_L.build() | ADCAN_PT_Reserve_Signal_R.build() | ADCAN_PT_Water_Pump_Signal.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_CH_Mainhoop_Diag_L_1.unbuild(Val);
		ADCAN_CH_Mainhoop_Diag_R_1.unbuild(Val);
		ADCAN_EL_BOTS_Diag_1.unbuild(Val);
		ADCAN_EL_BSPD_Shutdown_Out.unbuild(Val);
		ADCAN_EL_Cockpit_Diag_1.unbuild(Val);
		ADCAN_EL_Crash_Diag.unbuild(Val);
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
		ADCAN_EL_Shutdown_Cockpit.unbuild(Val);
		ADCAN_PT_Fuel_Pump_Signal.unbuild(Val);
		ADCAN_PT_Reserve_Signal_L.unbuild(Val);
		ADCAN_PT_Reserve_Signal_R.unbuild(Val);
		ADCAN_PT_Water_Pump_Signal.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Pitot : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Pitot;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_1 = {0, 16, 0, 0, 1, 17.5, -8.75};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_2 = {0, 16, 16, 0, 1, 17.5, -8.75};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_3 = {0, 16, 32, 0, 1, 17.5, -8.75};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Pitot() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Pitot_1.countOfBits + ADCAN_AE_Pitot_2.countOfBits + ADCAN_AE_Pitot_3.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Pitot_1.build() | ADCAN_AE_Pitot_2.build() | ADCAN_AE_Pitot_3.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_Pitot_1.unbuild(Val);
		ADCAN_AE_Pitot_2.unbuild(Val);
		ADCAN_AE_Pitot_3.unbuild(Val);
	}

};
struct STOS_CAN_PDU_RAS_PWM : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_RAS_PWM;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_L = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_R = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_RAS_PWM() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_RAS_PWM_L.countOfBits + ADCAN_SP_RAS_PWM_R.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_RAS_PWM_L.build() | ADCAN_SP_RAS_PWM_R.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_RAS_PWM_L.unbuild(Val);
		ADCAN_SP_RAS_PWM_R.unbuild(Val);
	}

};
struct STOS_CAN_PDU_RAS_Status_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_RAS_Status_Control;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Angle = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_L = {0, 1, 15, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_R = {0, 1, 14, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_RAS_Status_Control() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_RAS_Angle.countOfBits + ADCAN_SP_RAS_Homing_L.countOfBits + ADCAN_SP_RAS_Homing_R.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_RAS_Angle.build() | ADCAN_SP_RAS_Homing_L.build() | ADCAN_SP_RAS_Homing_R.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_RAS_Angle.unbuild(Val);
		ADCAN_SP_RAS_Homing_L.unbuild(Val);
		ADCAN_SP_RAS_Homing_R.unbuild(Val);
	}

};
struct STOS_CAN_PDU_RCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_RCU_ECU_Temp;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_1 = {0, 8, 0, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_2 = {0, 8, 8, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_RCU_ECU_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_ECU_Temp_RCU_1.countOfBits + ADCAN_EL_ECU_Temp_RCU_2.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_ECU_Temp_RCU_1.build() | ADCAN_EL_ECU_Temp_RCU_2.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_RCU_1.unbuild(Val);
		ADCAN_EL_ECU_Temp_RCU_2.unbuild(Val);
	}

};
struct STOS_CAN_PDU_RCU_Test_A : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_RCU_Test_A;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_1 = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_2 = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_3 = {0, 16, 32, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_4 = {0, 16, 48, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_RCU_Test_A() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_RCU_1.countOfBits + ADCAN_ZZ_Test_RCU_2.countOfBits + ADCAN_ZZ_Test_RCU_3.countOfBits + ADCAN_ZZ_Test_RCU_4.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_RCU_1.build() | ADCAN_ZZ_Test_RCU_2.build() | ADCAN_ZZ_Test_RCU_3.build() | ADCAN_ZZ_Test_RCU_4.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_1.unbuild(Val);
		ADCAN_ZZ_Test_RCU_2.unbuild(Val);
		ADCAN_ZZ_Test_RCU_3.unbuild(Val);
		ADCAN_ZZ_Test_RCU_4.unbuild(Val);
	}

};
struct STOS_CAN_PDU_RCU_Test_B : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_RCU_Test_B;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_5 = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_6 = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_7 = {0, 16, 32, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_8 = {0, 16, 48, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_RCU_Test_B() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_RCU_5.countOfBits + ADCAN_ZZ_Test_RCU_6.countOfBits + ADCAN_ZZ_Test_RCU_7.countOfBits + ADCAN_ZZ_Test_RCU_8.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_RCU_5.build() | ADCAN_ZZ_Test_RCU_6.build() | ADCAN_ZZ_Test_RCU_7.build() | ADCAN_ZZ_Test_RCU_8.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_5.unbuild(Val);
		ADCAN_ZZ_Test_RCU_6.unbuild(Val);
		ADCAN_ZZ_Test_RCU_7.unbuild(Val);
		ADCAN_ZZ_Test_RCU_8.unbuild(Val);
	}

};
struct STOS_CAN_PDU_RCU_Test_C : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_RCU_Test_C;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_10 = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_9 = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_RCU_Test_C() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_RCU_10.countOfBits + ADCAN_ZZ_Test_RCU_9.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_RCU_10.build() | ADCAN_ZZ_Test_RCU_9.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_10.unbuild(Val);
		ADCAN_ZZ_Test_RCU_9.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Rocker_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Rocker_F;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_FL = {0, 16, 0, 0, 1, 20, -5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_FR = {0, 16, 16, 0, 1, 20, -5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Rocker_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Rocker_FL.countOfBits + ADCAN_SP_Rocker_FR.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Rocker_FL.build() | ADCAN_SP_Rocker_FR.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Rocker_FL.unbuild(Val);
		ADCAN_SP_Rocker_FR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Rocker_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Rocker_R;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_RL = {0, 16, 0, 0, 1, 20, -5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_RR = {0, 16, 16, 0, 1, 20, -5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Rocker_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Rocker_RL.countOfBits + ADCAN_SP_Rocker_RR.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Rocker_RL.build() | ADCAN_SP_Rocker_RR.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Rocker_RL.unbuild(Val);
		ADCAN_SP_Rocker_RR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Shift_Clutch : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Shift_Clutch;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_DigIn = {0, 1, 21, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_LaunchC = {0, 1, 20, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_PT_Shift_Force_Sensor = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_DigIn = {0, 1, 23, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_LaunchC = {0, 1, 22, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Force_on_off = {0, 1, 19, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Shift_Clutch() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Gearshift_DigIn.countOfBits + ADCAN_PT_Gearshift_LaunchC.countOfBits + ADCAN_PT_Shift_Force_Sensor.countOfBits + ADCAN_SP_Clutch_DigIn.countOfBits + ADCAN_SP_Clutch_LaunchC.countOfBits + ADCAN_PT_Shift_Force_on_off.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Gearshift_DigIn.build() | ADCAN_PT_Gearshift_LaunchC.build() | ADCAN_PT_Shift_Force_Sensor.build() | ADCAN_SP_Clutch_DigIn.build() | ADCAN_SP_Clutch_LaunchC.build() | ADCAN_PT_Shift_Force_on_off.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_PT_Gearshift_DigIn.unbuild(Val);
		ADCAN_PT_Gearshift_LaunchC.unbuild(Val);
		ADCAN_PT_Shift_Force_Sensor.unbuild(Val);
		ADCAN_SP_Clutch_DigIn.unbuild(Val);
		ADCAN_SP_Clutch_LaunchC.unbuild(Val);
		ADCAN_PT_Shift_Force_on_off.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Steering_Whl_Angle : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Steering_Whl_Angle;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Steering_Wheel_Angle = {0, 16, 0, 0, 1, 75, -187.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Steering_Whl_Angle() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Steering_Wheel_Angle.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Steering_Wheel_Angle.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Steering_Wheel_Angle.unbuild(Val);
	}

};
struct STOS_CAN_PDU_SWCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_SWCU_ECU_Temp;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_SWCU = {0, 8, 0, 0, 0, 100, -50};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_SWCU_ECU_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_ECU_Temp_SWCU.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_ECU_Temp_SWCU.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_SWCU.unbuild(Val);
	}

};
struct STOS_CAN_PDU_SWCU_Oh_Shit : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_SWCU_Oh_Shit;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_INCR_1 = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_INCR_2 = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Oh_Shit = {0, 1, 23, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_SWCU_Oh_Shit() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_INCR_1.countOfBits + ADCAN_EL_INCR_2.countOfBits + ADCAN_EL_Oh_Shit.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_INCR_1.build() | ADCAN_EL_INCR_2.build() | ADCAN_EL_Oh_Shit.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_EL_INCR_1.unbuild(Val);
		ADCAN_EL_INCR_2.unbuild(Val);
		ADCAN_EL_Oh_Shit.unbuild(Val);
	}

};
struct STOS_CAN_PDU_SWCU_Switches : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_SWCU_Switches;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_AE_Switch_1 = {0, 1, 2, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_EL_Radio_Switch = {0, 1, 3, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Down = {0, 1, 4, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Up = {0, 1, 5, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_switch_1 = {0, 1, 6, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_Signal = {0, 1, 7, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_SWCU_Switches() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Switch_1.countOfBits + ADCAN_EL_Radio_Switch.countOfBits + ADCAN_PT_Shift_Down.countOfBits + ADCAN_PT_Shift_Up.countOfBits + ADCAN_SP_ARH_switch_1.countOfBits + ADCAN_SP_Clutch_Signal.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Switch_1.build() | ADCAN_EL_Radio_Switch.build() | ADCAN_PT_Shift_Down.build() | ADCAN_PT_Shift_Up.build() | ADCAN_SP_ARH_switch_1.build() | ADCAN_SP_Clutch_Signal.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_Switch_1.unbuild(Val);
		ADCAN_EL_Radio_Switch.unbuild(Val);
		ADCAN_PT_Shift_Down.unbuild(Val);
		ADCAN_PT_Shift_Up.unbuild(Val);
		ADCAN_SP_ARH_switch_1.unbuild(Val);
		ADCAN_SP_Clutch_Signal.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Test_FCU_A : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Test_FCU_A;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_1 = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_2 = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_3 = {0, 16, 32, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Test_FCU_A() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_FCU_1.countOfBits + ADCAN_ZZ_Test_FCU_2.countOfBits + ADCAN_ZZ_Test_FCU_3.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_FCU_1.build() | ADCAN_ZZ_Test_FCU_2.build() | ADCAN_ZZ_Test_FCU_3.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_FCU_1.unbuild(Val);
		ADCAN_ZZ_Test_FCU_2.unbuild(Val);
		ADCAN_ZZ_Test_FCU_3.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Test_FCU_B : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Test_FCU_B;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_4 = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_5 = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_6 = {0, 16, 32, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Test_FCU_B() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_FCU_4.countOfBits + ADCAN_ZZ_Test_FCU_5.countOfBits + ADCAN_ZZ_Test_FCU_6.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_FCU_4.build() | ADCAN_ZZ_Test_FCU_5.build() | ADCAN_ZZ_Test_FCU_6.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_FCU_4.unbuild(Val);
		ADCAN_ZZ_Test_FCU_5.unbuild(Val);
		ADCAN_ZZ_Test_FCU_6.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Water_Oil_Status_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Water_Oil_Status_Control;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Fan_Percent = {0, 8, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_PWM = {0, 8, 8, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Water_1_PWM = {0, 8, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Water_2_PWM = {0, 8, 24, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_1_Percent = {0, 8, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_2_Percent = {0, 8, 40, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Pump_Percent = {0, 8, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Water_Oil_Status_Control() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Oil_Fan_Percent.countOfBits + ADCAN_PT_Oil_PWM.countOfBits + ADCAN_PT_Water_1_PWM.countOfBits + ADCAN_PT_Water_2_PWM.countOfBits + ADCAN_PT_Water_Fan_1_Percent.countOfBits + ADCAN_PT_Water_Fan_2_Percent.countOfBits + ADCAN_PT_Water_Pump_Percent.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Oil_Fan_Percent.build() | ADCAN_PT_Oil_PWM.build() | ADCAN_PT_Water_1_PWM.build() | ADCAN_PT_Water_2_PWM.build() | ADCAN_PT_Water_Fan_1_Percent.build() | ADCAN_PT_Water_Fan_2_Percent.build() | ADCAN_PT_Water_Pump_Percent.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_PT_Oil_Fan_Percent.unbuild(Val);
		ADCAN_PT_Oil_PWM.unbuild(Val);
		ADCAN_PT_Water_1_PWM.unbuild(Val);
		ADCAN_PT_Water_2_PWM.unbuild(Val);
		ADCAN_PT_Water_Fan_1_Percent.unbuild(Val);
		ADCAN_PT_Water_Fan_2_Percent.unbuild(Val);
		ADCAN_PT_Water_Pump_Percent.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Whl_Speed_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Whl_Speed_F;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FL = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FR = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Whl_Speed_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Wheel_Speed_FL.countOfBits + ADCAN_SP_Wheel_Speed_FR.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Wheel_Speed_FL.build() | ADCAN_SP_Wheel_Speed_FR.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Wheel_Speed_FL.unbuild(Val);
		ADCAN_SP_Wheel_Speed_FR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Whl_Speed_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Whl_Speed_R;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RL = {0, 16, 0, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RR = {0, 16, 16, 0, 1, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Whl_Speed_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Wheel_Speed_RL.countOfBits + ADCAN_SP_Wheel_Speed_RR.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Wheel_Speed_RL.build() | ADCAN_SP_Wheel_Speed_RR.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_SP_Wheel_Speed_RL.unbuild(Val);
		ADCAN_SP_Wheel_Speed_RR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_1;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_1 = {0, 16, 0, 0, 0, 1.21968375, 79152.96};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_2 = {0, 16, 16, 0, 0, 1.21916625, 79083.79};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_3 = {0, 16, 32, 0, 0, 1.2189975, 78918.7};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_4 = {0, 16, 48, 0, 0, 1.2180825, 78998.83};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_1() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_1.countOfBits + ADCAN_AE_PT_2.countOfBits + ADCAN_AE_PT_3.countOfBits + ADCAN_AE_PT_4.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_1.build() | ADCAN_AE_PT_2.build() | ADCAN_AE_PT_3.build() | ADCAN_AE_PT_4.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_1.unbuild(Val);
		ADCAN_AE_PT_2.unbuild(Val);
		ADCAN_AE_PT_3.unbuild(Val);
		ADCAN_AE_PT_4.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_2;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_5 = {0, 16, 0, 0, 0, 1.218315, 78875.26};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_6 = {0, 16, 16, 0, 0, 1.21946625, 79318.41};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_7 = {0, 16, 32, 0, 0, 1.21980375, 79186.4};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_8 = {0, 16, 48, 0, 0, 1.21963125, 79074.58};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_2() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_5.countOfBits + ADCAN_AE_PT_6.countOfBits + ADCAN_AE_PT_7.countOfBits + ADCAN_AE_PT_8.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_5.build() | ADCAN_AE_PT_6.build() | ADCAN_AE_PT_7.build() | ADCAN_AE_PT_8.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_5.unbuild(Val);
		ADCAN_AE_PT_6.unbuild(Val);
		ADCAN_AE_PT_7.unbuild(Val);
		ADCAN_AE_PT_8.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_3 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_3;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_9 = {0, 16, 0, 0, 0, 1.22255625, 79231.34};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_10 = {0, 16, 16, 0, 0, 1.218995625, 79008.05};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_11 = {0, 16, 32, 0, 0, 1.219085625, 78882.42};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_12 = {0, 16, 48, 0, 0, 1.218811875, 78981.31};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_3() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_9.countOfBits + ADCAN_AE_PT_10.countOfBits + ADCAN_AE_PT_11.countOfBits + ADCAN_AE_PT_12.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_9.build() | ADCAN_AE_PT_10.build() | ADCAN_AE_PT_11.build() | ADCAN_AE_PT_12.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_9.unbuild(Val);
		ADCAN_AE_PT_10.unbuild(Val);
		ADCAN_AE_PT_11.unbuild(Val);
		ADCAN_AE_PT_12.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_4 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_4;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_13 = {0, 16, 0, 0, 0, 1.2216825, 79297.82};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_14 = {0, 16, 16, 0, 0, 1.2240825, 79301.32};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_15 = {0, 16, 32, 0, 0, 1.222959375, 79278.19};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_16 = {0, 16, 48, 0, 0, 1.2230175, 79293.07};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_4() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_13.countOfBits + ADCAN_AE_PT_14.countOfBits + ADCAN_AE_PT_15.countOfBits + ADCAN_AE_PT_16.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_13.build() | ADCAN_AE_PT_14.build() | ADCAN_AE_PT_15.build() | ADCAN_AE_PT_16.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_13.unbuild(Val);
		ADCAN_AE_PT_14.unbuild(Val);
		ADCAN_AE_PT_15.unbuild(Val);
		ADCAN_AE_PT_16.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_5 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_5;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_17 = {0, 16, 0, 0, 0, 1.21944375, 78928.01};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_18 = {0, 16, 16, 0, 0, 1.21787625, 78991.36};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_19 = {0, 16, 32, 0, 0, 1.2150806250000001, 78824.23};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_20 = {0, 16, 48, 0, 0, 1.22155875, 79133.06};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_5() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_17.countOfBits + ADCAN_AE_PT_18.countOfBits + ADCAN_AE_PT_19.countOfBits + ADCAN_AE_PT_20.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_17.build() | ADCAN_AE_PT_18.build() | ADCAN_AE_PT_19.build() | ADCAN_AE_PT_20.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_17.unbuild(Val);
		ADCAN_AE_PT_18.unbuild(Val);
		ADCAN_AE_PT_19.unbuild(Val);
		ADCAN_AE_PT_20.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_6 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_6;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_21 = {0, 16, 0, 0, 0, 1.219734375, 79013.39};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_22 = {0, 16, 16, 0, 0, 1.2183487499999999, 79045.41};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_23 = {0, 16, 32, 0, 0, 1.218144375, 78890.84};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_24 = {0, 16, 48, 0, 0, 1.21910625, 79086.83};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_6() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_21.countOfBits + ADCAN_AE_PT_22.countOfBits + ADCAN_AE_PT_23.countOfBits + ADCAN_AE_PT_24.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_21.build() | ADCAN_AE_PT_22.build() | ADCAN_AE_PT_23.build() | ADCAN_AE_PT_24.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_21.unbuild(Val);
		ADCAN_AE_PT_22.unbuild(Val);
		ADCAN_AE_PT_23.unbuild(Val);
		ADCAN_AE_PT_24.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_7 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_7;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_25 = {0, 16, 0, 0, 0, 1.2219881250000002, 79238.64};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_26 = {0, 16, 16, 0, 0, 1.224099375, 79296.5};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_27 = {0, 16, 32, 0, 0, 1.22308875, 79292.73};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_28 = {0, 16, 48, 0, 0, 1.22105625, 79189.83};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_7() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_25.countOfBits + ADCAN_AE_PT_26.countOfBits + ADCAN_AE_PT_27.countOfBits + ADCAN_AE_PT_28.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_25.build() | ADCAN_AE_PT_26.build() | ADCAN_AE_PT_27.build() | ADCAN_AE_PT_28.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_25.unbuild(Val);
		ADCAN_AE_PT_26.unbuild(Val);
		ADCAN_AE_PT_27.unbuild(Val);
		ADCAN_AE_PT_28.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_8 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_8;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_29 = {0, 16, 0, 0, 0, 1.21801125, 78937.21};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_30 = {0, 16, 16, 0, 0, 1.2178556249999999, 78876.56};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_1 = {0, 16, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_2 = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_Aero_ADC_8() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_29.countOfBits + ADCAN_AE_PT_30.countOfBits + ADCAN_SP_Rocker_1.countOfBits + ADCAN_SP_Rocker_2.countOfBits;
		if(temp % 8 != 0) temp = temp / 8 + 1;
		else temp = temp / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_29.build() | ADCAN_AE_PT_30.build() | ADCAN_SP_Rocker_1.build() | ADCAN_SP_Rocker_2.build();
		ID = _id;
	}
	void unbuild()
	{
		ADCAN_AE_PT_29.unbuild(Val);
		ADCAN_AE_PT_30.unbuild(Val);
		ADCAN_SP_Rocker_1.unbuild(Val);
		ADCAN_SP_Rocker_2.unbuild(Val);
	}

};
struct STOS_CAN_PDU_Aero_ADC_9 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_Aero_ADC_9;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_PT_33 = {0, 16, 0, 0, 0, 0.32608875000000004, -834.4};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_34 = {0, 16, 16, 0, 0, 0.32646562500000004, -831.88};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_AE_PT_35 = {0, 16, 32, 0, 0, 0.326529375, -792.27};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_3 = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	void unbuild()
	{
		ADCAN_AE_PT_33.unbuild(Val);
		ADCAN_AE_PT_34.unbuild(Val);
		ADCAN_AE_PT_35.unbuild(Val);
		ADCAN_SP_Rocker_3.unbuild(Val);
	}
	STOS_CAN_PDU_Aero_ADC_9() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_PT_33.countOfBits + ADCAN_AE_PT_34.countOfBits + ADCAN_AE_PT_35.countOfBits + ADCAN_SP_Rocker_3.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_PT_33.build() | ADCAN_AE_PT_34.build() | ADCAN_AE_PT_35.build() | ADCAN_SP_Rocker_3.build();
		ID = _id;
	}
;
}; 

#endif