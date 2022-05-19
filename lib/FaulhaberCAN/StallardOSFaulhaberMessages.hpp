#pragma once

class StallardOSFaulhaberMessager
{
private:
public:
    static void SendPDO1Message(int node_ID);
    static void SendPDO2Message(int node_ID, int pos);
    static void SendPDO3Message(int node_ID);
    static void SendPDO4Message(int node_ID);
    static void SendSDOMessage();
    static void SendNMTMessage(int node_ID, int cs);
};
