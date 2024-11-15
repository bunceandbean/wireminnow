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
    
    print_pcap_packet_sparse(i, pcap_packet_header.cap_len);
    
    if (fread(&ether_header, ETHERHDRSIZE, 1, fptr) != 1) {
      err("Error parsing ethernet header. Exiting.\n");
      fclose(fptr);
      fptr = NULL;
      return ERR;
    }
    
    print_ether(ether_header); // Print ether information

    int ip4_hdr_len = 0; // If we need to adjust our next fseek due to reading a datagram header
    int udp_len = 0; // If we need to adjust our next fseek due to reading a UDP header
    int tcp_len = 0; // If we need to adjust our next fseek due to reading a TCP header
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

      /* if (ip_header.type == 17) { // Check for UDP
        udp_len = UDPHDRSIZE;
        struct udphdr udp;
        if (fread(&udp, UDPHDRSIZE, 1, fptr) != 1) { // Read UDP Header
          err("Error parsing UDP header. Exiting.\n");
          fclose(fptr);
          fptr = NULL;
          return ERR;
        }

        print_udp(udp); // Print UDP Header

        int udp_payload_len = (ntohs(udp.msglen) - UDPHDRSIZE >= 32) ? 32 : ntohs(udp.msglen) - UDPHDRSIZE; // Get payload length (max 32)
        unsigned char udp_payload[32];
        if (fread(&udp_payload, udp_payload_len, 1, fptr) != 1) {
            err("Error parsing UDP payload. Exiting.\n");
            fclose(fptr);
            fptr = NULL;
            return ERR;
        }

        print_udp_payload(udp_payload, udp_payload_len);

        udp_len += udp_payload_len;

      } */

      if (ip_header.type == 6) { // Check for TCP
        struct tcphdr tcp;
        if (fread(&tcp, TCPHDRSIZE, 1, fptr) != 1) { // Read TCP Header
          err("Error parsing TCP header. Exiting.\n");
          fclose(fptr);
          fptr = NULL;
          return ERR;
        }

        print_tcp_hdr(tcp); // Print TCP Header

        int hlen = get_hlen(tcp.hlen_flags);
        int skip_tcp_bytes = hlen - TCPHDRSIZE;

        if (!skip_tcp_bytes || fseek(fptr, skip_tcp_bytes, SEEK_CUR)) { // Skip over unread TCP header bytes (w/ short circuit)
          err("Error getting to TCP payload. Exiting.\n");
          fclose(fptr);
          fptr = NULL;
          return ERR;
        }

        int tcp_payload_bytes = ntohs(ip_header.total_len) - IPHDRSIZE - hlen; // Get size of TCP payload
        int tcp_payload_K = (tcp_payload_bytes <= K) ? tcp_payload_bytes : K; // Get size of TCP payload to read based off K
        if (tcp_payload_K > 0) {
          printf("Start of payload: ");
          unsigned char tcp_buffer[65546];
          if (fread(tcp_buffer, tcp_payload_K, 1, fptr ) != 1) {
            err("Error parsing TCP payload. Exiting.\n");
            fclose(fptr);
            fptr = NULL;
            return ERR;
          }
          for (int i = 0; i < tcp_payload_K; i++) {
            printf((tcp_buffer[i] >= 32 && tcp_buffer[i] <= 126) ? ("%c ") : ("%02x "), tcp_buffer[i]); // Print out payload characters
          }
        } else {
          printf("No Data");
        }
        printf("\n");
        tcp_len += hlen + tcp_payload_K; // Adjust tcp_len based off read data
        

      }
      
    }

    printf("\n"); // Make it easier to read

    if (fseek(fptr, (pcap_packet_header.cap_len - ETHERHDRSIZE - ip4_hdr_len - udp_len - tcp_len), SEEK_CUR)) { // Read next packet based off header offsets
      err("Error parsing file. Exiting.\n");
      fclose(fptr);
      fptr = NULL;
      return ERR;
    }

    i++;
  }

  return OK;
}
