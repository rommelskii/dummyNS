//
// Created by MJ Ronduen on 1/27/26.
//

#ifndef DNS_PROJECT_DNS_MODEL_H
#define DNS_PROJECT_DNS_MODEL_H

struct DnsEntryLine {
    char ip[20];
    char hostname[256];
    char alias[256];
};

#endif //DNS_PROJECT_DNS_MODEL_H