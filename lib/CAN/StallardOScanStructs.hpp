#ifndef StallardOScanStructs_hpp
#define StallardOScanStructs_hpp
#include "stdint.h"
#include "StallardOScanTypes.hpp"
#include <math.h>

struct STOS_CAN_PDU_AGS1_gearbox_control_unit : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x100;
	uint16_t _size;
	CAN_Signal<int8_t> activate_blip = {0, 1, 60};//init,bitcount,startbit 
	CAN_Signal<uint8_t> activate_cut = {0, 1, 61};//init,bitcount,startbit 
	CAN_Signal<uint8_t> blip_state = {0, 4, 28};//init,bitcount,startbit 
	CAN_Signal<uint8_t> cut_level_gcu = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> engaged_gear = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint16_t> gearpot = {0, 10, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shift_state = {0, 4, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> state_cut = {0, 4, 56};//init,bitcount,startbit 
	CAN_Signal<uint16_t> target_engine_speed = {0, 14, 32};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		activate_blip.value = (Val & ~(jk_pow(activate_blip.startbit)-1) & ((jk_pow(activate_blip.countOfBits)-1) << activate_blip.startbit)) >> activate_blip.startbit;
		activate_cut.value = (Val & ~(jk_pow(activate_cut.startbit)-1) & ((jk_pow(activate_cut.countOfBits)-1) << activate_cut.startbit)) >> activate_cut.startbit;
		blip_state.value = (Val & ~(jk_pow(blip_state.startbit)-1) & ((jk_pow(blip_state.countOfBits)-1) << blip_state.startbit)) >> blip_state.startbit;
		cut_level_gcu.value = (Val & ~(jk_pow(cut_level_gcu.startbit)-1) & ((jk_pow(cut_level_gcu.countOfBits)-1) << cut_level_gcu.startbit)) >> cut_level_gcu.startbit;
		engaged_gear.value = (Val & ~(jk_pow(engaged_gear.startbit)-1) & ((jk_pow(engaged_gear.countOfBits)-1) << engaged_gear.startbit)) >> engaged_gear.startbit;
		gearpot.value = (Val & ~(jk_pow(gearpot.startbit)-1) & ((jk_pow(gearpot.countOfBits)-1) << gearpot.startbit)) >> gearpot.startbit;
		shift_state.value = (Val & ~(jk_pow(shift_state.startbit)-1) & ((jk_pow(shift_state.countOfBits)-1) << shift_state.startbit)) >> shift_state.startbit;
		state_cut.value = (Val & ~(jk_pow(state_cut.startbit)-1) & ((jk_pow(state_cut.countOfBits)-1) << state_cut.startbit)) >> state_cut.startbit;
		target_engine_speed.value = (Val & ~(jk_pow(target_engine_speed.startbit)-1) & ((jk_pow(target_engine_speed.countOfBits)-1) << target_engine_speed.startbit)) >> target_engine_speed.startbit;
	}
	STOS_CAN_PDU_AGS1_gearbox_control_unit() 
	{
		ID = _id;
		uint8_t temp = activate_blip.countOfBits + activate_cut.countOfBits + blip_state.countOfBits + cut_level_gcu.countOfBits + engaged_gear.countOfBits + gearpot.countOfBits + shift_state.countOfBits + state_cut.countOfBits + target_engine_speed.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = activate_blip.build() | activate_cut.build() | blip_state.build() | cut_level_gcu.build() | engaged_gear.build() | gearpot.build() | shift_state.build() | state_cut.build() | target_engine_speed.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_ABS_wheelspeeds : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x24A;
	uint16_t _size;
	CAN_Signal<uint16_t> speedABSfl = {0, 16, 0};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSfr = {0, 16, 16};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSrl = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSrr = {0, 16, 48};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		speedABSfl.value = (Val & ~(jk_pow(speedABSfl.startbit)-1) & ((jk_pow(speedABSfl.countOfBits)-1) << speedABSfl.startbit)) >> speedABSfl.startbit;
		speedABSfr.value = (Val & ~(jk_pow(speedABSfr.startbit)-1) & ((jk_pow(speedABSfr.countOfBits)-1) << speedABSfr.startbit)) >> speedABSfr.startbit;
		speedABSrl.value = (Val & ~(jk_pow(speedABSrl.startbit)-1) & ((jk_pow(speedABSrl.countOfBits)-1) << speedABSrl.startbit)) >> speedABSrl.startbit;
		speedABSrr.value = (Val & ~(jk_pow(speedABSrr.startbit)-1) & ((jk_pow(speedABSrr.countOfBits)-1) << speedABSrr.startbit)) >> speedABSrr.startbit;
	}
	STOS_CAN_PDU_ABS_wheelspeeds() 
	{
		ID = _id;
		uint8_t temp = speedABSfl.countOfBits + speedABSfr.countOfBits + speedABSrl.countOfBits + speedABSrr.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = speedABSfl.build() | speedABSfr.build() | speedABSrl.build() | speedABSrr.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_ABS_switch_state_slip_and_speed : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x5C0;
	uint16_t _size;
	CAN_Signal<uint16_t> ax1_Bremse60ABS = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ay1_Bremse60ABS = {0, 16, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> blsABS = {0, 1, 24};//init,bitcount,startbit 
	CAN_Signal<int16_t> p_HzABS = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> switchstateABS = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ax1_Bremse60ABS.value = (Val & ~(jk_pow(ax1_Bremse60ABS.startbit)-1) & ((jk_pow(ax1_Bremse60ABS.countOfBits)-1) << ax1_Bremse60ABS.startbit)) >> ax1_Bremse60ABS.startbit;
		ay1_Bremse60ABS.value = (Val & ~(jk_pow(ay1_Bremse60ABS.startbit)-1) & ((jk_pow(ay1_Bremse60ABS.countOfBits)-1) << ay1_Bremse60ABS.startbit)) >> ay1_Bremse60ABS.startbit;
		blsABS.value = (Val & ~(jk_pow(blsABS.startbit)-1) & ((jk_pow(blsABS.countOfBits)-1) << blsABS.startbit)) >> blsABS.startbit;
		p_HzABS.value = (Val & ~(jk_pow(p_HzABS.startbit)-1) & ((jk_pow(p_HzABS.countOfBits)-1) << p_HzABS.startbit)) >> p_HzABS.startbit;
		switchstateABS.value = (Val & ~(jk_pow(switchstateABS.startbit)-1) & ((jk_pow(switchstateABS.countOfBits)-1) << switchstateABS.startbit)) >> switchstateABS.startbit;
	}
	STOS_CAN_PDU_ABS_switch_state_slip_and_speed() 
	{
		ID = _id;
		uint8_t temp = ax1_Bremse60ABS.countOfBits + ay1_Bremse60ABS.countOfBits + blsABS.countOfBits + p_HzABS.countOfBits + switchstateABS.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ax1_Bremse60ABS.build() | ay1_Bremse60ABS.build() | blsABS.build() | p_HzABS.build() | switchstateABS.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Injection_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x770;
	uint16_t _size;
	CAN_Signal<uint8_t> ti_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_8 = {0, 8, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ti_1.value = (Val & ~(jk_pow(ti_1.startbit)-1) & ((jk_pow(ti_1.countOfBits)-1) << ti_1.startbit)) >> ti_1.startbit;
		ti_2.value = (Val & ~(jk_pow(ti_2.startbit)-1) & ((jk_pow(ti_2.countOfBits)-1) << ti_2.startbit)) >> ti_2.startbit;
		ti_3.value = (Val & ~(jk_pow(ti_3.startbit)-1) & ((jk_pow(ti_3.countOfBits)-1) << ti_3.startbit)) >> ti_3.startbit;
		ti_4.value = (Val & ~(jk_pow(ti_4.startbit)-1) & ((jk_pow(ti_4.countOfBits)-1) << ti_4.startbit)) >> ti_4.startbit;
		ti_5.value = (Val & ~(jk_pow(ti_5.startbit)-1) & ((jk_pow(ti_5.countOfBits)-1) << ti_5.startbit)) >> ti_5.startbit;
		ti_6.value = (Val & ~(jk_pow(ti_6.startbit)-1) & ((jk_pow(ti_6.countOfBits)-1) << ti_6.startbit)) >> ti_6.startbit;
		ti_7.value = (Val & ~(jk_pow(ti_7.startbit)-1) & ((jk_pow(ti_7.countOfBits)-1) << ti_7.startbit)) >> ti_7.startbit;
		ti_8.value = (Val & ~(jk_pow(ti_8.startbit)-1) & ((jk_pow(ti_8.countOfBits)-1) << ti_8.startbit)) >> ti_8.startbit;
	}
	STOS_CAN_PDU_Injection_1() 
	{
		ID = _id;
		uint8_t temp = ti_1.countOfBits + ti_2.countOfBits + ti_3.countOfBits + ti_4.countOfBits + ti_5.countOfBits + ti_6.countOfBits + ti_7.countOfBits + ti_8.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ti_1.build() | ti_2.build() | ti_3.build() | ti_4.build() | ti_5.build() | ti_6.build() | ti_7.build() | ti_8.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Injection_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x771;
	uint16_t _size;
	CAN_Signal<uint8_t> injang = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> injoff = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_2k = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_k = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tibase = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tibatt_o = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> timap = {0, 8, 16};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		injang.value = (Val & ~(jk_pow(injang.startbit)-1) & ((jk_pow(injang.countOfBits)-1) << injang.startbit)) >> injang.startbit;
		injoff.value = (Val & ~(jk_pow(injoff.startbit)-1) & ((jk_pow(injoff.countOfBits)-1) << injoff.startbit)) >> injoff.startbit;
		lamctrl_2k.value = (Val & ~(jk_pow(lamctrl_2k.startbit)-1) & ((jk_pow(lamctrl_2k.countOfBits)-1) << lamctrl_2k.startbit)) >> lamctrl_2k.startbit;
		lamctrl_k.value = (Val & ~(jk_pow(lamctrl_k.startbit)-1) & ((jk_pow(lamctrl_k.countOfBits)-1) << lamctrl_k.startbit)) >> lamctrl_k.startbit;
		tibase.value = (Val & ~(jk_pow(tibase.startbit)-1) & ((jk_pow(tibase.countOfBits)-1) << tibase.startbit)) >> tibase.startbit;
		tibatt_o.value = (Val & ~(jk_pow(tibatt_o.startbit)-1) & ((jk_pow(tibatt_o.countOfBits)-1) << tibatt_o.startbit)) >> tibatt_o.startbit;
		timap.value = (Val & ~(jk_pow(timap.startbit)-1) & ((jk_pow(timap.countOfBits)-1) << timap.startbit)) >> timap.startbit;
	}
	STOS_CAN_PDU_Injection_2() 
	{
		ID = _id;
		uint8_t temp = injang.countOfBits + injoff.countOfBits + lamctrl_2k.countOfBits + lamctrl_k.countOfBits + tibase.countOfBits + tibatt_o.countOfBits + timap.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = injang.build() | injoff.build() | lamctrl_2k.build() | lamctrl_k.build() | tibase.build() | tibatt_o.build() | timap.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Ignition : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x772;
	uint16_t _size;
	CAN_Signal<int8_t> ign_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_8 = {0, 8, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ign_1.value = (Val & ~(jk_pow(ign_1.startbit)-1) & ((jk_pow(ign_1.countOfBits)-1) << ign_1.startbit)) >> ign_1.startbit;
		ign_2.value = (Val & ~(jk_pow(ign_2.startbit)-1) & ((jk_pow(ign_2.countOfBits)-1) << ign_2.startbit)) >> ign_2.startbit;
		ign_3.value = (Val & ~(jk_pow(ign_3.startbit)-1) & ((jk_pow(ign_3.countOfBits)-1) << ign_3.startbit)) >> ign_3.startbit;
		ign_4.value = (Val & ~(jk_pow(ign_4.startbit)-1) & ((jk_pow(ign_4.countOfBits)-1) << ign_4.startbit)) >> ign_4.startbit;
		ign_5.value = (Val & ~(jk_pow(ign_5.startbit)-1) & ((jk_pow(ign_5.countOfBits)-1) << ign_5.startbit)) >> ign_5.startbit;
		ign_6.value = (Val & ~(jk_pow(ign_6.startbit)-1) & ((jk_pow(ign_6.countOfBits)-1) << ign_6.startbit)) >> ign_6.startbit;
		ign_7.value = (Val & ~(jk_pow(ign_7.startbit)-1) & ((jk_pow(ign_7.countOfBits)-1) << ign_7.startbit)) >> ign_7.startbit;
		ign_8.value = (Val & ~(jk_pow(ign_8.startbit)-1) & ((jk_pow(ign_8.countOfBits)-1) << ign_8.startbit)) >> ign_8.startbit;
	}
	STOS_CAN_PDU_Ignition() 
	{
		ID = _id;
		uint8_t temp = ign_1.countOfBits + ign_2.countOfBits + ign_3.countOfBits + ign_4.countOfBits + ign_5.countOfBits + ign_6.countOfBits + ign_7.countOfBits + ign_8.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ign_1.build() | ign_2.build() | ign_3.build() | ign_4.build() | ign_5.build() | ign_6.build() | ign_7.build() | ign_8.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Ignition_Rev_Ath : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x773;
	uint16_t _size;
	CAN_Signal<uint8_t> ath = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> dath = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> ignbase = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> ignmap = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> rev = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tdwell = {0, 8, 16};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ath.value = (Val & ~(jk_pow(ath.startbit)-1) & ((jk_pow(ath.countOfBits)-1) << ath.startbit)) >> ath.startbit;
		dath.value = (Val & ~(jk_pow(dath.startbit)-1) & ((jk_pow(dath.countOfBits)-1) << dath.startbit)) >> dath.startbit;
		ignbase.value = (Val & ~(jk_pow(ignbase.startbit)-1) & ((jk_pow(ignbase.countOfBits)-1) << ignbase.startbit)) >> ignbase.startbit;
		ignmap.value = (Val & ~(jk_pow(ignmap.startbit)-1) & ((jk_pow(ignmap.countOfBits)-1) << ignmap.startbit)) >> ignmap.startbit;
		rev.value = (Val & ~(jk_pow(rev.startbit)-1) & ((jk_pow(rev.countOfBits)-1) << rev.startbit)) >> rev.startbit;
		tdwell.value = (Val & ~(jk_pow(tdwell.startbit)-1) & ((jk_pow(tdwell.countOfBits)-1) << tdwell.startbit)) >> tdwell.startbit;
	}
	STOS_CAN_PDU_Ignition_Rev_Ath() 
	{
		ID = _id;
		uint8_t temp = ath.countOfBits + dath.countOfBits + ignbase.countOfBits + ignmap.countOfBits + rev.countOfBits + tdwell.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ath.build() | dath.build() | ignbase.build() | ignmap.build() | rev.build() | tdwell.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Lambda : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x774;
	uint16_t _size;
	CAN_Signal<uint8_t> lam = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lam_2 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> lami = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> lami_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lammap = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lammap_2 = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<int8_t> lamp = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<int8_t> lamp_2 = {0, 8, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		lam.value = (Val & ~(jk_pow(lam.startbit)-1) & ((jk_pow(lam.countOfBits)-1) << lam.startbit)) >> lam.startbit;
		lam_2.value = (Val & ~(jk_pow(lam_2.startbit)-1) & ((jk_pow(lam_2.countOfBits)-1) << lam_2.startbit)) >> lam_2.startbit;
		lami.value = (Val & ~(jk_pow(lami.startbit)-1) & ((jk_pow(lami.countOfBits)-1) << lami.startbit)) >> lami.startbit;
		lami_2.value = (Val & ~(jk_pow(lami_2.startbit)-1) & ((jk_pow(lami_2.countOfBits)-1) << lami_2.startbit)) >> lami_2.startbit;
		lammap.value = (Val & ~(jk_pow(lammap.startbit)-1) & ((jk_pow(lammap.countOfBits)-1) << lammap.startbit)) >> lammap.startbit;
		lammap_2.value = (Val & ~(jk_pow(lammap_2.startbit)-1) & ((jk_pow(lammap_2.countOfBits)-1) << lammap_2.startbit)) >> lammap_2.startbit;
		lamp.value = (Val & ~(jk_pow(lamp.startbit)-1) & ((jk_pow(lamp.countOfBits)-1) << lamp.startbit)) >> lamp.startbit;
		lamp_2.value = (Val & ~(jk_pow(lamp_2.startbit)-1) & ((jk_pow(lamp_2.countOfBits)-1) << lamp_2.startbit)) >> lamp_2.startbit;
	}
	STOS_CAN_PDU_Lambda() 
	{
		ID = _id;
		uint8_t temp = lam.countOfBits + lam_2.countOfBits + lami.countOfBits + lami_2.countOfBits + lammap.countOfBits + lammap_2.countOfBits + lamp.countOfBits + lamp_2.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = lam.build() | lam_2.build() | lami.build() | lami_2.build() | lammap.build() | lammap_2.build() | lamp.build() | lamp_2.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Speed : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x775;
	uint16_t _size;
	CAN_Signal<uint16_t> speed = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedfl = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedfr = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedrl = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedrr = {0, 8, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		speed.value = (Val & ~(jk_pow(speed.startbit)-1) & ((jk_pow(speed.countOfBits)-1) << speed.startbit)) >> speed.startbit;
		speedfl.value = (Val & ~(jk_pow(speedfl.startbit)-1) & ((jk_pow(speedfl.countOfBits)-1) << speedfl.startbit)) >> speedfl.startbit;
		speedfr.value = (Val & ~(jk_pow(speedfr.startbit)-1) & ((jk_pow(speedfr.countOfBits)-1) << speedfr.startbit)) >> speedfr.startbit;
		speedrl.value = (Val & ~(jk_pow(speedrl.startbit)-1) & ((jk_pow(speedrl.countOfBits)-1) << speedrl.startbit)) >> speedrl.startbit;
		speedrr.value = (Val & ~(jk_pow(speedrr.startbit)-1) & ((jk_pow(speedrr.countOfBits)-1) << speedrr.startbit)) >> speedrr.startbit;
	}
	STOS_CAN_PDU_Speed() 
	{
		ID = _id;
		uint8_t temp = speed.countOfBits + speedfl.countOfBits + speedfr.countOfBits + speedrl.countOfBits + speedrr.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = speed.build() | speedfl.build() | speedfr.build() | speedrl.build() | speedrr.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Lapfunc : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x776;
	uint16_t _size;
	CAN_Signal<uint16_t> lapdist = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptime = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptimediff = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptimefast = {0, 16, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		lapdist.value = (Val & ~(jk_pow(lapdist.startbit)-1) & ((jk_pow(lapdist.countOfBits)-1) << lapdist.startbit)) >> lapdist.startbit;
		laptime.value = (Val & ~(jk_pow(laptime.startbit)-1) & ((jk_pow(laptime.countOfBits)-1) << laptime.startbit)) >> laptime.startbit;
		laptimediff.value = (Val & ~(jk_pow(laptimediff.startbit)-1) & ((jk_pow(laptimediff.countOfBits)-1) << laptimediff.startbit)) >> laptimediff.startbit;
		laptimefast.value = (Val & ~(jk_pow(laptimefast.startbit)-1) & ((jk_pow(laptimefast.countOfBits)-1) << laptimefast.startbit)) >> laptimefast.startbit;
	}
	STOS_CAN_PDU_Lapfunc() 
	{
		ID = _id;
		uint8_t temp = lapdist.countOfBits + laptime.countOfBits + laptimediff.countOfBits + laptimefast.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = lapdist.build() | laptime.build() | laptimediff.build() | laptimefast.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Gear_Dashboard_Acceleration : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x777;
	uint16_t _size;
	CAN_Signal<int8_t> accx = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> accy = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> accz = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ddugear = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gcstate = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gear = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gearcut_u = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gearratio = {0, 8, 16};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		accx.value = (Val & ~(jk_pow(accx.startbit)-1) & ((jk_pow(accx.countOfBits)-1) << accx.startbit)) >> accx.startbit;
		accy.value = (Val & ~(jk_pow(accy.startbit)-1) & ((jk_pow(accy.countOfBits)-1) << accy.startbit)) >> accy.startbit;
		accz.value = (Val & ~(jk_pow(accz.startbit)-1) & ((jk_pow(accz.countOfBits)-1) << accz.startbit)) >> accz.startbit;
		ddugear.value = (Val & ~(jk_pow(ddugear.startbit)-1) & ((jk_pow(ddugear.countOfBits)-1) << ddugear.startbit)) >> ddugear.startbit;
		gcstate.value = (Val & ~(jk_pow(gcstate.startbit)-1) & ((jk_pow(gcstate.countOfBits)-1) << gcstate.startbit)) >> gcstate.startbit;
		gear.value = (Val & ~(jk_pow(gear.startbit)-1) & ((jk_pow(gear.countOfBits)-1) << gear.startbit)) >> gear.startbit;
		gearcut_u.value = (Val & ~(jk_pow(gearcut_u.startbit)-1) & ((jk_pow(gearcut_u.countOfBits)-1) << gearcut_u.startbit)) >> gearcut_u.startbit;
		gearratio.value = (Val & ~(jk_pow(gearratio.startbit)-1) & ((jk_pow(gearratio.countOfBits)-1) << gearratio.startbit)) >> gearratio.startbit;
	}
	STOS_CAN_PDU_Gear_Dashboard_Acceleration() 
	{
		ID = _id;
		uint8_t temp = accx.countOfBits + accy.countOfBits + accz.countOfBits + ddugear.countOfBits + gcstate.countOfBits + gear.countOfBits + gearcut_u.countOfBits + gearratio.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = accx.build() | accy.build() | accz.build() | ddugear.build() | gcstate.build() | gear.build() | gearcut_u.build() | gearratio.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Traction_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x778;
	uint16_t _size;
	CAN_Signal<uint8_t> slipsp = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> slra = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<int8_t> tcpfac = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tcsw = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> vdraxle = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> vref = {0, 16, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		slipsp.value = (Val & ~(jk_pow(slipsp.startbit)-1) & ((jk_pow(slipsp.countOfBits)-1) << slipsp.startbit)) >> slipsp.startbit;
		slra.value = (Val & ~(jk_pow(slra.startbit)-1) & ((jk_pow(slra.countOfBits)-1) << slra.startbit)) >> slra.startbit;
		tcpfac.value = (Val & ~(jk_pow(tcpfac.startbit)-1) & ((jk_pow(tcpfac.countOfBits)-1) << tcpfac.startbit)) >> tcpfac.startbit;
		tcsw.value = (Val & ~(jk_pow(tcsw.startbit)-1) & ((jk_pow(tcsw.countOfBits)-1) << tcsw.startbit)) >> tcsw.startbit;
		vdraxle.value = (Val & ~(jk_pow(vdraxle.startbit)-1) & ((jk_pow(vdraxle.countOfBits)-1) << vdraxle.startbit)) >> vdraxle.startbit;
		vref.value = (Val & ~(jk_pow(vref.startbit)-1) & ((jk_pow(vref.countOfBits)-1) << vref.startbit)) >> vref.startbit;
	}
	STOS_CAN_PDU_Traction_Control() 
	{
		ID = _id;
		uint8_t temp = slipsp.countOfBits + slra.countOfBits + tcpfac.countOfBits + tcsw.countOfBits + vdraxle.countOfBits + vref.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = slipsp.build() | slra.build() | tcpfac.build() | tcsw.build() | vdraxle.build() | vref.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Electronic_Throttle_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x779;
	uint16_t _size;
	CAN_Signal<uint8_t> aps = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> batt_u = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> camshaftpos = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> etb = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> etb_sp = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lap_c = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint16_t> p1 = {0, 16, 32};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		aps.value = (Val & ~(jk_pow(aps.startbit)-1) & ((jk_pow(aps.countOfBits)-1) << aps.startbit)) >> aps.startbit;
		batt_u.value = (Val & ~(jk_pow(batt_u.startbit)-1) & ((jk_pow(batt_u.countOfBits)-1) << batt_u.startbit)) >> batt_u.startbit;
		camshaftpos.value = (Val & ~(jk_pow(camshaftpos.startbit)-1) & ((jk_pow(camshaftpos.countOfBits)-1) << camshaftpos.startbit)) >> camshaftpos.startbit;
		etb.value = (Val & ~(jk_pow(etb.startbit)-1) & ((jk_pow(etb.countOfBits)-1) << etb.startbit)) >> etb.startbit;
		etb_sp.value = (Val & ~(jk_pow(etb_sp.startbit)-1) & ((jk_pow(etb_sp.countOfBits)-1) << etb_sp.startbit)) >> etb_sp.startbit;
		lap_c.value = (Val & ~(jk_pow(lap_c.startbit)-1) & ((jk_pow(lap_c.countOfBits)-1) << lap_c.startbit)) >> lap_c.startbit;
		p1.value = (Val & ~(jk_pow(p1.startbit)-1) & ((jk_pow(p1.countOfBits)-1) << p1.startbit)) >> p1.startbit;
	}
	STOS_CAN_PDU_Electronic_Throttle_Control() 
	{
		ID = _id;
		uint8_t temp = aps.countOfBits + batt_u.countOfBits + camshaftpos.countOfBits + etb.countOfBits + etb_sp.countOfBits + lap_c.countOfBits + p1.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = aps.build() | batt_u.build() | camshaftpos.build() | etb.build() | etb_sp.build() | lap_c.build() | p1.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_States_Temp_Press : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x77A;
	uint16_t _size;
	CAN_Signal<uint8_t> battlow_b = {0, 1, 61};//init,bitcount,startbit 
	CAN_Signal<uint8_t> etbsys_e = {0, 1, 25};//init,bitcount,startbit 
	CAN_Signal<uint16_t> fuellap = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<int16_t> fueltank = {0, 16, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gearcut_b = {0, 1, 9};//init,bitcount,startbit 
	CAN_Signal<uint8_t> idle_b = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ignoff_b = {0, 1, 31};//init,bitcount,startbit 
	CAN_Signal<uint8_t> injcut_b = {0, 1, 15};//init,bitcount,startbit 
	CAN_Signal<uint8_t> injcutin_b = {0, 1, 14};//init,bitcount,startbit 
	CAN_Signal<uint8_t> injenrich_b = {0, 1, 13};//init,bitcount,startbit 
	CAN_Signal<uint8_t> injstartphase_b = {0, 1, 12};//init,bitcount,startbit 
	CAN_Signal<uint8_t> knockadaptenable_b = {0, 1, 27};//init,bitcount,startbit 
	CAN_Signal<uint8_t> knockenable_b = {0, 1, 26};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_2b = {0, 1, 10};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_b = {0, 1, 11};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lap_b = {0, 1, 22};//init,bitcount,startbit 
	CAN_Signal<uint8_t> laptrig_b = {0, 1, 21};//init,bitcount,startbit 
	CAN_Signal<uint8_t> mappos = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> mil_b = {0, 1, 20};//init,bitcount,startbit 
	CAN_Signal<uint8_t> oillamp_b = {0, 1, 19};//init,bitcount,startbit 
	CAN_Signal<uint16_t> pamb = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> pcrank = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> pfuel = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> phsok_b = {0, 1, 18};//init,bitcount,startbit 
	CAN_Signal<uint8_t> phsokset_b = {0, 1, 17};//init,bitcount,startbit 
	CAN_Signal<uint8_t> poil = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> pwat = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> rev_b = {0, 1, 30};//init,bitcount,startbit 
	CAN_Signal<uint8_t> revlimit_b = {0, 1, 29};//init,bitcount,startbit 
	CAN_Signal<uint8_t> rowcounter_0x77A = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shled1_b = {0, 1, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shled2_b = {0, 1, 57};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shled3_b = {0, 1, 58};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shled4_b = {0, 1, 59};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shled5_b = {0, 1, 60};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedlimit_b = {0, 1, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedlimitreq_b = {0, 1, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> startend_b = {0, 1, 28};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tair = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tc_b = {0, 1, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tex = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tex_2 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tfuel = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tlam = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tlam_2 = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tmot = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> toil = {0, 8, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		battlow_b.value = (Val & ~(jk_pow(battlow_b.startbit)-1) & ((jk_pow(battlow_b.countOfBits)-1) << battlow_b.startbit)) >> battlow_b.startbit;
		etbsys_e.value = (Val & ~(jk_pow(etbsys_e.startbit)-1) & ((jk_pow(etbsys_e.countOfBits)-1) << etbsys_e.startbit)) >> etbsys_e.startbit;
		fuellap.value = (Val & ~(jk_pow(fuellap.startbit)-1) & ((jk_pow(fuellap.countOfBits)-1) << fuellap.startbit)) >> fuellap.startbit;
		fueltank.value = (Val & ~(jk_pow(fueltank.startbit)-1) & ((jk_pow(fueltank.countOfBits)-1) << fueltank.startbit)) >> fueltank.startbit;
		gearcut_b.value = (Val & ~(jk_pow(gearcut_b.startbit)-1) & ((jk_pow(gearcut_b.countOfBits)-1) << gearcut_b.startbit)) >> gearcut_b.startbit;
		idle_b.value = (Val & ~(jk_pow(idle_b.startbit)-1) & ((jk_pow(idle_b.countOfBits)-1) << idle_b.startbit)) >> idle_b.startbit;
		ignoff_b.value = (Val & ~(jk_pow(ignoff_b.startbit)-1) & ((jk_pow(ignoff_b.countOfBits)-1) << ignoff_b.startbit)) >> ignoff_b.startbit;
		injcut_b.value = (Val & ~(jk_pow(injcut_b.startbit)-1) & ((jk_pow(injcut_b.countOfBits)-1) << injcut_b.startbit)) >> injcut_b.startbit;
		injcutin_b.value = (Val & ~(jk_pow(injcutin_b.startbit)-1) & ((jk_pow(injcutin_b.countOfBits)-1) << injcutin_b.startbit)) >> injcutin_b.startbit;
		injenrich_b.value = (Val & ~(jk_pow(injenrich_b.startbit)-1) & ((jk_pow(injenrich_b.countOfBits)-1) << injenrich_b.startbit)) >> injenrich_b.startbit;
		injstartphase_b.value = (Val & ~(jk_pow(injstartphase_b.startbit)-1) & ((jk_pow(injstartphase_b.countOfBits)-1) << injstartphase_b.startbit)) >> injstartphase_b.startbit;
		knockadaptenable_b.value = (Val & ~(jk_pow(knockadaptenable_b.startbit)-1) & ((jk_pow(knockadaptenable_b.countOfBits)-1) << knockadaptenable_b.startbit)) >> knockadaptenable_b.startbit;
		knockenable_b.value = (Val & ~(jk_pow(knockenable_b.startbit)-1) & ((jk_pow(knockenable_b.countOfBits)-1) << knockenable_b.startbit)) >> knockenable_b.startbit;
		lamctrl_2b.value = (Val & ~(jk_pow(lamctrl_2b.startbit)-1) & ((jk_pow(lamctrl_2b.countOfBits)-1) << lamctrl_2b.startbit)) >> lamctrl_2b.startbit;
		lamctrl_b.value = (Val & ~(jk_pow(lamctrl_b.startbit)-1) & ((jk_pow(lamctrl_b.countOfBits)-1) << lamctrl_b.startbit)) >> lamctrl_b.startbit;
		lap_b.value = (Val & ~(jk_pow(lap_b.startbit)-1) & ((jk_pow(lap_b.countOfBits)-1) << lap_b.startbit)) >> lap_b.startbit;
		laptrig_b.value = (Val & ~(jk_pow(laptrig_b.startbit)-1) & ((jk_pow(laptrig_b.countOfBits)-1) << laptrig_b.startbit)) >> laptrig_b.startbit;
		mappos.value = (Val & ~(jk_pow(mappos.startbit)-1) & ((jk_pow(mappos.countOfBits)-1) << mappos.startbit)) >> mappos.startbit;
		mil_b.value = (Val & ~(jk_pow(mil_b.startbit)-1) & ((jk_pow(mil_b.countOfBits)-1) << mil_b.startbit)) >> mil_b.startbit;
		oillamp_b.value = (Val & ~(jk_pow(oillamp_b.startbit)-1) & ((jk_pow(oillamp_b.countOfBits)-1) << oillamp_b.startbit)) >> oillamp_b.startbit;
		pamb.value = (Val & ~(jk_pow(pamb.startbit)-1) & ((jk_pow(pamb.countOfBits)-1) << pamb.startbit)) >> pamb.startbit;
		pcrank.value = (Val & ~(jk_pow(pcrank.startbit)-1) & ((jk_pow(pcrank.countOfBits)-1) << pcrank.startbit)) >> pcrank.startbit;
		pfuel.value = (Val & ~(jk_pow(pfuel.startbit)-1) & ((jk_pow(pfuel.countOfBits)-1) << pfuel.startbit)) >> pfuel.startbit;
		phsok_b.value = (Val & ~(jk_pow(phsok_b.startbit)-1) & ((jk_pow(phsok_b.countOfBits)-1) << phsok_b.startbit)) >> phsok_b.startbit;
		phsokset_b.value = (Val & ~(jk_pow(phsokset_b.startbit)-1) & ((jk_pow(phsokset_b.countOfBits)-1) << phsokset_b.startbit)) >> phsokset_b.startbit;
		poil.value = (Val & ~(jk_pow(poil.startbit)-1) & ((jk_pow(poil.countOfBits)-1) << poil.startbit)) >> poil.startbit;
		pwat.value = (Val & ~(jk_pow(pwat.startbit)-1) & ((jk_pow(pwat.countOfBits)-1) << pwat.startbit)) >> pwat.startbit;
		rev_b.value = (Val & ~(jk_pow(rev_b.startbit)-1) & ((jk_pow(rev_b.countOfBits)-1) << rev_b.startbit)) >> rev_b.startbit;
		revlimit_b.value = (Val & ~(jk_pow(revlimit_b.startbit)-1) & ((jk_pow(revlimit_b.countOfBits)-1) << revlimit_b.startbit)) >> revlimit_b.startbit;
		rowcounter_0x77A.value = (Val & ~(jk_pow(rowcounter_0x77A.startbit)-1) & ((jk_pow(rowcounter_0x77A.countOfBits)-1) << rowcounter_0x77A.startbit)) >> rowcounter_0x77A.startbit;
		shled1_b.value = (Val & ~(jk_pow(shled1_b.startbit)-1) & ((jk_pow(shled1_b.countOfBits)-1) << shled1_b.startbit)) >> shled1_b.startbit;
		shled2_b.value = (Val & ~(jk_pow(shled2_b.startbit)-1) & ((jk_pow(shled2_b.countOfBits)-1) << shled2_b.startbit)) >> shled2_b.startbit;
		shled3_b.value = (Val & ~(jk_pow(shled3_b.startbit)-1) & ((jk_pow(shled3_b.countOfBits)-1) << shled3_b.startbit)) >> shled3_b.startbit;
		shled4_b.value = (Val & ~(jk_pow(shled4_b.startbit)-1) & ((jk_pow(shled4_b.countOfBits)-1) << shled4_b.startbit)) >> shled4_b.startbit;
		shled5_b.value = (Val & ~(jk_pow(shled5_b.startbit)-1) & ((jk_pow(shled5_b.countOfBits)-1) << shled5_b.startbit)) >> shled5_b.startbit;
		speedlimit_b.value = (Val & ~(jk_pow(speedlimit_b.startbit)-1) & ((jk_pow(speedlimit_b.countOfBits)-1) << speedlimit_b.startbit)) >> speedlimit_b.startbit;
		speedlimitreq_b.value = (Val & ~(jk_pow(speedlimitreq_b.startbit)-1) & ((jk_pow(speedlimitreq_b.countOfBits)-1) << speedlimitreq_b.startbit)) >> speedlimitreq_b.startbit;
		startend_b.value = (Val & ~(jk_pow(startend_b.startbit)-1) & ((jk_pow(startend_b.countOfBits)-1) << startend_b.startbit)) >> startend_b.startbit;
		tair.value = (Val & ~(jk_pow(tair.startbit)-1) & ((jk_pow(tair.countOfBits)-1) << tair.startbit)) >> tair.startbit;
		tc_b.value = (Val & ~(jk_pow(tc_b.startbit)-1) & ((jk_pow(tc_b.countOfBits)-1) << tc_b.startbit)) >> tc_b.startbit;
		tex.value = (Val & ~(jk_pow(tex.startbit)-1) & ((jk_pow(tex.countOfBits)-1) << tex.startbit)) >> tex.startbit;
		tex_2.value = (Val & ~(jk_pow(tex_2.startbit)-1) & ((jk_pow(tex_2.countOfBits)-1) << tex_2.startbit)) >> tex_2.startbit;
		tfuel.value = (Val & ~(jk_pow(tfuel.startbit)-1) & ((jk_pow(tfuel.countOfBits)-1) << tfuel.startbit)) >> tfuel.startbit;
		tlam.value = (Val & ~(jk_pow(tlam.startbit)-1) & ((jk_pow(tlam.countOfBits)-1) << tlam.startbit)) >> tlam.startbit;
		tlam_2.value = (Val & ~(jk_pow(tlam_2.startbit)-1) & ((jk_pow(tlam_2.countOfBits)-1) << tlam_2.startbit)) >> tlam_2.startbit;
		tmot.value = (Val & ~(jk_pow(tmot.startbit)-1) & ((jk_pow(tmot.countOfBits)-1) << tmot.startbit)) >> tmot.startbit;
		toil.value = (Val & ~(jk_pow(toil.startbit)-1) & ((jk_pow(toil.countOfBits)-1) << toil.startbit)) >> toil.startbit;
	}
	STOS_CAN_PDU_States_Temp_Press() 
	{
		ID = _id;
		uint8_t temp = battlow_b.countOfBits + etbsys_e.countOfBits + fuellap.countOfBits + fueltank.countOfBits + gearcut_b.countOfBits + idle_b.countOfBits + ignoff_b.countOfBits + injcut_b.countOfBits + injcutin_b.countOfBits + injenrich_b.countOfBits + injstartphase_b.countOfBits + knockadaptenable_b.countOfBits + knockenable_b.countOfBits + lamctrl_2b.countOfBits + lamctrl_b.countOfBits + lap_b.countOfBits + laptrig_b.countOfBits + mappos.countOfBits + mil_b.countOfBits + oillamp_b.countOfBits + pamb.countOfBits + pcrank.countOfBits + pfuel.countOfBits + phsok_b.countOfBits + phsokset_b.countOfBits + poil.countOfBits + pwat.countOfBits + rev_b.countOfBits + revlimit_b.countOfBits + rowcounter_0x77A.countOfBits + shled1_b.countOfBits + shled2_b.countOfBits + shled3_b.countOfBits + shled4_b.countOfBits + shled5_b.countOfBits + speedlimit_b.countOfBits + speedlimitreq_b.countOfBits + startend_b.countOfBits + tair.countOfBits + tc_b.countOfBits + tex.countOfBits + tex_2.countOfBits + tfuel.countOfBits + tlam.countOfBits + tlam_2.countOfBits + tmot.countOfBits + toil.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = battlow_b.build() | etbsys_e.build() | fuellap.build() | fueltank.build() | gearcut_b.build() | idle_b.build() | ignoff_b.build() | injcut_b.build() | injcutin_b.build() | injenrich_b.build() | injstartphase_b.build() | knockadaptenable_b.build() | knockenable_b.build() | lamctrl_2b.build() | lamctrl_b.build() | lap_b.build() | laptrig_b.build() | mappos.build() | mil_b.build() | oillamp_b.build() | pamb.build() | pcrank.build() | pfuel.build() | phsok_b.build() | phsokset_b.build() | poil.build() | pwat.build() | rev_b.build() | revlimit_b.build() | rowcounter_0x77A.build() | shled1_b.build() | shled2_b.build() | shled3_b.build() | shled4_b.build() | shled5_b.build() | speedlimit_b.build() | speedlimitreq_b.build() | startend_b.build() | tair.build() | tc_b.build() | tex.build() | tex_2.build() | tfuel.build() | tlam.build() | tlam_2.build() | tmot.build() | toil.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Boost_Pressures_Wastegate : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x77C;
	uint16_t _size;
	CAN_Signal<uint16_t> p22_2m_pwg_m = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> p22_m = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> p22_sp = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> pwg_sp = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> wgdc_2_wgdchold = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> wgdc_wgdcvent = {0, 8, 48};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		p22_2m_pwg_m.value = (Val & ~(jk_pow(p22_2m_pwg_m.startbit)-1) & ((jk_pow(p22_2m_pwg_m.countOfBits)-1) << p22_2m_pwg_m.startbit)) >> p22_2m_pwg_m.startbit;
		p22_m.value = (Val & ~(jk_pow(p22_m.startbit)-1) & ((jk_pow(p22_m.countOfBits)-1) << p22_m.startbit)) >> p22_m.startbit;
		p22_sp.value = (Val & ~(jk_pow(p22_sp.startbit)-1) & ((jk_pow(p22_sp.countOfBits)-1) << p22_sp.startbit)) >> p22_sp.startbit;
		pwg_sp.value = (Val & ~(jk_pow(pwg_sp.startbit)-1) & ((jk_pow(pwg_sp.countOfBits)-1) << pwg_sp.startbit)) >> pwg_sp.startbit;
		wgdc_2_wgdchold.value = (Val & ~(jk_pow(wgdc_2_wgdchold.startbit)-1) & ((jk_pow(wgdc_2_wgdchold.countOfBits)-1) << wgdc_2_wgdchold.startbit)) >> wgdc_2_wgdchold.startbit;
		wgdc_wgdcvent.value = (Val & ~(jk_pow(wgdc_wgdcvent.startbit)-1) & ((jk_pow(wgdc_wgdcvent.countOfBits)-1) << wgdc_wgdcvent.startbit)) >> wgdc_wgdcvent.startbit;
	}
	STOS_CAN_PDU_Boost_Pressures_Wastegate() 
	{
		ID = _id;
		uint8_t temp = p22_2m_pwg_m.countOfBits + p22_m.countOfBits + p22_sp.countOfBits + pwg_sp.countOfBits + wgdc_2_wgdchold.countOfBits + wgdc_wgdcvent.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = p22_2m_pwg_m.build() | p22_m.build() | p22_sp.build() | pwg_sp.build() | wgdc_2_wgdchold.build() | wgdc_wgdcvent.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Acceleration_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x150;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Z = {0, 16, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Accel_1_X.value = (Val & ~(jk_pow(ADCAN_SP_Accel_1_X.startbit)-1) & ((jk_pow(ADCAN_SP_Accel_1_X.countOfBits)-1) << ADCAN_SP_Accel_1_X.startbit)) >> ADCAN_SP_Accel_1_X.startbit;
		ADCAN_SP_Accel_1_Y.value = (Val & ~(jk_pow(ADCAN_SP_Accel_1_Y.startbit)-1) & ((jk_pow(ADCAN_SP_Accel_1_Y.countOfBits)-1) << ADCAN_SP_Accel_1_Y.startbit)) >> ADCAN_SP_Accel_1_Y.startbit;
		ADCAN_SP_Accel_1_Z.value = (Val & ~(jk_pow(ADCAN_SP_Accel_1_Z.startbit)-1) & ((jk_pow(ADCAN_SP_Accel_1_Z.countOfBits)-1) << ADCAN_SP_Accel_1_Z.startbit)) >> ADCAN_SP_Accel_1_Z.startbit;
	}
	STOS_CAN_PDU_Acceleration_1() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Accel_1_X.countOfBits + ADCAN_SP_Accel_1_Y.countOfBits + ADCAN_SP_Accel_1_Z.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Accel_1_X.build() | ADCAN_SP_Accel_1_Y.build() | ADCAN_SP_Accel_1_Z.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Acceleration_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x151;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Z = {0, 16, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Accel_2_X.value = (Val & ~(jk_pow(ADCAN_SP_Accel_2_X.startbit)-1) & ((jk_pow(ADCAN_SP_Accel_2_X.countOfBits)-1) << ADCAN_SP_Accel_2_X.startbit)) >> ADCAN_SP_Accel_2_X.startbit;
		ADCAN_SP_Accel_2_Y.value = (Val & ~(jk_pow(ADCAN_SP_Accel_2_Y.startbit)-1) & ((jk_pow(ADCAN_SP_Accel_2_Y.countOfBits)-1) << ADCAN_SP_Accel_2_Y.startbit)) >> ADCAN_SP_Accel_2_Y.startbit;
		ADCAN_SP_Accel_2_Z.value = (Val & ~(jk_pow(ADCAN_SP_Accel_2_Z.startbit)-1) & ((jk_pow(ADCAN_SP_Accel_2_Z.countOfBits)-1) << ADCAN_SP_Accel_2_Z.startbit)) >> ADCAN_SP_Accel_2_Z.startbit;
	}
	STOS_CAN_PDU_Acceleration_2() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Accel_2_X.countOfBits + ADCAN_SP_Accel_2_Y.countOfBits + ADCAN_SP_Accel_2_Z.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Accel_2_X.build() | ADCAN_SP_Accel_2_Y.build() | ADCAN_SP_Accel_2_Z.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Aero_Fan_PWM : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x157;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_AE_Fan_L_PWM = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_AE_Fan_R_PWM = {0, 8, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_AE_Fan_L_PWM.value = (Val & ~(jk_pow(ADCAN_AE_Fan_L_PWM.startbit)-1) & ((jk_pow(ADCAN_AE_Fan_L_PWM.countOfBits)-1) << ADCAN_AE_Fan_L_PWM.startbit)) >> ADCAN_AE_Fan_L_PWM.startbit;
		ADCAN_AE_Fan_R_PWM.value = (Val & ~(jk_pow(ADCAN_AE_Fan_R_PWM.startbit)-1) & ((jk_pow(ADCAN_AE_Fan_R_PWM.countOfBits)-1) << ADCAN_AE_Fan_R_PWM.startbit)) >> ADCAN_AE_Fan_R_PWM.startbit;
	}
	STOS_CAN_PDU_Aero_Fan_PWM() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Fan_L_PWM.countOfBits + ADCAN_AE_Fan_R_PWM.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Fan_L_PWM.build() | ADCAN_AE_Fan_R_PWM.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Aero_Fan_Telemetry : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x158;
	uint16_t _size;
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_1 = {0, 32, 24};//init,bitcount,startbit 
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_2 = {0, 32, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_AE_Fan_Telemetry_1.value = (Val & ~(jk_pow(ADCAN_AE_Fan_Telemetry_1.startbit)-1) & ((jk_pow(ADCAN_AE_Fan_Telemetry_1.countOfBits)-1) << ADCAN_AE_Fan_Telemetry_1.startbit)) >> ADCAN_AE_Fan_Telemetry_1.startbit;
		ADCAN_AE_Fan_Telemetry_2.value = (Val & ~(jk_pow(ADCAN_AE_Fan_Telemetry_2.startbit)-1) & ((jk_pow(ADCAN_AE_Fan_Telemetry_2.countOfBits)-1) << ADCAN_AE_Fan_Telemetry_2.startbit)) >> ADCAN_AE_Fan_Telemetry_2.startbit;
	}
	STOS_CAN_PDU_Aero_Fan_Telemetry() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Fan_Telemetry_1.countOfBits + ADCAN_AE_Fan_Telemetry_2.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Fan_Telemetry_1.build() | ADCAN_AE_Fan_Telemetry_2.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Aero_Fan_Warnings : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x105;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_AE_Warnings = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_AE_Warnings.value = (Val & ~(jk_pow(ADCAN_AE_Warnings.startbit)-1) & ((jk_pow(ADCAN_AE_Warnings.countOfBits)-1) << ADCAN_AE_Warnings.startbit)) >> ADCAN_AE_Warnings.startbit;
	}
	STOS_CAN_PDU_Aero_Fan_Warnings() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Warnings.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Warnings.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Airbox_Position : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x200;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Airbox_Pos = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_PT_Airbox_Pos.value = (Val & ~(jk_pow(ADCAN_PT_Airbox_Pos.startbit)-1) & ((jk_pow(ADCAN_PT_Airbox_Pos.countOfBits)-1) << ADCAN_PT_Airbox_Pos.startbit)) >> ADCAN_PT_Airbox_Pos.startbit;
	}
	STOS_CAN_PDU_Airbox_Position() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Airbox_Pos.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Airbox_Pos.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_ARH_Homing : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x201;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_Homing = {0, 1, 7};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_Homing = {0, 1, 6};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_ARH_1_Homing.value = (Val & ~(jk_pow(ADCAN_SP_ARH_1_Homing.startbit)-1) & ((jk_pow(ADCAN_SP_ARH_1_Homing.countOfBits)-1) << ADCAN_SP_ARH_1_Homing.startbit)) >> ADCAN_SP_ARH_1_Homing.startbit;
		ADCAN_SP_ARH_2_Homing.value = (Val & ~(jk_pow(ADCAN_SP_ARH_2_Homing.startbit)-1) & ((jk_pow(ADCAN_SP_ARH_2_Homing.countOfBits)-1) << ADCAN_SP_ARH_2_Homing.startbit)) >> ADCAN_SP_ARH_2_Homing.startbit;
	}
	STOS_CAN_PDU_ARH_Homing() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_ARH_1_Homing.countOfBits + ADCAN_SP_ARH_2_Homing.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_ARH_1_Homing.build() | ADCAN_SP_ARH_2_Homing.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_ARH_PWM : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x160;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_PWM = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_PWM = {0, 8, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_ARH_1_PWM.value = (Val & ~(jk_pow(ADCAN_SP_ARH_1_PWM.startbit)-1) & ((jk_pow(ADCAN_SP_ARH_1_PWM.countOfBits)-1) << ADCAN_SP_ARH_1_PWM.startbit)) >> ADCAN_SP_ARH_1_PWM.startbit;
		ADCAN_SP_ARH_2_PWM.value = (Val & ~(jk_pow(ADCAN_SP_ARH_2_PWM.startbit)-1) & ((jk_pow(ADCAN_SP_ARH_2_PWM.countOfBits)-1) << ADCAN_SP_ARH_2_PWM.startbit)) >> ADCAN_SP_ARH_2_PWM.startbit;
	}
	STOS_CAN_PDU_ARH_PWM() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_ARH_1_PWM.countOfBits + ADCAN_SP_ARH_2_PWM.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_ARH_1_PWM.build() | ADCAN_SP_ARH_2_PWM.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Battery_Temp_48V : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x203;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_3 = {0, 8, 16};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_Battery_48V_Temp_1.value = (Val & ~(jk_pow(ADCAN_EL_Battery_48V_Temp_1.startbit)-1) & ((jk_pow(ADCAN_EL_Battery_48V_Temp_1.countOfBits)-1) << ADCAN_EL_Battery_48V_Temp_1.startbit)) >> ADCAN_EL_Battery_48V_Temp_1.startbit;
		ADCAN_EL_Battery_48V_Temp_2.value = (Val & ~(jk_pow(ADCAN_EL_Battery_48V_Temp_2.startbit)-1) & ((jk_pow(ADCAN_EL_Battery_48V_Temp_2.countOfBits)-1) << ADCAN_EL_Battery_48V_Temp_2.startbit)) >> ADCAN_EL_Battery_48V_Temp_2.startbit;
		ADCAN_EL_Battery_48V_Temp_3.value = (Val & ~(jk_pow(ADCAN_EL_Battery_48V_Temp_3.startbit)-1) & ((jk_pow(ADCAN_EL_Battery_48V_Temp_3.countOfBits)-1) << ADCAN_EL_Battery_48V_Temp_3.startbit)) >> ADCAN_EL_Battery_48V_Temp_3.startbit;
	}
	STOS_CAN_PDU_Battery_Temp_48V() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_Battery_48V_Temp_1.countOfBits + ADCAN_EL_Battery_48V_Temp_2.countOfBits + ADCAN_EL_Battery_48V_Temp_3.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_Battery_48V_Temp_1.build() | ADCAN_EL_Battery_48V_Temp_2.build() | ADCAN_EL_Battery_48V_Temp_3.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Brake_Disc_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x205;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_FL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_FR = {0, 16, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Brake_Disc_Temp_FL.value = (Val & ~(jk_pow(ADCAN_SP_Brake_Disc_Temp_FL.startbit)-1) & ((jk_pow(ADCAN_SP_Brake_Disc_Temp_FL.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_FL.startbit)) >> ADCAN_SP_Brake_Disc_Temp_FL.startbit;
		ADCAN_SP_Brake_Disc_Temp_FR.value = (Val & ~(jk_pow(ADCAN_SP_Brake_Disc_Temp_FR.startbit)-1) & ((jk_pow(ADCAN_SP_Brake_Disc_Temp_FR.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_FR.startbit)) >> ADCAN_SP_Brake_Disc_Temp_FR.startbit;
	}
	STOS_CAN_PDU_Brake_Disc_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Brake_Disc_Temp_FL.countOfBits + ADCAN_SP_Brake_Disc_Temp_FR.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Brake_Disc_Temp_FL.build() | ADCAN_SP_Brake_Disc_Temp_FR.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Brake_Disc_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x206;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_RL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_RR = {0, 16, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Brake_Disc_Temp_RL.value = (Val & ~(jk_pow(ADCAN_SP_Brake_Disc_Temp_RL.startbit)-1) & ((jk_pow(ADCAN_SP_Brake_Disc_Temp_RL.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_RL.startbit)) >> ADCAN_SP_Brake_Disc_Temp_RL.startbit;
		ADCAN_SP_Brake_Disc_Temp_RR.value = (Val & ~(jk_pow(ADCAN_SP_Brake_Disc_Temp_RR.startbit)-1) & ((jk_pow(ADCAN_SP_Brake_Disc_Temp_RR.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_RR.startbit)) >> ADCAN_SP_Brake_Disc_Temp_RR.startbit;
	}
	STOS_CAN_PDU_Brake_Disc_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Brake_Disc_Temp_RL.countOfBits + ADCAN_SP_Brake_Disc_Temp_RR.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Brake_Disc_Temp_RL.build() | ADCAN_SP_Brake_Disc_Temp_RR.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Brake_Pressure : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x155;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Pressure_Front = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Pressure_Rear = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Bias = {0, 8, 32};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Brake_Pressure_Front.value = (Val & ~(jk_pow(ADCAN_SP_Brake_Pressure_Front.startbit)-1) & ((jk_pow(ADCAN_SP_Brake_Pressure_Front.countOfBits)-1) << ADCAN_SP_Brake_Pressure_Front.startbit)) >> ADCAN_SP_Brake_Pressure_Front.startbit;
		ADCAN_SP_Brake_Pressure_Rear.value = (Val & ~(jk_pow(ADCAN_SP_Brake_Pressure_Rear.startbit)-1) & ((jk_pow(ADCAN_SP_Brake_Pressure_Rear.countOfBits)-1) << ADCAN_SP_Brake_Pressure_Rear.startbit)) >> ADCAN_SP_Brake_Pressure_Rear.startbit;
		ADCAN_SP_Brake_Bias.value = (Val & ~(jk_pow(ADCAN_SP_Brake_Bias.startbit)-1) & ((jk_pow(ADCAN_SP_Brake_Bias.countOfBits)-1) << ADCAN_SP_Brake_Bias.startbit)) >> ADCAN_SP_Brake_Bias.startbit;
	}
	STOS_CAN_PDU_Brake_Pressure() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Brake_Pressure_Front.countOfBits + ADCAN_SP_Brake_Pressure_Rear.countOfBits + ADCAN_SP_Brake_Bias.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Brake_Pressure_Front.build() | ADCAN_SP_Brake_Pressure_Rear.build() | ADCAN_SP_Brake_Bias.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Current_Sensors : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x208;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_8 = {0, 8, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_Current_Sensor_1.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_1.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_1.countOfBits)-1) << ADCAN_EL_Current_Sensor_1.startbit)) >> ADCAN_EL_Current_Sensor_1.startbit;
		ADCAN_EL_Current_Sensor_2.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_2.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_2.countOfBits)-1) << ADCAN_EL_Current_Sensor_2.startbit)) >> ADCAN_EL_Current_Sensor_2.startbit;
		ADCAN_EL_Current_Sensor_3.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_3.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_3.countOfBits)-1) << ADCAN_EL_Current_Sensor_3.startbit)) >> ADCAN_EL_Current_Sensor_3.startbit;
		ADCAN_EL_Current_Sensor_4.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_4.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_4.countOfBits)-1) << ADCAN_EL_Current_Sensor_4.startbit)) >> ADCAN_EL_Current_Sensor_4.startbit;
		ADCAN_EL_Current_Sensor_5.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_5.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_5.countOfBits)-1) << ADCAN_EL_Current_Sensor_5.startbit)) >> ADCAN_EL_Current_Sensor_5.startbit;
		ADCAN_EL_Current_Sensor_6.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_6.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_6.countOfBits)-1) << ADCAN_EL_Current_Sensor_6.startbit)) >> ADCAN_EL_Current_Sensor_6.startbit;
		ADCAN_EL_Current_Sensor_7.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_7.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_7.countOfBits)-1) << ADCAN_EL_Current_Sensor_7.startbit)) >> ADCAN_EL_Current_Sensor_7.startbit;
		ADCAN_EL_Current_Sensor_8.value = (Val & ~(jk_pow(ADCAN_EL_Current_Sensor_8.startbit)-1) & ((jk_pow(ADCAN_EL_Current_Sensor_8.countOfBits)-1) << ADCAN_EL_Current_Sensor_8.startbit)) >> ADCAN_EL_Current_Sensor_8.startbit;
	}
	STOS_CAN_PDU_Current_Sensors() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_Current_Sensor_1.countOfBits + ADCAN_EL_Current_Sensor_2.countOfBits + ADCAN_EL_Current_Sensor_3.countOfBits + ADCAN_EL_Current_Sensor_4.countOfBits + ADCAN_EL_Current_Sensor_5.countOfBits + ADCAN_EL_Current_Sensor_6.countOfBits + ADCAN_EL_Current_Sensor_7.countOfBits + ADCAN_EL_Current_Sensor_8.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_Current_Sensor_1.build() | ADCAN_EL_Current_Sensor_2.build() | ADCAN_EL_Current_Sensor_3.build() | ADCAN_EL_Current_Sensor_4.build() | ADCAN_EL_Current_Sensor_5.build() | ADCAN_EL_Current_Sensor_6.build() | ADCAN_EL_Current_Sensor_7.build() | ADCAN_EL_Current_Sensor_8.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_FCU_ECU_Bat_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x210;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_24V_Temp = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_1 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_2 = {0, 8, 16};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_Battery_24V_Temp.value = (Val & ~(jk_pow(ADCAN_EL_Battery_24V_Temp.startbit)-1) & ((jk_pow(ADCAN_EL_Battery_24V_Temp.countOfBits)-1) << ADCAN_EL_Battery_24V_Temp.startbit)) >> ADCAN_EL_Battery_24V_Temp.startbit;
		ADCAN_EL_ECU_Temp_FCU_1.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_FCU_1.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_FCU_1.countOfBits)-1) << ADCAN_EL_ECU_Temp_FCU_1.startbit)) >> ADCAN_EL_ECU_Temp_FCU_1.startbit;
		ADCAN_EL_ECU_Temp_FCU_2.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_FCU_2.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_FCU_2.countOfBits)-1) << ADCAN_EL_ECU_Temp_FCU_2.startbit)) >> ADCAN_EL_ECU_Temp_FCU_2.startbit;
	}
	STOS_CAN_PDU_FCU_ECU_Bat_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_Battery_24V_Temp.countOfBits + ADCAN_EL_ECU_Temp_FCU_1.countOfBits + ADCAN_EL_ECU_Temp_FCU_2.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_Battery_24V_Temp.build() | ADCAN_EL_ECU_Temp_FCU_1.build() | ADCAN_EL_ECU_Temp_FCU_2.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_FCU_Switches : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x212;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_ARB_Switch = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Activated = {0, 1, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Switch = {0, 8, 31};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Switch = {0, 8, 16};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_ARB_Switch.value = (Val & ~(jk_pow(ADCAN_SP_ARB_Switch.startbit)-1) & ((jk_pow(ADCAN_SP_ARB_Switch.countOfBits)-1) << ADCAN_SP_ARB_Switch.startbit)) >> ADCAN_SP_ARB_Switch.startbit;
		ADCAN_SP_LaunchC_Activated.value = (Val & ~(jk_pow(ADCAN_SP_LaunchC_Activated.startbit)-1) & ((jk_pow(ADCAN_SP_LaunchC_Activated.countOfBits)-1) << ADCAN_SP_LaunchC_Activated.startbit)) >> ADCAN_SP_LaunchC_Activated.startbit;
		ADCAN_SP_LaunchC_Switch.value = (Val & ~(jk_pow(ADCAN_SP_LaunchC_Switch.startbit)-1) & ((jk_pow(ADCAN_SP_LaunchC_Switch.countOfBits)-1) << ADCAN_SP_LaunchC_Switch.startbit)) >> ADCAN_SP_LaunchC_Switch.startbit;
		ADCAN_SP_RAS_Switch.value = (Val & ~(jk_pow(ADCAN_SP_RAS_Switch.startbit)-1) & ((jk_pow(ADCAN_SP_RAS_Switch.countOfBits)-1) << ADCAN_SP_RAS_Switch.startbit)) >> ADCAN_SP_RAS_Switch.startbit;
	}
	STOS_CAN_PDU_FCU_Switches() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_ARB_Switch.countOfBits + ADCAN_SP_LaunchC_Activated.countOfBits + ADCAN_SP_LaunchC_Switch.countOfBits + ADCAN_SP_RAS_Switch.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_ARB_Switch.build() | ADCAN_SP_LaunchC_Activated.build() | ADCAN_SP_LaunchC_Switch.build() | ADCAN_SP_RAS_Switch.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_FDS_Parameters : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x215;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Friction_LC = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_mue_max = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Swim_VDE = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_FDS_Velo_VDE = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RL = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RR = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Yaw_VDE = {0, 8, 32};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_FDS_Friction_LC.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Friction_LC.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Friction_LC.countOfBits)-1) << ADCAN_SP_FDS_Friction_LC.startbit)) >> ADCAN_SP_FDS_Friction_LC.startbit;
		ADCAN_SP_FDS_Slip_mue_max.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Slip_mue_max.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Slip_mue_max.countOfBits)-1) << ADCAN_SP_FDS_Slip_mue_max.startbit)) >> ADCAN_SP_FDS_Slip_mue_max.startbit;
		ADCAN_SP_FDS_Swim_VDE.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Swim_VDE.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Swim_VDE.countOfBits)-1) << ADCAN_SP_FDS_Swim_VDE.startbit)) >> ADCAN_SP_FDS_Swim_VDE.startbit;
		ADCAN_SP_FDS_Velo_VDE.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Velo_VDE.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Velo_VDE.countOfBits)-1) << ADCAN_SP_FDS_Velo_VDE.startbit)) >> ADCAN_SP_FDS_Velo_VDE.startbit;
		ADCAN_SP_FDS_Wheel_Slip_RL.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Wheel_Slip_RL.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Wheel_Slip_RL.countOfBits)-1) << ADCAN_SP_FDS_Wheel_Slip_RL.startbit)) >> ADCAN_SP_FDS_Wheel_Slip_RL.startbit;
		ADCAN_SP_FDS_Wheel_Slip_RR.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Wheel_Slip_RR.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Wheel_Slip_RR.countOfBits)-1) << ADCAN_SP_FDS_Wheel_Slip_RR.startbit)) >> ADCAN_SP_FDS_Wheel_Slip_RR.startbit;
		ADCAN_SP_FDS_Yaw_VDE.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Yaw_VDE.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Yaw_VDE.countOfBits)-1) << ADCAN_SP_FDS_Yaw_VDE.startbit)) >> ADCAN_SP_FDS_Yaw_VDE.startbit;
	}
	STOS_CAN_PDU_FDS_Parameters() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_FDS_Friction_LC.countOfBits + ADCAN_SP_FDS_Slip_mue_max.countOfBits + ADCAN_SP_FDS_Swim_VDE.countOfBits + ADCAN_SP_FDS_Velo_VDE.countOfBits + ADCAN_SP_FDS_Wheel_Slip_RL.countOfBits + ADCAN_SP_FDS_Wheel_Slip_RR.countOfBits + ADCAN_SP_FDS_Yaw_VDE.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_FDS_Friction_LC.build() | ADCAN_SP_FDS_Slip_mue_max.build() | ADCAN_SP_FDS_Swim_VDE.build() | ADCAN_SP_FDS_Velo_VDE.build() | ADCAN_SP_FDS_Wheel_Slip_RL.build() | ADCAN_SP_FDS_Wheel_Slip_RR.build() | ADCAN_SP_FDS_Yaw_VDE.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_FDS_Wheel_Signals : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x216;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FL = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FR = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RL = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RR = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FL = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FR = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RL = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RR = {0, 8, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_FDS_Slip_Angle_FL.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Slip_Angle_FL.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Slip_Angle_FL.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_FL.startbit)) >> ADCAN_SP_FDS_Slip_Angle_FL.startbit;
		ADCAN_SP_FDS_Slip_Angle_FR.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Slip_Angle_FR.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Slip_Angle_FR.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_FR.startbit)) >> ADCAN_SP_FDS_Slip_Angle_FR.startbit;
		ADCAN_SP_FDS_Slip_Angle_RL.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Slip_Angle_RL.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Slip_Angle_RL.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_RL.startbit)) >> ADCAN_SP_FDS_Slip_Angle_RL.startbit;
		ADCAN_SP_FDS_Slip_Angle_RR.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Slip_Angle_RR.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Slip_Angle_RR.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_RR.startbit)) >> ADCAN_SP_FDS_Slip_Angle_RR.startbit;
		ADCAN_SP_FDS_Whl_Load_FL.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Whl_Load_FL.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Whl_Load_FL.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_FL.startbit)) >> ADCAN_SP_FDS_Whl_Load_FL.startbit;
		ADCAN_SP_FDS_Whl_Load_FR.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Whl_Load_FR.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Whl_Load_FR.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_FR.startbit)) >> ADCAN_SP_FDS_Whl_Load_FR.startbit;
		ADCAN_SP_FDS_Whl_Load_RL.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Whl_Load_RL.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Whl_Load_RL.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_RL.startbit)) >> ADCAN_SP_FDS_Whl_Load_RL.startbit;
		ADCAN_SP_FDS_Whl_Load_RR.value = (Val & ~(jk_pow(ADCAN_SP_FDS_Whl_Load_RR.startbit)-1) & ((jk_pow(ADCAN_SP_FDS_Whl_Load_RR.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_RR.startbit)) >> ADCAN_SP_FDS_Whl_Load_RR.startbit;
	}
	STOS_CAN_PDU_FDS_Wheel_Signals() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_FDS_Slip_Angle_FL.countOfBits + ADCAN_SP_FDS_Slip_Angle_FR.countOfBits + ADCAN_SP_FDS_Slip_Angle_RL.countOfBits + ADCAN_SP_FDS_Slip_Angle_RR.countOfBits + ADCAN_SP_FDS_Whl_Load_FL.countOfBits + ADCAN_SP_FDS_Whl_Load_FR.countOfBits + ADCAN_SP_FDS_Whl_Load_RL.countOfBits + ADCAN_SP_FDS_Whl_Load_RR.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_FDS_Slip_Angle_FL.build() | ADCAN_SP_FDS_Slip_Angle_FR.build() | ADCAN_SP_FDS_Slip_Angle_RL.build() | ADCAN_SP_FDS_Slip_Angle_RR.build() | ADCAN_SP_FDS_Whl_Load_FL.build() | ADCAN_SP_FDS_Whl_Load_FR.build() | ADCAN_SP_FDS_Whl_Load_RL.build() | ADCAN_SP_FDS_Whl_Load_RR.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Flash_Over_Can : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x222;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_FoC_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_FoC_2 = {0, 8, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_FoC_1.value = (Val & ~(jk_pow(ADCAN_EL_FoC_1.startbit)-1) & ((jk_pow(ADCAN_EL_FoC_1.countOfBits)-1) << ADCAN_EL_FoC_1.startbit)) >> ADCAN_EL_FoC_1.startbit;
		ADCAN_EL_FoC_2.value = (Val & ~(jk_pow(ADCAN_EL_FoC_2.startbit)-1) & ((jk_pow(ADCAN_EL_FoC_2.countOfBits)-1) << ADCAN_EL_FoC_2.startbit)) >> ADCAN_EL_FoC_2.startbit;
	}
	STOS_CAN_PDU_Flash_Over_Can() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_FoC_1.countOfBits + ADCAN_EL_FoC_2.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_FoC_1.build() | ADCAN_EL_FoC_2.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Frame_Pressure : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x218;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_CH_Frame_Pressure = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_CH_Frame_Pressure.value = (Val & ~(jk_pow(ADCAN_CH_Frame_Pressure.startbit)-1) & ((jk_pow(ADCAN_CH_Frame_Pressure.countOfBits)-1) << ADCAN_CH_Frame_Pressure.startbit)) >> ADCAN_CH_Frame_Pressure.startbit;
	}
	STOS_CAN_PDU_Frame_Pressure() 
	{
		ID = _id;
		uint8_t temp = ADCAN_CH_Frame_Pressure.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_CH_Frame_Pressure.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Gyroscope_1 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x152;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Z = {0, 16, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Gyro_1_X.value = (Val & ~(jk_pow(ADCAN_SP_Gyro_1_X.startbit)-1) & ((jk_pow(ADCAN_SP_Gyro_1_X.countOfBits)-1) << ADCAN_SP_Gyro_1_X.startbit)) >> ADCAN_SP_Gyro_1_X.startbit;
		ADCAN_SP_Gyro_1_Y.value = (Val & ~(jk_pow(ADCAN_SP_Gyro_1_Y.startbit)-1) & ((jk_pow(ADCAN_SP_Gyro_1_Y.countOfBits)-1) << ADCAN_SP_Gyro_1_Y.startbit)) >> ADCAN_SP_Gyro_1_Y.startbit;
		ADCAN_SP_Gyro_1_Z.value = (Val & ~(jk_pow(ADCAN_SP_Gyro_1_Z.startbit)-1) & ((jk_pow(ADCAN_SP_Gyro_1_Z.countOfBits)-1) << ADCAN_SP_Gyro_1_Z.startbit)) >> ADCAN_SP_Gyro_1_Z.startbit;
	}
	STOS_CAN_PDU_Gyroscope_1() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Gyro_1_X.countOfBits + ADCAN_SP_Gyro_1_Y.countOfBits + ADCAN_SP_Gyro_1_Z.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Gyro_1_X.build() | ADCAN_SP_Gyro_1_Y.build() | ADCAN_SP_Gyro_1_Z.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Gyroscope_2 : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x153;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Z = {0, 16, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Gyro_2_X.value = (Val & ~(jk_pow(ADCAN_SP_Gyro_2_X.startbit)-1) & ((jk_pow(ADCAN_SP_Gyro_2_X.countOfBits)-1) << ADCAN_SP_Gyro_2_X.startbit)) >> ADCAN_SP_Gyro_2_X.startbit;
		ADCAN_SP_Gyro_2_Y.value = (Val & ~(jk_pow(ADCAN_SP_Gyro_2_Y.startbit)-1) & ((jk_pow(ADCAN_SP_Gyro_2_Y.countOfBits)-1) << ADCAN_SP_Gyro_2_Y.startbit)) >> ADCAN_SP_Gyro_2_Y.startbit;
		ADCAN_SP_Gyro_2_Z.value = (Val & ~(jk_pow(ADCAN_SP_Gyro_2_Z.startbit)-1) & ((jk_pow(ADCAN_SP_Gyro_2_Z.countOfBits)-1) << ADCAN_SP_Gyro_2_Z.startbit)) >> ADCAN_SP_Gyro_2_Z.startbit;
	}
	STOS_CAN_PDU_Gyroscope_2() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Gyro_2_X.countOfBits + ADCAN_SP_Gyro_2_Y.countOfBits + ADCAN_SP_Gyro_2_Z.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Gyro_2_X.build() | ADCAN_SP_Gyro_2_Y.build() | ADCAN_SP_Gyro_2_Z.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Niveau_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x111;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Niveau = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Niveau = {0, 8, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_FL_Niveau.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FL_Niveau.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FL_Niveau.countOfBits)-1) << ADCAN_SP_Niveau_FL_Niveau.startbit)) >> ADCAN_SP_Niveau_FL_Niveau.startbit;
		ADCAN_SP_Niveau_FR_Niveau.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FR_Niveau.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FR_Niveau.countOfBits)-1) << ADCAN_SP_Niveau_FR_Niveau.startbit)) >> ADCAN_SP_Niveau_FR_Niveau.startbit;
	}
	STOS_CAN_PDU_Niveau_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_FL_Niveau.countOfBits + ADCAN_SP_Niveau_FR_Niveau.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_FL_Niveau.build() | ADCAN_SP_Niveau_FR_Niveau.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Niveau_Front_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x219;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Error = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Function = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_on_off = {0, 1, 22};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Error = {0, 1, 18};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Function = {0, 8, 21};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_on_off = {0, 1, 20};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_FL_Error.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FL_Error.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FL_Error.countOfBits)-1) << ADCAN_SP_Niveau_FL_Error.startbit)) >> ADCAN_SP_Niveau_FL_Error.startbit;
		ADCAN_SP_Niveau_FL_Function.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FL_Function.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FL_Function.countOfBits)-1) << ADCAN_SP_Niveau_FL_Function.startbit)) >> ADCAN_SP_Niveau_FL_Function.startbit;
		ADCAN_SP_Niveau_FL_on_off.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FL_on_off.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FL_on_off.countOfBits)-1) << ADCAN_SP_Niveau_FL_on_off.startbit)) >> ADCAN_SP_Niveau_FL_on_off.startbit;
		ADCAN_SP_Niveau_FR_Error.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FR_Error.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FR_Error.countOfBits)-1) << ADCAN_SP_Niveau_FR_Error.startbit)) >> ADCAN_SP_Niveau_FR_Error.startbit;
		ADCAN_SP_Niveau_FR_Function.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FR_Function.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FR_Function.countOfBits)-1) << ADCAN_SP_Niveau_FR_Function.startbit)) >> ADCAN_SP_Niveau_FR_Function.startbit;
		ADCAN_SP_Niveau_FR_on_off.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_FR_on_off.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_FR_on_off.countOfBits)-1) << ADCAN_SP_Niveau_FR_on_off.startbit)) >> ADCAN_SP_Niveau_FR_on_off.startbit;
	}
	STOS_CAN_PDU_Niveau_Front_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_FL_Error.countOfBits + ADCAN_SP_Niveau_FL_Function.countOfBits + ADCAN_SP_Niveau_FL_on_off.countOfBits + ADCAN_SP_Niveau_FR_Error.countOfBits + ADCAN_SP_Niveau_FR_Function.countOfBits + ADCAN_SP_Niveau_FR_on_off.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_FL_Error.build() | ADCAN_SP_Niveau_FL_Function.build() | ADCAN_SP_Niveau_FL_on_off.build() | ADCAN_SP_Niveau_FR_Error.build() | ADCAN_SP_Niveau_FR_Function.build() | ADCAN_SP_Niveau_FR_on_off.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Niveau_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x110;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Niveau = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_R_Niveau.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_R_Niveau.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_R_Niveau.countOfBits)-1) << ADCAN_SP_Niveau_R_Niveau.startbit)) >> ADCAN_SP_Niveau_R_Niveau.startbit;
	}
	STOS_CAN_PDU_Niveau_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_R_Niveau.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_R_Niveau.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Niveau_Rear_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x220;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Error = {0, 1, 15};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Function = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Niveau_R_Error.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_R_Error.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_R_Error.countOfBits)-1) << ADCAN_SP_Niveau_R_Error.startbit)) >> ADCAN_SP_Niveau_R_Error.startbit;
		ADCAN_SP_Niveau_R_Function.value = (Val & ~(jk_pow(ADCAN_SP_Niveau_R_Function.startbit)-1) & ((jk_pow(ADCAN_SP_Niveau_R_Function.countOfBits)-1) << ADCAN_SP_Niveau_R_Function.startbit)) >> ADCAN_SP_Niveau_R_Function.startbit;
	}
	STOS_CAN_PDU_Niveau_Rear_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Niveau_R_Error.countOfBits + ADCAN_SP_Niveau_R_Function.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Niveau_R_Error.build() | ADCAN_SP_Niveau_R_Function.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Oil_Pressure : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x163;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Pressure = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_PT_Oil_Pressure.value = (Val & ~(jk_pow(ADCAN_PT_Oil_Pressure.startbit)-1) & ((jk_pow(ADCAN_PT_Oil_Pressure.countOfBits)-1) << ADCAN_PT_Oil_Pressure.startbit)) >> ADCAN_PT_Oil_Pressure.startbit;
	}
	STOS_CAN_PDU_Oil_Pressure() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Oil_Pressure.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Oil_Pressure.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Oil_Pressure_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x224;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level_RS232 = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Temp = {0, 8, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_PT_Oil_Level.value = (Val & ~(jk_pow(ADCAN_PT_Oil_Level.startbit)-1) & ((jk_pow(ADCAN_PT_Oil_Level.countOfBits)-1) << ADCAN_PT_Oil_Level.startbit)) >> ADCAN_PT_Oil_Level.startbit;
		ADCAN_PT_Oil_Level_RS232.value = (Val & ~(jk_pow(ADCAN_PT_Oil_Level_RS232.startbit)-1) & ((jk_pow(ADCAN_PT_Oil_Level_RS232.countOfBits)-1) << ADCAN_PT_Oil_Level_RS232.startbit)) >> ADCAN_PT_Oil_Level_RS232.startbit;
		ADCAN_PT_Oil_Temp.value = (Val & ~(jk_pow(ADCAN_PT_Oil_Temp.startbit)-1) & ((jk_pow(ADCAN_PT_Oil_Temp.countOfBits)-1) << ADCAN_PT_Oil_Temp.startbit)) >> ADCAN_PT_Oil_Temp.startbit;
	}
	STOS_CAN_PDU_Oil_Pressure_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Oil_Level.countOfBits + ADCAN_PT_Oil_Level_RS232.countOfBits + ADCAN_PT_Oil_Temp.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Oil_Level.build() | ADCAN_PT_Oil_Level_RS232.build() | ADCAN_PT_Oil_Temp.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_PDU_ECU_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x230;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_4 = {0, 8, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_PDU_1.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_PDU_1.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_PDU_1.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_1.startbit)) >> ADCAN_EL_ECU_Temp_PDU_1.startbit;
		ADCAN_EL_ECU_Temp_PDU_2.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_PDU_2.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_PDU_2.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_2.startbit)) >> ADCAN_EL_ECU_Temp_PDU_2.startbit;
		ADCAN_EL_ECU_Temp_PDU_3.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_PDU_3.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_PDU_3.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_3.startbit)) >> ADCAN_EL_ECU_Temp_PDU_3.startbit;
		ADCAN_EL_ECU_Temp_PDU_4.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_PDU_4.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_PDU_4.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_4.startbit)) >> ADCAN_EL_ECU_Temp_PDU_4.startbit;
	}
	STOS_CAN_PDU_PDU_ECU_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_ECU_Temp_PDU_1.countOfBits + ADCAN_EL_ECU_Temp_PDU_2.countOfBits + ADCAN_EL_ECU_Temp_PDU_3.countOfBits + ADCAN_EL_ECU_Temp_PDU_4.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_ECU_Temp_PDU_1.build() | ADCAN_EL_ECU_Temp_PDU_2.build() | ADCAN_EL_ECU_Temp_PDU_3.build() | ADCAN_EL_ECU_Temp_PDU_4.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_PDU_Status : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x226;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_CH_Mainhoop_Diag_L_1 = {0, 1, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_CH_Mainhoop_Diag_R_1 = {0, 1, 1};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_BOTS_Diag_1 = {0, 1, 2};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_BSPD_Shutdown_Out = {0, 1, 3};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Cockpit_Diag_1 = {0, 1, 4};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Crash_Diag = {0, 1, 5};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_1 = {0, 1, 6};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_10 = {0, 1, 7};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_11 = {0, 1, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_12 = {0, 1, 9};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_13 = {0, 1, 10};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_14 = {0, 1, 11};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_15 = {0, 1, 12};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_16 = {0, 1, 13};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_17 = {0, 1, 14};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_18 = {0, 1, 15};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_19 = {0, 1, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_2 = {0, 1, 17};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_3 = {0, 1, 18};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_4 = {0, 1, 19};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_5 = {0, 1, 20};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_6 = {0, 1, 21};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_7 = {0, 1, 22};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_8 = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Fuse_Status_9 = {0, 1, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Relais_Status_1 = {0, 1, 25};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Relais_Status_2 = {0, 1, 26};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Shutdown_Cockpit = {0, 1, 27};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Fuel_Pump_Signal = {0, 1, 28};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Reserve_Signal_L = {0, 1, 29};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Reserve_Signal_R = {0, 1, 30};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Pump_Signal = {0, 1, 31};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_CH_Mainhoop_Diag_L_1.value = (Val & ~(jk_pow(ADCAN_CH_Mainhoop_Diag_L_1.startbit)-1) & ((jk_pow(ADCAN_CH_Mainhoop_Diag_L_1.countOfBits)-1) << ADCAN_CH_Mainhoop_Diag_L_1.startbit)) >> ADCAN_CH_Mainhoop_Diag_L_1.startbit;
		ADCAN_CH_Mainhoop_Diag_R_1.value = (Val & ~(jk_pow(ADCAN_CH_Mainhoop_Diag_R_1.startbit)-1) & ((jk_pow(ADCAN_CH_Mainhoop_Diag_R_1.countOfBits)-1) << ADCAN_CH_Mainhoop_Diag_R_1.startbit)) >> ADCAN_CH_Mainhoop_Diag_R_1.startbit;
		ADCAN_EL_BOTS_Diag_1.value = (Val & ~(jk_pow(ADCAN_EL_BOTS_Diag_1.startbit)-1) & ((jk_pow(ADCAN_EL_BOTS_Diag_1.countOfBits)-1) << ADCAN_EL_BOTS_Diag_1.startbit)) >> ADCAN_EL_BOTS_Diag_1.startbit;
		ADCAN_EL_BSPD_Shutdown_Out.value = (Val & ~(jk_pow(ADCAN_EL_BSPD_Shutdown_Out.startbit)-1) & ((jk_pow(ADCAN_EL_BSPD_Shutdown_Out.countOfBits)-1) << ADCAN_EL_BSPD_Shutdown_Out.startbit)) >> ADCAN_EL_BSPD_Shutdown_Out.startbit;
		ADCAN_EL_Cockpit_Diag_1.value = (Val & ~(jk_pow(ADCAN_EL_Cockpit_Diag_1.startbit)-1) & ((jk_pow(ADCAN_EL_Cockpit_Diag_1.countOfBits)-1) << ADCAN_EL_Cockpit_Diag_1.startbit)) >> ADCAN_EL_Cockpit_Diag_1.startbit;
		ADCAN_EL_Crash_Diag.value = (Val & ~(jk_pow(ADCAN_EL_Crash_Diag.startbit)-1) & ((jk_pow(ADCAN_EL_Crash_Diag.countOfBits)-1) << ADCAN_EL_Crash_Diag.startbit)) >> ADCAN_EL_Crash_Diag.startbit;
		ADCAN_EL_Fuse_Status_1.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_1.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_1.countOfBits)-1) << ADCAN_EL_Fuse_Status_1.startbit)) >> ADCAN_EL_Fuse_Status_1.startbit;
		ADCAN_EL_Fuse_Status_10.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_10.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_10.countOfBits)-1) << ADCAN_EL_Fuse_Status_10.startbit)) >> ADCAN_EL_Fuse_Status_10.startbit;
		ADCAN_EL_Fuse_Status_11.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_11.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_11.countOfBits)-1) << ADCAN_EL_Fuse_Status_11.startbit)) >> ADCAN_EL_Fuse_Status_11.startbit;
		ADCAN_EL_Fuse_Status_12.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_12.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_12.countOfBits)-1) << ADCAN_EL_Fuse_Status_12.startbit)) >> ADCAN_EL_Fuse_Status_12.startbit;
		ADCAN_EL_Fuse_Status_13.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_13.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_13.countOfBits)-1) << ADCAN_EL_Fuse_Status_13.startbit)) >> ADCAN_EL_Fuse_Status_13.startbit;
		ADCAN_EL_Fuse_Status_14.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_14.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_14.countOfBits)-1) << ADCAN_EL_Fuse_Status_14.startbit)) >> ADCAN_EL_Fuse_Status_14.startbit;
		ADCAN_EL_Fuse_Status_15.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_15.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_15.countOfBits)-1) << ADCAN_EL_Fuse_Status_15.startbit)) >> ADCAN_EL_Fuse_Status_15.startbit;
		ADCAN_EL_Fuse_Status_16.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_16.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_16.countOfBits)-1) << ADCAN_EL_Fuse_Status_16.startbit)) >> ADCAN_EL_Fuse_Status_16.startbit;
		ADCAN_EL_Fuse_Status_17.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_17.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_17.countOfBits)-1) << ADCAN_EL_Fuse_Status_17.startbit)) >> ADCAN_EL_Fuse_Status_17.startbit;
		ADCAN_EL_Fuse_Status_18.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_18.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_18.countOfBits)-1) << ADCAN_EL_Fuse_Status_18.startbit)) >> ADCAN_EL_Fuse_Status_18.startbit;
		ADCAN_EL_Fuse_Status_19.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_19.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_19.countOfBits)-1) << ADCAN_EL_Fuse_Status_19.startbit)) >> ADCAN_EL_Fuse_Status_19.startbit;
		ADCAN_EL_Fuse_Status_2.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_2.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_2.countOfBits)-1) << ADCAN_EL_Fuse_Status_2.startbit)) >> ADCAN_EL_Fuse_Status_2.startbit;
		ADCAN_EL_Fuse_Status_3.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_3.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_3.countOfBits)-1) << ADCAN_EL_Fuse_Status_3.startbit)) >> ADCAN_EL_Fuse_Status_3.startbit;
		ADCAN_EL_Fuse_Status_4.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_4.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_4.countOfBits)-1) << ADCAN_EL_Fuse_Status_4.startbit)) >> ADCAN_EL_Fuse_Status_4.startbit;
		ADCAN_EL_Fuse_Status_5.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_5.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_5.countOfBits)-1) << ADCAN_EL_Fuse_Status_5.startbit)) >> ADCAN_EL_Fuse_Status_5.startbit;
		ADCAN_EL_Fuse_Status_6.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_6.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_6.countOfBits)-1) << ADCAN_EL_Fuse_Status_6.startbit)) >> ADCAN_EL_Fuse_Status_6.startbit;
		ADCAN_EL_Fuse_Status_7.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_7.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_7.countOfBits)-1) << ADCAN_EL_Fuse_Status_7.startbit)) >> ADCAN_EL_Fuse_Status_7.startbit;
		ADCAN_EL_Fuse_Status_8.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_8.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_8.countOfBits)-1) << ADCAN_EL_Fuse_Status_8.startbit)) >> ADCAN_EL_Fuse_Status_8.startbit;
		ADCAN_EL_Fuse_Status_9.value = (Val & ~(jk_pow(ADCAN_EL_Fuse_Status_9.startbit)-1) & ((jk_pow(ADCAN_EL_Fuse_Status_9.countOfBits)-1) << ADCAN_EL_Fuse_Status_9.startbit)) >> ADCAN_EL_Fuse_Status_9.startbit;
		ADCAN_EL_Relais_Status_1.value = (Val & ~(jk_pow(ADCAN_EL_Relais_Status_1.startbit)-1) & ((jk_pow(ADCAN_EL_Relais_Status_1.countOfBits)-1) << ADCAN_EL_Relais_Status_1.startbit)) >> ADCAN_EL_Relais_Status_1.startbit;
		ADCAN_EL_Relais_Status_2.value = (Val & ~(jk_pow(ADCAN_EL_Relais_Status_2.startbit)-1) & ((jk_pow(ADCAN_EL_Relais_Status_2.countOfBits)-1) << ADCAN_EL_Relais_Status_2.startbit)) >> ADCAN_EL_Relais_Status_2.startbit;
		ADCAN_EL_Shutdown_Cockpit.value = (Val & ~(jk_pow(ADCAN_EL_Shutdown_Cockpit.startbit)-1) & ((jk_pow(ADCAN_EL_Shutdown_Cockpit.countOfBits)-1) << ADCAN_EL_Shutdown_Cockpit.startbit)) >> ADCAN_EL_Shutdown_Cockpit.startbit;
		ADCAN_PT_Fuel_Pump_Signal.value = (Val & ~(jk_pow(ADCAN_PT_Fuel_Pump_Signal.startbit)-1) & ((jk_pow(ADCAN_PT_Fuel_Pump_Signal.countOfBits)-1) << ADCAN_PT_Fuel_Pump_Signal.startbit)) >> ADCAN_PT_Fuel_Pump_Signal.startbit;
		ADCAN_PT_Reserve_Signal_L.value = (Val & ~(jk_pow(ADCAN_PT_Reserve_Signal_L.startbit)-1) & ((jk_pow(ADCAN_PT_Reserve_Signal_L.countOfBits)-1) << ADCAN_PT_Reserve_Signal_L.startbit)) >> ADCAN_PT_Reserve_Signal_L.startbit;
		ADCAN_PT_Reserve_Signal_R.value = (Val & ~(jk_pow(ADCAN_PT_Reserve_Signal_R.startbit)-1) & ((jk_pow(ADCAN_PT_Reserve_Signal_R.countOfBits)-1) << ADCAN_PT_Reserve_Signal_R.startbit)) >> ADCAN_PT_Reserve_Signal_R.startbit;
		ADCAN_PT_Water_Pump_Signal.value = (Val & ~(jk_pow(ADCAN_PT_Water_Pump_Signal.startbit)-1) & ((jk_pow(ADCAN_PT_Water_Pump_Signal.countOfBits)-1) << ADCAN_PT_Water_Pump_Signal.startbit)) >> ADCAN_PT_Water_Pump_Signal.startbit;
	}
	STOS_CAN_PDU_PDU_Status() 
	{
		ID = _id;
		uint8_t temp = ADCAN_CH_Mainhoop_Diag_L_1.countOfBits + ADCAN_CH_Mainhoop_Diag_R_1.countOfBits + ADCAN_EL_BOTS_Diag_1.countOfBits + ADCAN_EL_BSPD_Shutdown_Out.countOfBits + ADCAN_EL_Cockpit_Diag_1.countOfBits + ADCAN_EL_Crash_Diag.countOfBits + ADCAN_EL_Fuse_Status_1.countOfBits + ADCAN_EL_Fuse_Status_10.countOfBits + ADCAN_EL_Fuse_Status_11.countOfBits + ADCAN_EL_Fuse_Status_12.countOfBits + ADCAN_EL_Fuse_Status_13.countOfBits + ADCAN_EL_Fuse_Status_14.countOfBits + ADCAN_EL_Fuse_Status_15.countOfBits + ADCAN_EL_Fuse_Status_16.countOfBits + ADCAN_EL_Fuse_Status_17.countOfBits + ADCAN_EL_Fuse_Status_18.countOfBits + ADCAN_EL_Fuse_Status_19.countOfBits + ADCAN_EL_Fuse_Status_2.countOfBits + ADCAN_EL_Fuse_Status_3.countOfBits + ADCAN_EL_Fuse_Status_4.countOfBits + ADCAN_EL_Fuse_Status_5.countOfBits + ADCAN_EL_Fuse_Status_6.countOfBits + ADCAN_EL_Fuse_Status_7.countOfBits + ADCAN_EL_Fuse_Status_8.countOfBits + ADCAN_EL_Fuse_Status_9.countOfBits + ADCAN_EL_Relais_Status_1.countOfBits + ADCAN_EL_Relais_Status_2.countOfBits + ADCAN_EL_Shutdown_Cockpit.countOfBits + ADCAN_PT_Fuel_Pump_Signal.countOfBits + ADCAN_PT_Reserve_Signal_L.countOfBits + ADCAN_PT_Reserve_Signal_R.countOfBits + ADCAN_PT_Water_Pump_Signal.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_CH_Mainhoop_Diag_L_1.build() | ADCAN_CH_Mainhoop_Diag_R_1.build() | ADCAN_EL_BOTS_Diag_1.build() | ADCAN_EL_BSPD_Shutdown_Out.build() | ADCAN_EL_Cockpit_Diag_1.build() | ADCAN_EL_Crash_Diag.build() | ADCAN_EL_Fuse_Status_1.build() | ADCAN_EL_Fuse_Status_10.build() | ADCAN_EL_Fuse_Status_11.build() | ADCAN_EL_Fuse_Status_12.build() | ADCAN_EL_Fuse_Status_13.build() | ADCAN_EL_Fuse_Status_14.build() | ADCAN_EL_Fuse_Status_15.build() | ADCAN_EL_Fuse_Status_16.build() | ADCAN_EL_Fuse_Status_17.build() | ADCAN_EL_Fuse_Status_18.build() | ADCAN_EL_Fuse_Status_19.build() | ADCAN_EL_Fuse_Status_2.build() | ADCAN_EL_Fuse_Status_3.build() | ADCAN_EL_Fuse_Status_4.build() | ADCAN_EL_Fuse_Status_5.build() | ADCAN_EL_Fuse_Status_6.build() | ADCAN_EL_Fuse_Status_7.build() | ADCAN_EL_Fuse_Status_8.build() | ADCAN_EL_Fuse_Status_9.build() | ADCAN_EL_Relais_Status_1.build() | ADCAN_EL_Relais_Status_2.build() | ADCAN_EL_Shutdown_Cockpit.build() | ADCAN_PT_Fuel_Pump_Signal.build() | ADCAN_PT_Reserve_Signal_L.build() | ADCAN_PT_Reserve_Signal_R.build() | ADCAN_PT_Water_Pump_Signal.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Pitot : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x232;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_3 = {0, 16, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_AE_Pitot_1.value = (Val & ~(jk_pow(ADCAN_AE_Pitot_1.startbit)-1) & ((jk_pow(ADCAN_AE_Pitot_1.countOfBits)-1) << ADCAN_AE_Pitot_1.startbit)) >> ADCAN_AE_Pitot_1.startbit;
		ADCAN_AE_Pitot_2.value = (Val & ~(jk_pow(ADCAN_AE_Pitot_2.startbit)-1) & ((jk_pow(ADCAN_AE_Pitot_2.countOfBits)-1) << ADCAN_AE_Pitot_2.startbit)) >> ADCAN_AE_Pitot_2.startbit;
		ADCAN_AE_Pitot_3.value = (Val & ~(jk_pow(ADCAN_AE_Pitot_3.startbit)-1) & ((jk_pow(ADCAN_AE_Pitot_3.countOfBits)-1) << ADCAN_AE_Pitot_3.startbit)) >> ADCAN_AE_Pitot_3.startbit;
	}
	STOS_CAN_PDU_Pitot() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Pitot_1.countOfBits + ADCAN_AE_Pitot_2.countOfBits + ADCAN_AE_Pitot_3.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Pitot_1.build() | ADCAN_AE_Pitot_2.build() | ADCAN_AE_Pitot_3.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_RAS_PWM : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x161;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_L = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_R = {0, 8, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_RAS_PWM_L.value = (Val & ~(jk_pow(ADCAN_SP_RAS_PWM_L.startbit)-1) & ((jk_pow(ADCAN_SP_RAS_PWM_L.countOfBits)-1) << ADCAN_SP_RAS_PWM_L.startbit)) >> ADCAN_SP_RAS_PWM_L.startbit;
		ADCAN_SP_RAS_PWM_R.value = (Val & ~(jk_pow(ADCAN_SP_RAS_PWM_R.startbit)-1) & ((jk_pow(ADCAN_SP_RAS_PWM_R.countOfBits)-1) << ADCAN_SP_RAS_PWM_R.startbit)) >> ADCAN_SP_RAS_PWM_R.startbit;
	}
	STOS_CAN_PDU_RAS_PWM() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_RAS_PWM_L.countOfBits + ADCAN_SP_RAS_PWM_R.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_RAS_PWM_L.build() | ADCAN_SP_RAS_PWM_R.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_RAS_Status_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x234;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Angle = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_L = {0, 1, 15};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_R = {0, 1, 14};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_RAS_Angle.value = (Val & ~(jk_pow(ADCAN_SP_RAS_Angle.startbit)-1) & ((jk_pow(ADCAN_SP_RAS_Angle.countOfBits)-1) << ADCAN_SP_RAS_Angle.startbit)) >> ADCAN_SP_RAS_Angle.startbit;
		ADCAN_SP_RAS_Homing_L.value = (Val & ~(jk_pow(ADCAN_SP_RAS_Homing_L.startbit)-1) & ((jk_pow(ADCAN_SP_RAS_Homing_L.countOfBits)-1) << ADCAN_SP_RAS_Homing_L.startbit)) >> ADCAN_SP_RAS_Homing_L.startbit;
		ADCAN_SP_RAS_Homing_R.value = (Val & ~(jk_pow(ADCAN_SP_RAS_Homing_R.startbit)-1) & ((jk_pow(ADCAN_SP_RAS_Homing_R.countOfBits)-1) << ADCAN_SP_RAS_Homing_R.startbit)) >> ADCAN_SP_RAS_Homing_R.startbit;
	}
	STOS_CAN_PDU_RAS_Status_Control() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_RAS_Angle.countOfBits + ADCAN_SP_RAS_Homing_L.countOfBits + ADCAN_SP_RAS_Homing_R.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_RAS_Angle.build() | ADCAN_SP_RAS_Homing_L.build() | ADCAN_SP_RAS_Homing_R.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_RCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x236;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_2 = {0, 8, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_RCU_1.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_RCU_1.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_RCU_1.countOfBits)-1) << ADCAN_EL_ECU_Temp_RCU_1.startbit)) >> ADCAN_EL_ECU_Temp_RCU_1.startbit;
		ADCAN_EL_ECU_Temp_RCU_2.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_RCU_2.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_RCU_2.countOfBits)-1) << ADCAN_EL_ECU_Temp_RCU_2.startbit)) >> ADCAN_EL_ECU_Temp_RCU_2.startbit;
	}
	STOS_CAN_PDU_RCU_ECU_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_ECU_Temp_RCU_1.countOfBits + ADCAN_EL_ECU_Temp_RCU_2.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_ECU_Temp_RCU_1.build() | ADCAN_EL_ECU_Temp_RCU_2.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_RCU_Test_A : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x165;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_3 = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_4 = {0, 16, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_1.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_1.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_1.countOfBits)-1) << ADCAN_ZZ_Test_RCU_1.startbit)) >> ADCAN_ZZ_Test_RCU_1.startbit;
		ADCAN_ZZ_Test_RCU_2.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_2.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_2.countOfBits)-1) << ADCAN_ZZ_Test_RCU_2.startbit)) >> ADCAN_ZZ_Test_RCU_2.startbit;
		ADCAN_ZZ_Test_RCU_3.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_3.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_3.countOfBits)-1) << ADCAN_ZZ_Test_RCU_3.startbit)) >> ADCAN_ZZ_Test_RCU_3.startbit;
		ADCAN_ZZ_Test_RCU_4.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_4.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_4.countOfBits)-1) << ADCAN_ZZ_Test_RCU_4.startbit)) >> ADCAN_ZZ_Test_RCU_4.startbit;
	}
	STOS_CAN_PDU_RCU_Test_A() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_RCU_1.countOfBits + ADCAN_ZZ_Test_RCU_2.countOfBits + ADCAN_ZZ_Test_RCU_3.countOfBits + ADCAN_ZZ_Test_RCU_4.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_RCU_1.build() | ADCAN_ZZ_Test_RCU_2.build() | ADCAN_ZZ_Test_RCU_3.build() | ADCAN_ZZ_Test_RCU_4.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_RCU_Test_B : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x166;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_5 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_6 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_7 = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_8 = {0, 16, 56};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_5.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_5.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_5.countOfBits)-1) << ADCAN_ZZ_Test_RCU_5.startbit)) >> ADCAN_ZZ_Test_RCU_5.startbit;
		ADCAN_ZZ_Test_RCU_6.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_6.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_6.countOfBits)-1) << ADCAN_ZZ_Test_RCU_6.startbit)) >> ADCAN_ZZ_Test_RCU_6.startbit;
		ADCAN_ZZ_Test_RCU_7.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_7.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_7.countOfBits)-1) << ADCAN_ZZ_Test_RCU_7.startbit)) >> ADCAN_ZZ_Test_RCU_7.startbit;
		ADCAN_ZZ_Test_RCU_8.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_8.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_8.countOfBits)-1) << ADCAN_ZZ_Test_RCU_8.startbit)) >> ADCAN_ZZ_Test_RCU_8.startbit;
	}
	STOS_CAN_PDU_RCU_Test_B() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_RCU_5.countOfBits + ADCAN_ZZ_Test_RCU_6.countOfBits + ADCAN_ZZ_Test_RCU_7.countOfBits + ADCAN_ZZ_Test_RCU_8.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_RCU_5.build() | ADCAN_ZZ_Test_RCU_6.build() | ADCAN_ZZ_Test_RCU_7.build() | ADCAN_ZZ_Test_RCU_8.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_RCU_Test_C : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x167;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_10 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_9 = {0, 16, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_10.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_10.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_10.countOfBits)-1) << ADCAN_ZZ_Test_RCU_10.startbit)) >> ADCAN_ZZ_Test_RCU_10.startbit;
		ADCAN_ZZ_Test_RCU_9.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_RCU_9.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_RCU_9.countOfBits)-1) << ADCAN_ZZ_Test_RCU_9.startbit)) >> ADCAN_ZZ_Test_RCU_9.startbit;
	}
	STOS_CAN_PDU_RCU_Test_C() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_RCU_10.countOfBits + ADCAN_ZZ_Test_RCU_9.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_RCU_10.build() | ADCAN_ZZ_Test_RCU_9.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Rocker_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x238;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_FL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_FR = {0, 16, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Rocker_FL.value = (Val & ~(jk_pow(ADCAN_SP_Rocker_FL.startbit)-1) & ((jk_pow(ADCAN_SP_Rocker_FL.countOfBits)-1) << ADCAN_SP_Rocker_FL.startbit)) >> ADCAN_SP_Rocker_FL.startbit;
		ADCAN_SP_Rocker_FR.value = (Val & ~(jk_pow(ADCAN_SP_Rocker_FR.startbit)-1) & ((jk_pow(ADCAN_SP_Rocker_FR.countOfBits)-1) << ADCAN_SP_Rocker_FR.startbit)) >> ADCAN_SP_Rocker_FR.startbit;
	}
	STOS_CAN_PDU_Rocker_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Rocker_FL.countOfBits + ADCAN_SP_Rocker_FR.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Rocker_FL.build() | ADCAN_SP_Rocker_FR.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Rocker_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x239;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_RL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_RR = {0, 16, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Rocker_RL.value = (Val & ~(jk_pow(ADCAN_SP_Rocker_RL.startbit)-1) & ((jk_pow(ADCAN_SP_Rocker_RL.countOfBits)-1) << ADCAN_SP_Rocker_RL.startbit)) >> ADCAN_SP_Rocker_RL.startbit;
		ADCAN_SP_Rocker_RR.value = (Val & ~(jk_pow(ADCAN_SP_Rocker_RR.startbit)-1) & ((jk_pow(ADCAN_SP_Rocker_RR.countOfBits)-1) << ADCAN_SP_Rocker_RR.startbit)) >> ADCAN_SP_Rocker_RR.startbit;
	}
	STOS_CAN_PDU_Rocker_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Rocker_RL.countOfBits + ADCAN_SP_Rocker_RR.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Rocker_RL.build() | ADCAN_SP_Rocker_RR.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Shift_Clutch : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x170;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_DigIn = {0, 1, 21};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_LaunchC = {0, 1, 20};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_PT_Shift_Force_Sensor = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_DigIn = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_LaunchC = {0, 1, 22};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Force_on_off = {0, 1, 19};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_PT_Gearshift_DigIn.value = (Val & ~(jk_pow(ADCAN_PT_Gearshift_DigIn.startbit)-1) & ((jk_pow(ADCAN_PT_Gearshift_DigIn.countOfBits)-1) << ADCAN_PT_Gearshift_DigIn.startbit)) >> ADCAN_PT_Gearshift_DigIn.startbit;
		ADCAN_PT_Gearshift_LaunchC.value = (Val & ~(jk_pow(ADCAN_PT_Gearshift_LaunchC.startbit)-1) & ((jk_pow(ADCAN_PT_Gearshift_LaunchC.countOfBits)-1) << ADCAN_PT_Gearshift_LaunchC.startbit)) >> ADCAN_PT_Gearshift_LaunchC.startbit;
		ADCAN_PT_Shift_Force_Sensor.value = (Val & ~(jk_pow(ADCAN_PT_Shift_Force_Sensor.startbit)-1) & ((jk_pow(ADCAN_PT_Shift_Force_Sensor.countOfBits)-1) << ADCAN_PT_Shift_Force_Sensor.startbit)) >> ADCAN_PT_Shift_Force_Sensor.startbit;
		ADCAN_SP_Clutch_DigIn.value = (Val & ~(jk_pow(ADCAN_SP_Clutch_DigIn.startbit)-1) & ((jk_pow(ADCAN_SP_Clutch_DigIn.countOfBits)-1) << ADCAN_SP_Clutch_DigIn.startbit)) >> ADCAN_SP_Clutch_DigIn.startbit;
		ADCAN_SP_Clutch_LaunchC.value = (Val & ~(jk_pow(ADCAN_SP_Clutch_LaunchC.startbit)-1) & ((jk_pow(ADCAN_SP_Clutch_LaunchC.countOfBits)-1) << ADCAN_SP_Clutch_LaunchC.startbit)) >> ADCAN_SP_Clutch_LaunchC.startbit;
		ADCAN_PT_Shift_Force_on_off.value = (Val & ~(jk_pow(ADCAN_PT_Shift_Force_on_off.startbit)-1) & ((jk_pow(ADCAN_PT_Shift_Force_on_off.countOfBits)-1) << ADCAN_PT_Shift_Force_on_off.startbit)) >> ADCAN_PT_Shift_Force_on_off.startbit;
	}
	STOS_CAN_PDU_Shift_Clutch() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Gearshift_DigIn.countOfBits + ADCAN_PT_Gearshift_LaunchC.countOfBits + ADCAN_PT_Shift_Force_Sensor.countOfBits + ADCAN_SP_Clutch_DigIn.countOfBits + ADCAN_SP_Clutch_LaunchC.countOfBits + ADCAN_PT_Shift_Force_on_off.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Gearshift_DigIn.build() | ADCAN_PT_Gearshift_LaunchC.build() | ADCAN_PT_Shift_Force_Sensor.build() | ADCAN_SP_Clutch_DigIn.build() | ADCAN_SP_Clutch_LaunchC.build() | ADCAN_PT_Shift_Force_on_off.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Steering_Whl_Angle : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x172;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Steering_Wheel_Angle = {0, 16, 8};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Steering_Wheel_Angle.value = (Val & ~(jk_pow(ADCAN_SP_Steering_Wheel_Angle.startbit)-1) & ((jk_pow(ADCAN_SP_Steering_Wheel_Angle.countOfBits)-1) << ADCAN_SP_Steering_Wheel_Angle.startbit)) >> ADCAN_SP_Steering_Wheel_Angle.startbit;
	}
	STOS_CAN_PDU_Steering_Whl_Angle() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Steering_Wheel_Angle.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Steering_Wheel_Angle.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_SWCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x244;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_SWCU = {0, 8, 0};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_SWCU.value = (Val & ~(jk_pow(ADCAN_EL_ECU_Temp_SWCU.startbit)-1) & ((jk_pow(ADCAN_EL_ECU_Temp_SWCU.countOfBits)-1) << ADCAN_EL_ECU_Temp_SWCU.startbit)) >> ADCAN_EL_ECU_Temp_SWCU.startbit;
	}
	STOS_CAN_PDU_SWCU_ECU_Temp() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_ECU_Temp_SWCU.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_ECU_Temp_SWCU.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_SWCU_Oh_Shit : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x175;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_EL_INCR_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_INCR_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Oh_Shit = {0, 1, 23};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_EL_INCR_1.value = (Val & ~(jk_pow(ADCAN_EL_INCR_1.startbit)-1) & ((jk_pow(ADCAN_EL_INCR_1.countOfBits)-1) << ADCAN_EL_INCR_1.startbit)) >> ADCAN_EL_INCR_1.startbit;
		ADCAN_EL_INCR_2.value = (Val & ~(jk_pow(ADCAN_EL_INCR_2.startbit)-1) & ((jk_pow(ADCAN_EL_INCR_2.countOfBits)-1) << ADCAN_EL_INCR_2.startbit)) >> ADCAN_EL_INCR_2.startbit;
		ADCAN_EL_Oh_Shit.value = (Val & ~(jk_pow(ADCAN_EL_Oh_Shit.startbit)-1) & ((jk_pow(ADCAN_EL_Oh_Shit.countOfBits)-1) << ADCAN_EL_Oh_Shit.startbit)) >> ADCAN_EL_Oh_Shit.startbit;
	}
	STOS_CAN_PDU_SWCU_Oh_Shit() 
	{
		ID = _id;
		uint8_t temp = ADCAN_EL_INCR_1.countOfBits + ADCAN_EL_INCR_2.countOfBits + ADCAN_EL_Oh_Shit.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_EL_INCR_1.build() | ADCAN_EL_INCR_2.build() | ADCAN_EL_Oh_Shit.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_SWCU_Switches : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x099;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_AE_Switch_1 = {0, 1, 2};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Radio_Switch = {0, 1, 3};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Down = {0, 1, 4};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Up = {0, 1, 5};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_switch_1 = {0, 1, 6};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_Signal = {0, 1, 7};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_AE_Switch_1.value = (Val & ~(jk_pow(ADCAN_AE_Switch_1.startbit)-1) & ((jk_pow(ADCAN_AE_Switch_1.countOfBits)-1) << ADCAN_AE_Switch_1.startbit)) >> ADCAN_AE_Switch_1.startbit;
		ADCAN_EL_Radio_Switch.value = (Val & ~(jk_pow(ADCAN_EL_Radio_Switch.startbit)-1) & ((jk_pow(ADCAN_EL_Radio_Switch.countOfBits)-1) << ADCAN_EL_Radio_Switch.startbit)) >> ADCAN_EL_Radio_Switch.startbit;
		ADCAN_PT_Shift_Down.value = (Val & ~(jk_pow(ADCAN_PT_Shift_Down.startbit)-1) & ((jk_pow(ADCAN_PT_Shift_Down.countOfBits)-1) << ADCAN_PT_Shift_Down.startbit)) >> ADCAN_PT_Shift_Down.startbit;
		ADCAN_PT_Shift_Up.value = (Val & ~(jk_pow(ADCAN_PT_Shift_Up.startbit)-1) & ((jk_pow(ADCAN_PT_Shift_Up.countOfBits)-1) << ADCAN_PT_Shift_Up.startbit)) >> ADCAN_PT_Shift_Up.startbit;
		ADCAN_SP_ARH_switch_1.value = (Val & ~(jk_pow(ADCAN_SP_ARH_switch_1.startbit)-1) & ((jk_pow(ADCAN_SP_ARH_switch_1.countOfBits)-1) << ADCAN_SP_ARH_switch_1.startbit)) >> ADCAN_SP_ARH_switch_1.startbit;
		ADCAN_SP_Clutch_Signal.value = (Val & ~(jk_pow(ADCAN_SP_Clutch_Signal.startbit)-1) & ((jk_pow(ADCAN_SP_Clutch_Signal.countOfBits)-1) << ADCAN_SP_Clutch_Signal.startbit)) >> ADCAN_SP_Clutch_Signal.startbit;
	}
	STOS_CAN_PDU_SWCU_Switches() 
	{
		ID = _id;
		uint8_t temp = ADCAN_AE_Switch_1.countOfBits + ADCAN_EL_Radio_Switch.countOfBits + ADCAN_PT_Shift_Down.countOfBits + ADCAN_PT_Shift_Up.countOfBits + ADCAN_SP_ARH_switch_1.countOfBits + ADCAN_SP_Clutch_Signal.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_AE_Switch_1.build() | ADCAN_EL_Radio_Switch.build() | ADCAN_PT_Shift_Down.build() | ADCAN_PT_Shift_Up.build() | ADCAN_SP_ARH_switch_1.build() | ADCAN_SP_Clutch_Signal.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Test_FCU_A : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x177;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_3 = {0, 16, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_FCU_1.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_FCU_1.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_FCU_1.countOfBits)-1) << ADCAN_ZZ_Test_FCU_1.startbit)) >> ADCAN_ZZ_Test_FCU_1.startbit;
		ADCAN_ZZ_Test_FCU_2.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_FCU_2.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_FCU_2.countOfBits)-1) << ADCAN_ZZ_Test_FCU_2.startbit)) >> ADCAN_ZZ_Test_FCU_2.startbit;
		ADCAN_ZZ_Test_FCU_3.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_FCU_3.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_FCU_3.countOfBits)-1) << ADCAN_ZZ_Test_FCU_3.startbit)) >> ADCAN_ZZ_Test_FCU_3.startbit;
	}
	STOS_CAN_PDU_Test_FCU_A() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_FCU_1.countOfBits + ADCAN_ZZ_Test_FCU_2.countOfBits + ADCAN_ZZ_Test_FCU_3.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_FCU_1.build() | ADCAN_ZZ_Test_FCU_2.build() | ADCAN_ZZ_Test_FCU_3.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Test_FCU_B : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x178;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_4 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_5 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_6 = {0, 16, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_ZZ_Test_FCU_4.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_FCU_4.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_FCU_4.countOfBits)-1) << ADCAN_ZZ_Test_FCU_4.startbit)) >> ADCAN_ZZ_Test_FCU_4.startbit;
		ADCAN_ZZ_Test_FCU_5.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_FCU_5.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_FCU_5.countOfBits)-1) << ADCAN_ZZ_Test_FCU_5.startbit)) >> ADCAN_ZZ_Test_FCU_5.startbit;
		ADCAN_ZZ_Test_FCU_6.value = (Val & ~(jk_pow(ADCAN_ZZ_Test_FCU_6.startbit)-1) & ((jk_pow(ADCAN_ZZ_Test_FCU_6.countOfBits)-1) << ADCAN_ZZ_Test_FCU_6.startbit)) >> ADCAN_ZZ_Test_FCU_6.startbit;
	}
	STOS_CAN_PDU_Test_FCU_B() 
	{
		ID = _id;
		uint8_t temp = ADCAN_ZZ_Test_FCU_4.countOfBits + ADCAN_ZZ_Test_FCU_5.countOfBits + ADCAN_ZZ_Test_FCU_6.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_ZZ_Test_FCU_4.build() | ADCAN_ZZ_Test_FCU_5.build() | ADCAN_ZZ_Test_FCU_6.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Water_Oil_Status_Control : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x246;
	uint16_t _size;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Fan_Percent = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_PWM = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_1_PWM = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_2_PWM = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_1_Percent = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_2_Percent = {0, 8, 40};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_PT_Oil_Fan_Percent.value = (Val & ~(jk_pow(ADCAN_PT_Oil_Fan_Percent.startbit)-1) & ((jk_pow(ADCAN_PT_Oil_Fan_Percent.countOfBits)-1) << ADCAN_PT_Oil_Fan_Percent.startbit)) >> ADCAN_PT_Oil_Fan_Percent.startbit;
		ADCAN_PT_Oil_PWM.value = (Val & ~(jk_pow(ADCAN_PT_Oil_PWM.startbit)-1) & ((jk_pow(ADCAN_PT_Oil_PWM.countOfBits)-1) << ADCAN_PT_Oil_PWM.startbit)) >> ADCAN_PT_Oil_PWM.startbit;
		ADCAN_PT_Water_1_PWM.value = (Val & ~(jk_pow(ADCAN_PT_Water_1_PWM.startbit)-1) & ((jk_pow(ADCAN_PT_Water_1_PWM.countOfBits)-1) << ADCAN_PT_Water_1_PWM.startbit)) >> ADCAN_PT_Water_1_PWM.startbit;
		ADCAN_PT_Water_2_PWM.value = (Val & ~(jk_pow(ADCAN_PT_Water_2_PWM.startbit)-1) & ((jk_pow(ADCAN_PT_Water_2_PWM.countOfBits)-1) << ADCAN_PT_Water_2_PWM.startbit)) >> ADCAN_PT_Water_2_PWM.startbit;
		ADCAN_PT_Water_Fan_1_Percent.value = (Val & ~(jk_pow(ADCAN_PT_Water_Fan_1_Percent.startbit)-1) & ((jk_pow(ADCAN_PT_Water_Fan_1_Percent.countOfBits)-1) << ADCAN_PT_Water_Fan_1_Percent.startbit)) >> ADCAN_PT_Water_Fan_1_Percent.startbit;
		ADCAN_PT_Water_Fan_2_Percent.value = (Val & ~(jk_pow(ADCAN_PT_Water_Fan_2_Percent.startbit)-1) & ((jk_pow(ADCAN_PT_Water_Fan_2_Percent.countOfBits)-1) << ADCAN_PT_Water_Fan_2_Percent.startbit)) >> ADCAN_PT_Water_Fan_2_Percent.startbit;
	}
	STOS_CAN_PDU_Water_Oil_Status_Control() 
	{
		ID = _id;
		uint8_t temp = ADCAN_PT_Oil_Fan_Percent.countOfBits + ADCAN_PT_Oil_PWM.countOfBits + ADCAN_PT_Water_1_PWM.countOfBits + ADCAN_PT_Water_2_PWM.countOfBits + ADCAN_PT_Water_Fan_1_Percent.countOfBits + ADCAN_PT_Water_Fan_2_Percent.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_PT_Oil_Fan_Percent.build() | ADCAN_PT_Oil_PWM.build() | ADCAN_PT_Water_1_PWM.build() | ADCAN_PT_Water_2_PWM.build() | ADCAN_PT_Water_Fan_1_Percent.build() | ADCAN_PT_Water_Fan_2_Percent.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Whl_Speed_F : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x180;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FR = {0, 16, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Wheel_Speed_FL.value = (Val & ~(jk_pow(ADCAN_SP_Wheel_Speed_FL.startbit)-1) & ((jk_pow(ADCAN_SP_Wheel_Speed_FL.countOfBits)-1) << ADCAN_SP_Wheel_Speed_FL.startbit)) >> ADCAN_SP_Wheel_Speed_FL.startbit;
		ADCAN_SP_Wheel_Speed_FR.value = (Val & ~(jk_pow(ADCAN_SP_Wheel_Speed_FR.startbit)-1) & ((jk_pow(ADCAN_SP_Wheel_Speed_FR.countOfBits)-1) << ADCAN_SP_Wheel_Speed_FR.startbit)) >> ADCAN_SP_Wheel_Speed_FR.startbit;
	}
	STOS_CAN_PDU_Whl_Speed_F() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Wheel_Speed_FL.countOfBits + ADCAN_SP_Wheel_Speed_FR.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Wheel_Speed_FL.build() | ADCAN_SP_Wheel_Speed_FR.build();
		ID = _id;
	}
};

