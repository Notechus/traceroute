#include "TPacket.h"


TPacket::TPacket() : pid(0) {
}

TPacket::TPacket(int pid_, icmphdr header_)
        : pid(pid_), icmpHeader(header_) {

}

TPacket TPacket::createPacket(int pid_, icmphdr header_) {
    TPacket t(pid_, header_);
    return t;
}