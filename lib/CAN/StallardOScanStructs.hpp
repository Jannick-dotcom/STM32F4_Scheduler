#ifndef StallardOScanStructs_hpp
#define StallardOScanStructs_hpp
#include "stdint.h"
#include "StallardOScanTypes.hpp"
#include <math.h>

struct STOS_CAN_PDU_AGS1_gearbox_control_unit : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_AGS1_gearbox_control_unit() {
		ID = _id;
	}
	static const uint16_t _id = 0x100;
	CAN_Signal<int8_t> activate_blip = {0, 1, 60};//init,bitcount,startbit 
	CAN_Signal<uint8_t> activate_cut = {0, 1, 61};//init,bitcount,startbit 
	CAN_Signal<uint8_t> blip_state = {0, 4, 28};//init,bitcount,startbit 
	CAN_Signal<uint8_t> cut_level_gcu = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> engaged_gear = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint16_t> gearpot = {0, 10, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shift_state = {0, 4, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> state_cut = {0, 4, 56};//init,bitcount,startbit 
	CAN_Signal<uint16_t> target_engine_speed = {0, 14, 32};//init,bitcount,startbit 
	void unbuild()
	{
		activate_blip.value = *Val & ~(uint64_t(pow(2, activate_blip.startbit)-1)) & (uint64_t(pow(2, activate_blip.countOfBits)-1) << activate_blip.startbit);
		activate_cut.value = *Val & ~(uint64_t(pow(2, activate_cut.startbit)-1)) & (uint64_t(pow(2, activate_cut.countOfBits)-1) << activate_cut.startbit);
		blip_state.value = *Val & ~(uint64_t(pow(2, blip_state.startbit)-1)) & (uint64_t(pow(2, blip_state.countOfBits)-1) << blip_state.startbit);
		cut_level_gcu.value = *Val & ~(uint64_t(pow(2, cut_level_gcu.startbit)-1)) & (uint64_t(pow(2, cut_level_gcu.countOfBits)-1) << cut_level_gcu.startbit);
		engaged_gear.value = *Val & ~(uint64_t(pow(2, engaged_gear.startbit)-1)) & (uint64_t(pow(2, engaged_gear.countOfBits)-1) << engaged_gear.startbit);
		gearpot.value = *Val & ~(uint64_t(pow(2, gearpot.startbit)-1)) & (uint64_t(pow(2, gearpot.countOfBits)-1) << gearpot.startbit);
		shift_state.value = *Val & ~(uint64_t(pow(2, shift_state.startbit)-1)) & (uint64_t(pow(2, shift_state.countOfBits)-1) << shift_state.startbit);
		state_cut.value = *Val & ~(uint64_t(pow(2, state_cut.startbit)-1)) & (uint64_t(pow(2, state_cut.countOfBits)-1) << state_cut.startbit);
		target_engine_speed.value = *Val & ~(uint64_t(pow(2, target_engine_speed.startbit)-1)) & (uint64_t(pow(2, target_engine_speed.countOfBits)-1) << target_engine_speed.startbit);
	}
	void build() {
		*Val = activate_blip.build() | activate_cut.build() | blip_state.build() | cut_level_gcu.build() | engaged_gear.build() | gearpot.build() | shift_state.build() | state_cut.build() | target_engine_speed.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(activate_blip.value) + sizeof(activate_cut.value) + sizeof(blip_state.value) + sizeof(cut_level_gcu.value) + sizeof(engaged_gear.value) + sizeof(gearpot.value) + sizeof(shift_state.value) + sizeof(state_cut.value) + sizeof(target_engine_speed.value);
};

struct STOS_CAN_PDU_ABS_wheelspeeds : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_ABS_wheelspeeds() {
		ID = _id;
	}
	static const uint16_t _id = 0x24A;
	CAN_Signal<uint16_t> speedABSfl = {0, 16, 0};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSfr = {0, 16, 16};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSrl = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSrr = {0, 16, 48};//init,bitcount,startbit 
	void unbuild()
	{
		speedABSfl.value = *Val & ~(uint64_t(pow(2, speedABSfl.startbit)-1)) & (uint64_t(pow(2, speedABSfl.countOfBits)-1) << speedABSfl.startbit);
		speedABSfr.value = *Val & ~(uint64_t(pow(2, speedABSfr.startbit)-1)) & (uint64_t(pow(2, speedABSfr.countOfBits)-1) << speedABSfr.startbit);
		speedABSrl.value = *Val & ~(uint64_t(pow(2, speedABSrl.startbit)-1)) & (uint64_t(pow(2, speedABSrl.countOfBits)-1) << speedABSrl.startbit);
		speedABSrr.value = *Val & ~(uint64_t(pow(2, speedABSrr.startbit)-1)) & (uint64_t(pow(2, speedABSrr.countOfBits)-1) << speedABSrr.startbit);
	}
	void build() {
		*Val = speedABSfl.build() | speedABSfr.build() | speedABSrl.build() | speedABSrr.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(speedABSfl.value) + sizeof(speedABSfr.value) + sizeof(speedABSrl.value) + sizeof(speedABSrr.value);
};

struct STOS_CAN_PDU_ABS_switch_state_slip_and_speed : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_ABS_switch_state_slip_and_speed() {
		ID = _id;
	}
	static const uint16_t _id = 0x5C0;
	CAN_Signal<uint16_t> ax1_Bremse60ABS = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ay1_Bremse60ABS = {0, 16, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> blsABS = {0, 1, 24};//init,bitcount,startbit 
	CAN_Signal<int16_t> p_HzABS = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> switchstateABS = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ax1_Bremse60ABS.value = *Val & ~(uint64_t(pow(2, ax1_Bremse60ABS.startbit)-1)) & (uint64_t(pow(2, ax1_Bremse60ABS.countOfBits)-1) << ax1_Bremse60ABS.startbit);
		ay1_Bremse60ABS.value = *Val & ~(uint64_t(pow(2, ay1_Bremse60ABS.startbit)-1)) & (uint64_t(pow(2, ay1_Bremse60ABS.countOfBits)-1) << ay1_Bremse60ABS.startbit);
		blsABS.value = *Val & ~(uint64_t(pow(2, blsABS.startbit)-1)) & (uint64_t(pow(2, blsABS.countOfBits)-1) << blsABS.startbit);
		p_HzABS.value = *Val & ~(uint64_t(pow(2, p_HzABS.startbit)-1)) & (uint64_t(pow(2, p_HzABS.countOfBits)-1) << p_HzABS.startbit);
		switchstateABS.value = *Val & ~(uint64_t(pow(2, switchstateABS.startbit)-1)) & (uint64_t(pow(2, switchstateABS.countOfBits)-1) << switchstateABS.startbit);
	}
	void build() {
		*Val = ax1_Bremse60ABS.build() | ay1_Bremse60ABS.build() | blsABS.build() | p_HzABS.build() | switchstateABS.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ax1_Bremse60ABS.value) + sizeof(ay1_Bremse60ABS.value) + sizeof(blsABS.value) + sizeof(p_HzABS.value) + sizeof(switchstateABS.value);
};

struct STOS_CAN_PDU_Injection_1 : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Injection_1() {
		ID = _id;
	}
	static const uint16_t _id = 0x770;
	CAN_Signal<uint8_t> ti_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_8 = {0, 8, 56};//init,bitcount,startbit 
	void unbuild()
	{
		ti_1.value = *Val & ~(uint64_t(pow(2, ti_1.startbit)-1)) & (uint64_t(pow(2, ti_1.countOfBits)-1) << ti_1.startbit);
		ti_2.value = *Val & ~(uint64_t(pow(2, ti_2.startbit)-1)) & (uint64_t(pow(2, ti_2.countOfBits)-1) << ti_2.startbit);
		ti_3.value = *Val & ~(uint64_t(pow(2, ti_3.startbit)-1)) & (uint64_t(pow(2, ti_3.countOfBits)-1) << ti_3.startbit);
		ti_4.value = *Val & ~(uint64_t(pow(2, ti_4.startbit)-1)) & (uint64_t(pow(2, ti_4.countOfBits)-1) << ti_4.startbit);
		ti_5.value = *Val & ~(uint64_t(pow(2, ti_5.startbit)-1)) & (uint64_t(pow(2, ti_5.countOfBits)-1) << ti_5.startbit);
		ti_6.value = *Val & ~(uint64_t(pow(2, ti_6.startbit)-1)) & (uint64_t(pow(2, ti_6.countOfBits)-1) << ti_6.startbit);
		ti_7.value = *Val & ~(uint64_t(pow(2, ti_7.startbit)-1)) & (uint64_t(pow(2, ti_7.countOfBits)-1) << ti_7.startbit);
		ti_8.value = *Val & ~(uint64_t(pow(2, ti_8.startbit)-1)) & (uint64_t(pow(2, ti_8.countOfBits)-1) << ti_8.startbit);
	}
	void build() {
		*Val = ti_1.build() | ti_2.build() | ti_3.build() | ti_4.build() | ti_5.build() | ti_6.build() | ti_7.build() | ti_8.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ti_1.value) + sizeof(ti_2.value) + sizeof(ti_3.value) + sizeof(ti_4.value) + sizeof(ti_5.value) + sizeof(ti_6.value) + sizeof(ti_7.value) + sizeof(ti_8.value);
};

struct STOS_CAN_PDU_Injection_2 : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Injection_2() {
		ID = _id;
	}
	static const uint16_t _id = 0x771;
	CAN_Signal<uint8_t> injang = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> injoff = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_2k = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_k = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tibase = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tibatt_o = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> timap = {0, 8, 16};//init,bitcount,startbit 
	void unbuild()
	{
		injang.value = *Val & ~(uint64_t(pow(2, injang.startbit)-1)) & (uint64_t(pow(2, injang.countOfBits)-1) << injang.startbit);
		injoff.value = *Val & ~(uint64_t(pow(2, injoff.startbit)-1)) & (uint64_t(pow(2, injoff.countOfBits)-1) << injoff.startbit);
		lamctrl_2k.value = *Val & ~(uint64_t(pow(2, lamctrl_2k.startbit)-1)) & (uint64_t(pow(2, lamctrl_2k.countOfBits)-1) << lamctrl_2k.startbit);
		lamctrl_k.value = *Val & ~(uint64_t(pow(2, lamctrl_k.startbit)-1)) & (uint64_t(pow(2, lamctrl_k.countOfBits)-1) << lamctrl_k.startbit);
		tibase.value = *Val & ~(uint64_t(pow(2, tibase.startbit)-1)) & (uint64_t(pow(2, tibase.countOfBits)-1) << tibase.startbit);
		tibatt_o.value = *Val & ~(uint64_t(pow(2, tibatt_o.startbit)-1)) & (uint64_t(pow(2, tibatt_o.countOfBits)-1) << tibatt_o.startbit);
		timap.value = *Val & ~(uint64_t(pow(2, timap.startbit)-1)) & (uint64_t(pow(2, timap.countOfBits)-1) << timap.startbit);
	}
	void build() {
		*Val = injang.build() | injoff.build() | lamctrl_2k.build() | lamctrl_k.build() | tibase.build() | tibatt_o.build() | timap.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(injang.value) + sizeof(injoff.value) + sizeof(lamctrl_2k.value) + sizeof(lamctrl_k.value) + sizeof(tibase.value) + sizeof(tibatt_o.value) + sizeof(timap.value);
};

struct STOS_CAN_PDU_Ignition : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Ignition() {
		ID = _id;
	}
	static const uint16_t _id = 0x772;
	CAN_Signal<int8_t> ign_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_8 = {0, 8, 56};//init,bitcount,startbit 
	void unbuild()
	{
		ign_1.value = *Val & ~(uint64_t(pow(2, ign_1.startbit)-1)) & (uint64_t(pow(2, ign_1.countOfBits)-1) << ign_1.startbit);
		ign_2.value = *Val & ~(uint64_t(pow(2, ign_2.startbit)-1)) & (uint64_t(pow(2, ign_2.countOfBits)-1) << ign_2.startbit);
		ign_3.value = *Val & ~(uint64_t(pow(2, ign_3.startbit)-1)) & (uint64_t(pow(2, ign_3.countOfBits)-1) << ign_3.startbit);
		ign_4.value = *Val & ~(uint64_t(pow(2, ign_4.startbit)-1)) & (uint64_t(pow(2, ign_4.countOfBits)-1) << ign_4.startbit);
		ign_5.value = *Val & ~(uint64_t(pow(2, ign_5.startbit)-1)) & (uint64_t(pow(2, ign_5.countOfBits)-1) << ign_5.startbit);
		ign_6.value = *Val & ~(uint64_t(pow(2, ign_6.startbit)-1)) & (uint64_t(pow(2, ign_6.countOfBits)-1) << ign_6.startbit);
		ign_7.value = *Val & ~(uint64_t(pow(2, ign_7.startbit)-1)) & (uint64_t(pow(2, ign_7.countOfBits)-1) << ign_7.startbit);
		ign_8.value = *Val & ~(uint64_t(pow(2, ign_8.startbit)-1)) & (uint64_t(pow(2, ign_8.countOfBits)-1) << ign_8.startbit);
	}
	void build() {
		*Val = ign_1.build() | ign_2.build() | ign_3.build() | ign_4.build() | ign_5.build() | ign_6.build() | ign_7.build() | ign_8.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ign_1.value) + sizeof(ign_2.value) + sizeof(ign_3.value) + sizeof(ign_4.value) + sizeof(ign_5.value) + sizeof(ign_6.value) + sizeof(ign_7.value) + sizeof(ign_8.value);
};