struct STOS_CAN_PDU_Whl_Speed_R : public StallardOSCanMessage 
{
public:
	static const uint16_t _id = 0x181;
	uint16_t _size;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RR = {0, 16, 24};//init,bitcount,startbit 
	uint64_t jk_pow(uint8_t exp)
	{
		return (2 << exp);
	}
	void unbuild()
	{
		ADCAN_SP_Wheel_Speed_RL.value = (Val & ~(jk_pow(ADCAN_SP_Wheel_Speed_RL.startbit)-1) & ((jk_pow(ADCAN_SP_Wheel_Speed_RL.countOfBits)-1) << ADCAN_SP_Wheel_Speed_RL.startbit)) >> ADCAN_SP_Wheel_Speed_RL.startbit;
		ADCAN_SP_Wheel_Speed_RR.value = (Val & ~(jk_pow(ADCAN_SP_Wheel_Speed_RR.startbit)-1) & ((jk_pow(ADCAN_SP_Wheel_Speed_RR.countOfBits)-1) << ADCAN_SP_Wheel_Speed_RR.startbit)) >> ADCAN_SP_Wheel_Speed_RR.startbit;
	}
	STOS_CAN_PDU_Whl_Speed_R() 
	{
		ID = _id;
		uint8_t temp = ADCAN_SP_Wheel_Speed_RL.countOfBits + ADCAN_SP_Wheel_Speed_RR.countOfBits;
		temp = (temp + 8 - (temp % 8)) / 8;
		if(temp > 8) temp = 8;
		_size = dlc = temp;
	}
	void build() {
		Val = ADCAN_SP_Wheel_Speed_RL.build() | ADCAN_SP_Wheel_Speed_RR.build();
		ID = _id;
	}
;
}; 

#endif