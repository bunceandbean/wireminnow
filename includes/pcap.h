#ifndef PCAP_H
#define PCAP_H

#include <stdio.h>

/*********************/ // CONSTANTS

#define FILEHDRSIZE 24
#define FILEHDRSIZE 24
#define HDRSIZE 16

/*********************/


/*********************/ // STRUCTS

struct pcaphdr {
  unsigned int magic;
  unsigned short ver_major;
  unsigned short ver_minor;
  unsigned int reserved1;
  unsigned int reserved2;
  unsigned int snap_len;
  unsigned int link_type_CRC;
};
struct pcappkt {
  
  unsigned int timestamp_s;
  unsigned int timestamp_nm;
  unsigned int cap_len;
  unsigned int org_len;

};

/*********************/


/*********************/ // FUNCTIONS

/*
  Given a PCAP file's magic number,
  return microseconds or seconds string.
*/
const char * pcap_time_units(unsigned int magic) { return (magic == 0xA1B2C3D4) ? "microseconds" : "nanoseconds"; }

/*
  Print out verbose PCAP packet information.
*/
void print_pcap_packet_ver(int seq, unsigned int ts_macro, unsigned int ts_micro, const char * units, 
                           unsigned int act_len, unsigned int cap_len) {
    printf("Packet %d: timestamp = 0x%08X subtimestamp = 0x%08x (%s)", seq, ts_macro, ts_macro, units);
    printf(" actual length = %d captured length = %d\n", act_len, cap_len);
}

/*
  Print out non-verbose PCAP packet information.
*/
void print_pcap_packet(int seq, unsigned int cap_len) {
  printf("Packet %d: captured length = %d\n", seq, cap_len);
}


#endif //PCAP_H