struct STOS_CAN_PDU_Ignition_Rev_Ath : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Ignition_Rev_Ath() {
		ID = _id;
	}
	static const uint16_t _id = 0x773;
	CAN_Signal<uint8_t> ath = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> dath = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> ignbase = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> ignmap = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> rev = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tdwell = {0, 8, 16};//init,bitcount,startbit 
	void unbuild()
	{
		ath.value = *Val & ~(uint64_t(pow(2, ath.startbit)-1)) & (uint64_t(pow(2, ath.countOfBits)-1) << ath.startbit);
		dath.value = *Val & ~(uint64_t(pow(2, dath.startbit)-1)) & (uint64_t(pow(2, dath.countOfBits)-1) << dath.startbit);
		ignbase.value = *Val & ~(uint64_t(pow(2, ignbase.startbit)-1)) & (uint64_t(pow(2, ignbase.countOfBits)-1) << ignbase.startbit);
		ignmap.value = *Val & ~(uint64_t(pow(2, ignmap.startbit)-1)) & (uint64_t(pow(2, ignmap.countOfBits)-1) << ignmap.startbit);
		rev.value = *Val & ~(uint64_t(pow(2, rev.startbit)-1)) & (uint64_t(pow(2, rev.countOfBits)-1) << rev.startbit);
		tdwell.value = *Val & ~(uint64_t(pow(2, tdwell.startbit)-1)) & (uint64_t(pow(2, tdwell.countOfBits)-1) << tdwell.startbit);
	}
	void build() {
		*Val = ath.build() | dath.build() | ignbase.build() | ignmap.build() | rev.build() | tdwell.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ath.value) + sizeof(dath.value) + sizeof(ignbase.value) + sizeof(ignmap.value) + sizeof(rev.value) + sizeof(tdwell.value);
};

struct STOS_CAN_PDU_Lambda : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Lambda() {
		ID = _id;
	}
	static const uint16_t _id = 0x774;
	CAN_Signal<uint8_t> lam = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lam_2 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> lami = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> lami_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lammap = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lammap_2 = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<int8_t> lamp = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<int8_t> lamp_2 = {0, 8, 24};//init,bitcount,startbit 
	void unbuild()
	{
		lam.value = *Val & ~(uint64_t(pow(2, lam.startbit)-1)) & (uint64_t(pow(2, lam.countOfBits)-1) << lam.startbit);
		lam_2.value = *Val & ~(uint64_t(pow(2, lam_2.startbit)-1)) & (uint64_t(pow(2, lam_2.countOfBits)-1) << lam_2.startbit);
		lami.value = *Val & ~(uint64_t(pow(2, lami.startbit)-1)) & (uint64_t(pow(2, lami.countOfBits)-1) << lami.startbit);
		lami_2.value = *Val & ~(uint64_t(pow(2, lami_2.startbit)-1)) & (uint64_t(pow(2, lami_2.countOfBits)-1) << lami_2.startbit);
		lammap.value = *Val & ~(uint64_t(pow(2, lammap.startbit)-1)) & (uint64_t(pow(2, lammap.countOfBits)-1) << lammap.startbit);
		lammap_2.value = *Val & ~(uint64_t(pow(2, lammap_2.startbit)-1)) & (uint64_t(pow(2, lammap_2.countOfBits)-1) << lammap_2.startbit);
		lamp.value = *Val & ~(uint64_t(pow(2, lamp.startbit)-1)) & (uint64_t(pow(2, lamp.countOfBits)-1) << lamp.startbit);
		lamp_2.value = *Val & ~(uint64_t(pow(2, lamp_2.startbit)-1)) & (uint64_t(pow(2, lamp_2.countOfBits)-1) << lamp_2.startbit);
	}
	void build() {
		*Val = lam.build() | lam_2.build() | lami.build() | lami_2.build() | lammap.build() | lammap_2.build() | lamp.build() | lamp_2.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(lam.value) + sizeof(lam_2.value) + sizeof(lami.value) + sizeof(lami_2.value) + sizeof(lammap.value) + sizeof(lammap_2.value) + sizeof(lamp.value) + sizeof(lamp_2.value);
};

struct STOS_CAN_PDU_Speed : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Speed() {
		ID = _id;
	}
	static const uint16_t _id = 0x775;
	CAN_Signal<uint16_t> speed = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedfl = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedfr = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedrl = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedrr = {0, 8, 40};//init,bitcount,startbit 
	void unbuild()
	{
		speed.value = *Val & ~(uint64_t(pow(2, speed.startbit)-1)) & (uint64_t(pow(2, speed.countOfBits)-1) << speed.startbit);
		speedfl.value = *Val & ~(uint64_t(pow(2, speedfl.startbit)-1)) & (uint64_t(pow(2, speedfl.countOfBits)-1) << speedfl.startbit);
		speedfr.value = *Val & ~(uint64_t(pow(2, speedfr.startbit)-1)) & (uint64_t(pow(2, speedfr.countOfBits)-1) << speedfr.startbit);
		speedrl.value = *Val & ~(uint64_t(pow(2, speedrl.startbit)-1)) & (uint64_t(pow(2, speedrl.countOfBits)-1) << speedrl.startbit);
		speedrr.value = *Val & ~(uint64_t(pow(2, speedrr.startbit)-1)) & (uint64_t(pow(2, speedrr.countOfBits)-1) << speedrr.startbit);
	}
	void build() {
		*Val = speed.build() | speedfl.build() | speedfr.build() | speedrl.build() | speedrr.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(speed.value) + sizeof(speedfl.value) + sizeof(speedfr.value) + sizeof(speedrl.value) + sizeof(speedrr.value);
};

struct STOS_CAN_PDU_Lapfunc : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Lapfunc() {
		ID = _id;
	}
	static const uint16_t _id = 0x776;
	CAN_Signal<uint16_t> lapdist = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptime = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptimediff = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptimefast = {0, 16, 56};//init,bitcount,startbit 
	void unbuild()
	{
		lapdist.value = *Val & ~(uint64_t(pow(2, lapdist.startbit)-1)) & (uint64_t(pow(2, lapdist.countOfBits)-1) << lapdist.startbit);
		laptime.value = *Val & ~(uint64_t(pow(2, laptime.startbit)-1)) & (uint64_t(pow(2, laptime.countOfBits)-1) << laptime.startbit);
		laptimediff.value = *Val & ~(uint64_t(pow(2, laptimediff.startbit)-1)) & (uint64_t(pow(2, laptimediff.countOfBits)-1) << laptimediff.startbit);
		laptimefast.value = *Val & ~(uint64_t(pow(2, laptimefast.startbit)-1)) & (uint64_t(pow(2, laptimefast.countOfBits)-1) << laptimefast.startbit);
	}
	void build() {
		*Val = lapdist.build() | laptime.build() | laptimediff.build() | laptimefast.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(lapdist.value) + sizeof(laptime.value) + sizeof(laptimediff.value) + sizeof(laptimefast.value);
};

struct STOS_CAN_PDU_Gear_Dashboard_Acceleration : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Gear_Dashboard_Acceleration() {
		ID = _id;
	}
	static const uint16_t _id = 0x777;
	CAN_Signal<int8_t> accx = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> accy = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> accz = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ddugear = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gcstate = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gear = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gearcut_u = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gearratio = {0, 8, 16};//init,bitcount,startbit 
	void unbuild()
	{
		accx.value = *Val & ~(uint64_t(pow(2, accx.startbit)-1)) & (uint64_t(pow(2, accx.countOfBits)-1) << accx.startbit);
		accy.value = *Val & ~(uint64_t(pow(2, accy.startbit)-1)) & (uint64_t(pow(2, accy.countOfBits)-1) << accy.startbit);
		accz.value = *Val & ~(uint64_t(pow(2, accz.startbit)-1)) & (uint64_t(pow(2, accz.countOfBits)-1) << accz.startbit);
		ddugear.value = *Val & ~(uint64_t(pow(2, ddugear.startbit)-1)) & (uint64_t(pow(2, ddugear.countOfBits)-1) << ddugear.startbit);
		gcstate.value = *Val & ~(uint64_t(pow(2, gcstate.startbit)-1)) & (uint64_t(pow(2, gcstate.countOfBits)-1) << gcstate.startbit);
		gear.value = *Val & ~(uint64_t(pow(2, gear.startbit)-1)) & (uint64_t(pow(2, gear.countOfBits)-1) << gear.startbit);
		gearcut_u.value = *Val & ~(uint64_t(pow(2, gearcut_u.startbit)-1)) & (uint64_t(pow(2, gearcut_u.countOfBits)-1) << gearcut_u.startbit);
		gearratio.value = *Val & ~(uint64_t(pow(2, gearratio.startbit)-1)) & (uint64_t(pow(2, gearratio.countOfBits)-1) << gearratio.startbit);
	}
	void build() {
		*Val = accx.build() | accy.build() | accz.build() | ddugear.build() | gcstate.build() | gear.build() | gearcut_u.build() | gearratio.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(accx.value) + sizeof(accy.value) + sizeof(accz.value) + sizeof(ddugear.value) + sizeof(gcstate.value) + sizeof(gear.value) + sizeof(gearcut_u.value) + sizeof(gearratio.value);
};

struct STOS_CAN_PDU_Traction_Control : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Traction_Control() {
		ID = _id;
	}
	static const uint16_t _id = 0x778;
	CAN_Signal<uint8_t> slipsp = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> slra = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<int8_t> tcpfac = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tcsw = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> vdraxle = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> vref = {0, 16, 56};//init,bitcount,startbit 
	void unbuild()
	{
		slipsp.value = *Val & ~(uint64_t(pow(2, slipsp.startbit)-1)) & (uint64_t(pow(2, slipsp.countOfBits)-1) << slipsp.startbit);
		slra.value = *Val & ~(uint64_t(pow(2, slra.startbit)-1)) & (uint64_t(pow(2, slra.countOfBits)-1) << slra.startbit);
		tcpfac.value = *Val & ~(uint64_t(pow(2, tcpfac.startbit)-1)) & (uint64_t(pow(2, tcpfac.countOfBits)-1) << tcpfac.startbit);
		tcsw.value = *Val & ~(uint64_t(pow(2, tcsw.startbit)-1)) & (uint64_t(pow(2, tcsw.countOfBits)-1) << tcsw.startbit);
		vdraxle.value = *Val & ~(uint64_t(pow(2, vdraxle.startbit)-1)) & (uint64_t(pow(2, vdraxle.countOfBits)-1) << vdraxle.startbit);
		vref.value = *Val & ~(uint64_t(pow(2, vref.startbit)-1)) & (uint64_t(pow(2, vref.countOfBits)-1) << vref.startbit);
	}
	void build() {
		*Val = slipsp.build() | slra.build() | tcpfac.build() | tcsw.build() | vdraxle.build() | vref.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(slipsp.value) + sizeof(slra.value) + sizeof(tcpfac.value) + sizeof(tcsw.value) + sizeof(vdraxle.value) + sizeof(vref.value);
};

struct STOS_CAN_PDU_Electronic_Throttle_Control : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Electronic_Throttle_Control() {
		ID = _id;
	}
	static const uint16_t _id = 0x779;
	CAN_Signal<uint8_t> aps = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> batt_u = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> camshaftpos = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> etb = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> etb_sp = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lap_c = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint16_t> p1 = {0, 16, 32};//init,bitcount,startbit 
	void unbuild()
	{
		aps.value = *Val & ~(uint64_t(pow(2, aps.startbit)-1)) & (uint64_t(pow(2, aps.countOfBits)-1) << aps.startbit);
		batt_u.value = *Val & ~(uint64_t(pow(2, batt_u.startbit)-1)) & (uint64_t(pow(2, batt_u.countOfBits)-1) << batt_u.startbit);
		camshaftpos.value = *Val & ~(uint64_t(pow(2, camshaftpos.startbit)-1)) & (uint64_t(pow(2, camshaftpos.countOfBits)-1) << camshaftpos.startbit);
		etb.value = *Val & ~(uint64_t(pow(2, etb.startbit)-1)) & (uint64_t(pow(2, etb.countOfBits)-1) << etb.startbit);
		etb_sp.value = *Val & ~(uint64_t(pow(2, etb_sp.startbit)-1)) & (uint64_t(pow(2, etb_sp.countOfBits)-1) << etb_sp.startbit);
		lap_c.value = *Val & ~(uint64_t(pow(2, lap_c.startbit)-1)) & (uint64_t(pow(2, lap_c.countOfBits)-1) << lap_c.startbit);
		p1.value = *Val & ~(uint64_t(pow(2, p1.startbit)-1)) & (uint64_t(pow(2, p1.countOfBits)-1) << p1.startbit);
	}
	void build() {
		*Val = aps.build() | batt_u.build() | camshaftpos.build() | etb.build() | etb_sp.build() | lap_c.build() | p1.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(aps.value) + sizeof(batt_u.value) + sizeof(camshaftpos.value) + sizeof(etb.value) + sizeof(etb_sp.value) + sizeof(lap_c.value) + sizeof(p1.value);
};

