#pragma once

class StallardOSFaulhaberAntrieb
{
private:
    enum class State
    {
        SWITCH_ON_DISABLED,
        READY_TO_SWITCH_ON,
        SWITCHED_ON,
        OPERATION_ENABLE
    };

public:
    StallardOSFaulhaberAntrieb(/* args */);
    ~StallardOSFaulhaberAntrieb();
};

StallardOSFaulhaberAntrieb::StallardOSFaulhaberAntrieb(/* args */)
{
}

StallardOSFaulhaberAntrieb::~StallardOSFaulhaberAntrieb()
{
}
