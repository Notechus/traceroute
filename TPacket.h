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
    std::chrono::milliseconds millis;

public:
    TPacket();

    TPacket(int pid_, int ttl_, int sequence_, std::string from_, std::chrono::milliseconds millis_);

    int getPid() const;

    void setPid(int pid);

    const std::string &getIpAddress() const;

    void setIpAddress(const std::string &ipAddress_);

    const std::chrono::milliseconds &getMillis() const;

    void setMillis(const std::chrono::milliseconds &millis);

    int getTtl() const;

    void setTtl(int ttl);

    int getSequence() const;

    void setSequence(int sequence);

    friend std::ostream &operator<<(std::ostream &os, const TPacket &packet);
};


#endif //TRACEROUTE_T_PACKET_H