struct STOS_CAN_PDU_States_Temp_Press : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_States_Temp_Press() {
		ID = _id;
	}
	static const uint16_t _id = 0x77A;
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
	void unbuild()
	{
		battlow_b.value = *Val & ~(uint64_t(pow(2, battlow_b.startbit)-1)) & (uint64_t(pow(2, battlow_b.countOfBits)-1) << battlow_b.startbit);
		etbsys_e.value = *Val & ~(uint64_t(pow(2, etbsys_e.startbit)-1)) & (uint64_t(pow(2, etbsys_e.countOfBits)-1) << etbsys_e.startbit);
		fuellap.value = *Val & ~(uint64_t(pow(2, fuellap.startbit)-1)) & (uint64_t(pow(2, fuellap.countOfBits)-1) << fuellap.startbit);
		fueltank.value = *Val & ~(uint64_t(pow(2, fueltank.startbit)-1)) & (uint64_t(pow(2, fueltank.countOfBits)-1) << fueltank.startbit);
		gearcut_b.value = *Val & ~(uint64_t(pow(2, gearcut_b.startbit)-1)) & (uint64_t(pow(2, gearcut_b.countOfBits)-1) << gearcut_b.startbit);
		idle_b.value = *Val & ~(uint64_t(pow(2, idle_b.startbit)-1)) & (uint64_t(pow(2, idle_b.countOfBits)-1) << idle_b.startbit);
		ignoff_b.value = *Val & ~(uint64_t(pow(2, ignoff_b.startbit)-1)) & (uint64_t(pow(2, ignoff_b.countOfBits)-1) << ignoff_b.startbit);
		injcut_b.value = *Val & ~(uint64_t(pow(2, injcut_b.startbit)-1)) & (uint64_t(pow(2, injcut_b.countOfBits)-1) << injcut_b.startbit);
		injcutin_b.value = *Val & ~(uint64_t(pow(2, injcutin_b.startbit)-1)) & (uint64_t(pow(2, injcutin_b.countOfBits)-1) << injcutin_b.startbit);
		injenrich_b.value = *Val & ~(uint64_t(pow(2, injenrich_b.startbit)-1)) & (uint64_t(pow(2, injenrich_b.countOfBits)-1) << injenrich_b.startbit);
		injstartphase_b.value = *Val & ~(uint64_t(pow(2, injstartphase_b.startbit)-1)) & (uint64_t(pow(2, injstartphase_b.countOfBits)-1) << injstartphase_b.startbit);
		knockadaptenable_b.value = *Val & ~(uint64_t(pow(2, knockadaptenable_b.startbit)-1)) & (uint64_t(pow(2, knockadaptenable_b.countOfBits)-1) << knockadaptenable_b.startbit);
		knockenable_b.value = *Val & ~(uint64_t(pow(2, knockenable_b.startbit)-1)) & (uint64_t(pow(2, knockenable_b.countOfBits)-1) << knockenable_b.startbit);
		lamctrl_2b.value = *Val & ~(uint64_t(pow(2, lamctrl_2b.startbit)-1)) & (uint64_t(pow(2, lamctrl_2b.countOfBits)-1) << lamctrl_2b.startbit);
		lamctrl_b.value = *Val & ~(uint64_t(pow(2, lamctrl_b.startbit)-1)) & (uint64_t(pow(2, lamctrl_b.countOfBits)-1) << lamctrl_b.startbit);
		lap_b.value = *Val & ~(uint64_t(pow(2, lap_b.startbit)-1)) & (uint64_t(pow(2, lap_b.countOfBits)-1) << lap_b.startbit);
		laptrig_b.value = *Val & ~(uint64_t(pow(2, laptrig_b.startbit)-1)) & (uint64_t(pow(2, laptrig_b.countOfBits)-1) << laptrig_b.startbit);
		mappos.value = *Val & ~(uint64_t(pow(2, mappos.startbit)-1)) & (uint64_t(pow(2, mappos.countOfBits)-1) << mappos.startbit);
		mil_b.value = *Val & ~(uint64_t(pow(2, mil_b.startbit)-1)) & (uint64_t(pow(2, mil_b.countOfBits)-1) << mil_b.startbit);
		oillamp_b.value = *Val & ~(uint64_t(pow(2, oillamp_b.startbit)-1)) & (uint64_t(pow(2, oillamp_b.countOfBits)-1) << oillamp_b.startbit);
		pamb.value = *Val & ~(uint64_t(pow(2, pamb.startbit)-1)) & (uint64_t(pow(2, pamb.countOfBits)-1) << pamb.startbit);
		pcrank.value = *Val & ~(uint64_t(pow(2, pcrank.startbit)-1)) & (uint64_t(pow(2, pcrank.countOfBits)-1) << pcrank.startbit);
		pfuel.value = *Val & ~(uint64_t(pow(2, pfuel.startbit)-1)) & (uint64_t(pow(2, pfuel.countOfBits)-1) << pfuel.startbit);
		phsok_b.value = *Val & ~(uint64_t(pow(2, phsok_b.startbit)-1)) & (uint64_t(pow(2, phsok_b.countOfBits)-1) << phsok_b.startbit);
		phsokset_b.value = *Val & ~(uint64_t(pow(2, phsokset_b.startbit)-1)) & (uint64_t(pow(2, phsokset_b.countOfBits)-1) << phsokset_b.startbit);
		poil.value = *Val & ~(uint64_t(pow(2, poil.startbit)-1)) & (uint64_t(pow(2, poil.countOfBits)-1) << poil.startbit);
		pwat.value = *Val & ~(uint64_t(pow(2, pwat.startbit)-1)) & (uint64_t(pow(2, pwat.countOfBits)-1) << pwat.startbit);
		rev_b.value = *Val & ~(uint64_t(pow(2, rev_b.startbit)-1)) & (uint64_t(pow(2, rev_b.countOfBits)-1) << rev_b.startbit);
		revlimit_b.value = *Val & ~(uint64_t(pow(2, revlimit_b.startbit)-1)) & (uint64_t(pow(2, revlimit_b.countOfBits)-1) << revlimit_b.startbit);
		rowcounter_0x77A.value = *Val & ~(uint64_t(pow(2, rowcounter_0x77A.startbit)-1)) & (uint64_t(pow(2, rowcounter_0x77A.countOfBits)-1) << rowcounter_0x77A.startbit);
		shled1_b.value = *Val & ~(uint64_t(pow(2, shled1_b.startbit)-1)) & (uint64_t(pow(2, shled1_b.countOfBits)-1) << shled1_b.startbit);
		shled2_b.value = *Val & ~(uint64_t(pow(2, shled2_b.startbit)-1)) & (uint64_t(pow(2, shled2_b.countOfBits)-1) << shled2_b.startbit);
		shled3_b.value = *Val & ~(uint64_t(pow(2, shled3_b.startbit)-1)) & (uint64_t(pow(2, shled3_b.countOfBits)-1) << shled3_b.startbit);
		shled4_b.value = *Val & ~(uint64_t(pow(2, shled4_b.startbit)-1)) & (uint64_t(pow(2, shled4_b.countOfBits)-1) << shled4_b.startbit);
		shled5_b.value = *Val & ~(uint64_t(pow(2, shled5_b.startbit)-1)) & (uint64_t(pow(2, shled5_b.countOfBits)-1) << shled5_b.startbit);
		speedlimit_b.value = *Val & ~(uint64_t(pow(2, speedlimit_b.startbit)-1)) & (uint64_t(pow(2, speedlimit_b.countOfBits)-1) << speedlimit_b.startbit);
		speedlimitreq_b.value = *Val & ~(uint64_t(pow(2, speedlimitreq_b.startbit)-1)) & (uint64_t(pow(2, speedlimitreq_b.countOfBits)-1) << speedlimitreq_b.startbit);
		startend_b.value = *Val & ~(uint64_t(pow(2, startend_b.startbit)-1)) & (uint64_t(pow(2, startend_b.countOfBits)-1) << startend_b.startbit);
		tair.value = *Val & ~(uint64_t(pow(2, tair.startbit)-1)) & (uint64_t(pow(2, tair.countOfBits)-1) << tair.startbit);
		tc_b.value = *Val & ~(uint64_t(pow(2, tc_b.startbit)-1)) & (uint64_t(pow(2, tc_b.countOfBits)-1) << tc_b.startbit);
		tex.value = *Val & ~(uint64_t(pow(2, tex.startbit)-1)) & (uint64_t(pow(2, tex.countOfBits)-1) << tex.startbit);
		tex_2.value = *Val & ~(uint64_t(pow(2, tex_2.startbit)-1)) & (uint64_t(pow(2, tex_2.countOfBits)-1) << tex_2.startbit);
		tfuel.value = *Val & ~(uint64_t(pow(2, tfuel.startbit)-1)) & (uint64_t(pow(2, tfuel.countOfBits)-1) << tfuel.startbit);
		tlam.value = *Val & ~(uint64_t(pow(2, tlam.startbit)-1)) & (uint64_t(pow(2, tlam.countOfBits)-1) << tlam.startbit);
		tlam_2.value = *Val & ~(uint64_t(pow(2, tlam_2.startbit)-1)) & (uint64_t(pow(2, tlam_2.countOfBits)-1) << tlam_2.startbit);
		tmot.value = *Val & ~(uint64_t(pow(2, tmot.startbit)-1)) & (uint64_t(pow(2, tmot.countOfBits)-1) << tmot.startbit);
		toil.value = *Val & ~(uint64_t(pow(2, toil.startbit)-1)) & (uint64_t(pow(2, toil.countOfBits)-1) << toil.startbit);
	}
	void build() {
		*Val = battlow_b.build() | etbsys_e.build() | fuellap.build() | fueltank.build() | gearcut_b.build() | idle_b.build() | ignoff_b.build() | injcut_b.build() | injcutin_b.build() | injenrich_b.build() | injstartphase_b.build() | knockadaptenable_b.build() | knockenable_b.build() | lamctrl_2b.build() | lamctrl_b.build() | lap_b.build() | laptrig_b.build() | mappos.build() | mil_b.build() | oillamp_b.build() | pamb.build() | pcrank.build() | pfuel.build() | phsok_b.build() | phsokset_b.build() | poil.build() | pwat.build() | rev_b.build() | revlimit_b.build() | rowcounter_0x77A.build() | shled1_b.build() | shled2_b.build() | shled3_b.build() | shled4_b.build() | shled5_b.build() | speedlimit_b.build() | speedlimitreq_b.build() | startend_b.build() | tair.build() | tc_b.build() | tex.build() | tex_2.build() | tfuel.build() | tlam.build() | tlam_2.build() | tmot.build() | toil.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(battlow_b.value) + sizeof(etbsys_e.value) + sizeof(fuellap.value) + sizeof(fueltank.value) + sizeof(gearcut_b.value) + sizeof(idle_b.value) + sizeof(ignoff_b.value) + sizeof(injcut_b.value) + sizeof(injcutin_b.value) + sizeof(injenrich_b.value) + sizeof(injstartphase_b.value) + sizeof(knockadaptenable_b.value) + sizeof(knockenable_b.value) + sizeof(lamctrl_2b.value) + sizeof(lamctrl_b.value) + sizeof(lap_b.value) + sizeof(laptrig_b.value) + sizeof(mappos.value) + sizeof(mil_b.value) + sizeof(oillamp_b.value) + sizeof(pamb.value) + sizeof(pcrank.value) + sizeof(pfuel.value) + sizeof(phsok_b.value) + sizeof(phsokset_b.value) + sizeof(poil.value) + sizeof(pwat.value) + sizeof(rev_b.value) + sizeof(revlimit_b.value) + sizeof(rowcounter_0x77A.value) + sizeof(shled1_b.value) + sizeof(shled2_b.value) + sizeof(shled3_b.value) + sizeof(shled4_b.value) + sizeof(shled5_b.value) + sizeof(speedlimit_b.value) + sizeof(speedlimitreq_b.value) + sizeof(startend_b.value) + sizeof(tair.value) + sizeof(tc_b.value) + sizeof(tex.value) + sizeof(tex_2.value) + sizeof(tfuel.value) + sizeof(tlam.value) + sizeof(tlam_2.value) + sizeof(tmot.value) + sizeof(toil.value);
};

