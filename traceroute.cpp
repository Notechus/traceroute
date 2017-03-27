// Sebastian Paulus 266446
#include "headers.h"
#include "ICMPReceiver.h"
#include "ICMPSender.h"

int main(int argc, char *argv[]) {

    int pid = ::getpid();
    std::string ip_address = argv[1];
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0) {
        fprintf(stderr, "socket error: %s\n", std::strerror(errno));

        return -1;
    }

    std::vector<TPacket> packets;

    ICMPSender sender(pid, &sockfd);
    ICMPReceiver receiver(pid, &sockfd);

    fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    uint32_t ttl = 1;
    uint16_t UUID = 1;
    bool end = false;
    while (ttl <= 30 && !end) {

        for (int i = 0; i < 3; i++) {
            sender.sendICMPEcho(ip_address, UUID++, (uint32_t) ttl);
        }

        auto start_time = std::chrono::system_clock::now();
        auto end_time = std::chrono::system_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        while (delta.count() < 1000) {
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
            if (ready > 0) {
                TPacket p = receiver.receivePacket();
                if (p.getIpAddress() == ip_address) {
                    end = true;
                }
//                if (p.getPid() == pid && p.getTtl() == ttl) {
                auto received = std::chrono::system_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(received - start_time);
                p.setMillis(elapsed.count());
                packets.push_back(std::move(p));
//        }
            }
            end_time = std::chrono::system_clock::now();
            delta = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        }
        ttl++;
    }

    for (int i = 0; i < packets.size(); i++) {
        std::cout << packets[i] << std::endl;
    }

    close(sockfd);

    return 0;
}