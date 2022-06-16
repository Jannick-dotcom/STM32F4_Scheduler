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
    int statusword;
    // int controllword;

    void StateTransitionNotReadyToSwitchOn();
    void StateTransitionSwitchOnDisabled();
    void StateTransitionReadyToSwitchOn();
    void StateTransitionSwitchedOn();
    void StateTransitionOperationEnable();
    void StateTransitionStartHoming();

    void StateUpdate();
    void StatuswordUpdate();

    void ShutDown();
    void SwitchOn();
    void EnableOperation();

    // bool CheckIfReadytoSwitchOn();
    // bool CheckIfSwitchedOn();
    // bool CheckIfOperationEnable();

    void OperationModeTransitionHoming();
    void OperationModeTransitionProfilePositionMode();
    void OperationModeTransitionProfileVelocityMode();

    void OperationModeUpdate();

    void SetOperationModeHoming();
    void SetOperationModeProfilePositionMode();

    // bool CheckIfOperationModeIsHoming();
    // bool CheckIfOperationModeIsProfilePositonMode();
    // bool CheckIfOperationModeIsProfileVelocityMode();

    // void OperationModeUpdate();
    void StartHomingMode();
    void SetTargetPosition(int pos);
    bool CheckIfTargetReached();

public:
    StallardOSFaulhaberDrive();
    State GetState() { return state; }
    void SetState(State new_state) { state = new_state; }
    OperationMode GetOperationMode() { return operation_mode; }
    void GetStatusword() { return statusword; }
    OperationMode SetOperationMode(OperationMode new_operation_mode) { operation_mode = new_operation_mode; }
};