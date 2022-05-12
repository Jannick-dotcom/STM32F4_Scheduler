#pragma once

class StallardOSFaulhaberAntrieb
{
private:
    enum class State
    {
        NOT_READY_TO_SWITCH_ON,
        SWITCH_ON_DISABLED,
        READY_TO_SWITCH_ON,
        SWITCHED_ON,
        OPERATION_ENABLE
    };
    enum class OperationMode
    {
        HOMING,
        PROFILE_POSITION_MODE,
        PROFILE_VELOCITY_MODE
    };

    State state;
    OperationMode operation_mode;

    void StateTransitionSwitchOnDisabled();
    void StateTransitionReadyToSwitchOn();
    void StateTransitionSwitchedOn();
    void StateTransitionOperationEnable();
    void StateTransitionStartHoming();

    void ShutDown();
    void SwitchOn();
    void EnableOperation();

    bool CheckIfReadytoSwitchOn();
    bool CheckIfSwitchedOn();
    bool CheckIfOperationEnable();

    bool CheckIfOperationModeIsHoming();
    bool CheckIfOperationModeIsProfilePositonMode();
    bool CheckIfOperationModeIsProfileVelocityMode();

    bool CheckIfTargetReached();

public:
    StallardOSFaulhaberAntrieb(/* args */);
    ~StallardOSFaulhaberAntrieb();
    State GetState();
};

StallardOSFaulhaberAntrieb::StallardOSFaulhaberAntrieb(/* args */)
{
}

StallardOSFaulhaberAntrieb::~StallardOSFaulhaberAntrieb()
{
}
