#pragma once
#include "StallardoOSFaulhaberControllword.hpp"

class StallardOSFaulhaberMotionController
{
private:
    enum class State
    {
        INITIALIZATION,
        PRE_OPERATIONAL,
        STOPPED,
        OPERATIONAL
    };

    int node_ID;
    State state;
    StallardoOSFaulhaberControllword controllword;

    void StateTransitionInitialization();
    void StateTransitionPreOperational();
    void StateTransitionOperational();
    void StateTransitionStopped();

    void InitializationFinished();
    void StartRemoteNodeIndication();
    void EnterPreOperationalStateIndication();
    void StopRemoteNodeIndication();
    void StartRemoteNodeIndication();
    void ResetCommunicationIndication();
    void ResetNodeIndication();

public:
    StallardOSFaulhaberMotionController(/* args */);
    ~StallardOSFaulhaberMotionController();
    State GetState();
    int GetNodeID();
};

StallardOSFaulhaberMotionController::StallardOSFaulhaberMotionController(/* args */)
{
}

StallardOSFaulhaberMotionController::~StallardOSFaulhaberMotionController()
{
}
