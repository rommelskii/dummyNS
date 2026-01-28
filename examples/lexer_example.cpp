//
// Created by MJ Ronduen on 1/27/26.
//

#include <iostream>
#include <fstream>
#include <vector>


struct DnsEntryLine {
    char ip[20];
    char hostname[256];
    char alias[256];
};

class LineProcessor {
public:
    std::vector<std::string> keyword_buffer;

    LineProcessor() {
        this->keyword_buffer.reserve(3);
    }

    void ParseLine(char* line_buffer) {
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
                this->keyword_buffer.push_back(std::string(&line_buffer[start], length));
            }
        }
    }

    DnsEntryLine GetDnsEntry() {
        DnsEntryLine dns_entry = {};

        if (this->keyword_buffer.size()  < 2) {
            std::cerr << "GetDnsEntry: keyword buffer too small" << "\n";
            return dns_entry;
        }

        const size_t ip_len = this->keyword_buffer[0].size();
        const size_t hostname_len = this->keyword_buffer[1].size();

        if (ip_len >= sizeof(dns_entry.ip)) {
            std::cerr << "GetDnsEntry: extracted ip too large" << "\n";
            return dns_entry;
        }
        if (hostname_len >= sizeof(dns_entry.hostname)) {
            std::cerr << "GetDnsEntry: hostname too long" << "\n";
            return dns_entry;
        }

        memcpy(dns_entry.ip, this->keyword_buffer[0].c_str(), ip_len);
        memcpy(dns_entry.hostname, this->keyword_buffer[1].c_str(), hostname_len);

        if (this->keyword_buffer.size() == 3) {
            size_t alias_len = this->keyword_buffer[2].size();
            if (alias_len >= sizeof(dns_entry.alias)) {
                std::cerr << "GetDnsEntry: alias too long" << "\n";
                return dns_entry;
            }
            memcpy(dns_entry.alias, this->keyword_buffer[2].c_str(), alias_len);
        }

        this->keyword_buffer.clear();

        return dns_entry;
    }

    static void PrintEntry(DnsEntryLine dns_entry) {
        std::cout << "IP: " << dns_entry.ip << "\n";
        std::cout << "Hostname: " << dns_entry.hostname << "\n";
        std::cout << "Alias: " << dns_entry.alias << "\n";
        std::cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: dns <PATH_TO_RESOLVER_FILE>" << "\n";
        exit(EXIT_FAILURE);
    }
    char line_buffer[1024];
    std::vector<std::string> line_tokens;

    const std::string RESOLVER_PATH = argv[1];
    std::ifstream infile(RESOLVER_PATH);
    if (!infile) {
        std::cerr << "File error: cannot find " << RESOLVER_PATH << "\n";
        exit(EXIT_FAILURE);
    }

    std::vector<DnsEntryLine> dns_entries;
    LineProcessor line_processor;
    while (infile.getline(line_buffer, 1024)) { // extract lines from file
        line_processor.ParseLine(line_buffer);
        dns_entries.push_back(line_processor.GetDnsEntry());
    }

    for ( auto d : dns_entries) {
        LineProcessor::PrintEntry(d);
    }

    exit(EXIT_SUCCESS);
}

