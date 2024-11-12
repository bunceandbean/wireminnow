#include "wireminnow.h"

#define OK 0
#define ERR 1
#define err(X) (fprintf(stderr, (X)))

int main(int argc, char ** argv) {
  
  if (argc < MINIMUM_ARGS || argc > MAXIMUM_ARGS) {
    fprintf(stderr, "Incorrect argument count (at least %d needed, max %d). Exiting.\n", MINIMUM_ARGS, MAXIMUM_ARGS);
    return ERR;
  }

  if (argc > MINIMUM_ARGS) process_arguments(&argv[MINIMUM_ARGS], argc - MINIMUM_ARGS); // Process given flags

  struct pcaphdr file_header;
  struct pcappkt pcap_packet_header;
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
  while((fread(&pcap_packet_header, HDRSIZE, 1, fptr))) {
    
    print_pcap_packet_minimal(i, pcap_packet_header.timestamp_s, pcap_packet_header.cap_len);
    
    if (fread(&ether_header, ETHERHDRSIZE, 1, fptr) != 1) {
      err("Error parsing ethernet header. Exiting.\n");
      fclose(fptr);
      fptr = NULL;
      return ERR;
    }
    
    print_ether(ether_header.dest, ether_header.src, ether_header.type); // Print ether information

    int ip4_hdr_len = 0; // If we need to adjust our next fseek due to reading a datagram header
    if (ntohs(ether_header.type) == 0x0800) { // If we have a IPv4 address
      ip4_hdr_len = IPHDRSIZE;
      struct iphdr ip_header;

      if (fread(&ip_header, IPHDRSIZE, 1, fptr) != 1) { // Read IP header
        err("Error parsing IPv4 header. Exiting.\n");
        fclose(fptr);
        fptr = NULL;
        return ERR;
      }

      print_ipv4(ip_header);
      
    }
     
    if (fseek(fptr, (pcap_packet_header.cap_len - ETHERHDRSIZE - ip4_hdr_len), SEEK_CUR)) { // Read next packet based off ipv4 offset
      err("Error parsing file. Exiting.\n");
      fclose(fptr);
      fptr = NULL;
      return ERR;
    }

    i++;
  }

  return OK;
}
