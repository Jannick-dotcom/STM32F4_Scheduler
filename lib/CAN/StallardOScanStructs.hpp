#ifndef StallardOScanStructs_hpp
#define StallardOScanStructs_hpp
#include "stdint.h"
#include "StallardOScanTypes.hpp"
struct STOS_CAN_PDU_AGS1_gearbox_control_unit : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x100;
	CAN_Signal<int8_t> activate_blip = {0, 1, 60};//init,bitcount,startbit 
	CAN_Signal<uint8_t> activate_cut = {0, 1, 61};//init,bitcount,startbit 
	CAN_Signal<uint8_t> blip_state = {0, 4, 28};//init,bitcount,startbit 
	CAN_Signal<uint8_t> cut_level_gcu = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> engaged_gear = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint16_t> gearpot = {0, 10, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> shift_state = {0, 4, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> state_cut = {0, 4, 56};//init,bitcount,startbit 
	CAN_Signal<uint16_t> target_engine_speed = {0, 14, 32};//init,bitcount,startbit 
	void build() {
		*Val = activate_blip.build() | activate_cut.build() | blip_state.build() | cut_level_gcu.build() | engaged_gear.build() | gearpot.build() | shift_state.build() | state_cut.build() | target_engine_speed.build();
	}
	uint16_t _size = dlc = sizeof(activate_blip.value) + sizeof(activate_cut.value) + sizeof(blip_state.value) + sizeof(cut_level_gcu.value) + sizeof(engaged_gear.value) + sizeof(gearpot.value) + sizeof(shift_state.value) + sizeof(state_cut.value) + sizeof(target_engine_speed.value);
};

struct STOS_CAN_PDU_ABS_wheelspeeds : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x24A;
	CAN_Signal<uint16_t> speedABSfl = {0, 16, 0};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSfr = {0, 16, 16};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSrl = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint16_t> speedABSrr = {0, 16, 48};//init,bitcount,startbit 
	void build() {
		*Val = speedABSfl.build() | speedABSfr.build() | speedABSrl.build() | speedABSrr.build();
	}
	uint16_t _size = dlc = sizeof(speedABSfl.value) + sizeof(speedABSfr.value) + sizeof(speedABSrl.value) + sizeof(speedABSrr.value);
};

struct STOS_CAN_PDU_ABS_switch_state_slip_and_speed : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x5C0;
	CAN_Signal<uint16_t> ax1_Bremse60ABS = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ay1_Bremse60ABS = {0, 16, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> blsABS = {0, 1, 24};//init,bitcount,startbit 
	CAN_Signal<int16_t> p_HzABS = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> switchstateABS = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ax1_Bremse60ABS.build() | ay1_Bremse60ABS.build() | blsABS.build() | p_HzABS.build() | switchstateABS.build();
	}
	uint16_t _size = dlc = sizeof(ax1_Bremse60ABS.value) + sizeof(ay1_Bremse60ABS.value) + sizeof(blsABS.value) + sizeof(p_HzABS.value) + sizeof(switchstateABS.value);
};

struct STOS_CAN_PDU_Injection_1 : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x770;
	CAN_Signal<uint8_t> ti_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ti_8 = {0, 8, 56};//init,bitcount,startbit 
	void build() {
		*Val = ti_1.build() | ti_2.build() | ti_3.build() | ti_4.build() | ti_5.build() | ti_6.build() | ti_7.build() | ti_8.build();
	}
	uint16_t _size = dlc = sizeof(ti_1.value) + sizeof(ti_2.value) + sizeof(ti_3.value) + sizeof(ti_4.value) + sizeof(ti_5.value) + sizeof(ti_6.value) + sizeof(ti_7.value) + sizeof(ti_8.value);
};

struct STOS_CAN_PDU_Injection_2 : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x771;
	CAN_Signal<uint8_t> injang = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> injoff = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_2k = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lamctrl_k = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tibase = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tibatt_o = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> timap = {0, 8, 16};//init,bitcount,startbit 
	void build() {
		*Val = injang.build() | injoff.build() | lamctrl_2k.build() | lamctrl_k.build() | tibase.build() | tibatt_o.build() | timap.build();
	}
	uint16_t _size = dlc = sizeof(injang.value) + sizeof(injoff.value) + sizeof(lamctrl_2k.value) + sizeof(lamctrl_k.value) + sizeof(tibase.value) + sizeof(tibatt_o.value) + sizeof(timap.value);
};

struct STOS_CAN_PDU_Ignition : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x772;
	CAN_Signal<int8_t> ign_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> ign_8 = {0, 8, 56};//init,bitcount,startbit 
	void build() {
		*Val = ign_1.build() | ign_2.build() | ign_3.build() | ign_4.build() | ign_5.build() | ign_6.build() | ign_7.build() | ign_8.build();
	}
	uint16_t _size = dlc = sizeof(ign_1.value) + sizeof(ign_2.value) + sizeof(ign_3.value) + sizeof(ign_4.value) + sizeof(ign_5.value) + sizeof(ign_6.value) + sizeof(ign_7.value) + sizeof(ign_8.value);
};

