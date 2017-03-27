// Sebastian Paulus 266446
#include "ICMPSender.h"

ICMPSender::ICMPSender(int pid_, int *sock)
        : pid(pid_), socket(sock) {

}

void ICMPSender::sendICMPEcho(std::string ip, uint16_t UUID, uint32_t ttl) {
    setsockopt(*socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

    icmphdr icmp_header = createICMPHeader(pid, UUID);
    sockaddr_in recipient = createRecipient(ip);

    ssize_t bytes_sent = sendto(*socket,
                                &icmp_header, sizeof(icmp_header),
                                0,
                                (struct sockaddr *) &recipient, sizeof(recipient)
    );
}

sockaddr_in ICMPSender::createRecipient(std::string ip_addr) {
    sockaddr_in rec;
    bzero(&rec, sizeof(rec));
    rec.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr.c_str(), &rec.sin_addr);

    return rec;
}

icmphdr ICMPSender::createICMPHeader(int pid, uint16_t sequence) {
    icmphdr icmp_header;
    icmp_header.type = ICMP_ECHO;
    icmp_header.code = 0;
    icmp_header.un.echo.id = (u_int16_t) pid;
    icmp_header.un.echo.sequence = sequence;
    icmp_header.checksum = 0;
    icmp_header.checksum = computeICMPChecksum(
            (u_int16_t *) &icmp_header, sizeof(icmp_header));

    return icmp_header;
}

u_int16_t ICMPSender::computeICMPChecksum(const void *buff, int length) {
    u_int32_t sum;
    const uint16_t *ptr = (const uint16_t *) buff;
    assert(length % 2 == 0);
    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;
    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t) (~(sum + (sum >> 16)));
}

