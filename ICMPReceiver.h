// Sebastian Paulus 266446
#pragma once
#ifndef TRACEROUTE_ICMPRECEIVER_H
#define TRACEROUTE_ICMPRECEIVER_H

#include "TPacket.h"
#include "headers.h"

class ICMPReceiver {
private:
    int pid;
    int *socket;
public:
    ICMPReceiver(int pid_, int *sock);

    TPacket receivePacket();

};


#endif //TRACEROUTE_ICMPRECEIVER_H