struct STOS_CAN_PDU_Boost_Pressures_Wastegate : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Boost_Pressures_Wastegate() {
		ID = _id;
	}
	static const uint16_t _id = 0x77C;
	CAN_Signal<uint16_t> p22_2m_pwg_m = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> p22_m = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> p22_sp = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> pwg_sp = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> wgdc_2_wgdchold = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> wgdc_wgdcvent = {0, 8, 48};//init,bitcount,startbit 
	void unbuild()
	{
		p22_2m_pwg_m.value = *Val & ~(uint64_t(pow(2, p22_2m_pwg_m.startbit)-1)) & (uint64_t(pow(2, p22_2m_pwg_m.countOfBits)-1) << p22_2m_pwg_m.startbit);
		p22_m.value = *Val & ~(uint64_t(pow(2, p22_m.startbit)-1)) & (uint64_t(pow(2, p22_m.countOfBits)-1) << p22_m.startbit);
		p22_sp.value = *Val & ~(uint64_t(pow(2, p22_sp.startbit)-1)) & (uint64_t(pow(2, p22_sp.countOfBits)-1) << p22_sp.startbit);
		pwg_sp.value = *Val & ~(uint64_t(pow(2, pwg_sp.startbit)-1)) & (uint64_t(pow(2, pwg_sp.countOfBits)-1) << pwg_sp.startbit);
		wgdc_2_wgdchold.value = *Val & ~(uint64_t(pow(2, wgdc_2_wgdchold.startbit)-1)) & (uint64_t(pow(2, wgdc_2_wgdchold.countOfBits)-1) << wgdc_2_wgdchold.startbit);
		wgdc_wgdcvent.value = *Val & ~(uint64_t(pow(2, wgdc_wgdcvent.startbit)-1)) & (uint64_t(pow(2, wgdc_wgdcvent.countOfBits)-1) << wgdc_wgdcvent.startbit);
	}
	void build() {
		*Val = p22_2m_pwg_m.build() | p22_m.build() | p22_sp.build() | pwg_sp.build() | wgdc_2_wgdchold.build() | wgdc_wgdcvent.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(p22_2m_pwg_m.value) + sizeof(p22_m.value) + sizeof(p22_sp.value) + sizeof(pwg_sp.value) + sizeof(wgdc_2_wgdchold.value) + sizeof(wgdc_wgdcvent.value);
};

struct STOS_CAN_PDU_Acceleration_1 : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Acceleration_1() {
		ID = _id;
	}
	static const uint16_t _id = 0x150;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Z = {0, 16, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Accel_1_X.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Accel_1_X.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Accel_1_X.countOfBits)-1) << ADCAN_SP_Accel_1_X.startbit);
		ADCAN_SP_Accel_1_Y.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Accel_1_Y.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Accel_1_Y.countOfBits)-1) << ADCAN_SP_Accel_1_Y.startbit);
		ADCAN_SP_Accel_1_Z.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Accel_1_Z.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Accel_1_Z.countOfBits)-1) << ADCAN_SP_Accel_1_Z.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Accel_1_X.build() | ADCAN_SP_Accel_1_Y.build() | ADCAN_SP_Accel_1_Z.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Accel_1_X.value) + sizeof(ADCAN_SP_Accel_1_Y.value) + sizeof(ADCAN_SP_Accel_1_Z.value);
};

struct STOS_CAN_PDU_Acceleration_2 : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Acceleration_2() {
		ID = _id;
	}
	static const uint16_t _id = 0x151;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Z = {0, 16, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Accel_2_X.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Accel_2_X.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Accel_2_X.countOfBits)-1) << ADCAN_SP_Accel_2_X.startbit);
		ADCAN_SP_Accel_2_Y.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Accel_2_Y.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Accel_2_Y.countOfBits)-1) << ADCAN_SP_Accel_2_Y.startbit);
		ADCAN_SP_Accel_2_Z.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Accel_2_Z.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Accel_2_Z.countOfBits)-1) << ADCAN_SP_Accel_2_Z.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Accel_2_X.build() | ADCAN_SP_Accel_2_Y.build() | ADCAN_SP_Accel_2_Z.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Accel_2_X.value) + sizeof(ADCAN_SP_Accel_2_Y.value) + sizeof(ADCAN_SP_Accel_2_Z.value);
};

struct STOS_CAN_PDU_Aero_Fan_PWM : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Aero_Fan_PWM() {
		ID = _id;
	}
	static const uint16_t _id = 0x157;
	CAN_Signal<uint8_t> ADCAN_AE_Fan_L_PWM = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_AE_Fan_R_PWM = {0, 8, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_AE_Fan_L_PWM.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Fan_L_PWM.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Fan_L_PWM.countOfBits)-1) << ADCAN_AE_Fan_L_PWM.startbit);
		ADCAN_AE_Fan_R_PWM.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Fan_R_PWM.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Fan_R_PWM.countOfBits)-1) << ADCAN_AE_Fan_R_PWM.startbit);
	}
	void build() {
		*Val = ADCAN_AE_Fan_L_PWM.build() | ADCAN_AE_Fan_R_PWM.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Fan_L_PWM.value) + sizeof(ADCAN_AE_Fan_R_PWM.value);
};

struct STOS_CAN_PDU_Aero_Fan_Telemetry : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Aero_Fan_Telemetry() {
		ID = _id;
	}
	static const uint16_t _id = 0x158;
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_1 = {0, 32, 24};//init,bitcount,startbit 
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_2 = {0, 32, 56};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_AE_Fan_Telemetry_1.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Fan_Telemetry_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Fan_Telemetry_1.countOfBits)-1) << ADCAN_AE_Fan_Telemetry_1.startbit);
		ADCAN_AE_Fan_Telemetry_2.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Fan_Telemetry_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Fan_Telemetry_2.countOfBits)-1) << ADCAN_AE_Fan_Telemetry_2.startbit);
	}
	void build() {
		*Val = ADCAN_AE_Fan_Telemetry_1.build() | ADCAN_AE_Fan_Telemetry_2.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Fan_Telemetry_1.value) + sizeof(ADCAN_AE_Fan_Telemetry_2.value);
};

struct STOS_CAN_PDU_Aero_Fan_Warnings : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Aero_Fan_Warnings() {
		ID = _id;
	}
	static const uint16_t _id = 0x105;
	CAN_Signal<uint8_t> ADCAN_AE_Warnings = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_AE_Warnings.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Warnings.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Warnings.countOfBits)-1) << ADCAN_AE_Warnings.startbit);
	}
	void build() {
		*Val = ADCAN_AE_Warnings.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Warnings.value);
};

struct STOS_CAN_PDU_Airbox_Position : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Airbox_Position() {
		ID = _id;
	}
	static const uint16_t _id = 0x200;
	CAN_Signal<uint8_t> ADCAN_PT_Airbox_Pos = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_PT_Airbox_Pos.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Airbox_Pos.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Airbox_Pos.countOfBits)-1) << ADCAN_PT_Airbox_Pos.startbit);
	}
	void build() {
		*Val = ADCAN_PT_Airbox_Pos.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Airbox_Pos.value);
};

struct STOS_CAN_PDU_ARH_Homing : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_ARH_Homing() {
		ID = _id;
	}
	static const uint16_t _id = 0x201;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_Homing = {0, 1, 7};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_Homing = {0, 1, 6};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_ARH_1_Homing.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_ARH_1_Homing.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_ARH_1_Homing.countOfBits)-1) << ADCAN_SP_ARH_1_Homing.startbit);
		ADCAN_SP_ARH_2_Homing.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_ARH_2_Homing.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_ARH_2_Homing.countOfBits)-1) << ADCAN_SP_ARH_2_Homing.startbit);
	}
	void build() {
		*Val = ADCAN_SP_ARH_1_Homing.build() | ADCAN_SP_ARH_2_Homing.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_ARH_1_Homing.value) + sizeof(ADCAN_SP_ARH_2_Homing.value);
};

struct STOS_CAN_PDU_ARH_PWM : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_ARH_PWM() {
		ID = _id;
	}
	static const uint16_t _id = 0x160;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_PWM = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_PWM = {0, 8, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_ARH_1_PWM.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_ARH_1_PWM.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_ARH_1_PWM.countOfBits)-1) << ADCAN_SP_ARH_1_PWM.startbit);
		ADCAN_SP_ARH_2_PWM.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_ARH_2_PWM.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_ARH_2_PWM.countOfBits)-1) << ADCAN_SP_ARH_2_PWM.startbit);
	}
	void build() {
		*Val = ADCAN_SP_ARH_1_PWM.build() | ADCAN_SP_ARH_2_PWM.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_ARH_1_PWM.value) + sizeof(ADCAN_SP_ARH_2_PWM.value);
};

struct STOS_CAN_PDU_Battery_Temp_48V : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Battery_Temp_48V() {
		ID = _id;
	}
	static const uint16_t _id = 0x203;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_3 = {0, 8, 16};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_Battery_48V_Temp_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Battery_48V_Temp_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Battery_48V_Temp_1.countOfBits)-1) << ADCAN_EL_Battery_48V_Temp_1.startbit);
		ADCAN_EL_Battery_48V_Temp_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Battery_48V_Temp_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Battery_48V_Temp_2.countOfBits)-1) << ADCAN_EL_Battery_48V_Temp_2.startbit);
		ADCAN_EL_Battery_48V_Temp_3.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Battery_48V_Temp_3.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Battery_48V_Temp_3.countOfBits)-1) << ADCAN_EL_Battery_48V_Temp_3.startbit);
	}
	void build() {
		*Val = ADCAN_EL_Battery_48V_Temp_1.build() | ADCAN_EL_Battery_48V_Temp_2.build() | ADCAN_EL_Battery_48V_Temp_3.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_Battery_48V_Temp_1.value) + sizeof(ADCAN_EL_Battery_48V_Temp_2.value) + sizeof(ADCAN_EL_Battery_48V_Temp_3.value);
};

struct STOS_CAN_PDU_Brake_Disc_F : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Brake_Disc_F() {
		ID = _id;
	}
	static const uint16_t _id = 0x205;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_FL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_FR = {0, 16, 24};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Brake_Disc_Temp_FL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_FL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_FL.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_FL.startbit);
		ADCAN_SP_Brake_Disc_Temp_FR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_FR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_FR.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_FR.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Brake_Disc_Temp_FL.build() | ADCAN_SP_Brake_Disc_Temp_FR.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Brake_Disc_Temp_FL.value) + sizeof(ADCAN_SP_Brake_Disc_Temp_FR.value);
};

struct STOS_CAN_PDU_Brake_Disc_R : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Brake_Disc_R() {
		ID = _id;
	}
	static const uint16_t _id = 0x206;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_RL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Disc_Temp_RR = {0, 16, 24};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Brake_Disc_Temp_RL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_RL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_RL.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_RL.startbit);
		ADCAN_SP_Brake_Disc_Temp_RR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_RR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Brake_Disc_Temp_RR.countOfBits)-1) << ADCAN_SP_Brake_Disc_Temp_RR.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Brake_Disc_Temp_RL.build() | ADCAN_SP_Brake_Disc_Temp_RR.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Brake_Disc_Temp_RL.value) + sizeof(ADCAN_SP_Brake_Disc_Temp_RR.value);
};

struct STOS_CAN_PDU_Brake_Pressure : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Brake_Pressure() {
		ID = _id;
	}
	static const uint16_t _id = 0x155;
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Pressure_Front = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Brake_Pressure_Rear = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Bias = {0, 8, 32};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Brake_Pressure_Front.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Brake_Pressure_Front.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Brake_Pressure_Front.countOfBits)-1) << ADCAN_SP_Brake_Pressure_Front.startbit);
		ADCAN_SP_Brake_Pressure_Rear.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Brake_Pressure_Rear.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Brake_Pressure_Rear.countOfBits)-1) << ADCAN_SP_Brake_Pressure_Rear.startbit);
		ADCAN_SP_Brake_Bias.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Brake_Bias.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Brake_Bias.countOfBits)-1) << ADCAN_SP_Brake_Bias.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Brake_Pressure_Front.build() | ADCAN_SP_Brake_Pressure_Rear.build() | ADCAN_SP_Brake_Bias.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Brake_Pressure_Front.value) + sizeof(ADCAN_SP_Brake_Pressure_Rear.value) + sizeof(ADCAN_SP_Brake_Bias.value);
};

