// Sebastian Paulus 266446
#include "TPacket.h"

TPacket::TPacket() :
        pid(-1), ttl(-1), sequence(-1), ipAddress(""), millis(0) {

}

TPacket::TPacket(int pid_, int ttl_, int sequence_, std::string from_, int millis_) :
        pid(pid_), ttl(ttl_), sequence(sequence_), ipAddress(from_), millis(millis_) {

}

int TPacket::getPid() const {
    return pid;
}

void TPacket::setPid(int pid) {
    TPacket::pid = pid;
}

const std::string &TPacket::getIpAddress() const {
    return ipAddress;
}

void TPacket::setIpAddress(const std::string &ipAddress_) {
    TPacket::ipAddress = ipAddress_;
}

int TPacket::getTtl() const {
    return ttl;
}

void TPacket::setTtl(int ttl) {
    TPacket::ttl = ttl;
}

int TPacket::getSequence() const {
    return sequence;
}

void TPacket::setSequence(int sequence) {
    TPacket::sequence = sequence;
}

std::ostream &operator<<(std::ostream &os, const TPacket &packet) {
    os << "pid: " << packet.pid << " ttl: " << packet.ttl << " sequence: " << packet.sequence << " ipAddress: "
       << packet.ipAddress << " millis: " << packet.millis;
    return os;
}

int TPacket::getMillis() const {
    return millis;
}

void TPacket::setMillis(int millis) {
    TPacket::millis = millis;
}
