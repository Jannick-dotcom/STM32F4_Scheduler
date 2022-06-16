#include "StallardOSFaulhaberDrive.hpp"

void StallardOSFaulhaberDrive::StateTransitionSwitchOnDisabled() { state = State::SWITCH_ON_DISABLED; }
void StallardOSFaulhaberDrive::StateTransitionReadyToSwitchOn() { state = State::READY_TO_SWITCH_ON; }
void StallardOSFaulhaberDrive::StateTransitionReadyToSwitchOn() { state = State::SWITCHED_ON; }
void StallardOSFaulhaberDrive::StateTransitionOperationEnable() { state = State::OPERATION_ENABLE; }
void StallardOSFaulhaberDrive::StateUpdate()
{
    if (state == State::NOT_READY_TO_SWITCH_ON &&)
    {
        StateTransitionSwitchOnDisabled();
    }
    if (state == State::SWITCH_ON_DISABLED &&)
    {
        StateTransitionReadyToSwitchOn();
    }
    if (state == State::SWITCHED_ON &&)
    {
        StateTransitionOperational();
    }
}
// void StallardOSFaulhaberDrive::OperationModeUpdate() {
//     if (operation_mode == OperationMode::HOMING )
// }
void StallardOSFaulhaberDrive::ShutDown() { StallardOSFaulhaberMessager::SendPDO1Message(GetNodeID(), 0x0006); }
void StallardOSFaulhaberDrive::SwitchOn() { StallardOSFaulhaberMessager::SendPDO1Message(GetNodeID(), 0x0007); }
void StallardOSFaulhaberDrive::EnableOperation() { StallardOSFaulhaberMessager::SendPDO1Message(GetNodeID(), 0x000f); }
void StallardOSFaulhaberDrive::OperationModeTransitionHoming() { operation_mode = OperationMode::HOMING; }
void StallardOSFaulhaberDrive::OperationModeTransitionProfilePositionMode() { operation_mode = OperationMode::PROFILE_POSITION_MODE; }
void StallardOSFaulhaberDrive::SetOperationModeHoming() { StallardOSFaulhaberMessager::SendSDOMessage(GetNodeID(), 0x2f, 0x6060, 0x00, 6); }
void StallardOSFaulhaberDrive::SetOperationModeProfilePositionMode() { StallardOSFaulhaberMessager::SendSDOMessage(GetNodeID(), 0x2f, 0x6060, 0x00, 1); }