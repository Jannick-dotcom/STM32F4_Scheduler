#pragma once
#include "StallardOScan.hpp"

class StallardOSFaulhaberMessager
{
private:
    StallardOSCAN can;

public:
    static void RecivePDO1Message(int node_ID, int controllword);
    static void RecivePDO2Message(int node_ID, int pos);
    static void RecivePDO3Message(int node_ID, int vel);
    static void RecivePDO4Message(int node_ID, int tork);
    static void ReciveSDOMessage(int node_ID, int cs, int index, int subindex, int data);
    static void ReciveNMTMessage(int node_ID, int cs);
    static void TransmittedPDO1Message(int node_ID);
    static void TransmittedPDO2Message(int node_ID);
    static void TransmittedPDO3Message(int node_ID);
    static void TransmittedPDO4Message(int node_ID);
};
