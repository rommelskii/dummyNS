//
// Created by MJ Ronduen on 1/26/26.
//

#include "resolver_map.h"
#include "line_parser.h"

#include <iostream>
#include <fstream>
#include <arpa/inet.h>


ResolverMap::ResolverMap() { this->rmap = {}; }

void ResolverMap::AddDnsEntry(DnsEntryLine current_entry) {
  uint32_t ip = inet_addr(current_entry.ip);
  std::string domain = current_entry.hostname;

  if (this->insert_domain(domain, ip) <= 0) {
    std::cerr << "insert_domain error: failed to insert domain " << domain
              << "(" << current_entry.ip << ")" << ", probably exists" 
              << "\n";
  }
}

void ResolverMap::ProcessDnsList(std::vector<DnsEntryLine> dns_entries) {
  if (dns_entries.size() == 0) return;
  for (int i = 0; i < dns_entries.size(); ++i) {
    ResolverMap::AddDnsEntry(dns_entries[i]);
  }
}

ResolverMap::ResolverMap(const std::string PATH) {
  std::ifstream infile(PATH);
  if (!infile) {
    std::cerr << "Resolver map build error: file not found or cannot be opened"
              << "\n";
  } else {
    char buf[1024];
    memset(buf, 0, sizeof(buf));

    std::vector<DnsEntryLine> dns_entries;

    while (infile.getline(buf, sizeof(buf))) {
      dns_entries.push_back(LineProcessor::GetDnsEntry(buf));   
    }

    this->ProcessDnsList(dns_entries);
  }
    
}


size_t ResolverMap::insert_domain(std::string domain, uint32_t resolved_ip) {
  auto find_it = this->rmap.find(domain);
  if (find_it != this->rmap.end()) { // check if duplicate exists
    return 0;
  }
  
  this->rmap[domain] = resolved_ip;

  return domain.size();
}

size_t ResolverMap::remove_domain(std::string domain) {
  auto find_it = this->rmap.find(domain);
  if (find_it == this->rmap.end()) { // check if duplicate exists
    return -1;
  }
  
  this->rmap.erase(domain);
 
  return domain.size();
}

uint32_t ResolverMap::resolve_domain(std::string domain) {
  auto find_it = this->rmap.find(domain);
  if (find_it == this->rmap.end()) { // check if duplicate exists
    return 0;
  }

  return find_it->second;
}

size_t ResolverMap::get_map_length() {
  return this->rmap.size();
}
