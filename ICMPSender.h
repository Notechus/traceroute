// Sebastian Paulus 266446
#pragma once
#ifndef TRACEROUTE_ICMPSENDER_H
#define TRACEROUTE_ICMPSENDER_H

#include "headers.h"

class ICMPSender {
private:
    int pid;
    int *socket;
public:
    ICMPSender(int pid_, int *sock);

    void sendICMPEcho(std::string ip, uint16_t UUID, uint32_t ttl);

private:
    sockaddr_in createRecipient(std::string ip_address);

    u_int16_t computeICMPChecksum(const void *buff, int length);

    icmphdr createICMPHeader(int pid, uint16_t sequence);
};


#endif //TRACEROUTE_ICMPSENDER_H
