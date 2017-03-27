// Sebastian Paulus 266446
#include <iostream>

#include "headers.h"
#include "ICMPReceiver.h"
#include "ICMPSender.h"

int main(int argc, char *argv[]) {

    int pid = ::getpid();
    std::string ip_address = argv[1];
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));

        return -1;
    }

    std::vector<TPacket> packets;

    ICMPSender sender(pid, &sockfd);
    ICMPReceiver receiver(pid, &sockfd);

    fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    uint32_t ttl = 1;
    uint16_t UUID = 1;
    bool end = false;
    while (ttl <= 30 && !end) {

        for (int i = 0; i < 3; i++) {
            sender.sendICMPEcho(ip_address, UUID++, (uint32_t) ttl);
        }
        int received = 0;

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while (received < 3) {
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
            if (ready > 0) {
                TPacket p = receiver.receivePacket();
                packets.push_back(std::move(p));
                received++;
                if (p.getIpAddress() == ip_address) {
                    std::cout << "reached " << p.getIpAddress() << std::endl;
                    end = true;
                }
            }
        }
        ttl++;
    }

    for (int i = 0; i < packets.size(); i += 3) {
        std::cout << packets[i] << std::endl;
    }

    close(sockfd);

    return 0;
}