struct STOS_CAN_PDU_Ignition_Rev_Ath : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x773;
	CAN_Signal<uint8_t> ath = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> dath = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> ignbase = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> ignmap = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> rev = {0, 16, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tdwell = {0, 8, 16};//init,bitcount,startbit 
	void build() {
		*Val = ath.build() | dath.build() | ignbase.build() | ignmap.build() | rev.build() | tdwell.build();
	}
	uint16_t _size = dlc = sizeof(ath.value) + sizeof(dath.value) + sizeof(ignbase.value) + sizeof(ignmap.value) + sizeof(rev.value) + sizeof(tdwell.value);
};

struct STOS_CAN_PDU_Lambda : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x774;
	CAN_Signal<uint8_t> lam = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lam_2 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> lami = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<int8_t> lami_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lammap = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lammap_2 = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<int8_t> lamp = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<int8_t> lamp_2 = {0, 8, 24};//init,bitcount,startbit 
	void build() {
		*Val = lam.build() | lam_2.build() | lami.build() | lami_2.build() | lammap.build() | lammap_2.build() | lamp.build() | lamp_2.build();
	}
	uint16_t _size = dlc = sizeof(lam.value) + sizeof(lam_2.value) + sizeof(lami.value) + sizeof(lami_2.value) + sizeof(lammap.value) + sizeof(lammap_2.value) + sizeof(lamp.value) + sizeof(lamp_2.value);
};

struct STOS_CAN_PDU_Speed : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x775;
	CAN_Signal<uint16_t> speed = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedfl = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedfr = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedrl = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> speedrr = {0, 8, 40};//init,bitcount,startbit 
	void build() {
		*Val = speed.build() | speedfl.build() | speedfr.build() | speedrl.build() | speedrr.build();
	}
	uint16_t _size = dlc = sizeof(speed.value) + sizeof(speedfl.value) + sizeof(speedfr.value) + sizeof(speedrl.value) + sizeof(speedrr.value);
};

struct STOS_CAN_PDU_Lapfunc : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x776;
	CAN_Signal<uint16_t> lapdist = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptime = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptimediff = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> laptimefast = {0, 16, 56};//init,bitcount,startbit 
	void build() {
		*Val = lapdist.build() | laptime.build() | laptimediff.build() | laptimefast.build();
	}
	uint16_t _size = dlc = sizeof(lapdist.value) + sizeof(laptime.value) + sizeof(laptimediff.value) + sizeof(laptimefast.value);
};

struct STOS_CAN_PDU_Gear_Dashboard_Acceleration : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x777;
	CAN_Signal<int8_t> accx = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<int8_t> accy = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<int8_t> accz = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ddugear = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gcstate = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gear = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gearcut_u = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> gearratio = {0, 8, 16};//init,bitcount,startbit 
	void build() {
		*Val = accx.build() | accy.build() | accz.build() | ddugear.build() | gcstate.build() | gear.build() | gearcut_u.build() | gearratio.build();
	}
	uint16_t _size = dlc = sizeof(accx.value) + sizeof(accy.value) + sizeof(accz.value) + sizeof(ddugear.value) + sizeof(gcstate.value) + sizeof(gear.value) + sizeof(gearcut_u.value) + sizeof(gearratio.value);
};

struct STOS_CAN_PDU_Traction_Control : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x778;
	CAN_Signal<uint8_t> slipsp = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> slra = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<int8_t> tcpfac = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> tcsw = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> vdraxle = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> vref = {0, 16, 56};//init,bitcount,startbit 
	void build() {
		*Val = slipsp.build() | slra.build() | tcpfac.build() | tcsw.build() | vdraxle.build() | vref.build();
	}
	uint16_t _size = dlc = sizeof(slipsp.value) + sizeof(slra.value) + sizeof(tcpfac.value) + sizeof(tcsw.value) + sizeof(vdraxle.value) + sizeof(vref.value);
};

struct STOS_CAN_PDU_Electronic_Throttle_Control : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x779;
	CAN_Signal<uint8_t> aps = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> batt_u = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> camshaftpos = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> etb = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> etb_sp = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> lap_c = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint16_t> p1 = {0, 16, 32};//init,bitcount,startbit 
	void build() {
		*Val = aps.build() | batt_u.build() | camshaftpos.build() | etb.build() | etb_sp.build() | lap_c.build() | p1.build();
	}
	uint16_t _size = dlc = sizeof(aps.value) + sizeof(batt_u.value) + sizeof(camshaftpos.value) + sizeof(etb.value) + sizeof(etb_sp.value) + sizeof(lap_c.value) + sizeof(p1.value);
};

