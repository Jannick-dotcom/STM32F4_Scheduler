#pragma once

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
    int Node_ID;

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
    State getState();
    int getNodeID();
};

StallardOSFaulhaberMotionController::StallardOSFaulhaberMotionController(/* args */)
{
}

StallardOSFaulhaberMotionController::~StallardOSFaulhaberMotionController()
{
}
