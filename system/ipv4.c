#include "wireminnow.h"

/*
  Returns a hostname if one is found of a given ip.
*/
char * gethostname(unsigned int * ip) {

  struct in_addr byteIP;
  byteIP.s_addr = *ip;

  struct hostent * host = gethostbyaddr(&byteIP, sizeof(byteIP), AF_INET);

  return (!host) ? NULL : host->h_name;
}

/*
  Returns boolean of an IPv4 address being a multicast address.
*/
int is_multicast(unsigned char * ip) { // Confirms whether or not an IPv4 address is multicast
  return (ntohl(*((unsigned int *) ip)) & 0xF0000000) == 0xE0000000;
}

/*
  Gets multicast number of an IPv4 multicast address.
*/
unsigned int get_multicast_num(unsigned char * ip) { // If an IPv4 address is multicast, returns the multicast number (28 bits)
  return ntohl(*((unsigned int *) ip)) & 0x00FFFFFF;
}
/*********************/

/*
  Prints out an IPv4 packet header.
*/
void print_ipv4(struct iphdr ip_header) {
      printf("IP: src = ");
      char * src_hostname = gethostname((unsigned int *) ip_header.src); // Check for the host name of an IP address
      if (check_flag(IP_USE_NAME) && src_hostname != NULL && !is_multicast(ip_header.src)) {
        printf("%s", src_hostname);
      } else if (check_flag(IP_USE_NAME) && is_multicast(ip_header.src)) { // Check for multicast (Bonus)
        printf("mcast %u", get_multicast_num(ip_header.src));
      }
      else {
        printf("%u.%u.%u.%u", ip_header.src[0], ip_header.src[1], ip_header.src[2],
               ip_header.src[3]);
      }
      printf(" dst = ");
      char * dest_hostname = gethostname((unsigned int *) ip_header.dest);
      if (check_flag(IP_USE_NAME) && dest_hostname != NULL && !is_multicast(ip_header.dest)) {
        printf("%s", dest_hostname);
      } else if (check_flag(IP_USE_NAME) && is_multicast(ip_header.dest)) {
        printf("mcast %u", get_multicast_num(ip_header.dest));
      }
      else {
        printf("%u.%u.%u.%u", ip_header.dest[0], ip_header.dest[1], ip_header.dest[2],
               ip_header.dest[3]);
      }
      printf(" typ = "); // Determine the type name
      if (check_flag(IP_USE_NAME)) {
        switch (ip_header.type) {
          case 1:
            printf("ICMP\n");
            break;
          case 2:
            printf("IGMP\n");
            break;
          case 6:
            printf("TCP\n");
            break;
          case 17:
            printf("UDP\n");
            break;
          default:
            printf("%u\n", ip_header.type);
        }
      } else {
        printf("%u\n", ip_header.type);
      }
}