struct STOS_CAN_PDU_States_Temp_Press : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x77A;
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
	void build() {
		*Val = battlow_b.build() | etbsys_e.build() | fuellap.build() | fueltank.build() | gearcut_b.build() | idle_b.build() | ignoff_b.build() | injcut_b.build() | injcutin_b.build() | injenrich_b.build() | injstartphase_b.build() | knockadaptenable_b.build() | knockenable_b.build() | lamctrl_2b.build() | lamctrl_b.build() | lap_b.build() | laptrig_b.build() | mappos.build() | mil_b.build() | oillamp_b.build() | pamb.build() | pcrank.build() | pfuel.build() | phsok_b.build() | phsokset_b.build() | poil.build() | pwat.build() | rev_b.build() | revlimit_b.build() | rowcounter_0x77A.build() | shled1_b.build() | shled2_b.build() | shled3_b.build() | shled4_b.build() | shled5_b.build() | speedlimit_b.build() | speedlimitreq_b.build() | startend_b.build() | tair.build() | tc_b.build() | tex.build() | tex_2.build() | tfuel.build() | tlam.build() | tlam_2.build() | tmot.build() | toil.build();
	}
	uint16_t _size = dlc = sizeof(battlow_b.value) + sizeof(etbsys_e.value) + sizeof(fuellap.value) + sizeof(fueltank.value) + sizeof(gearcut_b.value) + sizeof(idle_b.value) + sizeof(ignoff_b.value) + sizeof(injcut_b.value) + sizeof(injcutin_b.value) + sizeof(injenrich_b.value) + sizeof(injstartphase_b.value) + sizeof(knockadaptenable_b.value) + sizeof(knockenable_b.value) + sizeof(lamctrl_2b.value) + sizeof(lamctrl_b.value) + sizeof(lap_b.value) + sizeof(laptrig_b.value) + sizeof(mappos.value) + sizeof(mil_b.value) + sizeof(oillamp_b.value) + sizeof(pamb.value) + sizeof(pcrank.value) + sizeof(pfuel.value) + sizeof(phsok_b.value) + sizeof(phsokset_b.value) + sizeof(poil.value) + sizeof(pwat.value) + sizeof(rev_b.value) + sizeof(revlimit_b.value) + sizeof(rowcounter_0x77A.value) + sizeof(shled1_b.value) + sizeof(shled2_b.value) + sizeof(shled3_b.value) + sizeof(shled4_b.value) + sizeof(shled5_b.value) + sizeof(speedlimit_b.value) + sizeof(speedlimitreq_b.value) + sizeof(startend_b.value) + sizeof(tair.value) + sizeof(tc_b.value) + sizeof(tex.value) + sizeof(tex_2.value) + sizeof(tfuel.value) + sizeof(tlam.value) + sizeof(tlam_2.value) + sizeof(tmot.value) + sizeof(toil.value);
};

struct STOS_CAN_PDU_Boost_Pressures_Wastegate : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x77C;
	CAN_Signal<uint16_t> p22_2m_pwg_m = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> p22_m = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> p22_sp = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> pwg_sp = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> wgdc_2_wgdchold = {0, 8, 56};//init,bitcount,startbit 
	CAN_Signal<uint8_t> wgdc_wgdcvent = {0, 8, 48};//init,bitcount,startbit 
	void build() {
		*Val = p22_2m_pwg_m.build() | p22_m.build() | p22_sp.build() | pwg_sp.build() | wgdc_2_wgdchold.build() | wgdc_wgdcvent.build();
	}
	uint16_t _size = dlc = sizeof(p22_2m_pwg_m.value) + sizeof(p22_m.value) + sizeof(p22_sp.value) + sizeof(pwg_sp.value) + sizeof(wgdc_2_wgdchold.value) + sizeof(wgdc_wgdcvent.value);
};

struct STOS_CAN_PDU_Acceleration_1 : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x150;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_1_Z = {0, 16, 40};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Accel_1_X.build() | ADCAN_SP_Accel_1_Y.build() | ADCAN_SP_Accel_1_Z.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Accel_1_X.value) + sizeof(ADCAN_SP_Accel_1_Y.value) + sizeof(ADCAN_SP_Accel_1_Z.value);
};

struct STOS_CAN_PDU_Acceleration_2 : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x151;
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Accel_2_Z = {0, 16, 40};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Accel_2_X.build() | ADCAN_SP_Accel_2_Y.build() | ADCAN_SP_Accel_2_Z.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Accel_2_X.value) + sizeof(ADCAN_SP_Accel_2_Y.value) + sizeof(ADCAN_SP_Accel_2_Z.value);
};

struct STOS_CAN_PDU_Aero_Fan_PWM : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x157;
	CAN_Signal<uint8_t> ADCAN_AE_Fan_L_PWM = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_AE_Fan_R_PWM = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_AE_Fan_L_PWM.build() | ADCAN_AE_Fan_R_PWM.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Fan_L_PWM.value) + sizeof(ADCAN_AE_Fan_R_PWM.value);
};

struct STOS_CAN_PDU_Aero_Fan_Telemetry : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x158;
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_1 = {0, 32, 24};//init,bitcount,startbit 
	CAN_Signal<uint32_t> ADCAN_AE_Fan_Telemetry_2 = {0, 32, 56};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_AE_Fan_Telemetry_1.build() | ADCAN_AE_Fan_Telemetry_2.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Fan_Telemetry_1.value) + sizeof(ADCAN_AE_Fan_Telemetry_2.value);
};

struct STOS_CAN_PDU_Aero_Fan_Warnings : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x105;
	CAN_Signal<uint8_t> ADCAN_AE_Warnings = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_AE_Warnings.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Warnings.value);
};

struct STOS_CAN_PDU_Airbox_Position : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x200;
	CAN_Signal<uint8_t> ADCAN_PT_Airbox_Pos = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_PT_Airbox_Pos.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Airbox_Pos.value);
};

