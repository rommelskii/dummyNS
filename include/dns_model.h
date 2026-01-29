//
// Created by MJ Ronduen on 1/27/26.
//

#ifndef DNS_PROJECT_DNS_MODEL_H
#define DNS_PROJECT_DNS_MODEL_H

#include <filesystem>

struct DnsEntryLine {
    char ip[20];
    char hostname[256];
    char alias[256];
};

/**
  * @brief Processes the contents of the configuration file to get the path 
  * of the configured hosts database file
  *
  * @return Filesystem path object to the hosts file
  */
std::filesystem::path GetHostsContent();



#endif //DNS_PROJECT_DNS_MODEL_H
