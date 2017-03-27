// Sebastian Paulus 266446
#include "ICMPReceiver.h"
#include "headers.h"

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

    u_int8_t *ptr = buffer; // tymczasowy ptr do bufora

    iphdr *ip_header = (iphdr *) ptr; // bierzemy ip header
    ssize_t ip_header_len = 4 * ip_header->ihl;
    ptr += ip_header_len + 8; // przesuwamy się na początek pakietu(za nagłówek)
    ip *ip_packet = (ip *) (ptr);
    ptr += (ip_packet->ip_hl * 4); // przesuwamy się na icmp
    icmp *icmp_p = (icmp *) ptr; // bierzemy icmp

    u_int8_t *icmp_packet = buffer + ip_header_len;
    icmphdr *icmp_header = (icmphdr *) icmp_packet;


    if (icmp_header->type == ICMP_ECHOREPLY) {
        return TPacket(icmp_header->un.echo.id, icmp_header->un.echo.sequence / 3 + 1, icmp_header->un.echo.sequence,
                       sender_ip_str); //TODO FIXME temporary shit
    }
    if (icmp_header->type == ICMP_TIME_EXCEEDED) {
        //makro icmp_seq = icmp_hun.ih_idseq.icd_id = sequence - to samo co un.echo.seq
        // makro icmp_id = icmp_hun_ih_idseq.icd = pid
        return TPacket(icmp_p->icmp_id, icmp_p->icmp_seq / 3 + 1, icmp_p->icmp_seq,
                       sender_ip_str); //TODO FIXME temporary shit
    }
    return TPacket();
}
