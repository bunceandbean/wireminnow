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

  srand(time(NULL)); // Set up random number

  print_fish(); // Optional Fun Fish ASCII Art

  const char * time_units = pcap_time_units(file_header.magic); // Get micro/nano seconds based off PCAP magic number

  int i = 1;
  while((fread(&pcap_packet_header, HDRSIZE, 1, fptr))) {
    
    char packet_buffer[MAXPACKETSIZE];
    if (fread(&packet_buffer, pcap_packet_header.cap_len, 1, fptr) != 1) {
      fprintf(stderr, "Error parsing packet %d. Exiting.\n", i);
      fclose(fptr);
      fptr = NULL;
      return ERR;
    }
    
    int b = 0; // Index for current location in packet_buffer

    memcpy(&ether_header, packet_buffer, ETHERHDRSIZE); // Read ether_header
    b = ETHERHDRSIZE; // Move index to end of ether_header location


    if (ntohs(ether_header.type) == 0x0800) { // If we have a IPv4 address
      struct iphdr ip_header;

      memcpy(&ip_header, &packet_buffer[b], IPHDRSIZE); // Read IP header
      b += IPHDRSIZE;

      if (ip_header.type == 6) { // Check for TCP
        
        print_pcap_packet_sparse(i, pcap_packet_header.cap_len);
    
        print_ether(ether_header); // Print ether information
      
        print_ipv4(ip_header);

        struct tcphdr tcp;
        
        memcpy(&tcp, &packet_buffer[b], TCPHDRSIZE);  // Read TCP Header
        b += TCPHDRSIZE;

        print_tcp_hdr(tcp); // Print TCP Header

        int hlen = get_hlen(tcp.hlen_flags);
        int skip_tcp_bytes = hlen - TCPHDRSIZE; // How many TCP header bytes to skip over

        b += skip_tcp_bytes;
       
        int tcp_payload_bytes = ntohs(ip_header.total_len) - IPHDRSIZE - hlen; // Get size of TCP payload
        int tcp_payload_K = (tcp_payload_bytes <= K) ? tcp_payload_bytes : K; // Get size of TCP payload to read based off K
        if (tcp_payload_K > 0) {
          printf("Start of payload: ");
          for (int j = 0; j < tcp_payload_K; j++) {
            printf((packet_buffer[j+b] >= 32 && packet_buffer[j+b] <= 126) ? ("%c ") : ("%02x "), packet_buffer[j+b]); // Print out payload characters
          }
        } else {
          printf("No Data");
        }
        printf("\n\n"); // Make it easier to read
      }
    }

    i++;
  }

  return OK;
}
