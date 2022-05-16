#pragma once

struct StallardOSFaulhaberStatusword
{
    bool ready_to_switch_on = false;
    bool switched_on = false;
    bool operation_enabled = false;
    bool voltage_enable = false;
    bool quick_Stop = false;
    bool switch_om_disabled = false;
    bool warning = false;
    bool remote = false;
    bool target_reached = false;
    bool Internal_Limit_Active = false;
    bool seet_point_Acknowledge_or_speed_or_homing_attained = false;
};
