#include "StallardOSFaulhaberMotionController.hpp"
StallardOSFaulhaberMotionController::StallardOSFaulhaberMotionController(int node_ID)
{
    node_ID = node_ID;
    StateTransitionInitialization();
    driver = StallardOSFaulhaberDrive::StallardOSFaulhaberDrive();
}
void StallardOSFaulhaberMotionController::StateTransitionInitialization()
{
    state = State::INITIALIZATION;
}
void StallardOSFaulhaberMotionController::StateTransitionPreOperational()
{
    state = State::PRE_OPERATIONAL;
}
void StallardOSFaulhaberMotionController::StateTransitionOperational()
{
    state = State::OPERATIONAL;
}
void StallardOSFaulhaberMotionController::StateTransitionStopped()
{
    state = State::STOPPED;
}
// void StallardOSFaulhaberMotionController::StateUpdate()
// {
//     if (state == State::INITIALIZATION && /*Boot Up*/) // ID Node_id + 1792, data = x00
//     {
//         StateTransitionPreOperational();
//     }
//     if (state == (State::PRE_OPERATIONAL || State::STOPPED) && /*statusword 0x00 */)
//     {
//         StateTransitionOperational();
//     }
// }
void StallardOSFaulhaberMotionController::statuswordUpdate() {}
void StallardOSFaulhaberMotionController::InitializationFinished() {} // check if bootup
void StallardOSFaulhaberMotionController::StartRemoteNodeIndication()
{
    StallardOSFaulhaberMessager::SendNMTMessage(node_ID, 1);
    StateTransitionOperational();
}

void UpdateAllDriverStates()
{
    driver.StatuswordUpdate();
    driver.StateUpdate();
}
