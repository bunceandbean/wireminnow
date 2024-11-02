#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include "includes/minnow.h"

#define OK 0
#define ERR 1
#define err(X) (fprintf(stderr, (X)))

int main(int argc, char ** argv) {
  
  if (argc != 2) {
    err("Incorrect argument count (needed 2). Exiting.\n");
    return ERR;
  }

  struct pcaphdr file_header;
  struct pcappkt header;
  struct etherhdr ether_header;
  FILE * fptr;

  if (!(fptr = fopen(argv[1], "r"))) {
    err("Cannot open file. Exiting.\n");
    return ERR;
  }

  if (fread(&file_header, FILEHDRSIZE, 1, fptr) < 1) {
    err("Error reading file. Exiting.\n");
    fclose(fptr);
    fptr = NULL;
    return ERR;
  }

  const char * time_units = pcap_time_units(file_header.magic); // Get micro/nano seconds based off PCAP magic number

  int i = 1;
  while((fread(&header, HDRSIZE, 1, fptr))) {
    
    print_pcap_packet_ver(i, header.timestamp_s, header.timestamp_nm, time_units, header.org_len, header.cap_len);
    
    if (fread(&ether_header, ETHERHDRSIZE, 1, fptr) != 1) {
      err("Error parsing ethernet header. Exiting.\n");
      fclose(fptr);
      fptr = NULL;
      return ERR;
    }
    
    print_ether(ether_header.dest, ether_header.src, ether_header.type); // Print ether information

    if (fseek(fptr, (header.cap_len - ETHERHDRSIZE), SEEK_CUR)) {
      err("Error parsing file. Exiting.\n");
      fclose(fptr);
      fptr = NULL;
      return ERR;
    }

    i++;
  }

  return OK;
}
