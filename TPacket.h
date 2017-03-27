// Sebastian Paulus 266446
#pragma once
#ifndef TRACEROUTE_T_PACKET_H
#define TRACEROUTE_T_PACKET_H

#include <ostream>
#include "headers.h"

class TPacket {

private:
    int pid;
    int ttl;
    int sequence;
    std::string ipAddress;
    int millis;

public:
    TPacket();

    TPacket(int pid_, int ttl_, int sequence_, std::string from_, int millis_ = 0);

    int getPid() const;

    void setPid(int pid);

    const std::string &getIpAddress() const;

    void setIpAddress(const std::string &ipAddress_);

    int getMillis() const;

    void setMillis(int millis);

    int getTtl() const;

    void setTtl(int ttl);

    int getSequence() const;

    void setSequence(int sequence);

    friend std::ostream &operator<<(std::ostream &os, const TPacket &packet);
};


#endif //TRACEROUTE_T_PACKET_H