struct STOS_CAN_PDU_Current_Sensors : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Current_Sensors() {
		ID = _id;
	}
	static const uint16_t _id = 0x208;
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_8 = {0, 8, 56};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_Current_Sensor_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_1.countOfBits)-1) << ADCAN_EL_Current_Sensor_1.startbit);
		ADCAN_EL_Current_Sensor_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_2.countOfBits)-1) << ADCAN_EL_Current_Sensor_2.startbit);
		ADCAN_EL_Current_Sensor_3.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_3.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_3.countOfBits)-1) << ADCAN_EL_Current_Sensor_3.startbit);
		ADCAN_EL_Current_Sensor_4.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_4.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_4.countOfBits)-1) << ADCAN_EL_Current_Sensor_4.startbit);
		ADCAN_EL_Current_Sensor_5.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_5.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_5.countOfBits)-1) << ADCAN_EL_Current_Sensor_5.startbit);
		ADCAN_EL_Current_Sensor_6.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_6.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_6.countOfBits)-1) << ADCAN_EL_Current_Sensor_6.startbit);
		ADCAN_EL_Current_Sensor_7.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_7.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_7.countOfBits)-1) << ADCAN_EL_Current_Sensor_7.startbit);
		ADCAN_EL_Current_Sensor_8.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Current_Sensor_8.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Current_Sensor_8.countOfBits)-1) << ADCAN_EL_Current_Sensor_8.startbit);
	}
	void build() {
		*Val = ADCAN_EL_Current_Sensor_1.build() | ADCAN_EL_Current_Sensor_2.build() | ADCAN_EL_Current_Sensor_3.build() | ADCAN_EL_Current_Sensor_4.build() | ADCAN_EL_Current_Sensor_5.build() | ADCAN_EL_Current_Sensor_6.build() | ADCAN_EL_Current_Sensor_7.build() | ADCAN_EL_Current_Sensor_8.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_Current_Sensor_1.value) + sizeof(ADCAN_EL_Current_Sensor_2.value) + sizeof(ADCAN_EL_Current_Sensor_3.value) + sizeof(ADCAN_EL_Current_Sensor_4.value) + sizeof(ADCAN_EL_Current_Sensor_5.value) + sizeof(ADCAN_EL_Current_Sensor_6.value) + sizeof(ADCAN_EL_Current_Sensor_7.value) + sizeof(ADCAN_EL_Current_Sensor_8.value);
};

struct STOS_CAN_PDU_FCU_ECU_Bat_Temp : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_FCU_ECU_Bat_Temp() {
		ID = _id;
	}
	static const uint16_t _id = 0x210;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_24V_Temp = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_1 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_2 = {0, 8, 16};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_Battery_24V_Temp.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Battery_24V_Temp.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Battery_24V_Temp.countOfBits)-1) << ADCAN_EL_Battery_24V_Temp.startbit);
		ADCAN_EL_ECU_Temp_FCU_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_FCU_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_FCU_1.countOfBits)-1) << ADCAN_EL_ECU_Temp_FCU_1.startbit);
		ADCAN_EL_ECU_Temp_FCU_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_FCU_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_FCU_2.countOfBits)-1) << ADCAN_EL_ECU_Temp_FCU_2.startbit);
	}
	void build() {
		*Val = ADCAN_EL_Battery_24V_Temp.build() | ADCAN_EL_ECU_Temp_FCU_1.build() | ADCAN_EL_ECU_Temp_FCU_2.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_Battery_24V_Temp.value) + sizeof(ADCAN_EL_ECU_Temp_FCU_1.value) + sizeof(ADCAN_EL_ECU_Temp_FCU_2.value);
};

struct STOS_CAN_PDU_FCU_Switches : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_FCU_Switches() {
		ID = _id;
	}
	static const uint16_t _id = 0x212;
	CAN_Signal<uint8_t> ADCAN_SP_ARB_Switch = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Activated = {0, 1, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Switch = {0, 8, 31};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Switch = {0, 8, 16};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_ARB_Switch.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_ARB_Switch.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_ARB_Switch.countOfBits)-1) << ADCAN_SP_ARB_Switch.startbit);
		ADCAN_SP_LaunchC_Activated.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_LaunchC_Activated.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_LaunchC_Activated.countOfBits)-1) << ADCAN_SP_LaunchC_Activated.startbit);
		ADCAN_SP_LaunchC_Switch.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_LaunchC_Switch.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_LaunchC_Switch.countOfBits)-1) << ADCAN_SP_LaunchC_Switch.startbit);
		ADCAN_SP_RAS_Switch.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_RAS_Switch.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_RAS_Switch.countOfBits)-1) << ADCAN_SP_RAS_Switch.startbit);
	}
	void build() {
		*Val = ADCAN_SP_ARB_Switch.build() | ADCAN_SP_LaunchC_Activated.build() | ADCAN_SP_LaunchC_Switch.build() | ADCAN_SP_RAS_Switch.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_ARB_Switch.value) + sizeof(ADCAN_SP_LaunchC_Activated.value) + sizeof(ADCAN_SP_LaunchC_Switch.value) + sizeof(ADCAN_SP_RAS_Switch.value);
};

struct STOS_CAN_PDU_FDS_Parameters : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_FDS_Parameters() {
		ID = _id;
	}
	static const uint16_t _id = 0x215;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Friction_LC = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_mue_max = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Swim_VDE = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_FDS_Velo_VDE = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RL = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RR = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Yaw_VDE = {0, 8, 32};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_FDS_Friction_LC.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Friction_LC.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Friction_LC.countOfBits)-1) << ADCAN_SP_FDS_Friction_LC.startbit);
		ADCAN_SP_FDS_Slip_mue_max.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Slip_mue_max.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Slip_mue_max.countOfBits)-1) << ADCAN_SP_FDS_Slip_mue_max.startbit);
		ADCAN_SP_FDS_Swim_VDE.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Swim_VDE.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Swim_VDE.countOfBits)-1) << ADCAN_SP_FDS_Swim_VDE.startbit);
		ADCAN_SP_FDS_Velo_VDE.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Velo_VDE.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Velo_VDE.countOfBits)-1) << ADCAN_SP_FDS_Velo_VDE.startbit);
		ADCAN_SP_FDS_Wheel_Slip_RL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Wheel_Slip_RL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Wheel_Slip_RL.countOfBits)-1) << ADCAN_SP_FDS_Wheel_Slip_RL.startbit);
		ADCAN_SP_FDS_Wheel_Slip_RR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Wheel_Slip_RR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Wheel_Slip_RR.countOfBits)-1) << ADCAN_SP_FDS_Wheel_Slip_RR.startbit);
		ADCAN_SP_FDS_Yaw_VDE.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Yaw_VDE.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Yaw_VDE.countOfBits)-1) << ADCAN_SP_FDS_Yaw_VDE.startbit);
	}
	void build() {
		*Val = ADCAN_SP_FDS_Friction_LC.build() | ADCAN_SP_FDS_Slip_mue_max.build() | ADCAN_SP_FDS_Swim_VDE.build() | ADCAN_SP_FDS_Velo_VDE.build() | ADCAN_SP_FDS_Wheel_Slip_RL.build() | ADCAN_SP_FDS_Wheel_Slip_RR.build() | ADCAN_SP_FDS_Yaw_VDE.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_FDS_Friction_LC.value) + sizeof(ADCAN_SP_FDS_Slip_mue_max.value) + sizeof(ADCAN_SP_FDS_Swim_VDE.value) + sizeof(ADCAN_SP_FDS_Velo_VDE.value) + sizeof(ADCAN_SP_FDS_Wheel_Slip_RL.value) + sizeof(ADCAN_SP_FDS_Wheel_Slip_RR.value) + sizeof(ADCAN_SP_FDS_Yaw_VDE.value);
};

struct STOS_CAN_PDU_FDS_Wheel_Signals : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_FDS_Wheel_Signals() {
		ID = _id;
	}
	static const uint16_t _id = 0x216;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FL = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FR = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RL = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RR = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FL = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FR = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RL = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RR = {0, 8, 56};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_FDS_Slip_Angle_FL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_FL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_FL.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_FL.startbit);
		ADCAN_SP_FDS_Slip_Angle_FR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_FR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_FR.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_FR.startbit);
		ADCAN_SP_FDS_Slip_Angle_RL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_RL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_RL.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_RL.startbit);
		ADCAN_SP_FDS_Slip_Angle_RR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_RR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Slip_Angle_RR.countOfBits)-1) << ADCAN_SP_FDS_Slip_Angle_RR.startbit);
		ADCAN_SP_FDS_Whl_Load_FL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_FL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_FL.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_FL.startbit);
		ADCAN_SP_FDS_Whl_Load_FR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_FR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_FR.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_FR.startbit);
		ADCAN_SP_FDS_Whl_Load_RL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_RL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_RL.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_RL.startbit);
		ADCAN_SP_FDS_Whl_Load_RR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_RR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_FDS_Whl_Load_RR.countOfBits)-1) << ADCAN_SP_FDS_Whl_Load_RR.startbit);
	}
	void build() {
		*Val = ADCAN_SP_FDS_Slip_Angle_FL.build() | ADCAN_SP_FDS_Slip_Angle_FR.build() | ADCAN_SP_FDS_Slip_Angle_RL.build() | ADCAN_SP_FDS_Slip_Angle_RR.build() | ADCAN_SP_FDS_Whl_Load_FL.build() | ADCAN_SP_FDS_Whl_Load_FR.build() | ADCAN_SP_FDS_Whl_Load_RL.build() | ADCAN_SP_FDS_Whl_Load_RR.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_FDS_Slip_Angle_FL.value) + sizeof(ADCAN_SP_FDS_Slip_Angle_FR.value) + sizeof(ADCAN_SP_FDS_Slip_Angle_RL.value) + sizeof(ADCAN_SP_FDS_Slip_Angle_RR.value) + sizeof(ADCAN_SP_FDS_Whl_Load_FL.value) + sizeof(ADCAN_SP_FDS_Whl_Load_FR.value) + sizeof(ADCAN_SP_FDS_Whl_Load_RL.value) + sizeof(ADCAN_SP_FDS_Whl_Load_RR.value);
};

struct STOS_CAN_PDU_Flash_Over_Can : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Flash_Over_Can() {
		ID = _id;
	}
	static const uint16_t _id = 0x222;
	CAN_Signal<uint8_t> ADCAN_EL_FoC_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_FoC_2 = {0, 8, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_FoC_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_FoC_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_FoC_1.countOfBits)-1) << ADCAN_EL_FoC_1.startbit);
		ADCAN_EL_FoC_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_FoC_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_FoC_2.countOfBits)-1) << ADCAN_EL_FoC_2.startbit);
	}
	void build() {
		*Val = ADCAN_EL_FoC_1.build() | ADCAN_EL_FoC_2.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_FoC_1.value) + sizeof(ADCAN_EL_FoC_2.value);
};

struct STOS_CAN_PDU_Frame_Pressure : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Frame_Pressure() {
		ID = _id;
	}
	static const uint16_t _id = 0x218;
	CAN_Signal<uint8_t> ADCAN_CH_Frame_Pressure = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_CH_Frame_Pressure.value = *Val & ~(uint64_t(pow(2, ADCAN_CH_Frame_Pressure.startbit)-1)) & (uint64_t(pow(2, ADCAN_CH_Frame_Pressure.countOfBits)-1) << ADCAN_CH_Frame_Pressure.startbit);
	}
	void build() {
		*Val = ADCAN_CH_Frame_Pressure.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_CH_Frame_Pressure.value);
};

struct STOS_CAN_PDU_Gyroscope_1 : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Gyroscope_1() {
		ID = _id;
	}
	static const uint16_t _id = 0x152;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Z = {0, 16, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Gyro_1_X.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Gyro_1_X.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Gyro_1_X.countOfBits)-1) << ADCAN_SP_Gyro_1_X.startbit);
		ADCAN_SP_Gyro_1_Y.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Gyro_1_Y.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Gyro_1_Y.countOfBits)-1) << ADCAN_SP_Gyro_1_Y.startbit);
		ADCAN_SP_Gyro_1_Z.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Gyro_1_Z.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Gyro_1_Z.countOfBits)-1) << ADCAN_SP_Gyro_1_Z.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Gyro_1_X.build() | ADCAN_SP_Gyro_1_Y.build() | ADCAN_SP_Gyro_1_Z.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Gyro_1_X.value) + sizeof(ADCAN_SP_Gyro_1_Y.value) + sizeof(ADCAN_SP_Gyro_1_Z.value);
};

struct STOS_CAN_PDU_Gyroscope_2 : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Gyroscope_2() {
		ID = _id;
	}
	static const uint16_t _id = 0x153;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Z = {0, 16, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Gyro_2_X.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Gyro_2_X.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Gyro_2_X.countOfBits)-1) << ADCAN_SP_Gyro_2_X.startbit);
		ADCAN_SP_Gyro_2_Y.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Gyro_2_Y.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Gyro_2_Y.countOfBits)-1) << ADCAN_SP_Gyro_2_Y.startbit);
		ADCAN_SP_Gyro_2_Z.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Gyro_2_Z.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Gyro_2_Z.countOfBits)-1) << ADCAN_SP_Gyro_2_Z.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Gyro_2_X.build() | ADCAN_SP_Gyro_2_Y.build() | ADCAN_SP_Gyro_2_Z.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Gyro_2_X.value) + sizeof(ADCAN_SP_Gyro_2_Y.value) + sizeof(ADCAN_SP_Gyro_2_Z.value);
};

