#ifndef ETHER_H
#define ETHER_H

#include<arpa/inet.h>

/*********************/ // CONSTANTS

#define ETHERHDRSIZE 14
#define XINUCOMPCOUNT 25
unsigned char xinus[XINUCOMPCOUNT][3] = 
{
    {0xb9,0x7a,0xd2},
    {0xb9,0x72,0xd0},
    {0xb9,0x65,0x11},
    {0xb9,0x7a,0xc4},
    {0xb9,0x72,0x77},
    {0xb9,0x7a,0x87},
    {0xb9,0x79,0x68},
    {0xb9,0x7a,0x7f},
    {0xb9,0x7b,0xca},
    {0xb9,0x7a,0x53},
    {0xb9,0x7a,0xff},
    {0xb9,0x79,0xe5},
    {0xb7,0xa8,0x5e},
    {0xb9,0x79,0xb8},
    {0xb9,0x79,0x7f},
    {0xb9,0x7d,0x0f},
    {0xa7,0x0b,0xe0},
    {0xb9,0x7a,0x9c},
    {0xb9,0x7d,0xec},
    {0xb9,0x77,0xcb},
    {0xb9,0x79,0x52},
    {0x00,0x00,0x00},
    {0xb9,0x7a,0x8d},
    {0xb7,0xa6,0x57},
    {0xb9,0x7a,0xbd}
};

/*********************/


/*********************/ // STRUCTS

struct etherhdr {
  unsigned char dest[6];
  unsigned char src[6];
  unsigned short type;
};

/*********************/


/*********************/ // FUNCTIONS

/*
    Print out known Xinu MAC addresses.
*/
void print_xinu(unsigned char dest[6], unsigned char src[6]) {
  
  int dest_x = -1;
  int src_x = -1;
  if (dest[0] != 0xb8 || dest[1] != 0x85 || dest[2] != 0x84) {
    dest_x = -2;
  }
  if (src[0] != 0xb8 || src[1] != 0x85 || src[2] != 0x84) {
    src_x = -2;
  }

  for (int i = 0; i < XINUCOMPCOUNT; i++) {
    if (i == 21) continue; //Cannot access xinu21
    if (dest_x != -2 && dest[3] == xinus[i][0] && dest[4] == xinus[i][1] && dest[5] == xinus[i][2]) {
      dest_x = i;
    }
    if (src_x != -2 && src[3] == xinus[i][0] && src[4] == xinus[i][1] && src[5] == xinus[i][2]) {
      src_x = i;
    }

  }

  printf("Ether: ");
  if (dest_x > 0) {
    printf("dst = xinu%02d ", dest_x);
  } else {
    printf("dst = %02X:%02X:%02X:%02X:%02X:%02X ", dest[0], dest[1], dest[2], dest[3], dest[4], dest[5]);
  }

  if (src_x > 0) {
    printf("src = xinu%02d ", src_x);
  } else {
    printf("src = %02X:%02X:%02X:%02X:%02X:%02X ", src[0], src[1], src[2], src[3], src[4], src[5]);
  }

}

void print_ether(unsigned char dest[6], unsigned char src[6], unsigned short type) {
    print_xinu(dest, src); // Analyze Xinu MAC Addresses
    printf("typ = %04X\n", ntohs(type));
}

/*********************/




#endif // ETHER_H