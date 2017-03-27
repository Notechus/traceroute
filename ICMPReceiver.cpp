// Sebastian Paulus 266446
#include "ICMPReceiver.h"

ICMPReceiver::ICMPReceiver(int pid_, int *sock)
        : pid(pid_), socket(sock) {

}

TPacket ICMPReceiver::receivePacket() {
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    ssize_t packet_len = recvfrom(*socket, buffer, IP_MAXPACKET, MSG_DONTWAIT, (sockaddr *) &sender, &sender_len);

    if (packet_len < 0) {
        std::cout << "recvfrom error" << std::strerror(errno) << std::endl;
    }

    char sender_ip_str[20];
    inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));

    ip *ip_header = (ip *) buffer;
    ssize_t ip_header_len = 4 * ip_header->ip_hl;

    u_int8_t *icmp_packet = buffer + ip_header_len;
    icmphdr *icmp_header = (struct icmphdr *) icmp_packet;

    if (icmp_header->type == ICMP_ECHOREPLY) {
        return TPacket(pid, icmp_header->un.echo.sequence / 3, icmp_header->un.echo.sequence, sender_ip_str,
                       std::chrono::seconds(1)); //TODO FIXME temporary shit
    }
    if (icmp_header->type == ICMP_TIME_EXCEEDED) {
        return TPacket(pid, icmp_header->un.echo.sequence / 3, icmp_header->un.echo.sequence, sender_ip_str,
                       std::chrono::seconds(1)); //TODO FIXME temporary shit
    }
    return TPacket();
}