struct STOS_CAN_PDU_ARH_Homing : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x201;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_Homing = {0, 1, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_Homing = {0, 1, 1};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_ARH_1_Homing.build() | ADCAN_SP_ARH_2_Homing.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_ARH_1_Homing.value) + sizeof(ADCAN_SP_ARH_2_Homing.value);
};

struct STOS_CAN_PDU_ARH_PWM : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x160;
	CAN_Signal<uint8_t> ADCAN_SP_ARH_1_PWM = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_2_PWM = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_ARH_1_PWM.build() | ADCAN_SP_ARH_2_PWM.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_ARH_1_PWM.value) + sizeof(ADCAN_SP_ARH_2_PWM.value);
};

struct STOS_CAN_PDU_Battery_Temp_48V : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x203;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Battery_48V_Temp_3 = {0, 8, 16};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_Battery_48V_Temp_1.build() | ADCAN_EL_Battery_48V_Temp_2.build() | ADCAN_EL_Battery_48V_Temp_3.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_Battery_48V_Temp_1.value) + sizeof(ADCAN_EL_Battery_48V_Temp_2.value) + sizeof(ADCAN_EL_Battery_48V_Temp_3.value);
};

struct STOS_CAN_PDU_Brake_Disc_F : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x205;
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Disc_Temp_FL = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Disc_Temp_FR = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Brake_Disc_Temp_FL.build() | ADCAN_SP_Brake_Disc_Temp_FR.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Brake_Disc_Temp_FL.value) + sizeof(ADCAN_SP_Brake_Disc_Temp_FR.value);
};

struct STOS_CAN_PDU_Brake_Disc_R : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x206;
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Disc_Temp_RL = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Disc_Temp_RR = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Brake_Disc_Temp_RL.build() | ADCAN_SP_Brake_Disc_Temp_RR.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Brake_Disc_Temp_RL.value) + sizeof(ADCAN_SP_Brake_Disc_Temp_RR.value);
};

struct STOS_CAN_PDU_Brake_Pressure : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x155;
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Pressure_Front = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Brake_Pressure_Rear = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Brake_Pressure_Front.build() | ADCAN_SP_Brake_Pressure_Rear.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Brake_Pressure_Front.value) + sizeof(ADCAN_SP_Brake_Pressure_Rear.value);
};

struct STOS_CAN_PDU_Current_Sensors : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x208;
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_4 = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_5 = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_6 = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_7 = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Current_Sensor_8 = {0, 8, 56};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_Current_Sensor_1.build() | ADCAN_EL_Current_Sensor_2.build() | ADCAN_EL_Current_Sensor_3.build() | ADCAN_EL_Current_Sensor_4.build() | ADCAN_EL_Current_Sensor_5.build() | ADCAN_EL_Current_Sensor_6.build() | ADCAN_EL_Current_Sensor_7.build() | ADCAN_EL_Current_Sensor_8.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_Current_Sensor_1.value) + sizeof(ADCAN_EL_Current_Sensor_2.value) + sizeof(ADCAN_EL_Current_Sensor_3.value) + sizeof(ADCAN_EL_Current_Sensor_4.value) + sizeof(ADCAN_EL_Current_Sensor_5.value) + sizeof(ADCAN_EL_Current_Sensor_6.value) + sizeof(ADCAN_EL_Current_Sensor_7.value) + sizeof(ADCAN_EL_Current_Sensor_8.value);
};

struct STOS_CAN_PDU_FCU_ECU_Bat_Temp : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x210;
	CAN_Signal<uint8_t> ADCAN_EL_Battery_24V_Temp = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_1 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_FCU_2 = {0, 8, 16};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_Battery_24V_Temp.build() | ADCAN_EL_ECU_Temp_FCU_1.build() | ADCAN_EL_ECU_Temp_FCU_2.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_Battery_24V_Temp.value) + sizeof(ADCAN_EL_ECU_Temp_FCU_1.value) + sizeof(ADCAN_EL_ECU_Temp_FCU_2.value);
};

struct STOS_CAN_PDU_FCU_Switches : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x212;
	CAN_Signal<uint8_t> ADCAN_SP_ARB_Switch = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Activated = {0, 1, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_LaunchC_Switch = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Switch = {0, 8, 16};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_ARB_Switch.build() | ADCAN_SP_LaunchC_Activated.build() | ADCAN_SP_LaunchC_Switch.build() | ADCAN_SP_RAS_Switch.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_ARB_Switch.value) + sizeof(ADCAN_SP_LaunchC_Activated.value) + sizeof(ADCAN_SP_LaunchC_Switch.value) + sizeof(ADCAN_SP_RAS_Switch.value);
};

