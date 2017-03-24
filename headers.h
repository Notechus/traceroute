#pragma once
#ifndef TRACEROUTE_HEADERS_H
#define TRACEROUTE_HEADERS_H

#define MAC_PLATFORM 1

#include <chrono>
#include <ctime>
#include <unistd.h>
#include <assert.h>
#include <string>
#include <cerrno>
#include <iostream>

#if MAC_PLATFORM

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>


struct icmphdr {
    u_int8_t type;        /* message type */
    u_int8_t code;        /* type sub-code */
    u_int16_t checksum;
    union {
        struct {
            u_int16_t id;
            u_int16_t sequence;
        } echo;            /* echo datagram */
        u_int32_t gateway;    /* gateway address */
        struct {
            u_int16_t mtu;
        } frag;            /* path mtu discovery */
    } un;
};

#else


#endif

#endif //TRACEROUTE_HEADERS_H
