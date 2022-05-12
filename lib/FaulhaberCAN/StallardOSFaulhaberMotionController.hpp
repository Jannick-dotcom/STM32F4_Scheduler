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

public:
    StallardOSFaulhaberMotionController(/* args */);
    ~StallardOSFaulhaberMotionController();
};

StallardOSFaulhaberMotionController::StallardOSFaulhaberMotionController(/* args */)
{
}

StallardOSFaulhaberMotionController::~StallardOSFaulhaberMotionController()
{
}
