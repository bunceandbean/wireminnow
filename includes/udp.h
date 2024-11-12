#ifndef UDP_H
#define UDP_H

/*********************/ // CONSTANTS

#define UDPHDRSIZE 8

/*********************/


/*********************/ // STRUCTS

struct udphdr { // UDP Header
    unsigned short srcport;
    unsigned short destport;
    unsigned short msglen;
    unsigned short checksum;
};

/*********************/


/*********************/ // FUNCTIONS

void print_udp(struct udphdr);
void print_udp_payload(unsigned char *, int);

/*********************/



#endif


