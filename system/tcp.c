#include "wireminnow.h"

char * tcp_flags[] = {"FIN", "SYN", "RST", "PSH", "ACK", "URG"};

/*
    Prints out TCP header information.
*/
void print_tcp_hdr(struct tcphdr tcp) {
    printf("TCP: srcport = %d dstport = %d\n", ntohs(tcp.src_port), ntohs(tcp.dest_port));
    printf("%sseq = %u ack = %u window = %d urgent = 0x%04X\n", LIST_INDENT, ntohl(tcp.seq_num), 
                                                          ntohl(tcp.ack_num), ntohs(tcp.window), ntohs(tcp.urgent_ptr));
    print_flags(tcp);
}

/*
    Prints out TCP flag information.
*/
void print_flags(struct tcphdr tcp) {
    printf("%sFlags: ", LIST_INDENT);
    unsigned short flag_bits = ntohs(tcp.hlen_flags) & 0x00000FFF;
    for (int i = 0; i < 6; i++) {
        if ((flag_bits >> i) % 2) printf(" %s", tcp_flags[i]);
    }
    printf("  ");
}

/*
    Returns the hlen (adjusted) of a TCP header given a network endianness unsigned short.
*/
int get_hlen(unsigned short hlen_flags) {
    return (ntohs(hlen_flags) >> 10) & 0xFFFFFFF0;
}