struct STOS_CAN_PDU_FDS_Parameters : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x215;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Friction_LC = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_mue_max = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Swim_VDE = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Velo_VDE = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RL = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Wheel_Slip_RR = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Yaw_VDE = {0, 8, 24};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_FDS_Friction_LC.build() | ADCAN_SP_FDS_Slip_mue_max.build() | ADCAN_SP_FDS_Swim_VDE.build() | ADCAN_SP_FDS_Velo_VDE.build() | ADCAN_SP_FDS_Wheel_Slip_RL.build() | ADCAN_SP_FDS_Wheel_Slip_RR.build() | ADCAN_SP_FDS_Yaw_VDE.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_FDS_Friction_LC.value) + sizeof(ADCAN_SP_FDS_Slip_mue_max.value) + sizeof(ADCAN_SP_FDS_Swim_VDE.value) + sizeof(ADCAN_SP_FDS_Velo_VDE.value) + sizeof(ADCAN_SP_FDS_Wheel_Slip_RL.value) + sizeof(ADCAN_SP_FDS_Wheel_Slip_RR.value) + sizeof(ADCAN_SP_FDS_Yaw_VDE.value);
};

struct STOS_CAN_PDU_FDS_Wheel_Signals : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x216;
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FL = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_FR = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RL = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Slip_Angle_RR = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FL = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_FR = {0, 8, 40};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RL = {0, 8, 48};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_FDS_Whl_Load_RR = {0, 8, 56};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_FDS_Slip_Angle_FL.build() | ADCAN_SP_FDS_Slip_Angle_FR.build() | ADCAN_SP_FDS_Slip_Angle_RL.build() | ADCAN_SP_FDS_Slip_Angle_RR.build() | ADCAN_SP_FDS_Whl_Load_FL.build() | ADCAN_SP_FDS_Whl_Load_FR.build() | ADCAN_SP_FDS_Whl_Load_RL.build() | ADCAN_SP_FDS_Whl_Load_RR.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_FDS_Slip_Angle_FL.value) + sizeof(ADCAN_SP_FDS_Slip_Angle_FR.value) + sizeof(ADCAN_SP_FDS_Slip_Angle_RL.value) + sizeof(ADCAN_SP_FDS_Slip_Angle_RR.value) + sizeof(ADCAN_SP_FDS_Whl_Load_FL.value) + sizeof(ADCAN_SP_FDS_Whl_Load_FR.value) + sizeof(ADCAN_SP_FDS_Whl_Load_RL.value) + sizeof(ADCAN_SP_FDS_Whl_Load_RR.value);
};

struct STOS_CAN_PDU_Flash_Over_Can : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x222;
	CAN_Signal<uint8_t> ADCAN_EL_FoC_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_FoC_2 = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_FoC_1.build() | ADCAN_EL_FoC_2.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_FoC_1.value) + sizeof(ADCAN_EL_FoC_2.value);
};

struct STOS_CAN_PDU_Frame_Pressure : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x218;
	CAN_Signal<uint8_t> ADCAN_CH_Frame_Pressure = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_CH_Frame_Pressure.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_CH_Frame_Pressure.value);
};

struct STOS_CAN_PDU_Gyroscope_1 : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x152;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_1_Z = {0, 16, 40};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Gyro_1_X.build() | ADCAN_SP_Gyro_1_Y.build() | ADCAN_SP_Gyro_1_Z.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Gyro_1_X.value) + sizeof(ADCAN_SP_Gyro_1_Y.value) + sizeof(ADCAN_SP_Gyro_1_Z.value);
};

struct STOS_CAN_PDU_Gyroscope_2 : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x153;
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_X = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Y = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Gyro_2_Z = {0, 16, 40};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Gyro_2_X.build() | ADCAN_SP_Gyro_2_Y.build() | ADCAN_SP_Gyro_2_Z.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Gyro_2_X.value) + sizeof(ADCAN_SP_Gyro_2_Y.value) + sizeof(ADCAN_SP_Gyro_2_Z.value);
};

struct STOS_CAN_PDU_Niveau_F : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x111;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Niveau = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Niveau = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Niveau_FL_Niveau.build() | ADCAN_SP_Niveau_FR_Niveau.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_FL_Niveau.value) + sizeof(ADCAN_SP_Niveau_FR_Niveau.value);
};

struct STOS_CAN_PDU_Niveau_Front_Status : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x219;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Error = {0, 1, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_Function = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FL_on_off = {0, 1, 17};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Error = {0, 1, 18};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_Function = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_FR_on_off = {0, 1, 19};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Niveau_FL_Error.build() | ADCAN_SP_Niveau_FL_Function.build() | ADCAN_SP_Niveau_FL_on_off.build() | ADCAN_SP_Niveau_FR_Error.build() | ADCAN_SP_Niveau_FR_Function.build() | ADCAN_SP_Niveau_FR_on_off.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_FL_Error.value) + sizeof(ADCAN_SP_Niveau_FL_Function.value) + sizeof(ADCAN_SP_Niveau_FL_on_off.value) + sizeof(ADCAN_SP_Niveau_FR_Error.value) + sizeof(ADCAN_SP_Niveau_FR_Function.value) + sizeof(ADCAN_SP_Niveau_FR_on_off.value);
};

struct STOS_CAN_PDU_Niveau_R : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x110;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Niveau = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Niveau_R_Niveau.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_R_Niveau.value);
};

struct STOS_CAN_PDU_Niveau_Rear_Status : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x220;
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Error = {0, 1, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Niveau_R_Function = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Niveau_R_Error.build() | ADCAN_SP_Niveau_R_Function.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Niveau_R_Error.value) + sizeof(ADCAN_SP_Niveau_R_Function.value);
};

