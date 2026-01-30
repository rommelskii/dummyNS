#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include "resolver_map.h"
#include "line_parser.h"
#include "dns_model.h"

int main() 
{
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  
  if (sockfd == -1) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  sockaddr_in dest, cli;
  std::memset(&cli, 0, sizeof(cli));
  std::memset(&dest, 0, sizeof(dest));

  dest.sin_family = AF_INET;
  dest.sin_port = htons(DUMMYNS_PORT);
  dest.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd, (const struct sockaddr *)&dest, n) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  char buf[1024]; //< buffer for storing domain from requests
  char ip_buf[INET_ADDRSTRLEN]; //< character buffer for printing IPs

  // ensure null-termination 
  std::memset(buf, 0, sizeof(buf));
  std::memset(ip_buf, 0, INET_ADDRSTRLEN);

  std::cout << "Server is now running on port " << DUMMYNS_PORT << "\n";

  // resolver map prep + addressable reference to client address size 
  ResolverMap resolver = ResolverMap( GetHostsContent() ); 
  socklen_t n = sizeof(cli);

  for (;;) {
    //attempt to receive bytes from source
    int bytes_received =
        recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cli, &n);
    if (bytes_received < 0 ) { //< reset process if failed to receive bytes
      std::cerr << "recvfrom error: failed to receive bytes from client" 
                << "\n";
      continue;
    }

    // log on success
    std::cout << "RECEIVED req "
              << inet_ntop(AF_INET, &(cli.sin_addr.s_addr), ip_buf,
                           INET_ADDRSTRLEN) << "\n";

    buf[bytes_received] = '\0'; //< null terminate the end of the received domain

    // resolve the received domain
    uint32_t resolved_ip = resolver.resolve_domain(std::string(buf)); 

    // send to the client the resolved ip as a uint32_t number
    int bytes_sent = sendto(sockfd, &resolved_ip, sizeof(resolved_ip), 0,
                            (struct sockaddr *)&cli, n); 

    std::cout << "REPLIED ip="
              << inet_ntop(AF_INET, &resolved_ip, ip_buf, INET_ADDRSTRLEN)
              << " for dns="
              << std::string(buf)
	            << " to " 
              << inet_ntop(AF_INET, &(cli.sin_addr.s_addr), ip_buf, INET_ADDRSTRLEN)
	            << "\n";

    if (bytes_sent < 0) {
      std::cerr << "Server error: failed to send bytes to destination"
                << "\n";
      break;
    }
  }

  close(sockfd);

  return 0;
}
