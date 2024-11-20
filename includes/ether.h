#ifndef ETHER_H
#define ETHER_H

/*********************/ // CONSTANTS

#define ETHERHDRSIZE 14
#define XINUCOMPCOUNT 25
#define MAXPACKETSIZE 65550

/*********************/


/*********************/ // STRUCTS

struct etherhdr {
  unsigned char dest[6];
  unsigned char src[6];
  unsigned short type;
};

/*********************/

/*********************/ // FUNCTIONS

void print_xinu(unsigned char[6], unsigned char[6]);

void print_ether(struct etherhdr);

/*********************/



#endif // ETHER_H