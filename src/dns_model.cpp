#include <iostream>
#include <cstdlib>
#include <fstream>
#include "dns_model.h"

//std::filesystem::path CONFIG_PATH = std::getenv("HOME") / .config / dummyns / config.dummy;

std::filesystem::path GetHostsContent()
{

  std::filesystem::path CONFIG_PATH = std::filesystem::path(std::getenv("HOME")) / ".config" / "dummyns" / "config.dummy";
  std::filesystem::path DEFAULT_HOSTS_PATH = std::filesystem::path(std::getenv("HOME")) / ".config" / "dummyns" / "default_hosts.txt";

  std::ifstream infile(CONFIG_PATH);
  if (!infile) 
  {
    std::cerr << "File error: cannot find configuration file" << "\n";
    std::cout << "You should utilize the configuration agent "
              << "to create the config file (dns_config create)"
              << "\n";
    exit(EXIT_FAILURE);
  }

  char buf[1024];
  memset(buf, 0, sizeof(buf));

  infile.getline(buf, sizeof(buf));
  size_t pathlen = strnlen(buf, sizeof(buf));


  // check if we can find a path from the configuration file
  if (pathlen == 0)
  {
    std::cerr << "Path error: custom configuration file has no path" 
              << "\n";
    exit(EXIT_FAILURE);
  }

  std::filesystem::path hosts_path;

  if (strncmp(buf, "default", 1024) == 0) 
  {
    hosts_path = DEFAULT_HOSTS_PATH;
  } 
  else 
  {
    hosts_path = std::filesystem::path(buf);
  }

  hosts_path = hosts_path.lexically_normal();
  
  //check if hosts file actually exists
  if (!std::filesystem::exists(hosts_path)) 
  {
    std::cerr << "Hosts file error: hosts file specified " 
              << "from configuration does not exist"
              << "\n";
    exit(EXIT_FAILURE);
  }



  //return a std::string of the path stored in buf
  return hosts_path;
}