struct STOS_CAN_PDU_Oil_Pressure : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x163;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Pressure = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_PT_Oil_Pressure.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Oil_Pressure.value);
};

struct STOS_CAN_PDU_Oil_Pressure_Status : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x224;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Level_RS232 = {0, 1, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Temp = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_PT_Oil_Level.build() | ADCAN_PT_Oil_Level_RS232.build() | ADCAN_PT_Oil_Temp.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Oil_Level.value) + sizeof(ADCAN_PT_Oil_Level_RS232.value) + sizeof(ADCAN_PT_Oil_Temp.value);
};

struct STOS_CAN_PDU_PDU_ECU_Temp : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x230;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_3 = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_PDU_4 = {0, 8, 24};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_ECU_Temp_PDU_1.build() | ADCAN_EL_ECU_Temp_PDU_2.build() | ADCAN_EL_ECU_Temp_PDU_3.build() | ADCAN_EL_ECU_Temp_PDU_4.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_ECU_Temp_PDU_1.value) + sizeof(ADCAN_EL_ECU_Temp_PDU_2.value) + sizeof(ADCAN_EL_ECU_Temp_PDU_3.value) + sizeof(ADCAN_EL_ECU_Temp_PDU_4.value);
};

struct STOS_CAN_PDU_PDU_Status : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x226;
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
	void build() {
		*Val = ADCAN_CH_Mainhoop_Diag_L_1.build() | ADCAN_CH_Mainhoop_Diag_R_1.build() | ADCAN_EL_BOTS_Diag_1.build() | ADCAN_EL_BSPD_Shutdown_Out.build() | ADCAN_EL_Cockpit_Diag_1.build() | ADCAN_EL_Crash_Diag.build() | ADCAN_EL_Fuse_Status_1.build() | ADCAN_EL_Fuse_Status_10.build() | ADCAN_EL_Fuse_Status_11.build() | ADCAN_EL_Fuse_Status_12.build() | ADCAN_EL_Fuse_Status_13.build() | ADCAN_EL_Fuse_Status_14.build() | ADCAN_EL_Fuse_Status_15.build() | ADCAN_EL_Fuse_Status_16.build() | ADCAN_EL_Fuse_Status_17.build() | ADCAN_EL_Fuse_Status_18.build() | ADCAN_EL_Fuse_Status_19.build() | ADCAN_EL_Fuse_Status_2.build() | ADCAN_EL_Fuse_Status_3.build() | ADCAN_EL_Fuse_Status_4.build() | ADCAN_EL_Fuse_Status_5.build() | ADCAN_EL_Fuse_Status_6.build() | ADCAN_EL_Fuse_Status_7.build() | ADCAN_EL_Fuse_Status_8.build() | ADCAN_EL_Fuse_Status_9.build() | ADCAN_EL_Relais_Status_1.build() | ADCAN_EL_Relais_Status_2.build() | ADCAN_EL_Shutdown_Cockpit.build() | ADCAN_PT_Fuel_Pump_Signal.build() | ADCAN_PT_Reserve_Signal_L.build() | ADCAN_PT_Reserve_Signal_R.build() | ADCAN_PT_Water_Pump_Signal.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_CH_Mainhoop_Diag_L_1.value) + sizeof(ADCAN_CH_Mainhoop_Diag_R_1.value) + sizeof(ADCAN_EL_BOTS_Diag_1.value) + sizeof(ADCAN_EL_BSPD_Shutdown_Out.value) + sizeof(ADCAN_EL_Cockpit_Diag_1.value) + sizeof(ADCAN_EL_Crash_Diag.value) + sizeof(ADCAN_EL_Fuse_Status_1.value) + sizeof(ADCAN_EL_Fuse_Status_10.value) + sizeof(ADCAN_EL_Fuse_Status_11.value) + sizeof(ADCAN_EL_Fuse_Status_12.value) + sizeof(ADCAN_EL_Fuse_Status_13.value) + sizeof(ADCAN_EL_Fuse_Status_14.value) + sizeof(ADCAN_EL_Fuse_Status_15.value) + sizeof(ADCAN_EL_Fuse_Status_16.value) + sizeof(ADCAN_EL_Fuse_Status_17.value) + sizeof(ADCAN_EL_Fuse_Status_18.value) + sizeof(ADCAN_EL_Fuse_Status_19.value) + sizeof(ADCAN_EL_Fuse_Status_2.value) + sizeof(ADCAN_EL_Fuse_Status_3.value) + sizeof(ADCAN_EL_Fuse_Status_4.value) + sizeof(ADCAN_EL_Fuse_Status_5.value) + sizeof(ADCAN_EL_Fuse_Status_6.value) + sizeof(ADCAN_EL_Fuse_Status_7.value) + sizeof(ADCAN_EL_Fuse_Status_8.value) + sizeof(ADCAN_EL_Fuse_Status_9.value) + sizeof(ADCAN_EL_Relais_Status_1.value) + sizeof(ADCAN_EL_Relais_Status_2.value) + sizeof(ADCAN_EL_Shutdown_Cockpit.value) + sizeof(ADCAN_PT_Fuel_Pump_Signal.value) + sizeof(ADCAN_PT_Reserve_Signal_L.value) + sizeof(ADCAN_PT_Reserve_Signal_R.value) + sizeof(ADCAN_PT_Water_Pump_Signal.value);
};

