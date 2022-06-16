#pragma once
#include "StallardOSFaulhaberMotionController.hpp"
#include "StallardOSFaulhaberMessages.hpp"
class StallardOSFaulhaberDrive : StallardOSFaulhaberMotionController
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

    void StateUpdate();

    void ShutDown();
    void SwitchOn();
    void EnableOperation();

    // bool CheckIfReadytoSwitchOn();
    // bool CheckIfSwitchedOn();
    // bool CheckIfOperationEnable();

    void OperationModeTransitionHoming();
    void OperationModeTransitionProfilePositionMode();

    void SetOperationModeHoming();
    void SetOperationModeProfilePositionMode();

    // bool CheckIfOperationModeIsHoming();
    // bool CheckIfOperationModeIsProfilePositonMode();
    // bool CheckIfOperationModeIsProfileVelocityMode();

    // void OperationModeUpdate();

    bool CheckIfTargetReached();

public:
    StallardOSFaulhaberDrive(/* args */);
    ~StallardOSFaulhaberDrive();
    State GetState() { return state; }
    void SetState(State new_state) { state = new_state; }
    OperationMode GetOperationMode() { return operation_mode; }
    OperationMode SetOperationMode(OperationMode new_operation_mode) { operation_mode = new_operation_mode; }
};

StallardOSFaulhaberDrive::StallardOSFaulhaberDrive(/* args */)
{
}

StallardOSFaulhaberDrive::~StallardOSFaulhaberDrive()
{
}
