//
// Created by MJ Ronduen on 1/27/26.
//

#include <iostream>
#include <vector>
#include "dns_model.h"
#include "line_parser.h"

void LineProcessor::ParseLine(const char *line_buffer, std::vector<std::string>& keyword_buffer) {
    int start = 0;
    int end = 0;

    while (line_buffer[end] != '\0') {
        while (line_buffer[end] == ' ' || line_buffer[end] == '\t') end++;
        if (line_buffer[end] == '\0') break;

        start = end;

        while (line_buffer[end] != ' ' && line_buffer[end] != '\t'
            && line_buffer[end] != '\0') end++;

        int length = end - start;
        if (length > 0) {
            keyword_buffer.emplace_back(&line_buffer[start], length);
        }
    }
}

DnsEntryLine LineProcessor::GetDnsEntry(char* line_buffer) {
  std::vector<std::string> keyword_buffer;
  LineProcessor::ParseLine(line_buffer, keyword_buffer);
  DnsEntryLine dns_entry = DnsEntryLine();

  if (keyword_buffer.size() < 2) {
    std::cerr << "GetDnsEntry: keyword buffer too small" << "\n";
    return dns_entry;
  }

  const size_t ip_len = keyword_buffer[0].size();
  const size_t hostname_len = keyword_buffer[1].size();

  if (ip_len >= sizeof(dns_entry.ip)) {
    std::cerr << "GetDnsEntry: extracted ip too large" << "\n";
    return dns_entry;
  }
  if (hostname_len >= sizeof(dns_entry.hostname)) {
    std::cerr << "GetDnsEntry: hostname too long" << "\n";
    return dns_entry;
  }

  std::memcpy(dns_entry.ip, keyword_buffer[0].c_str(), ip_len);
  std::memcpy(dns_entry.hostname, keyword_buffer[1].c_str(), hostname_len);

  if (keyword_buffer.size() >= 3) {
    size_t alias_len = keyword_buffer[2].size();
    if (alias_len >= sizeof(dns_entry.alias)) {
      std::cerr << "GetDnsEntry: alias too long" << "\n";
      return dns_entry;
    }
    std::memcpy(dns_entry.alias, keyword_buffer[2].c_str(), alias_len);
  }

  keyword_buffer.clear();

  return dns_entry;
}