struct STOS_CAN_PDU_Niveau_F : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Niveau_F() {
		ID = _id;
	}
	static const uint16_t _id = 0x111;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Niveau = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Niveau = {0, 8, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Niveau_FL_Niveau.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FL_Niveau.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FL_Niveau.countOfBits)-1) << ADCAN_SP_Niveau_FL_Niveau.startbit);
		ADCAN_SP_Niveau_FR_Niveau.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FR_Niveau.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FR_Niveau.countOfBits)-1) << ADCAN_SP_Niveau_FR_Niveau.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Niveau_FL_Niveau.build() | ADCAN_SP_Niveau_FR_Niveau.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_FL_Niveau.value) + sizeof(ADCAN_SP_Niveau_FR_Niveau.value);
};

struct STOS_CAN_PDU_Niveau_Front_Status : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Niveau_Front_Status() {
		ID = _id;
	}
	static const uint16_t _id = 0x219;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Error = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Function = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_on_off = {0, 1, 22};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Error = {0, 1, 18};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Function = {0, 8, 21};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_on_off = {0, 1, 20};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Niveau_FL_Error.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FL_Error.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FL_Error.countOfBits)-1) << ADCAN_SP_Niveau_FL_Error.startbit);
		ADCAN_SP_Niveau_FL_Function.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FL_Function.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FL_Function.countOfBits)-1) << ADCAN_SP_Niveau_FL_Function.startbit);
		ADCAN_SP_Niveau_FL_on_off.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FL_on_off.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FL_on_off.countOfBits)-1) << ADCAN_SP_Niveau_FL_on_off.startbit);
		ADCAN_SP_Niveau_FR_Error.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FR_Error.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FR_Error.countOfBits)-1) << ADCAN_SP_Niveau_FR_Error.startbit);
		ADCAN_SP_Niveau_FR_Function.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FR_Function.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FR_Function.countOfBits)-1) << ADCAN_SP_Niveau_FR_Function.startbit);
		ADCAN_SP_Niveau_FR_on_off.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_FR_on_off.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_FR_on_off.countOfBits)-1) << ADCAN_SP_Niveau_FR_on_off.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Niveau_FL_Error.build() | ADCAN_SP_Niveau_FL_Function.build() | ADCAN_SP_Niveau_FL_on_off.build() | ADCAN_SP_Niveau_FR_Error.build() | ADCAN_SP_Niveau_FR_Function.build() | ADCAN_SP_Niveau_FR_on_off.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_FL_Error.value) + sizeof(ADCAN_SP_Niveau_FL_Function.value) + sizeof(ADCAN_SP_Niveau_FL_on_off.value) + sizeof(ADCAN_SP_Niveau_FR_Error.value) + sizeof(ADCAN_SP_Niveau_FR_Function.value) + sizeof(ADCAN_SP_Niveau_FR_on_off.value);
};

struct STOS_CAN_PDU_Niveau_R : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Niveau_R() {
		ID = _id;
	}
	static const uint16_t _id = 0x110;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Niveau = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Niveau_R_Niveau.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_R_Niveau.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_R_Niveau.countOfBits)-1) << ADCAN_SP_Niveau_R_Niveau.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Niveau_R_Niveau.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_R_Niveau.value);
};

struct STOS_CAN_PDU_Niveau_Rear_Status : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Niveau_Rear_Status() {
		ID = _id;
	}
	static const uint16_t _id = 0x220;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Error = {0, 1, 15};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Function = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Niveau_R_Error.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_R_Error.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_R_Error.countOfBits)-1) << ADCAN_SP_Niveau_R_Error.startbit);
		ADCAN_SP_Niveau_R_Function.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Niveau_R_Function.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Niveau_R_Function.countOfBits)-1) << ADCAN_SP_Niveau_R_Function.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Niveau_R_Error.build() | ADCAN_SP_Niveau_R_Function.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_R_Error.value) + sizeof(ADCAN_SP_Niveau_R_Function.value);
};

struct STOS_CAN_PDU_Oil_Pressure : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Oil_Pressure() {
		ID = _id;
	}
	static const uint16_t _id = 0x163;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Pressure = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_PT_Oil_Pressure.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Oil_Pressure.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Oil_Pressure.countOfBits)-1) << ADCAN_PT_Oil_Pressure.startbit);
	}
	void build() {
		*Val = ADCAN_PT_Oil_Pressure.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Oil_Pressure.value);
};

struct STOS_CAN_PDU_Oil_Pressure_Status : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Oil_Pressure_Status() {
		ID = _id;
	}
	static const uint16_t _id = 0x224;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level_RS232 = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Temp = {0, 8, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_PT_Oil_Level.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Oil_Level.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Oil_Level.countOfBits)-1) << ADCAN_PT_Oil_Level.startbit);
		ADCAN_PT_Oil_Level_RS232.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Oil_Level_RS232.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Oil_Level_RS232.countOfBits)-1) << ADCAN_PT_Oil_Level_RS232.startbit);
		ADCAN_PT_Oil_Temp.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Oil_Temp.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Oil_Temp.countOfBits)-1) << ADCAN_PT_Oil_Temp.startbit);
	}
	void build() {
		*Val = ADCAN_PT_Oil_Level.build() | ADCAN_PT_Oil_Level_RS232.build() | ADCAN_PT_Oil_Temp.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Oil_Level.value) + sizeof(ADCAN_PT_Oil_Level_RS232.value) + sizeof(ADCAN_PT_Oil_Temp.value);
};

struct STOS_CAN_PDU_PDU_ECU_Temp : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_PDU_ECU_Temp() {
		ID = _id;
	}
	static const uint16_t _id = 0x230;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_4 = {0, 8, 24};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_PDU_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_1.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_1.startbit);
		ADCAN_EL_ECU_Temp_PDU_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_2.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_2.startbit);
		ADCAN_EL_ECU_Temp_PDU_3.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_3.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_3.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_3.startbit);
		ADCAN_EL_ECU_Temp_PDU_4.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_4.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_PDU_4.countOfBits)-1) << ADCAN_EL_ECU_Temp_PDU_4.startbit);
	}
	void build() {
		*Val = ADCAN_EL_ECU_Temp_PDU_1.build() | ADCAN_EL_ECU_Temp_PDU_2.build() | ADCAN_EL_ECU_Temp_PDU_3.build() | ADCAN_EL_ECU_Temp_PDU_4.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_ECU_Temp_PDU_1.value) + sizeof(ADCAN_EL_ECU_Temp_PDU_2.value) + sizeof(ADCAN_EL_ECU_Temp_PDU_3.value) + sizeof(ADCAN_EL_ECU_Temp_PDU_4.value);
};

struct STOS_CAN_PDU_PDU_Status : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_PDU_Status() {
		ID = _id;
	}
	static const uint16_t _id = 0x226;
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
	void unbuild()
	{
		ADCAN_CH_Mainhoop_Diag_L_1.value = *Val & ~(uint64_t(pow(2, ADCAN_CH_Mainhoop_Diag_L_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_CH_Mainhoop_Diag_L_1.countOfBits)-1) << ADCAN_CH_Mainhoop_Diag_L_1.startbit);
		ADCAN_CH_Mainhoop_Diag_R_1.value = *Val & ~(uint64_t(pow(2, ADCAN_CH_Mainhoop_Diag_R_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_CH_Mainhoop_Diag_R_1.countOfBits)-1) << ADCAN_CH_Mainhoop_Diag_R_1.startbit);
		ADCAN_EL_BOTS_Diag_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_BOTS_Diag_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_BOTS_Diag_1.countOfBits)-1) << ADCAN_EL_BOTS_Diag_1.startbit);
		ADCAN_EL_BSPD_Shutdown_Out.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_BSPD_Shutdown_Out.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_BSPD_Shutdown_Out.countOfBits)-1) << ADCAN_EL_BSPD_Shutdown_Out.startbit);
		ADCAN_EL_Cockpit_Diag_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Cockpit_Diag_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Cockpit_Diag_1.countOfBits)-1) << ADCAN_EL_Cockpit_Diag_1.startbit);
		ADCAN_EL_Crash_Diag.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Crash_Diag.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Crash_Diag.countOfBits)-1) << ADCAN_EL_Crash_Diag.startbit);
		ADCAN_EL_Fuse_Status_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_1.countOfBits)-1) << ADCAN_EL_Fuse_Status_1.startbit);
		ADCAN_EL_Fuse_Status_10.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_10.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_10.countOfBits)-1) << ADCAN_EL_Fuse_Status_10.startbit);
		ADCAN_EL_Fuse_Status_11.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_11.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_11.countOfBits)-1) << ADCAN_EL_Fuse_Status_11.startbit);
		ADCAN_EL_Fuse_Status_12.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_12.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_12.countOfBits)-1) << ADCAN_EL_Fuse_Status_12.startbit);
		ADCAN_EL_Fuse_Status_13.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_13.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_13.countOfBits)-1) << ADCAN_EL_Fuse_Status_13.startbit);
		ADCAN_EL_Fuse_Status_14.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_14.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_14.countOfBits)-1) << ADCAN_EL_Fuse_Status_14.startbit);
		ADCAN_EL_Fuse_Status_15.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_15.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_15.countOfBits)-1) << ADCAN_EL_Fuse_Status_15.startbit);
		ADCAN_EL_Fuse_Status_16.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_16.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_16.countOfBits)-1) << ADCAN_EL_Fuse_Status_16.startbit);
		ADCAN_EL_Fuse_Status_17.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_17.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_17.countOfBits)-1) << ADCAN_EL_Fuse_Status_17.startbit);
		ADCAN_EL_Fuse_Status_18.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_18.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_18.countOfBits)-1) << ADCAN_EL_Fuse_Status_18.startbit);
		ADCAN_EL_Fuse_Status_19.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_19.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_19.countOfBits)-1) << ADCAN_EL_Fuse_Status_19.startbit);
		ADCAN_EL_Fuse_Status_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_2.countOfBits)-1) << ADCAN_EL_Fuse_Status_2.startbit);
		ADCAN_EL_Fuse_Status_3.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_3.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_3.countOfBits)-1) << ADCAN_EL_Fuse_Status_3.startbit);
		ADCAN_EL_Fuse_Status_4.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_4.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_4.countOfBits)-1) << ADCAN_EL_Fuse_Status_4.startbit);
		ADCAN_EL_Fuse_Status_5.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_5.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_5.countOfBits)-1) << ADCAN_EL_Fuse_Status_5.startbit);
		ADCAN_EL_Fuse_Status_6.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_6.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_6.countOfBits)-1) << ADCAN_EL_Fuse_Status_6.startbit);
		ADCAN_EL_Fuse_Status_7.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_7.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_7.countOfBits)-1) << ADCAN_EL_Fuse_Status_7.startbit);
		ADCAN_EL_Fuse_Status_8.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_8.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_8.countOfBits)-1) << ADCAN_EL_Fuse_Status_8.startbit);
		ADCAN_EL_Fuse_Status_9.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Fuse_Status_9.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Fuse_Status_9.countOfBits)-1) << ADCAN_EL_Fuse_Status_9.startbit);
		ADCAN_EL_Relais_Status_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Relais_Status_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Relais_Status_1.countOfBits)-1) << ADCAN_EL_Relais_Status_1.startbit);
		ADCAN_EL_Relais_Status_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Relais_Status_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Relais_Status_2.countOfBits)-1) << ADCAN_EL_Relais_Status_2.startbit);
		ADCAN_EL_Shutdown_Cockpit.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Shutdown_Cockpit.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Shutdown_Cockpit.countOfBits)-1) << ADCAN_EL_Shutdown_Cockpit.startbit);
		ADCAN_PT_Fuel_Pump_Signal.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Fuel_Pump_Signal.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Fuel_Pump_Signal.countOfBits)-1) << ADCAN_PT_Fuel_Pump_Signal.startbit);
		ADCAN_PT_Reserve_Signal_L.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Reserve_Signal_L.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Reserve_Signal_L.countOfBits)-1) << ADCAN_PT_Reserve_Signal_L.startbit);
		ADCAN_PT_Reserve_Signal_R.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Reserve_Signal_R.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Reserve_Signal_R.countOfBits)-1) << ADCAN_PT_Reserve_Signal_R.startbit);
		ADCAN_PT_Water_Pump_Signal.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Water_Pump_Signal.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Water_Pump_Signal.countOfBits)-1) << ADCAN_PT_Water_Pump_Signal.startbit);
	}
	void build() {
		*Val = ADCAN_CH_Mainhoop_Diag_L_1.build() | ADCAN_CH_Mainhoop_Diag_R_1.build() | ADCAN_EL_BOTS_Diag_1.build() | ADCAN_EL_BSPD_Shutdown_Out.build() | ADCAN_EL_Cockpit_Diag_1.build() | ADCAN_EL_Crash_Diag.build() | ADCAN_EL_Fuse_Status_1.build() | ADCAN_EL_Fuse_Status_10.build() | ADCAN_EL_Fuse_Status_11.build() | ADCAN_EL_Fuse_Status_12.build() | ADCAN_EL_Fuse_Status_13.build() | ADCAN_EL_Fuse_Status_14.build() | ADCAN_EL_Fuse_Status_15.build() | ADCAN_EL_Fuse_Status_16.build() | ADCAN_EL_Fuse_Status_17.build() | ADCAN_EL_Fuse_Status_18.build() | ADCAN_EL_Fuse_Status_19.build() | ADCAN_EL_Fuse_Status_2.build() | ADCAN_EL_Fuse_Status_3.build() | ADCAN_EL_Fuse_Status_4.build() | ADCAN_EL_Fuse_Status_5.build() | ADCAN_EL_Fuse_Status_6.build() | ADCAN_EL_Fuse_Status_7.build() | ADCAN_EL_Fuse_Status_8.build() | ADCAN_EL_Fuse_Status_9.build() | ADCAN_EL_Relais_Status_1.build() | ADCAN_EL_Relais_Status_2.build() | ADCAN_EL_Shutdown_Cockpit.build() | ADCAN_PT_Fuel_Pump_Signal.build() | ADCAN_PT_Reserve_Signal_L.build() | ADCAN_PT_Reserve_Signal_R.build() | ADCAN_PT_Water_Pump_Signal.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_CH_Mainhoop_Diag_L_1.value) + sizeof(ADCAN_CH_Mainhoop_Diag_R_1.value) + sizeof(ADCAN_EL_BOTS_Diag_1.value) + sizeof(ADCAN_EL_BSPD_Shutdown_Out.value) + sizeof(ADCAN_EL_Cockpit_Diag_1.value) + sizeof(ADCAN_EL_Crash_Diag.value) + sizeof(ADCAN_EL_Fuse_Status_1.value) + sizeof(ADCAN_EL_Fuse_Status_10.value) + sizeof(ADCAN_EL_Fuse_Status_11.value) + sizeof(ADCAN_EL_Fuse_Status_12.value) + sizeof(ADCAN_EL_Fuse_Status_13.value) + sizeof(ADCAN_EL_Fuse_Status_14.value) + sizeof(ADCAN_EL_Fuse_Status_15.value) + sizeof(ADCAN_EL_Fuse_Status_16.value) + sizeof(ADCAN_EL_Fuse_Status_17.value) + sizeof(ADCAN_EL_Fuse_Status_18.value) + sizeof(ADCAN_EL_Fuse_Status_19.value) + sizeof(ADCAN_EL_Fuse_Status_2.value) + sizeof(ADCAN_EL_Fuse_Status_3.value) + sizeof(ADCAN_EL_Fuse_Status_4.value) + sizeof(ADCAN_EL_Fuse_Status_5.value) + sizeof(ADCAN_EL_Fuse_Status_6.value) + sizeof(ADCAN_EL_Fuse_Status_7.value) + sizeof(ADCAN_EL_Fuse_Status_8.value) + sizeof(ADCAN_EL_Fuse_Status_9.value) + sizeof(ADCAN_EL_Relais_Status_1.value) + sizeof(ADCAN_EL_Relais_Status_2.value) + sizeof(ADCAN_EL_Shutdown_Cockpit.value) + sizeof(ADCAN_PT_Fuel_Pump_Signal.value) + sizeof(ADCAN_PT_Reserve_Signal_L.value) + sizeof(ADCAN_PT_Reserve_Signal_R.value) + sizeof(ADCAN_PT_Water_Pump_Signal.value);
};

