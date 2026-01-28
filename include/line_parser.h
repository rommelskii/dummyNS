//
// Created by MJ Ronduen on 1/27/26.
//

#ifndef DNS_PROJECT_LINE_PARSER_H
#define DNS_PROJECT_LINE_PARSER_H

#include "dns_model.h"
#include <vector>

/**
 * @file line_parser.h
 *
 * @brief API for processing lines from the resolver file into DNS entry lines
 */

class LineProcessor {
public:
  static void ParseLine(const char *line_buffer, std::vector<std::string>& keyword_buffer);
  static DnsEntryLine GetDnsEntry(char* line_buffer);
};


/*
class LineProcessor {
public:
    std::vector<std::string> keyword_buffer; //<< string buffer for parsed keywords

    LineProcessor() {
        this->keyword_buffer.reserve(3);
    }

    void ParseLine(const char* line_buffer);

    DnsEntryLine GetDnsEntry();
};
*/

#endif //DNS_PROJECT_LINE_PARSER_H