struct STOS_CAN_PDU_Pitot : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x232;
	CAN_Signal<uint8_t> ADCAN_AE_Pitot_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_AE_Pitot_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_AE_Pitot_3 = {0, 8, 16};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_AE_Pitot_1.build() | ADCAN_AE_Pitot_2.build() | ADCAN_AE_Pitot_3.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Pitot_1.value) + sizeof(ADCAN_AE_Pitot_2.value) + sizeof(ADCAN_AE_Pitot_3.value);
};

struct STOS_CAN_PDU_RAS_PWM : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x161;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_L = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_PWM_R = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_RAS_PWM_L.build() | ADCAN_SP_RAS_PWM_R.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_RAS_PWM_L.value) + sizeof(ADCAN_SP_RAS_PWM_R.value);
};

struct STOS_CAN_PDU_RAS_Status_Control : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x234;
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Angle = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_L = {0, 1, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_RAS_Homing_R = {0, 1, 9};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_RAS_Angle.build() | ADCAN_SP_RAS_Homing_L.build() | ADCAN_SP_RAS_Homing_R.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_RAS_Angle.value) + sizeof(ADCAN_SP_RAS_Homing_L.value) + sizeof(ADCAN_SP_RAS_Homing_R.value);
};

struct STOS_CAN_PDU_RCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x236;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_RCU_2 = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_ECU_Temp_RCU_1.build() | ADCAN_EL_ECU_Temp_RCU_2.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_ECU_Temp_RCU_1.value) + sizeof(ADCAN_EL_ECU_Temp_RCU_2.value);
};

struct STOS_CAN_PDU_RCU_Test_A : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x165;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_3 = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_4 = {0, 16, 56};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_ZZ_Test_RCU_1.build() | ADCAN_ZZ_Test_RCU_2.build() | ADCAN_ZZ_Test_RCU_3.build() | ADCAN_ZZ_Test_RCU_4.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_RCU_1.value) + sizeof(ADCAN_ZZ_Test_RCU_2.value) + sizeof(ADCAN_ZZ_Test_RCU_3.value) + sizeof(ADCAN_ZZ_Test_RCU_4.value);
};

struct STOS_CAN_PDU_RCU_Test_B : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x166;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_5 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_6 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_7 = {0, 16, 40};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_8 = {0, 16, 56};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_ZZ_Test_RCU_5.build() | ADCAN_ZZ_Test_RCU_6.build() | ADCAN_ZZ_Test_RCU_7.build() | ADCAN_ZZ_Test_RCU_8.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_RCU_5.value) + sizeof(ADCAN_ZZ_Test_RCU_6.value) + sizeof(ADCAN_ZZ_Test_RCU_7.value) + sizeof(ADCAN_ZZ_Test_RCU_8.value);
};

struct STOS_CAN_PDU_RCU_Test_C : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x167;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_10 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_RCU_9 = {0, 16, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_ZZ_Test_RCU_10.build() | ADCAN_ZZ_Test_RCU_9.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_RCU_10.value) + sizeof(ADCAN_ZZ_Test_RCU_9.value);
};

struct STOS_CAN_PDU_Rocker_F : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x238;
	CAN_Signal<uint8_t> ADCAN_SP_Rocker_FL = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Rocker_FR = {0, 8, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Rocker_FL.build() | ADCAN_SP_Rocker_FR.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Rocker_FL.value) + sizeof(ADCAN_SP_Rocker_FR.value);
};

struct STOS_CAN_PDU_Rocker_R : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x239;
	CAN_Signal<uint8_t> ADCAN_SP_Rocker_RL = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Rocker_RR = {0, 8, 24};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Rocker_RL.build() | ADCAN_SP_Rocker_RR.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Rocker_RL.value) + sizeof(ADCAN_SP_Rocker_RR.value);
};

struct STOS_CAN_PDU_Shift_Clutch : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x170;
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_DigIn = {0, 1, 18};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Gearshift_LaunchC = {0, 1, 19};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Power_on_off = {0, 1, 20};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_PT_Shift_Power_Sensor = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_DigIn = {0, 1, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_LaunchC = {0, 1, 17};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_PT_Gearshift_DigIn.build() | ADCAN_PT_Gearshift_LaunchC.build() | ADCAN_PT_Shift_Power_on_off.build() | ADCAN_PT_Shift_Power_Sensor.build() | ADCAN_SP_Clutch_DigIn.build() | ADCAN_SP_Clutch_LaunchC.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Gearshift_DigIn.value) + sizeof(ADCAN_PT_Gearshift_LaunchC.value) + sizeof(ADCAN_PT_Shift_Power_on_off.value) + sizeof(ADCAN_PT_Shift_Power_Sensor.value) + sizeof(ADCAN_SP_Clutch_DigIn.value) + sizeof(ADCAN_SP_Clutch_LaunchC.value);
};

struct STOS_CAN_PDU_Steering_Whl_Angle : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x172;
	CAN_Signal<uint16_t> ADCAN_SP_Steering_Wheel_Angle = {0, 16, 8};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Steering_Wheel_Angle.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Steering_Wheel_Angle.value);
};

