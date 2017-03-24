#include <iostream>
#include "headers.h"
#include "ICMPReceiver.h"
#include "ICMPSender.h"

int main() {

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    int pid = ::getpid();

    if (sockfd < 0) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));

        return -1;
    }
    std::string ip_address = "172.217.20.163";
    ICMPSender sender(pid, &sockfd);
    ICMPReceiver receiver(pid, &sockfd);

    for (int i = 0; i <= 30; i++) {

        sender.sendICMPEcho(ip_address, (uint32_t) i);
        TPacket p = receiver.receivePacket();
    }

    uint32_t ttl = 1;


    close(sockfd);

    return 0;
}