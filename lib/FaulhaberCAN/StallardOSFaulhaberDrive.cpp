#include "StallardOSFaulhaberDrive.hpp"
StallardOSFaulhaberDrive::StallardOSFaulhaberDrive()
{
    statusword = 0x0000;
    StateTransitionNotReadyToSwitchOn();
}
void StallardOSFaulhaberDrive::StateTransitionNotReadyToSwitchOn() { state = State::NOT_READY_TO_SWITCH_ON; }
void StallardOSFaulhaberDrive::StateTransitionSwitchOnDisabled() { state = State::SWITCH_ON_DISABLED; }
void StallardOSFaulhaberDrive::StateTransitionReadyToSwitchOn() { state = State::READY_TO_SWITCH_ON; }
void StallardOSFaulhaberDrive::StateTransitionReadyToSwitchOn() { state = State::SWITCHED_ON; }
void StallardOSFaulhaberDrive::StateTransitionOperationEnable() { state = State::OPERATION_ENABLE; }
void StallardOSFaulhaberDrive::StateUpdate()
{
    if (state == State::NOT_READY_TO_SWITCH_ON && (statusword & 0x0000) == 0x0000)
    {
        StateTransitionSwitchOnDisabled();
    }
    if (state == State::SWITCH_ON_DISABLED && (statusword & 0x0041) == 0x0041)
    {
        StateTransitionReadyToSwitchOn();
    }
    if (state == State::READY_TO_SWITCH_ON && (statusword & 0x0043) == 0x0043)
    {
        StateTransitionNotReadyToSwitchOn();
    }
    if (state == State::SWITCHED_ON && (statusword & 0x0047) == 0x0047)
    {
        StateTransitionOperational();
    }
}
// void StallardOSFaulhaberDrive::OperationModeUpdate() {
//     if (operation_mode == OperationMode::HOMING )
// }
void StallardOSFaulhaberDrive::OperationModeUpdate()
{
    if (operation_mode == OperationMode::HOMING &&) // SDO Response
    {
        operation_mode = OperationMode::
    }
}

void StallardOSFaulhaberDrive::ShutDown() { StallardOSFaulhaberMessager::RecivePDO1Message(GetNodeID(), 0x0006); }
void StallardOSFaulhaberDrive::SwitchOn() { StallardOSFaulhaberMessager::RecivePDO1Message(GetNodeID(), 0x0007); }
void StallardOSFaulhaberDrive::EnableOperation() { StallardOSFaulhaberMessager::RecivePDO1Message(GetNodeID(), 0x000f); }

void StallardOSFaulhaberDrive::OperationModeTransitionHoming() { operation_mode = OperationMode::HOMING; }
void StallardOSFaulhaberDrive::OperationModeTransitionProfilePositionMode() { operation_mode = OperationMode::PROFILE_POSITION_MODE; }
void StallardOSFaulhaberDrive::OperationModeTransitionProfileVelocityMode() { operation_mode = OperationMode::PROFILE_VELOCITY_MODE; }

void StallardOSFaulhaberDrive::SetOperationModeHoming() { StallardOSFaulhaberMessager::SendSDOMessage(GetNodeID(), 0x2f, 0x6060, 0x00, 6); }
void StallardOSFaulhaberDrive::SetOperationModeProfilePositionMode() { StallardOSFaulhaberMessager::SendSDOMessage(GetNodeID(), 0x2f, 0x6060, 0x00, 1); }

void StallardOSFaulhaberDrive::StartHomingMode() { StallardOSFaulhaberMessager::RecivePDO1Message(GetNodeID(), 0x001f); }
void StallardOSFaulhaberDrive::SetTargetPosition(int pos) { StallardOSFaulhaberMessager::RecivePDO2Message(GetNodeID(), 0x023f, pos); }
