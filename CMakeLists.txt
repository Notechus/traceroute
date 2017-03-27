cmake_minimum_required(VERSION 3.6)
project(traceroute)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES traceroute.cpp headers.h)
set(TPACKET TPacket.h TPacket.cpp)
set(ICMP_SENDER ICMPSender.h ICMPSender.cpp)
set(ICMP_RECEIVER ICMPReceiver.h ICMPReceiver.cpp)
add_executable(traceroute ${SOURCE_FILES} ${TPACKET} ${ICMP_SENDER} ${ICMP_RECEIVER})