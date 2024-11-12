#ifndef PCAP_H
#define PCAP_H

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

const char * pcap_time_units(unsigned int);

void print_pcap_packet_verbose(int, unsigned int, unsigned int, const char *, 
                           unsigned int, unsigned int);

void print_pcap_packet_minimal(int, unsigned int, unsigned int);

void print_pcap_packet_sparse(int, unsigned int);

/*********************/


#endif //PCAP_H