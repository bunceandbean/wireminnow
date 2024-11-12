#include "wireminnow.h"

/*
    Prints UDP header.
*/
void print_udp(struct udphdr udp) {
    printf("UDP: srcport = %d dstport = %d len = %d\n", ntohs(udp.srcport), ntohs(udp.destport), ntohs(udp.msglen));
}

/*
    Prints `len` number of bytes from UDP `payload`.
*/
void print_udp_payload(unsigned char * payload, int len) {
    printf("%sStart of payload: ", LIST_INDENT);
    print_bytes(payload, len, 1, '\n');
}