struct STOS_CAN_PDU_Pitot : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Pitot() {
		ID = _id;
	}
	static const uint16_t _id = 0x232;
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_AE_Pitot_3 = {0, 16, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_AE_Pitot_1.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Pitot_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Pitot_1.countOfBits)-1) << ADCAN_AE_Pitot_1.startbit);
		ADCAN_AE_Pitot_2.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Pitot_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Pitot_2.countOfBits)-1) << ADCAN_AE_Pitot_2.startbit);
		ADCAN_AE_Pitot_3.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Pitot_3.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Pitot_3.countOfBits)-1) << ADCAN_AE_Pitot_3.startbit);
	}
	void build() {
		*Val = ADCAN_AE_Pitot_1.build() | ADCAN_AE_Pitot_2.build() | ADCAN_AE_Pitot_3.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Pitot_1.value) + sizeof(ADCAN_AE_Pitot_2.value) + sizeof(ADCAN_AE_Pitot_3.value);
};

struct STOS_CAN_PDU_RAS_PWM : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_RAS_PWM() {
		ID = _id;
	}
	static const uint16_t _id = 0x161;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_L = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_R = {0, 8, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_RAS_PWM_L.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_RAS_PWM_L.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_RAS_PWM_L.countOfBits)-1) << ADCAN_SP_RAS_PWM_L.startbit);
		ADCAN_SP_RAS_PWM_R.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_RAS_PWM_R.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_RAS_PWM_R.countOfBits)-1) << ADCAN_SP_RAS_PWM_R.startbit);
	}
	void build() {
		*Val = ADCAN_SP_RAS_PWM_L.build() | ADCAN_SP_RAS_PWM_R.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_RAS_PWM_L.value) + sizeof(ADCAN_SP_RAS_PWM_R.value);
};

struct STOS_CAN_PDU_RAS_Status_Control : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_RAS_Status_Control() {
		ID = _id;
	}
	static const uint16_t _id = 0x234;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Angle = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_L = {0, 1, 15};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_R = {0, 1, 14};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_RAS_Angle.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_RAS_Angle.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_RAS_Angle.countOfBits)-1) << ADCAN_SP_RAS_Angle.startbit);
		ADCAN_SP_RAS_Homing_L.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_RAS_Homing_L.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_RAS_Homing_L.countOfBits)-1) << ADCAN_SP_RAS_Homing_L.startbit);
		ADCAN_SP_RAS_Homing_R.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_RAS_Homing_R.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_RAS_Homing_R.countOfBits)-1) << ADCAN_SP_RAS_Homing_R.startbit);
	}
	void build() {
		*Val = ADCAN_SP_RAS_Angle.build() | ADCAN_SP_RAS_Homing_L.build() | ADCAN_SP_RAS_Homing_R.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_RAS_Angle.value) + sizeof(ADCAN_SP_RAS_Homing_L.value) + sizeof(ADCAN_SP_RAS_Homing_R.value);
};

struct STOS_CAN_PDU_RCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_RCU_ECU_Temp() {
		ID = _id;
	}
	static const uint16_t _id = 0x236;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_2 = {0, 8, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_RCU_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_RCU_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_RCU_1.countOfBits)-1) << ADCAN_EL_ECU_Temp_RCU_1.startbit);
		ADCAN_EL_ECU_Temp_RCU_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_RCU_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_RCU_2.countOfBits)-1) << ADCAN_EL_ECU_Temp_RCU_2.startbit);
	}
	void build() {
		*Val = ADCAN_EL_ECU_Temp_RCU_1.build() | ADCAN_EL_ECU_Temp_RCU_2.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_ECU_Temp_RCU_1.value) + sizeof(ADCAN_EL_ECU_Temp_RCU_2.value);
};

struct STOS_CAN_PDU_RCU_Test_A : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_RCU_Test_A() {
		ID = _id;
	}
	static const uint16_t _id = 0x165;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_3 = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_4 = {0, 16, 56};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_1.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_1.countOfBits)-1) << ADCAN_ZZ_Test_RCU_1.startbit);
		ADCAN_ZZ_Test_RCU_2.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_2.countOfBits)-1) << ADCAN_ZZ_Test_RCU_2.startbit);
		ADCAN_ZZ_Test_RCU_3.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_3.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_3.countOfBits)-1) << ADCAN_ZZ_Test_RCU_3.startbit);
		ADCAN_ZZ_Test_RCU_4.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_4.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_4.countOfBits)-1) << ADCAN_ZZ_Test_RCU_4.startbit);
	}
	void build() {
		*Val = ADCAN_ZZ_Test_RCU_1.build() | ADCAN_ZZ_Test_RCU_2.build() | ADCAN_ZZ_Test_RCU_3.build() | ADCAN_ZZ_Test_RCU_4.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_RCU_1.value) + sizeof(ADCAN_ZZ_Test_RCU_2.value) + sizeof(ADCAN_ZZ_Test_RCU_3.value) + sizeof(ADCAN_ZZ_Test_RCU_4.value);
};

struct STOS_CAN_PDU_RCU_Test_B : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_RCU_Test_B() {
		ID = _id;
	}
	static const uint16_t _id = 0x166;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_5 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_6 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_7 = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_8 = {0, 16, 56};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_5.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_5.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_5.countOfBits)-1) << ADCAN_ZZ_Test_RCU_5.startbit);
		ADCAN_ZZ_Test_RCU_6.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_6.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_6.countOfBits)-1) << ADCAN_ZZ_Test_RCU_6.startbit);
		ADCAN_ZZ_Test_RCU_7.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_7.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_7.countOfBits)-1) << ADCAN_ZZ_Test_RCU_7.startbit);
		ADCAN_ZZ_Test_RCU_8.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_8.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_8.countOfBits)-1) << ADCAN_ZZ_Test_RCU_8.startbit);
	}
	void build() {
		*Val = ADCAN_ZZ_Test_RCU_5.build() | ADCAN_ZZ_Test_RCU_6.build() | ADCAN_ZZ_Test_RCU_7.build() | ADCAN_ZZ_Test_RCU_8.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_RCU_5.value) + sizeof(ADCAN_ZZ_Test_RCU_6.value) + sizeof(ADCAN_ZZ_Test_RCU_7.value) + sizeof(ADCAN_ZZ_Test_RCU_8.value);
};

struct STOS_CAN_PDU_RCU_Test_C : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_RCU_Test_C() {
		ID = _id;
	}
	static const uint16_t _id = 0x167;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_10 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_9 = {0, 16, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_ZZ_Test_RCU_10.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_10.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_10.countOfBits)-1) << ADCAN_ZZ_Test_RCU_10.startbit);
		ADCAN_ZZ_Test_RCU_9.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_RCU_9.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_RCU_9.countOfBits)-1) << ADCAN_ZZ_Test_RCU_9.startbit);
	}
	void build() {
		*Val = ADCAN_ZZ_Test_RCU_10.build() | ADCAN_ZZ_Test_RCU_9.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_RCU_10.value) + sizeof(ADCAN_ZZ_Test_RCU_9.value);
};

struct STOS_CAN_PDU_Rocker_F : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Rocker_F() {
		ID = _id;
	}
	static const uint16_t _id = 0x238;
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_FL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_FR = {0, 16, 24};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Rocker_FL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Rocker_FL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Rocker_FL.countOfBits)-1) << ADCAN_SP_Rocker_FL.startbit);
		ADCAN_SP_Rocker_FR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Rocker_FR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Rocker_FR.countOfBits)-1) << ADCAN_SP_Rocker_FR.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Rocker_FL.build() | ADCAN_SP_Rocker_FR.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Rocker_FL.value) + sizeof(ADCAN_SP_Rocker_FR.value);
};

struct STOS_CAN_PDU_Rocker_R : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Rocker_R() {
		ID = _id;
	}
	static const uint16_t _id = 0x239;
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_RL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Rocker_RR = {0, 16, 24};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Rocker_RL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Rocker_RL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Rocker_RL.countOfBits)-1) << ADCAN_SP_Rocker_RL.startbit);
		ADCAN_SP_Rocker_RR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Rocker_RR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Rocker_RR.countOfBits)-1) << ADCAN_SP_Rocker_RR.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Rocker_RL.build() | ADCAN_SP_Rocker_RR.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Rocker_RL.value) + sizeof(ADCAN_SP_Rocker_RR.value);
};

