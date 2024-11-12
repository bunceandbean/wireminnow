#ifndef IPV4_H
#define IPV4_H

/*********************/ // CONSTANTS

#define IPHDRSIZE 20 // We do not care past dest. ip

// IP Packet Types
#define ICMP 1
#define IGMP 2
#define TCP 6
#define UDP 17

/*********************/


/*********************/ // STRUCTS

struct iphdr { //IPv4 Header
  unsigned int unused_1;
  unsigned int unused_2;
  char ttl;
  char type;
  unsigned short unused_3;
  unsigned char src[4];
  unsigned char dest[4];
};

/*********************/

/*********************/ //FUNCTIONS

char * gethostname(unsigned int *);

int is_multicast(unsigned char *);

unsigned int get_multicast_num(unsigned char *);

void print_ipv4(struct iphdr);


/*********************/



#endif // IPV4_H