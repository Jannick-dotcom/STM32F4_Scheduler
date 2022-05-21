#pragma once

class StallardOSFaulhaberMessager
{
private:
public:
    static void SendPDO1Message(int node_ID, int controllword);
    static void SendPDO2Message(int node_ID, int pos);
    static void SendPDO3Message(int node_ID, int vel);
    static void SendPDO4Message(int node_ID, int tork);
    static void SendSDOMessage(int node_ID, int cs, int index, int subindex, int data);
    static void SendNMTMessage(int node_ID, int cs);
};
