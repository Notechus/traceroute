#ifndef TRACEROUTE_T_PACKET_H
#define TRACEROUTE_T_PACKET_H

#include "headers.h"

class TPacket {

private:
    int pid;
    icmphdr icmpHeader;

public:
    TPacket();

    TPacket(int pid_, icmphdr header_);

    static TPacket createPacket(int pid_, icmphdr header_);

private:

};


#endif //TRACEROUTE_T_PACKET_H
