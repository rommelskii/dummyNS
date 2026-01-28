#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXARGLEN 256
#define DUMMYNS_PORT 8070

int main(int argc, char* argv[]) 
{
  if (argc <= 2) 
  {
    std::cerr << "Usage: dns_client (domain)"
              << "\n";
    exit(EXIT_FAILURE);
  }
  if  ((strnlen(argv[1], MAXARGLEN) >= MAXARGLEN) || 
        strnlen(argv[2], INET_ADDRSTRLEN) >= INET_ADDRSTRLEN)
  {
    std::cerr << "Argument error: domain or dns ip too long"
              << "\n";

    exit(EXIT_FAILURE);
  }
   
  const char* ARG_DOMAIN = argv[1];
  const char* ARG_DNS_IP = argv[2];
  uint32_t resolved_ip;
  char buf[INET_ADDRSTRLEN];
  sockaddr_in serv;

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) 
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  memset(&serv, 0, sizeof(serv));
  memset(buf, 0, sizeof(buf));

  serv.sin_family = AF_INET;
  serv.sin_port = htons(DUMMYNS_PORT);
  serv.sin_addr.s_addr = inet_addr(ARG_DNS_IP);

  std::cout << "Sending DNS request to dns=" << ARG_DNS_IP << "..." << "\n";

  int bytes_sent = sendto(sockfd, &ARG_DOMAIN, strnlen(ARG_DOMAIN, MAXARGLEN), 
                          0, (const struct sockaddr*)&serv, sizeof(serv));
  if (bytes_sent < 0) 
  {
    perror("sendto failed");
    exit(EXIT_FAILURE);
  }

  socklen_t addr_len = sizeof(serv);

  int bytes_received = recvfrom(sockfd, &resolved_ip, sizeof(resolved_ip), 0,
                                (struct sockaddr*)&serv, &addr_len);
  if (bytes_received != sizeof(resolved_ip)) 
  {
    std::cerr << "Receive error: server reply size mismatch to ip" << "\n";
    exit(EXIT_FAILURE);
  }

  std::cout << "Received DNS resolution: "  << ARG_DOMAIN << "=" 
            << inet_ntop(AF_INET, &resolved_ip, buf, INET_ADDRSTRLEN) << "\n";

  return 0;
}
