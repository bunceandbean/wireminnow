#include "wireminnow.h"

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

/*
  Prints out ethernet address as numbered xinu machines (if there is a match).
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
  if (0 && dest_x > 0) { // No printing XINU's
    printf("dst = xinu%02d ", dest_x);
  } else {
    printf("dst = %02X:%02X:%02X:%02X:%02X:%02X ", dest[0], dest[1], dest[2], dest[3], dest[4], dest[5]);
  }

  if (0 && src_x > 0) {
    printf("src = xinu%02d ", src_x);
  } else {
    printf("src = %02X:%02X:%02X:%02X:%02X:%02X ", src[0], src[1], src[2], src[3], src[4], src[5]);
  }

}

/*
  Prints out ethernet header information.
*/
void print_ether(struct etherhdr eth) {
    print_xinu(eth.dest, eth.src); // Analyze Xinu MAC Addresses
    printf("typ = %04X\n", ntohs(eth.type));
}
