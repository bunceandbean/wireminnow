#ifndef TCP_H
#define TCP_H

/*********************/ // CONSTANTS

#define TCPHDRSIZE 20
#define K 80

/*********************/

/*********************/ // STRUCTS

struct tcphdr {
    unsigned short src_port;
    unsigned short dest_port;
    unsigned int seq_num;
    unsigned int ack_num;
    unsigned short hlen_flags;
    unsigned short window;
    unsigned short checksum;
    unsigned short urgent_ptr;
};

/*********************/

/*********************/ // FUNCTIONS

void print_flags(struct tcphdr);
void print_tcp_hdr(struct tcphdr);
int get_hlen(unsigned short);

/*********************/



#endif