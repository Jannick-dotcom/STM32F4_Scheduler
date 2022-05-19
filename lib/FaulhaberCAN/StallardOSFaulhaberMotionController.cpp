#include "StallardOSFaulhaberMotionController.hpp"
StallardOSFaulhaberMotionController::StallardOSFaulhaberMotionController(int node_ID)
{
    node_ID = node_ID;
    StateTransitionInitialization();
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
void StallardOSFaulhaberMotionController::InitializationFinished() {}
void StallardOSFaulhaberMotionController::StartRemoteNodeIndication()
{
    StallardOSFaulhaberMessager::SendNMTMessage(node_ID, 1);
    StateTransitionOperational();
}
