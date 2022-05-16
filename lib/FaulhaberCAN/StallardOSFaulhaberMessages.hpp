#pragma once

class StallardoOSFaulhaberMessages
{
private:
public:
    void SendPDO1Messages(int node_ID);
    void SendPDO2Messages(int node_ID);
    void SendPDO3Messages(int node_ID);
    void SendPDO4Messages();
    void SendSDOMessages();

    StallardoOSFaulhaberMessages(/* args */);
    ~StallardoOSFaulhaberMessages();
};

StallardoOSFaulhaberMessages::StallardoOSFaulhaberMessages(/* args */)
{
}

StallardoOSFaulhaberMessages::~StallardoOSFaulhaberMessages()
{
}
