// Sebastian Paulus 266446
#include "TPacket.h"

TPacket::TPacket() :
        pid(-1), ttl(-1), sequence(-1), ipAddress(""), millis(0) {

}

TPacket::TPacket(int pid_, int ttl_, int sequence_, std::string from_, std::chrono::milliseconds millis_) :
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

const std::chrono::milliseconds &TPacket::getMillis() const {
    return millis;
}

void TPacket::setMillis(const std::chrono::milliseconds &millis) {
    TPacket::millis = millis;
}

std::ostream &operator<<(std::ostream &os, const TPacket &packet) {
    os << "pid: " << packet.pid << " ipAddress: " << packet.ipAddress << " millis: " << packet.millis.count();
    return os;
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
