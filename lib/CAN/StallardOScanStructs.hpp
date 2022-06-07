#ifndef StallardOScanStructs_hpp
#define StallardOScanStructs_hpp
#include "stdint.h"
#include "StallardOScanTypes.hpp"
#include <math.h>
#include "StallardOScanIDs.h"
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= activate_blip.build();
		temp_dlc += activate_blip.countOfBits;
		Val |= activate_cut.build();
		temp_dlc += activate_cut.countOfBits;
		Val |= blip_state.build();
		temp_dlc += blip_state.countOfBits;
		Val |= cut_level_gcu.build();
		temp_dlc += cut_level_gcu.countOfBits;
		Val |= engaged_gear.build();
		temp_dlc += engaged_gear.countOfBits;
		Val |= gearpot.build();
		temp_dlc += gearpot.countOfBits;
		Val |= shift_state.build();
		temp_dlc += shift_state.countOfBits;
		Val |= state_cut.build();
		temp_dlc += state_cut.countOfBits;
		Val |= target_engine_speed.build();
		temp_dlc += target_engine_speed.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= speedABSfl.build();
		temp_dlc += speedABSfl.countOfBits;
		Val |= speedABSfr.build();
		temp_dlc += speedABSfr.countOfBits;
		Val |= speedABSrl.build();
		temp_dlc += speedABSrl.countOfBits;
		Val |= speedABSrr.build();
		temp_dlc += speedABSrr.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ax1_Bremse60ABS.build();
		temp_dlc += ax1_Bremse60ABS.countOfBits;
		Val |= ay1_Bremse60ABS.build();
		temp_dlc += ay1_Bremse60ABS.countOfBits;
		Val |= blsABS.build();
		temp_dlc += blsABS.countOfBits;
		Val |= p_HzABS.build();
		temp_dlc += p_HzABS.countOfBits;
		Val |= switchstateABS.build();
		temp_dlc += switchstateABS.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ti_1.build();
		temp_dlc += ti_1.countOfBits;
		Val |= ti_2.build();
		temp_dlc += ti_2.countOfBits;
		Val |= ti_3.build();
		temp_dlc += ti_3.countOfBits;
		Val |= ti_4.build();
		temp_dlc += ti_4.countOfBits;
		Val |= ti_5.build();
		temp_dlc += ti_5.countOfBits;
		Val |= ti_6.build();
		temp_dlc += ti_6.countOfBits;
		Val |= ti_7.build();
		temp_dlc += ti_7.countOfBits;
		Val |= ti_8.build();
		temp_dlc += ti_8.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= injang.build();
		temp_dlc += injang.countOfBits;
		Val |= injoff.build();
		temp_dlc += injoff.countOfBits;
		Val |= lamctrl_2k.build();
		temp_dlc += lamctrl_2k.countOfBits;
		Val |= lamctrl_k.build();
		temp_dlc += lamctrl_k.countOfBits;
		Val |= tibase.build();
		temp_dlc += tibase.countOfBits;
		Val |= tibatt_o.build();
		temp_dlc += tibatt_o.countOfBits;
		Val |= timap.build();
		temp_dlc += timap.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ign_1.build();
		temp_dlc += ign_1.countOfBits;
		Val |= ign_2.build();
		temp_dlc += ign_2.countOfBits;
		Val |= ign_3.build();
		temp_dlc += ign_3.countOfBits;
		Val |= ign_4.build();
		temp_dlc += ign_4.countOfBits;
		Val |= ign_5.build();
		temp_dlc += ign_5.countOfBits;
		Val |= ign_6.build();
		temp_dlc += ign_6.countOfBits;
		Val |= ign_7.build();
		temp_dlc += ign_7.countOfBits;
		Val |= ign_8.build();
		temp_dlc += ign_8.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ath.build();
		temp_dlc += ath.countOfBits;
		Val |= dath.build();
		temp_dlc += dath.countOfBits;
		Val |= ignbase.build();
		temp_dlc += ignbase.countOfBits;
		Val |= ignmap.build();
		temp_dlc += ignmap.countOfBits;
		Val |= rev.build();
		temp_dlc += rev.countOfBits;
		Val |= tdwell.build();
		temp_dlc += tdwell.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= lam.build();
		temp_dlc += lam.countOfBits;
		Val |= lam_2.build();
		temp_dlc += lam_2.countOfBits;
		Val |= lami.build();
		temp_dlc += lami.countOfBits;
		Val |= lami_2.build();
		temp_dlc += lami_2.countOfBits;
		Val |= lammap.build();
		temp_dlc += lammap.countOfBits;
		Val |= lammap_2.build();
		temp_dlc += lammap_2.countOfBits;
		Val |= lamp.build();
		temp_dlc += lamp.countOfBits;
		Val |= lamp_2.build();
		temp_dlc += lamp_2.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= speed.build();
		temp_dlc += speed.countOfBits;
		Val |= speedfl.build();
		temp_dlc += speedfl.countOfBits;
		Val |= speedfr.build();
		temp_dlc += speedfr.countOfBits;
		Val |= speedrl.build();
		temp_dlc += speedrl.countOfBits;
		Val |= speedrr.build();
		temp_dlc += speedrr.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= lapdist.build();
		temp_dlc += lapdist.countOfBits;
		Val |= laptime.build();
		temp_dlc += laptime.countOfBits;
		Val |= laptimediff.build();
		temp_dlc += laptimediff.countOfBits;
		Val |= laptimefast.build();
		temp_dlc += laptimefast.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= accx.build();
		temp_dlc += accx.countOfBits;
		Val |= accy.build();
		temp_dlc += accy.countOfBits;
		Val |= accz.build();
		temp_dlc += accz.countOfBits;
		Val |= ddugear.build();
		temp_dlc += ddugear.countOfBits;
		Val |= gcstate.build();
		temp_dlc += gcstate.countOfBits;
		Val |= gear.build();
		temp_dlc += gear.countOfBits;
		Val |= gearcut_u.build();
		temp_dlc += gearcut_u.countOfBits;
		Val |= gearratio.build();
		temp_dlc += gearratio.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= slipsp.build();
		temp_dlc += slipsp.countOfBits;
		Val |= slra.build();
		temp_dlc += slra.countOfBits;
		Val |= tcpfac.build();
		temp_dlc += tcpfac.countOfBits;
		Val |= tcsw.build();
		temp_dlc += tcsw.countOfBits;
		Val |= vdraxle.build();
		temp_dlc += vdraxle.countOfBits;
		Val |= vref.build();
		temp_dlc += vref.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= aps.build();
		temp_dlc += aps.countOfBits;
		Val |= batt_u.build();
		temp_dlc += batt_u.countOfBits;
		Val |= camshaftpos.build();
		temp_dlc += camshaftpos.countOfBits;
		Val |= etb.build();
		temp_dlc += etb.countOfBits;
		Val |= etb_sp.build();
		temp_dlc += etb_sp.countOfBits;
		Val |= lap_c.build();
		temp_dlc += lap_c.countOfBits;
		Val |= p1.build();
		temp_dlc += p1.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		if(rowcounter_0x77A.physValue == battlow_b.rowcount)
		{
			Val |= battlow_b.build();
			temp_dlc += battlow_b.countOfBits;
		}
		Val |= etbsys_e.build();
		temp_dlc += etbsys_e.countOfBits;
		if(rowcounter_0x77A.physValue == fuellap.rowcount)
		{
			Val |= fuellap.build();
			temp_dlc += fuellap.countOfBits;
		}
		if(rowcounter_0x77A.physValue == fueltank.rowcount)
		{
			Val |= fueltank.build();
			temp_dlc += fueltank.countOfBits;
		}
		Val |= gearcut_b.build();
		temp_dlc += gearcut_b.countOfBits;
		Val |= idle_b.build();
		temp_dlc += idle_b.countOfBits;
		Val |= ignoff_b.build();
		temp_dlc += ignoff_b.countOfBits;
		Val |= injcut_b.build();
		temp_dlc += injcut_b.countOfBits;
		Val |= injcutin_b.build();
		temp_dlc += injcutin_b.countOfBits;
		Val |= injenrich_b.build();
		temp_dlc += injenrich_b.countOfBits;
		Val |= injstartphase_b.build();
		temp_dlc += injstartphase_b.countOfBits;
		Val |= knockadaptenable_b.build();
		temp_dlc += knockadaptenable_b.countOfBits;
		Val |= knockenable_b.build();
		temp_dlc += knockenable_b.countOfBits;
		Val |= lamctrl_2b.build();
		temp_dlc += lamctrl_2b.countOfBits;
		Val |= lamctrl_b.build();
		temp_dlc += lamctrl_b.countOfBits;
		Val |= lap_b.build();
		temp_dlc += lap_b.countOfBits;
		Val |= laptrig_b.build();
		temp_dlc += laptrig_b.countOfBits;
		if(rowcounter_0x77A.physValue == mappos.rowcount)
		{
			Val |= mappos.build();
			temp_dlc += mappos.countOfBits;
		}
		Val |= mil_b.build();
		temp_dlc += mil_b.countOfBits;
		Val |= oillamp_b.build();
		temp_dlc += oillamp_b.countOfBits;
		if(rowcounter_0x77A.physValue == pamb.rowcount)
		{
			Val |= pamb.build();
			temp_dlc += pamb.countOfBits;
		}
		if(rowcounter_0x77A.physValue == pcrank.rowcount)
		{
			Val |= pcrank.build();
			temp_dlc += pcrank.countOfBits;
		}
		if(rowcounter_0x77A.physValue == pfuel.rowcount)
		{
			Val |= pfuel.build();
			temp_dlc += pfuel.countOfBits;
		}
		Val |= phsok_b.build();
		temp_dlc += phsok_b.countOfBits;
		Val |= phsokset_b.build();
		temp_dlc += phsokset_b.countOfBits;
		if(rowcounter_0x77A.physValue == poil.rowcount)
		{
			Val |= poil.build();
			temp_dlc += poil.countOfBits;
		}
		if(rowcounter_0x77A.physValue == pwat.rowcount)
		{
			Val |= pwat.build();
			temp_dlc += pwat.countOfBits;
		}
		Val |= rev_b.build();
		temp_dlc += rev_b.countOfBits;
		Val |= revlimit_b.build();
		temp_dlc += revlimit_b.countOfBits;
		Val |= rowcounter_0x77A.build();
		temp_dlc += rowcounter_0x77A.countOfBits;
		if(rowcounter_0x77A.physValue == shled1_b.rowcount)
		{
			Val |= shled1_b.build();
			temp_dlc += shled1_b.countOfBits;
		}
		if(rowcounter_0x77A.physValue == shled2_b.rowcount)
		{
			Val |= shled2_b.build();
			temp_dlc += shled2_b.countOfBits;
		}
		if(rowcounter_0x77A.physValue == shled3_b.rowcount)
		{
			Val |= shled3_b.build();
			temp_dlc += shled3_b.countOfBits;
		}
		if(rowcounter_0x77A.physValue == shled4_b.rowcount)
		{
			Val |= shled4_b.build();
			temp_dlc += shled4_b.countOfBits;
		}
		if(rowcounter_0x77A.physValue == shled5_b.rowcount)
		{
			Val |= shled5_b.build();
			temp_dlc += shled5_b.countOfBits;
		}
		Val |= speedlimit_b.build();
		temp_dlc += speedlimit_b.countOfBits;
		Val |= speedlimitreq_b.build();
		temp_dlc += speedlimitreq_b.countOfBits;
		Val |= startend_b.build();
		temp_dlc += startend_b.countOfBits;
		if(rowcounter_0x77A.physValue == tair.rowcount)
		{
			Val |= tair.build();
			temp_dlc += tair.countOfBits;
		}
		Val |= tc_b.build();
		temp_dlc += tc_b.countOfBits;
		if(rowcounter_0x77A.physValue == tex.rowcount)
		{
			Val |= tex.build();
			temp_dlc += tex.countOfBits;
		}
		if(rowcounter_0x77A.physValue == tex_2.rowcount)
		{
			Val |= tex_2.build();
			temp_dlc += tex_2.countOfBits;
		}
		if(rowcounter_0x77A.physValue == tfuel.rowcount)
		{
			Val |= tfuel.build();
			temp_dlc += tfuel.countOfBits;
		}
		if(rowcounter_0x77A.physValue == tlam.rowcount)
		{
			Val |= tlam.build();
			temp_dlc += tlam.countOfBits;
		}
		if(rowcounter_0x77A.physValue == tlam_2.rowcount)
		{
			Val |= tlam_2.build();
			temp_dlc += tlam_2.countOfBits;
		}
		if(rowcounter_0x77A.physValue == tmot.rowcount)
		{
			Val |= tmot.build();
			temp_dlc += tmot.countOfBits;
		}
		if(rowcounter_0x77A.physValue == toil.rowcount)
		{
			Val |= toil.build();
			temp_dlc += toil.countOfBits;
		}
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= p22_2m_pwg_m.build();
		temp_dlc += p22_2m_pwg_m.countOfBits;
		Val |= p22_m.build();
		temp_dlc += p22_m.countOfBits;
		Val |= p22_sp.build();
		temp_dlc += p22_sp.countOfBits;
		Val |= pwg_sp.build();
		temp_dlc += pwg_sp.countOfBits;
		Val |= wgdc_2_wgdchold.build();
		temp_dlc += wgdc_2_wgdchold.countOfBits;
		Val |= wgdc_wgdcvent.build();
		temp_dlc += wgdc_wgdcvent.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Accel_1_X.build();
		temp_dlc += ADCAN_SP_Accel_1_X.countOfBits;
		Val |= ADCAN_SP_Accel_1_Y.build();
		temp_dlc += ADCAN_SP_Accel_1_Y.countOfBits;
		Val |= ADCAN_SP_Accel_1_Z.build();
		temp_dlc += ADCAN_SP_Accel_1_Z.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Accel_2_X.build();
		temp_dlc += ADCAN_SP_Accel_2_X.countOfBits;
		Val |= ADCAN_SP_Accel_2_Y.build();
		temp_dlc += ADCAN_SP_Accel_2_Y.countOfBits;
		Val |= ADCAN_SP_Accel_2_Z.build();
		temp_dlc += ADCAN_SP_Accel_2_Z.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_Fan_L_PWM.build();
		temp_dlc += ADCAN_AE_Fan_L_PWM.countOfBits;
		Val |= ADCAN_AE_Fan_R_PWM.build();
		temp_dlc += ADCAN_AE_Fan_R_PWM.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_Fan_Telemetry_1.build();
		temp_dlc += ADCAN_AE_Fan_Telemetry_1.countOfBits;
		Val |= ADCAN_AE_Fan_Telemetry_2.build();
		temp_dlc += ADCAN_AE_Fan_Telemetry_2.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_Warnings.build();
		temp_dlc += ADCAN_AE_Warnings.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_PT_Airbox_Pos.build();
		temp_dlc += ADCAN_PT_Airbox_Pos.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_ARH_1_Homing.build();
		temp_dlc += ADCAN_SP_ARH_1_Homing.countOfBits;
		Val |= ADCAN_SP_ARH_2_Homing.build();
		temp_dlc += ADCAN_SP_ARH_2_Homing.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_ARH_1_PWM.build();
		temp_dlc += ADCAN_SP_ARH_1_PWM.countOfBits;
		Val |= ADCAN_SP_ARH_2_PWM.build();
		temp_dlc += ADCAN_SP_ARH_2_PWM.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_Battery_48V_Temp_1.build();
		temp_dlc += ADCAN_EL_Battery_48V_Temp_1.countOfBits;
		Val |= ADCAN_EL_Battery_48V_Temp_2.build();
		temp_dlc += ADCAN_EL_Battery_48V_Temp_2.countOfBits;
		Val |= ADCAN_EL_Battery_48V_Temp_3.build();
		temp_dlc += ADCAN_EL_Battery_48V_Temp_3.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Brake_Disc_Temp_FL.build();
		temp_dlc += ADCAN_SP_Brake_Disc_Temp_FL.countOfBits;
		Val |= ADCAN_SP_Brake_Disc_Temp_FR.build();
		temp_dlc += ADCAN_SP_Brake_Disc_Temp_FR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Brake_Disc_Temp_RL.build();
		temp_dlc += ADCAN_SP_Brake_Disc_Temp_RL.countOfBits;
		Val |= ADCAN_SP_Brake_Disc_Temp_RR.build();
		temp_dlc += ADCAN_SP_Brake_Disc_Temp_RR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Brake_Pressure_Front.build();
		temp_dlc += ADCAN_SP_Brake_Pressure_Front.countOfBits;
		Val |= ADCAN_SP_Brake_Pressure_Rear.build();
		temp_dlc += ADCAN_SP_Brake_Pressure_Rear.countOfBits;
		Val |= ADCAN_SP_Brake_Bias.build();
		temp_dlc += ADCAN_SP_Brake_Bias.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_Current_Sensor_1.build();
		temp_dlc += ADCAN_EL_Current_Sensor_1.countOfBits;
		Val |= ADCAN_EL_Current_Sensor_2.build();
		temp_dlc += ADCAN_EL_Current_Sensor_2.countOfBits;
		Val |= ADCAN_EL_Current_Sensor_3.build();
		temp_dlc += ADCAN_EL_Current_Sensor_3.countOfBits;
		Val |= ADCAN_EL_Current_Sensor_4.build();
		temp_dlc += ADCAN_EL_Current_Sensor_4.countOfBits;
		Val |= ADCAN_EL_Current_Sensor_5.build();
		temp_dlc += ADCAN_EL_Current_Sensor_5.countOfBits;
		Val |= ADCAN_EL_Current_Sensor_6.build();
		temp_dlc += ADCAN_EL_Current_Sensor_6.countOfBits;
		Val |= ADCAN_EL_Current_Sensor_7.build();
		temp_dlc += ADCAN_EL_Current_Sensor_7.countOfBits;
		Val |= ADCAN_EL_Current_Sensor_8.build();
		temp_dlc += ADCAN_EL_Current_Sensor_8.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_Battery_24V_Temp.build();
		temp_dlc += ADCAN_EL_Battery_24V_Temp.countOfBits;
		Val |= ADCAN_EL_ECU_Temp_FCU_1.build();
		temp_dlc += ADCAN_EL_ECU_Temp_FCU_1.countOfBits;
		Val |= ADCAN_EL_ECU_Temp_FCU_2.build();
		temp_dlc += ADCAN_EL_ECU_Temp_FCU_2.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_ARB_Switch.build();
		temp_dlc += ADCAN_SP_ARB_Switch.countOfBits;
		Val |= ADCAN_SP_LaunchC_Activated.build();
		temp_dlc += ADCAN_SP_LaunchC_Activated.countOfBits;
		Val |= ADCAN_SP_LaunchC_Switch.build();
		temp_dlc += ADCAN_SP_LaunchC_Switch.countOfBits;
		Val |= ADCAN_SP_RAS_Switch.build();
		temp_dlc += ADCAN_SP_RAS_Switch.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_FDS_Friction_LC.build();
		temp_dlc += ADCAN_SP_FDS_Friction_LC.countOfBits;
		Val |= ADCAN_SP_FDS_Slip_mue_max.build();
		temp_dlc += ADCAN_SP_FDS_Slip_mue_max.countOfBits;
		Val |= ADCAN_SP_FDS_Swim_VDE.build();
		temp_dlc += ADCAN_SP_FDS_Swim_VDE.countOfBits;
		Val |= ADCAN_SP_FDS_Velo_VDE.build();
		temp_dlc += ADCAN_SP_FDS_Velo_VDE.countOfBits;
		Val |= ADCAN_SP_FDS_Wheel_Slip_RL.build();
		temp_dlc += ADCAN_SP_FDS_Wheel_Slip_RL.countOfBits;
		Val |= ADCAN_SP_FDS_Wheel_Slip_RR.build();
		temp_dlc += ADCAN_SP_FDS_Wheel_Slip_RR.countOfBits;
		Val |= ADCAN_SP_FDS_Yaw_VDE.build();
		temp_dlc += ADCAN_SP_FDS_Yaw_VDE.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_FDS_Slip_Angle_FL.build();
		temp_dlc += ADCAN_SP_FDS_Slip_Angle_FL.countOfBits;
		Val |= ADCAN_SP_FDS_Slip_Angle_FR.build();
		temp_dlc += ADCAN_SP_FDS_Slip_Angle_FR.countOfBits;
		Val |= ADCAN_SP_FDS_Slip_Angle_RL.build();
		temp_dlc += ADCAN_SP_FDS_Slip_Angle_RL.countOfBits;
		Val |= ADCAN_SP_FDS_Slip_Angle_RR.build();
		temp_dlc += ADCAN_SP_FDS_Slip_Angle_RR.countOfBits;
		Val |= ADCAN_SP_FDS_Whl_Load_FL.build();
		temp_dlc += ADCAN_SP_FDS_Whl_Load_FL.countOfBits;
		Val |= ADCAN_SP_FDS_Whl_Load_FR.build();
		temp_dlc += ADCAN_SP_FDS_Whl_Load_FR.countOfBits;
		Val |= ADCAN_SP_FDS_Whl_Load_RL.build();
		temp_dlc += ADCAN_SP_FDS_Whl_Load_RL.countOfBits;
		Val |= ADCAN_SP_FDS_Whl_Load_RR.build();
		temp_dlc += ADCAN_SP_FDS_Whl_Load_RR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_FoC_1.build();
		temp_dlc += ADCAN_EL_FoC_1.countOfBits;
		Val |= ADCAN_EL_FoC_2.build();
		temp_dlc += ADCAN_EL_FoC_2.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_CH_Frame_Pressure.build();
		temp_dlc += ADCAN_CH_Frame_Pressure.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Gyro_1_X.build();
		temp_dlc += ADCAN_SP_Gyro_1_X.countOfBits;
		Val |= ADCAN_SP_Gyro_1_Y.build();
		temp_dlc += ADCAN_SP_Gyro_1_Y.countOfBits;
		Val |= ADCAN_SP_Gyro_1_Z.build();
		temp_dlc += ADCAN_SP_Gyro_1_Z.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Gyro_2_X.build();
		temp_dlc += ADCAN_SP_Gyro_2_X.countOfBits;
		Val |= ADCAN_SP_Gyro_2_Y.build();
		temp_dlc += ADCAN_SP_Gyro_2_Y.countOfBits;
		Val |= ADCAN_SP_Gyro_2_Z.build();
		temp_dlc += ADCAN_SP_Gyro_2_Z.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Niveau_FL_Niveau.build();
		temp_dlc += ADCAN_SP_Niveau_FL_Niveau.countOfBits;
		Val |= ADCAN_SP_Niveau_FR_Niveau.build();
		temp_dlc += ADCAN_SP_Niveau_FR_Niveau.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Niveau_FL_Error.build();
		temp_dlc += ADCAN_SP_Niveau_FL_Error.countOfBits;
		Val |= ADCAN_SP_Niveau_FL_Function.build();
		temp_dlc += ADCAN_SP_Niveau_FL_Function.countOfBits;
		Val |= ADCAN_SP_Niveau_FL_on_off.build();
		temp_dlc += ADCAN_SP_Niveau_FL_on_off.countOfBits;
		Val |= ADCAN_SP_Niveau_FR_Error.build();
		temp_dlc += ADCAN_SP_Niveau_FR_Error.countOfBits;
		Val |= ADCAN_SP_Niveau_FR_Function.build();
		temp_dlc += ADCAN_SP_Niveau_FR_Function.countOfBits;
		Val |= ADCAN_SP_Niveau_FR_on_off.build();
		temp_dlc += ADCAN_SP_Niveau_FR_on_off.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Niveau_R_Niveau.build();
		temp_dlc += ADCAN_SP_Niveau_R_Niveau.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Niveau_R_Error.build();
		temp_dlc += ADCAN_SP_Niveau_R_Error.countOfBits;
		Val |= ADCAN_SP_Niveau_R_Function.build();
		temp_dlc += ADCAN_SP_Niveau_R_Function.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_PT_Oil_Pressure.build();
		temp_dlc += ADCAN_PT_Oil_Pressure.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_PT_Oil_Level.build();
		temp_dlc += ADCAN_PT_Oil_Level.countOfBits;
		Val |= ADCAN_PT_Oil_Level_RS232.build();
		temp_dlc += ADCAN_PT_Oil_Level_RS232.countOfBits;
		Val |= ADCAN_PT_Oil_Temp.build();
		temp_dlc += ADCAN_PT_Oil_Temp.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_ECU_Temp_PDU_1.build();
		temp_dlc += ADCAN_EL_ECU_Temp_PDU_1.countOfBits;
		Val |= ADCAN_EL_ECU_Temp_PDU_2.build();
		temp_dlc += ADCAN_EL_ECU_Temp_PDU_2.countOfBits;
		Val |= ADCAN_EL_ECU_Temp_PDU_3.build();
		temp_dlc += ADCAN_EL_ECU_Temp_PDU_3.countOfBits;
		Val |= ADCAN_EL_ECU_Temp_PDU_4.build();
		temp_dlc += ADCAN_EL_ECU_Temp_PDU_4.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_CH_Mainhoop_Diag_L_1.build();
		temp_dlc += ADCAN_CH_Mainhoop_Diag_L_1.countOfBits;
		Val |= ADCAN_CH_Mainhoop_Diag_R_1.build();
		temp_dlc += ADCAN_CH_Mainhoop_Diag_R_1.countOfBits;
		Val |= ADCAN_EL_BOTS_Diag_1.build();
		temp_dlc += ADCAN_EL_BOTS_Diag_1.countOfBits;
		Val |= ADCAN_EL_BSPD_Shutdown_Out.build();
		temp_dlc += ADCAN_EL_BSPD_Shutdown_Out.countOfBits;
		Val |= ADCAN_EL_Cockpit_Diag_1.build();
		temp_dlc += ADCAN_EL_Cockpit_Diag_1.countOfBits;
		Val |= ADCAN_EL_Crash_Diag.build();
		temp_dlc += ADCAN_EL_Crash_Diag.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_1.build();
		temp_dlc += ADCAN_EL_Fuse_Status_1.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_10.build();
		temp_dlc += ADCAN_EL_Fuse_Status_10.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_11.build();
		temp_dlc += ADCAN_EL_Fuse_Status_11.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_12.build();
		temp_dlc += ADCAN_EL_Fuse_Status_12.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_13.build();
		temp_dlc += ADCAN_EL_Fuse_Status_13.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_14.build();
		temp_dlc += ADCAN_EL_Fuse_Status_14.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_15.build();
		temp_dlc += ADCAN_EL_Fuse_Status_15.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_16.build();
		temp_dlc += ADCAN_EL_Fuse_Status_16.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_17.build();
		temp_dlc += ADCAN_EL_Fuse_Status_17.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_18.build();
		temp_dlc += ADCAN_EL_Fuse_Status_18.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_19.build();
		temp_dlc += ADCAN_EL_Fuse_Status_19.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_2.build();
		temp_dlc += ADCAN_EL_Fuse_Status_2.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_3.build();
		temp_dlc += ADCAN_EL_Fuse_Status_3.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_4.build();
		temp_dlc += ADCAN_EL_Fuse_Status_4.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_5.build();
		temp_dlc += ADCAN_EL_Fuse_Status_5.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_6.build();
		temp_dlc += ADCAN_EL_Fuse_Status_6.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_7.build();
		temp_dlc += ADCAN_EL_Fuse_Status_7.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_8.build();
		temp_dlc += ADCAN_EL_Fuse_Status_8.countOfBits;
		Val |= ADCAN_EL_Fuse_Status_9.build();
		temp_dlc += ADCAN_EL_Fuse_Status_9.countOfBits;
		Val |= ADCAN_EL_Relais_Status_1.build();
		temp_dlc += ADCAN_EL_Relais_Status_1.countOfBits;
		Val |= ADCAN_EL_Relais_Status_2.build();
		temp_dlc += ADCAN_EL_Relais_Status_2.countOfBits;
		Val |= ADCAN_EL_Shutdown_Cockpit.build();
		temp_dlc += ADCAN_EL_Shutdown_Cockpit.countOfBits;
		Val |= ADCAN_PT_Fuel_Pump_Signal.build();
		temp_dlc += ADCAN_PT_Fuel_Pump_Signal.countOfBits;
		Val |= ADCAN_PT_Reserve_Signal_L.build();
		temp_dlc += ADCAN_PT_Reserve_Signal_L.countOfBits;
		Val |= ADCAN_PT_Reserve_Signal_R.build();
		temp_dlc += ADCAN_PT_Reserve_Signal_R.countOfBits;
		Val |= ADCAN_PT_Water_Pump_Signal.build();
		temp_dlc += ADCAN_PT_Water_Pump_Signal.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_Pitot_1.build();
		temp_dlc += ADCAN_AE_Pitot_1.countOfBits;
		Val |= ADCAN_AE_Pitot_2.build();
		temp_dlc += ADCAN_AE_Pitot_2.countOfBits;
		Val |= ADCAN_AE_Pitot_3.build();
		temp_dlc += ADCAN_AE_Pitot_3.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_RAS_PWM_L.build();
		temp_dlc += ADCAN_SP_RAS_PWM_L.countOfBits;
		Val |= ADCAN_SP_RAS_PWM_R.build();
		temp_dlc += ADCAN_SP_RAS_PWM_R.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_RAS_Angle.build();
		temp_dlc += ADCAN_SP_RAS_Angle.countOfBits;
		Val |= ADCAN_SP_RAS_Homing_L.build();
		temp_dlc += ADCAN_SP_RAS_Homing_L.countOfBits;
		Val |= ADCAN_SP_RAS_Homing_R.build();
		temp_dlc += ADCAN_SP_RAS_Homing_R.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_ECU_Temp_RCU_1.build();
		temp_dlc += ADCAN_EL_ECU_Temp_RCU_1.countOfBits;
		Val |= ADCAN_EL_ECU_Temp_RCU_2.build();
		temp_dlc += ADCAN_EL_ECU_Temp_RCU_2.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_ZZ_Test_RCU_1.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_1.countOfBits;
		Val |= ADCAN_ZZ_Test_RCU_2.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_2.countOfBits;
		Val |= ADCAN_ZZ_Test_RCU_3.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_3.countOfBits;
		Val |= ADCAN_ZZ_Test_RCU_4.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_4.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_ZZ_Test_RCU_5.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_5.countOfBits;
		Val |= ADCAN_ZZ_Test_RCU_6.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_6.countOfBits;
		Val |= ADCAN_ZZ_Test_RCU_7.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_7.countOfBits;
		Val |= ADCAN_ZZ_Test_RCU_8.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_8.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_ZZ_Test_RCU_10.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_10.countOfBits;
		Val |= ADCAN_ZZ_Test_RCU_9.build();
		temp_dlc += ADCAN_ZZ_Test_RCU_9.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Rocker_FL.build();
		temp_dlc += ADCAN_SP_Rocker_FL.countOfBits;
		Val |= ADCAN_SP_Rocker_FR.build();
		temp_dlc += ADCAN_SP_Rocker_FR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Rocker_RL.build();
		temp_dlc += ADCAN_SP_Rocker_RL.countOfBits;
		Val |= ADCAN_SP_Rocker_RR.build();
		temp_dlc += ADCAN_SP_Rocker_RR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_PT_Gearshift_DigIn.build();
		temp_dlc += ADCAN_PT_Gearshift_DigIn.countOfBits;
		Val |= ADCAN_PT_Gearshift_LaunchC.build();
		temp_dlc += ADCAN_PT_Gearshift_LaunchC.countOfBits;
		Val |= ADCAN_PT_Shift_Force_Sensor.build();
		temp_dlc += ADCAN_PT_Shift_Force_Sensor.countOfBits;
		Val |= ADCAN_SP_Clutch_DigIn.build();
		temp_dlc += ADCAN_SP_Clutch_DigIn.countOfBits;
		Val |= ADCAN_SP_Clutch_LaunchC.build();
		temp_dlc += ADCAN_SP_Clutch_LaunchC.countOfBits;
		Val |= ADCAN_PT_Shift_Force_on_off.build();
		temp_dlc += ADCAN_PT_Shift_Force_on_off.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Steering_Wheel_Angle.build();
		temp_dlc += ADCAN_SP_Steering_Wheel_Angle.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_ECU_Temp_SWCU.build();
		temp_dlc += ADCAN_EL_ECU_Temp_SWCU.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_EL_INCR_1.build();
		temp_dlc += ADCAN_EL_INCR_1.countOfBits;
		Val |= ADCAN_EL_INCR_2.build();
		temp_dlc += ADCAN_EL_INCR_2.countOfBits;
		Val |= ADCAN_EL_Oh_Shit.build();
		temp_dlc += ADCAN_EL_Oh_Shit.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_Switch_1.build();
		temp_dlc += ADCAN_AE_Switch_1.countOfBits;
		Val |= ADCAN_EL_Radio_Switch.build();
		temp_dlc += ADCAN_EL_Radio_Switch.countOfBits;
		Val |= ADCAN_PT_Shift_Down.build();
		temp_dlc += ADCAN_PT_Shift_Down.countOfBits;
		Val |= ADCAN_PT_Shift_Up.build();
		temp_dlc += ADCAN_PT_Shift_Up.countOfBits;
		Val |= ADCAN_SP_ARH_switch_1.build();
		temp_dlc += ADCAN_SP_ARH_switch_1.countOfBits;
		Val |= ADCAN_SP_Clutch_Signal.build();
		temp_dlc += ADCAN_SP_Clutch_Signal.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_ZZ_Test_FCU_1.build();
		temp_dlc += ADCAN_ZZ_Test_FCU_1.countOfBits;
		Val |= ADCAN_ZZ_Test_FCU_2.build();
		temp_dlc += ADCAN_ZZ_Test_FCU_2.countOfBits;
		Val |= ADCAN_ZZ_Test_FCU_3.build();
		temp_dlc += ADCAN_ZZ_Test_FCU_3.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_ZZ_Test_FCU_4.build();
		temp_dlc += ADCAN_ZZ_Test_FCU_4.countOfBits;
		Val |= ADCAN_ZZ_Test_FCU_5.build();
		temp_dlc += ADCAN_ZZ_Test_FCU_5.countOfBits;
		Val |= ADCAN_ZZ_Test_FCU_6.build();
		temp_dlc += ADCAN_ZZ_Test_FCU_6.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_PT_Oil_Fan_Percent.build();
		temp_dlc += ADCAN_PT_Oil_Fan_Percent.countOfBits;
		Val |= ADCAN_PT_Oil_PWM.build();
		temp_dlc += ADCAN_PT_Oil_PWM.countOfBits;
		Val |= ADCAN_PT_Water_1_PWM.build();
		temp_dlc += ADCAN_PT_Water_1_PWM.countOfBits;
		Val |= ADCAN_PT_Water_2_PWM.build();
		temp_dlc += ADCAN_PT_Water_2_PWM.countOfBits;
		Val |= ADCAN_PT_Water_Fan_1_Percent.build();
		temp_dlc += ADCAN_PT_Water_Fan_1_Percent.countOfBits;
		Val |= ADCAN_PT_Water_Fan_2_Percent.build();
		temp_dlc += ADCAN_PT_Water_Fan_2_Percent.countOfBits;
		Val |= ADCAN_PT_Water_Pump_Percent.build();
		temp_dlc += ADCAN_PT_Water_Pump_Percent.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Wheel_Speed_FL.build();
		temp_dlc += ADCAN_SP_Wheel_Speed_FL.countOfBits;
		Val |= ADCAN_SP_Wheel_Speed_FR.build();
		temp_dlc += ADCAN_SP_Wheel_Speed_FR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Wheel_Speed_RL.build();
		temp_dlc += ADCAN_SP_Wheel_Speed_RL.countOfBits;
		Val |= ADCAN_SP_Wheel_Speed_RR.build();
		temp_dlc += ADCAN_SP_Wheel_Speed_RR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_1.build();
		temp_dlc += ADCAN_AE_PT_1.countOfBits;
		Val |= ADCAN_AE_PT_2.build();
		temp_dlc += ADCAN_AE_PT_2.countOfBits;
		Val |= ADCAN_AE_PT_3.build();
		temp_dlc += ADCAN_AE_PT_3.countOfBits;
		Val |= ADCAN_AE_PT_4.build();
		temp_dlc += ADCAN_AE_PT_4.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_5.build();
		temp_dlc += ADCAN_AE_PT_5.countOfBits;
		Val |= ADCAN_AE_PT_6.build();
		temp_dlc += ADCAN_AE_PT_6.countOfBits;
		Val |= ADCAN_AE_PT_7.build();
		temp_dlc += ADCAN_AE_PT_7.countOfBits;
		Val |= ADCAN_AE_PT_8.build();
		temp_dlc += ADCAN_AE_PT_8.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_9.build();
		temp_dlc += ADCAN_AE_PT_9.countOfBits;
		Val |= ADCAN_AE_PT_10.build();
		temp_dlc += ADCAN_AE_PT_10.countOfBits;
		Val |= ADCAN_AE_PT_11.build();
		temp_dlc += ADCAN_AE_PT_11.countOfBits;
		Val |= ADCAN_AE_PT_12.build();
		temp_dlc += ADCAN_AE_PT_12.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_13.build();
		temp_dlc += ADCAN_AE_PT_13.countOfBits;
		Val |= ADCAN_AE_PT_14.build();
		temp_dlc += ADCAN_AE_PT_14.countOfBits;
		Val |= ADCAN_AE_PT_15.build();
		temp_dlc += ADCAN_AE_PT_15.countOfBits;
		Val |= ADCAN_AE_PT_16.build();
		temp_dlc += ADCAN_AE_PT_16.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_17.build();
		temp_dlc += ADCAN_AE_PT_17.countOfBits;
		Val |= ADCAN_AE_PT_18.build();
		temp_dlc += ADCAN_AE_PT_18.countOfBits;
		Val |= ADCAN_AE_PT_19.build();
		temp_dlc += ADCAN_AE_PT_19.countOfBits;
		Val |= ADCAN_AE_PT_20.build();
		temp_dlc += ADCAN_AE_PT_20.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_21.build();
		temp_dlc += ADCAN_AE_PT_21.countOfBits;
		Val |= ADCAN_AE_PT_22.build();
		temp_dlc += ADCAN_AE_PT_22.countOfBits;
		Val |= ADCAN_AE_PT_23.build();
		temp_dlc += ADCAN_AE_PT_23.countOfBits;
		Val |= ADCAN_AE_PT_24.build();
		temp_dlc += ADCAN_AE_PT_24.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_25.build();
		temp_dlc += ADCAN_AE_PT_25.countOfBits;
		Val |= ADCAN_AE_PT_26.build();
		temp_dlc += ADCAN_AE_PT_26.countOfBits;
		Val |= ADCAN_AE_PT_27.build();
		temp_dlc += ADCAN_AE_PT_27.countOfBits;
		Val |= ADCAN_AE_PT_28.build();
		temp_dlc += ADCAN_AE_PT_28.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_29.build();
		temp_dlc += ADCAN_AE_PT_29.countOfBits;
		Val |= ADCAN_AE_PT_30.build();
		temp_dlc += ADCAN_AE_PT_30.countOfBits;
		Val |= ADCAN_SP_Rocker_1.build();
		temp_dlc += ADCAN_SP_Rocker_1.countOfBits;
		Val |= ADCAN_SP_Rocker_2.build();
		temp_dlc += ADCAN_SP_Rocker_2.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
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
	STOS_CAN_PDU_Aero_ADC_9() 
	{
		ID = _id;
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_AE_PT_33.build();
		temp_dlc += ADCAN_AE_PT_33.countOfBits;
		Val |= ADCAN_AE_PT_34.build();
		temp_dlc += ADCAN_AE_PT_34.countOfBits;
		Val |= ADCAN_AE_PT_35.build();
		temp_dlc += ADCAN_AE_PT_35.countOfBits;
		Val |= ADCAN_SP_Rocker_3.build();
		temp_dlc += ADCAN_SP_Rocker_3.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
	}
	void unbuild()
	{
		ADCAN_AE_PT_33.unbuild(Val);
		ADCAN_AE_PT_34.unbuild(Val);
		ADCAN_AE_PT_35.unbuild(Val);
		ADCAN_SP_Rocker_3.unbuild(Val);
	}

};
struct STOS_CAN_PDU_SP_RW : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_SP_RW;
	uint16_t _size;
	CAN_Signal<int16_t> ADCAN_SP_RW1 = {0, 16, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int16_t> ADCAN_SP_RW2 = {0, 16, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int16_t> ADCAN_SP_RW3 = {0, 16, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<int16_t> ADCAN_SP_RW4 = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_SP_RW() 
	{
		ID = _id;
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_RW1.build();
		temp_dlc += ADCAN_SP_RW1.countOfBits;
		Val |= ADCAN_SP_RW2.build();
		temp_dlc += ADCAN_SP_RW2.countOfBits;
		Val |= ADCAN_SP_RW3.build();
		temp_dlc += ADCAN_SP_RW3.countOfBits;
		Val |= ADCAN_SP_RW4.build();
		temp_dlc += ADCAN_SP_RW4.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
	}
	void unbuild()
	{
		ADCAN_SP_RW1.unbuild(Val);
		ADCAN_SP_RW2.unbuild(Val);
		ADCAN_SP_RW3.unbuild(Val);
		ADCAN_SP_RW4.unbuild(Val);
	}

};
struct STOS_CAN_PDU_UCU_ADC_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_UCU_ADC_1;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_PT_Temp_1 = {0, 16, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_PT_Temp_2 = {0, 16, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_PT_Temp_3 = {0, 16, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_PT_Temp_4 = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_UCU_ADC_1() 
	{
		ID = _id;
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_PT_Temp_1.build();
		temp_dlc += ADCAN_PT_Temp_1.countOfBits;
		Val |= ADCAN_PT_Temp_2.build();
		temp_dlc += ADCAN_PT_Temp_2.countOfBits;
		Val |= ADCAN_PT_Temp_3.build();
		temp_dlc += ADCAN_PT_Temp_3.countOfBits;
		Val |= ADCAN_PT_Temp_4.build();
		temp_dlc += ADCAN_PT_Temp_4.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
	}
	void unbuild()
	{
		ADCAN_PT_Temp_1.unbuild(Val);
		ADCAN_PT_Temp_2.unbuild(Val);
		ADCAN_PT_Temp_3.unbuild(Val);
		ADCAN_PT_Temp_4.unbuild(Val);
	}

};
struct STOS_CAN_PDU_UCU_ADC_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_UCU_ADC_2;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_PT_Temp_5 = {0, 16, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_PT_Temp_6 = {0, 16, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_X = {0, 16, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_Y = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_UCU_ADC_2() 
	{
		ID = _id;
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_PT_Temp_5.build();
		temp_dlc += ADCAN_PT_Temp_5.countOfBits;
		Val |= ADCAN_PT_Temp_6.build();
		temp_dlc += ADCAN_PT_Temp_6.countOfBits;
		Val |= ADCAN_SP_Accel_X.build();
		temp_dlc += ADCAN_SP_Accel_X.countOfBits;
		Val |= ADCAN_SP_Accel_Y.build();
		temp_dlc += ADCAN_SP_Accel_Y.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
	}
	void unbuild()
	{
		ADCAN_PT_Temp_5.unbuild(Val);
		ADCAN_PT_Temp_6.unbuild(Val);
		ADCAN_SP_Accel_X.unbuild(Val);
		ADCAN_SP_Accel_Y.unbuild(Val);
	}

};
struct STOS_CAN_PDU_UCU_ADC_3 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_UCU_ADC_3;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_Z = {0, 16, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rot_X = {0, 16, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rot_Y = {0, 16, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_Rot_Z = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_UCU_ADC_3() 
	{
		ID = _id;
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_Accel_Z.build();
		temp_dlc += ADCAN_SP_Accel_Z.countOfBits;
		Val |= ADCAN_SP_Rot_X.build();
		temp_dlc += ADCAN_SP_Rot_X.countOfBits;
		Val |= ADCAN_SP_Rot_Y.build();
		temp_dlc += ADCAN_SP_Rot_Y.countOfBits;
		Val |= ADCAN_SP_Rot_Z.build();
		temp_dlc += ADCAN_SP_Rot_Z.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
	}
	void unbuild()
	{
		ADCAN_SP_Accel_Z.unbuild(Val);
		ADCAN_SP_Rot_X.unbuild(Val);
		ADCAN_SP_Rot_Y.unbuild(Val);
		ADCAN_SP_Rot_Z.unbuild(Val);
	}

};
struct STOS_CAN_PDU_UCU_ADC_4 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_UCU_ADC_4;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_TBRAKE_VL = {0, 16, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_TBRAKE_VR = {0, 16, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_TBRAKE_HL = {0, 16, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_TBRAKE_HR = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_UCU_ADC_4() 
	{
		ID = _id;
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_TBRAKE_VL.build();
		temp_dlc += ADCAN_SP_TBRAKE_VL.countOfBits;
		Val |= ADCAN_SP_TBRAKE_VR.build();
		temp_dlc += ADCAN_SP_TBRAKE_VR.countOfBits;
		Val |= ADCAN_SP_TBRAKE_HL.build();
		temp_dlc += ADCAN_SP_TBRAKE_HL.countOfBits;
		Val |= ADCAN_SP_TBRAKE_HR.build();
		temp_dlc += ADCAN_SP_TBRAKE_HR.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
	}
	void unbuild()
	{
		ADCAN_SP_TBRAKE_VL.unbuild(Val);
		ADCAN_SP_TBRAKE_VR.unbuild(Val);
		ADCAN_SP_TBRAKE_HL.unbuild(Val);
		ADCAN_SP_TBRAKE_HR.unbuild(Val);
	}

};
struct STOS_CAN_PDU_UCU_ADC_5 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = STOS_CAN_ID_UCU_ADC_5;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_PBRAKE_HA = {0, 16, 0, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> ADCAN_SP_PBRAKE_VA = {0, 16, 16, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> Typ_K_1 = {0, 16, 32, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	CAN_Signal<uint16_t> Typ_K_2 = {0, 16, 48, 0, 0, 1, 0};//init,bitcount,startbit,rowcount,isMotorola,factor,offset 
	STOS_CAN_PDU_UCU_ADC_5() 
	{
		ID = _id;
	}
	void build()
	{
		uint8_t temp_dlc = 0;
		Val |= ADCAN_SP_PBRAKE_HA.build();
		temp_dlc += ADCAN_SP_PBRAKE_HA.countOfBits;
		Val |= ADCAN_SP_PBRAKE_VA.build();
		temp_dlc += ADCAN_SP_PBRAKE_VA.countOfBits;
		Val |= Typ_K_1.build();
		temp_dlc += Typ_K_1.countOfBits;
		Val |= Typ_K_2.build();
		temp_dlc += Typ_K_2.countOfBits;
		ID = _id;
		if(temp_dlc % 8 != 0) temp_dlc = temp_dlc / 8 + 1;
		else temp_dlc = temp_dlc / 8;
		if(temp_dlc > 8) temp_dlc = 8;
		_size = dlc = temp_dlc;
	}
	void unbuild()
	{
		ADCAN_SP_PBRAKE_HA.unbuild(Val);
		ADCAN_SP_PBRAKE_VA.unbuild(Val);
		Typ_K_1.unbuild(Val);
		Typ_K_2.unbuild(Val);
	}

};


#endif