struct STOS_CAN_PDU_SWCU_ECU_Temp : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x244;
	CAN_Signal<uint8_t> ADCAN_EL_ECU_Temp_SWCU = {0, 8, 0};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_ECU_Temp_SWCU.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_ECU_Temp_SWCU.value);
};

struct STOS_CAN_PDU_SWCU_Oh_Shit : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x175;
	CAN_Signal<uint8_t> ADCAN_EL_INCR_1 = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_INCR_2 = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Oh_Shit = {0, 1, 16};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_EL_INCR_1.build() | ADCAN_EL_INCR_2.build() | ADCAN_EL_Oh_Shit.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_EL_INCR_1.value) + sizeof(ADCAN_EL_INCR_2.value) + sizeof(ADCAN_EL_Oh_Shit.value);
};

struct STOS_CAN_PDU_SWCU_Switches : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x100;
	CAN_Signal<uint8_t> ADCAN_AE_Switch_1 = {0, 1, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_EL_Radio_Switch = {0, 1, 1};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Down = {0, 1, 2};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Shift_Up = {0, 1, 3};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_ARH_switch_1 = {0, 1, 4};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_SP_Clutch_Signal = {0, 1, 5};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_AE_Switch_1.build() | ADCAN_EL_Radio_Switch.build() | ADCAN_PT_Shift_Down.build() | ADCAN_PT_Shift_Up.build() | ADCAN_SP_ARH_switch_1.build() | ADCAN_SP_Clutch_Signal.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_AE_Switch_1.value) + sizeof(ADCAN_EL_Radio_Switch.value) + sizeof(ADCAN_PT_Shift_Down.value) + sizeof(ADCAN_PT_Shift_Up.value) + sizeof(ADCAN_SP_ARH_switch_1.value) + sizeof(ADCAN_SP_Clutch_Signal.value);
};

struct STOS_CAN_PDU_Test_FCU_A : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x177;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_1 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_2 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_3 = {0, 16, 40};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_ZZ_Test_FCU_1.build() | ADCAN_ZZ_Test_FCU_2.build() | ADCAN_ZZ_Test_FCU_3.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_FCU_1.value) + sizeof(ADCAN_ZZ_Test_FCU_2.value) + sizeof(ADCAN_ZZ_Test_FCU_3.value);
};

struct STOS_CAN_PDU_Test_FCU_B : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x178;
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_4 = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_5 = {0, 16, 24};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_ZZ_Test_FCU_6 = {0, 16, 40};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_ZZ_Test_FCU_4.build() | ADCAN_ZZ_Test_FCU_5.build() | ADCAN_ZZ_Test_FCU_6.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_ZZ_Test_FCU_4.value) + sizeof(ADCAN_ZZ_Test_FCU_5.value) + sizeof(ADCAN_ZZ_Test_FCU_6.value);
};

struct STOS_CAN_PDU_Water_Oil_Status_Control : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x246;
	CAN_Signal<uint8_t> ADCAN_PT_Oil_Fan_Percent = {0, 8, 0};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Oil_PWM = {0, 8, 8};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_1_PWM = {0, 8, 16};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_2_PWM = {0, 8, 24};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_1_Percent = {0, 8, 32};//init,bitcount,startbit 
	CAN_Signal<uint8_t> ADCAN_PT_Water_Fan_2_Percent = {0, 8, 40};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_PT_Oil_Fan_Percent.build() | ADCAN_PT_Oil_PWM.build() | ADCAN_PT_Water_1_PWM.build() | ADCAN_PT_Water_2_PWM.build() | ADCAN_PT_Water_Fan_1_Percent.build() | ADCAN_PT_Water_Fan_2_Percent.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_PT_Oil_Fan_Percent.value) + sizeof(ADCAN_PT_Oil_PWM.value) + sizeof(ADCAN_PT_Water_1_PWM.value) + sizeof(ADCAN_PT_Water_2_PWM.value) + sizeof(ADCAN_PT_Water_Fan_1_Percent.value) + sizeof(ADCAN_PT_Water_Fan_2_Percent.value);
};

struct STOS_CAN_PDU_Whl_Speed_F : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x180;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_FR = {0, 16, 24};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Wheel_Speed_FL.build() | ADCAN_SP_Wheel_Speed_FR.build();
	}
	uint16_t _size = dlc = sizeof(ADCAN_SP_Wheel_Speed_FL.value) + sizeof(ADCAN_SP_Wheel_Speed_FR.value);
};

struct STOS_CAN_PDU_Whl_Speed_R : public StallardOSCanMessage 
{
public:
	uint16_t _id = ID = 0x181;
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RL = {0, 16, 8};//init,bitcount,startbit 
	CAN_Signal<uint16_t> ADCAN_SP_Wheel_Speed_RR = {0, 16, 24};//init,bitcount,startbit 
	void build() {
		*Val = ADCAN_SP_Wheel_Speed_RL.build() | ADCAN_SP_Wheel_Speed_RR.build();
	}
	uint16_t _size = sizeof(ADCAN_SP_Wheel_Speed_RL.value) + sizeof(ADCAN_SP_Wheel_Speed_RR.value);
}; 

#endif