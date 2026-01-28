//
// Created by MJ Ronduen on 1/26/26.
//

#ifndef DNS_PROJECT_RESOLVER_MAP_H
#define DNS_PROJECT_RESOLVER_MAP_H

#include <unordered_map>
#include <string>
#include "dns_model.h"

/**
 * file: resolver_map.h
 *
 * API for creating resolver map (rmap) data structures and accessing/modifying its elements.
 * In a way, it acts as the buffer for the DNS changes before being saved to the appropriate
 * file.
 */

class ResolverMap {
public:
    std::unordered_map<std::string, uint32_t> rmap;

    /**
     * @brief Initializes resolver map to an empty unordered map with 0 entries
     */
    ResolverMap();

    /**
     * @brief Builds a resolver map out of a resolver file in plain text
     * @param infile Descriptor to input resolver file
     */
    ResolverMap(const std::string PATH);

    /**
     * @brief Retrieves existing count of rmap entries
     * @return Length of rmap list
     */
    size_t get_map_length();

    /**
     * @param domain Cstring domain name
     * @brief Resolves a domain name string to an IP address
     * @return uint32_t Resolved IP in network-order unsigned 32-bit integer. 0 if not found
     */
    uint32_t resolve_domain(std::string domain);

    // RMAP MUTATORS
    /**
     * @param domain Cstring domain name
     * @brief Removes a domain and its corresponding IP address in the rmap
     * @return String length of domain name removed. -1 if not found
     */
    size_t remove_domain(std::string domain);

    /**
     * @param domain Cstring representing
     * @brief Adds a domain and its corresponding IP address in the rmap
     * @return String length of domain name added. 0 if the domain exists already. -1 if add failure.
     */
    size_t insert_domain(std::string domain, uint32_t resolved_ip);

    void ProcessDnsList(std::vector<DnsEntryLine> dns_entries);

    void AddDnsEntry(DnsEntryLine current_entry);
  
};

#endif //DNS_PROJECT_RESOLVER_MAP_H