struct STOS_CAN_PDU_Shift_Clutch : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Shift_Clutch() {
		ID = _id;
	}
	static const uint16_t _id = 0x170;
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_DigIn = {0, 1, 21};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_LaunchC = {0, 1, 20};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_PT_Shift_Force_Sensor = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_DigIn = {0, 1, 23};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_LaunchC = {0, 1, 22};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Force_on_off = {0, 1, 19};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_PT_Gearshift_DigIn.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Gearshift_DigIn.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Gearshift_DigIn.countOfBits)-1) << ADCAN_PT_Gearshift_DigIn.startbit);
		ADCAN_PT_Gearshift_LaunchC.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Gearshift_LaunchC.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Gearshift_LaunchC.countOfBits)-1) << ADCAN_PT_Gearshift_LaunchC.startbit);
		ADCAN_PT_Shift_Force_Sensor.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Shift_Force_Sensor.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Shift_Force_Sensor.countOfBits)-1) << ADCAN_PT_Shift_Force_Sensor.startbit);
		ADCAN_SP_Clutch_DigIn.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Clutch_DigIn.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Clutch_DigIn.countOfBits)-1) << ADCAN_SP_Clutch_DigIn.startbit);
		ADCAN_SP_Clutch_LaunchC.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Clutch_LaunchC.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Clutch_LaunchC.countOfBits)-1) << ADCAN_SP_Clutch_LaunchC.startbit);
		ADCAN_PT_Shift_Force_on_off.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Shift_Force_on_off.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Shift_Force_on_off.countOfBits)-1) << ADCAN_PT_Shift_Force_on_off.startbit);
	}
	void build() {
		*Val = ADCAN_PT_Gearshift_DigIn.build() | ADCAN_PT_Gearshift_LaunchC.build() | ADCAN_PT_Shift_Force_Sensor.build() | ADCAN_SP_Clutch_DigIn.build() | ADCAN_SP_Clutch_LaunchC.build() | ADCAN_PT_Shift_Force_on_off.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Gearshift_DigIn.value) + sizeof(ADCAN_PT_Gearshift_LaunchC.value) + sizeof(ADCAN_PT_Shift_Force_Sensor.value) + sizeof(ADCAN_SP_Clutch_DigIn.value) + sizeof(ADCAN_SP_Clutch_LaunchC.value) + sizeof(ADCAN_PT_Shift_Force_on_off.value);
};

struct STOS_CAN_PDU_Steering_Whl_Angle : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Steering_Whl_Angle() {
		ID = _id;
	}
	static const uint16_t _id = 0x172;
	CAN_Signal<uint16_t> ADCAN_SP_Steering_Wheel_Angle = {0, 16, 8};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Steering_Wheel_Angle.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Steering_Wheel_Angle.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Steering_Wheel_Angle.countOfBits)-1) << ADCAN_SP_Steering_Wheel_Angle.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Steering_Wheel_Angle.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Steering_Wheel_Angle.value);
};

struct STOS_CAN_PDU_SWCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_SWCU_ECU_Temp() {
		ID = _id;
	}
	static const uint16_t _id = 0x244;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_SWCU = {0, 8, 0};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_ECU_Temp_SWCU.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_ECU_Temp_SWCU.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_ECU_Temp_SWCU.countOfBits)-1) << ADCAN_EL_ECU_Temp_SWCU.startbit);
	}
	void build() {
		*Val = ADCAN_EL_ECU_Temp_SWCU.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_ECU_Temp_SWCU.value);
};

struct STOS_CAN_PDU_SWCU_Oh_Shit : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_SWCU_Oh_Shit() {
		ID = _id;
	}
	static const uint16_t _id = 0x175;
	CAN_Signal<uint8_t> ADCAN_EL_INCR_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_INCR_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Oh_Shit = {0, 1, 23};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_EL_INCR_1.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_INCR_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_INCR_1.countOfBits)-1) << ADCAN_EL_INCR_1.startbit);
		ADCAN_EL_INCR_2.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_INCR_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_INCR_2.countOfBits)-1) << ADCAN_EL_INCR_2.startbit);
		ADCAN_EL_Oh_Shit.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Oh_Shit.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Oh_Shit.countOfBits)-1) << ADCAN_EL_Oh_Shit.startbit);
	}
	void build() {
		*Val = ADCAN_EL_INCR_1.build() | ADCAN_EL_INCR_2.build() | ADCAN_EL_Oh_Shit.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_INCR_1.value) + sizeof(ADCAN_EL_INCR_2.value) + sizeof(ADCAN_EL_Oh_Shit.value);
};

struct STOS_CAN_PDU_SWCU_Switches : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_SWCU_Switches() {
		ID = _id;
	}
	static const uint16_t _id = 0x099;
	CAN_Signal<uint8_t> ADCAN_AE_Switch_1 = {0, 1, 2};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Radio_Switch = {0, 1, 3};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Down = {0, 1, 4};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Up = {0, 1, 5};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_switch_1 = {0, 1, 6};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_Signal = {0, 1, 7};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_AE_Switch_1.value = *Val & ~(uint64_t(pow(2, ADCAN_AE_Switch_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_AE_Switch_1.countOfBits)-1) << ADCAN_AE_Switch_1.startbit);
		ADCAN_EL_Radio_Switch.value = *Val & ~(uint64_t(pow(2, ADCAN_EL_Radio_Switch.startbit)-1)) & (uint64_t(pow(2, ADCAN_EL_Radio_Switch.countOfBits)-1) << ADCAN_EL_Radio_Switch.startbit);
		ADCAN_PT_Shift_Down.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Shift_Down.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Shift_Down.countOfBits)-1) << ADCAN_PT_Shift_Down.startbit);
		ADCAN_PT_Shift_Up.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Shift_Up.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Shift_Up.countOfBits)-1) << ADCAN_PT_Shift_Up.startbit);
		ADCAN_SP_ARH_switch_1.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_ARH_switch_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_ARH_switch_1.countOfBits)-1) << ADCAN_SP_ARH_switch_1.startbit);
		ADCAN_SP_Clutch_Signal.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Clutch_Signal.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Clutch_Signal.countOfBits)-1) << ADCAN_SP_Clutch_Signal.startbit);
	}
	void build() {
		*Val = ADCAN_AE_Switch_1.build() | ADCAN_EL_Radio_Switch.build() | ADCAN_PT_Shift_Down.build() | ADCAN_PT_Shift_Up.build() | ADCAN_SP_ARH_switch_1.build() | ADCAN_SP_Clutch_Signal.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Switch_1.value) + sizeof(ADCAN_EL_Radio_Switch.value) + sizeof(ADCAN_PT_Shift_Down.value) + sizeof(ADCAN_PT_Shift_Up.value) + sizeof(ADCAN_SP_ARH_switch_1.value) + sizeof(ADCAN_SP_Clutch_Signal.value);
};

struct STOS_CAN_PDU_Test_FCU_A : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Test_FCU_A() {
		ID = _id;
	}
	static const uint16_t _id = 0x177;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_3 = {0, 16, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_ZZ_Test_FCU_1.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_FCU_1.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_FCU_1.countOfBits)-1) << ADCAN_ZZ_Test_FCU_1.startbit);
		ADCAN_ZZ_Test_FCU_2.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_FCU_2.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_FCU_2.countOfBits)-1) << ADCAN_ZZ_Test_FCU_2.startbit);
		ADCAN_ZZ_Test_FCU_3.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_FCU_3.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_FCU_3.countOfBits)-1) << ADCAN_ZZ_Test_FCU_3.startbit);
	}
	void build() {
		*Val = ADCAN_ZZ_Test_FCU_1.build() | ADCAN_ZZ_Test_FCU_2.build() | ADCAN_ZZ_Test_FCU_3.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_FCU_1.value) + sizeof(ADCAN_ZZ_Test_FCU_2.value) + sizeof(ADCAN_ZZ_Test_FCU_3.value);
};

struct STOS_CAN_PDU_Test_FCU_B : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Test_FCU_B() {
		ID = _id;
	}
	static const uint16_t _id = 0x178;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_4 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_5 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_6 = {0, 16, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_ZZ_Test_FCU_4.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_FCU_4.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_FCU_4.countOfBits)-1) << ADCAN_ZZ_Test_FCU_4.startbit);
		ADCAN_ZZ_Test_FCU_5.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_FCU_5.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_FCU_5.countOfBits)-1) << ADCAN_ZZ_Test_FCU_5.startbit);
		ADCAN_ZZ_Test_FCU_6.value = *Val & ~(uint64_t(pow(2, ADCAN_ZZ_Test_FCU_6.startbit)-1)) & (uint64_t(pow(2, ADCAN_ZZ_Test_FCU_6.countOfBits)-1) << ADCAN_ZZ_Test_FCU_6.startbit);
	}
	void build() {
		*Val = ADCAN_ZZ_Test_FCU_4.build() | ADCAN_ZZ_Test_FCU_5.build() | ADCAN_ZZ_Test_FCU_6.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_FCU_4.value) + sizeof(ADCAN_ZZ_Test_FCU_5.value) + sizeof(ADCAN_ZZ_Test_FCU_6.value);
};

struct STOS_CAN_PDU_Water_Oil_Status_Control : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Water_Oil_Status_Control() {
		ID = _id;
	}
	static const uint16_t _id = 0x246;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Fan_Percent = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_PWM = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_1_PWM = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_2_PWM = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_1_Percent = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_2_Percent = {0, 8, 40};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_PT_Oil_Fan_Percent.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Oil_Fan_Percent.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Oil_Fan_Percent.countOfBits)-1) << ADCAN_PT_Oil_Fan_Percent.startbit);
		ADCAN_PT_Oil_PWM.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Oil_PWM.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Oil_PWM.countOfBits)-1) << ADCAN_PT_Oil_PWM.startbit);
		ADCAN_PT_Water_1_PWM.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Water_1_PWM.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Water_1_PWM.countOfBits)-1) << ADCAN_PT_Water_1_PWM.startbit);
		ADCAN_PT_Water_2_PWM.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Water_2_PWM.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Water_2_PWM.countOfBits)-1) << ADCAN_PT_Water_2_PWM.startbit);
		ADCAN_PT_Water_Fan_1_Percent.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Water_Fan_1_Percent.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Water_Fan_1_Percent.countOfBits)-1) << ADCAN_PT_Water_Fan_1_Percent.startbit);
		ADCAN_PT_Water_Fan_2_Percent.value = *Val & ~(uint64_t(pow(2, ADCAN_PT_Water_Fan_2_Percent.startbit)-1)) & (uint64_t(pow(2, ADCAN_PT_Water_Fan_2_Percent.countOfBits)-1) << ADCAN_PT_Water_Fan_2_Percent.startbit);
	}
	void build() {
		*Val = ADCAN_PT_Oil_Fan_Percent.build() | ADCAN_PT_Oil_PWM.build() | ADCAN_PT_Water_1_PWM.build() | ADCAN_PT_Water_2_PWM.build() | ADCAN_PT_Water_Fan_1_Percent.build() | ADCAN_PT_Water_Fan_2_Percent.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Oil_Fan_Percent.value) + sizeof(ADCAN_PT_Oil_PWM.value) + sizeof(ADCAN_PT_Water_1_PWM.value) + sizeof(ADCAN_PT_Water_2_PWM.value) + sizeof(ADCAN_PT_Water_Fan_1_Percent.value) + sizeof(ADCAN_PT_Water_Fan_2_Percent.value);
};

struct STOS_CAN_PDU_Whl_Speed_F : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Whl_Speed_F() {
		ID = _id;
	}
	static const uint16_t _id = 0x180;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FR = {0, 16, 24};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Wheel_Speed_FL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Wheel_Speed_FL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Wheel_Speed_FL.countOfBits)-1) << ADCAN_SP_Wheel_Speed_FL.startbit);
		ADCAN_SP_Wheel_Speed_FR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Wheel_Speed_FR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Wheel_Speed_FR.countOfBits)-1) << ADCAN_SP_Wheel_Speed_FR.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Wheel_Speed_FL.build() | ADCAN_SP_Wheel_Speed_FR.build();
		ID = _id;
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Wheel_Speed_FL.value) + sizeof(ADCAN_SP_Wheel_Speed_FR.value);
};

struct STOS_CAN_PDU_Whl_Speed_R : public StallardOSCanMessage 
{
public:
	STOS_CAN_PDU_Whl_Speed_R() {
		ID = _id;
	}
	static const uint16_t _id = 0x181;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RR = {0, 16, 24};//init,bitcount,startbit 
	void unbuild()
	{
		ADCAN_SP_Wheel_Speed_RL.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Wheel_Speed_RL.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Wheel_Speed_RL.countOfBits)-1) << ADCAN_SP_Wheel_Speed_RL.startbit);
		ADCAN_SP_Wheel_Speed_RR.value = *Val & ~(uint64_t(pow(2, ADCAN_SP_Wheel_Speed_RR.startbit)-1)) & (uint64_t(pow(2, ADCAN_SP_Wheel_Speed_RR.countOfBits)-1) << ADCAN_SP_Wheel_Speed_RR.startbit);
	}
	void build() {
		*Val = ADCAN_SP_Wheel_Speed_RL.build() | ADCAN_SP_Wheel_Speed_RR.build();
		ID = _id;
	}
	uint16_t _size = sizeof(ADCAN_SP_Wheel_Speed_RL.value) + sizeof(ADCAN_SP_Wheel_Speed_RR.value);
}; 

#endif