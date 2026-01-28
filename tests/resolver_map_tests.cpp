#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <fstream>
#include "resolver_map.h"

const std::string HOST_FILENAME = "hosts.txt";

void setup_test_host_file() {
    const std::string LINE_1 = "172.0.0.1   localhost   localdomain\n";
    const std::string LINE_2 = "8.8.8.8     google.com  app.google.com\n";
    const std::string LINE_3 = "203.118.3.2 ec2.aws.com aws.com";
    std::ofstream outfile(HOST_FILENAME, std::ios::out | std::ios::trunc);

    outfile << LINE_1 << LINE_2 << LINE_3;
}

TEST(ResolverMapSuite, DeclarationTest) {
    ResolverMap rmap = ResolverMap();
    ASSERT_EQ(rmap.get_map_length(), 0);
}

TEST(ResolverMapSuite, InsertTest) {
    const uint32_t IP = inet_addr("172.0.0.1");
    const std::string DOMAIN_NAME = "google.com";
    ResolverMap rmap = ResolverMap();

    const size_t INSERT_RESULT = rmap.insert_domain(DOMAIN_NAME, IP) ;

    ASSERT_EQ(INSERT_RESULT, DOMAIN_NAME.size());
    ASSERT_EQ(rmap.get_map_length(), 1);
    ASSERT_EQ(rmap.resolve_domain(DOMAIN_NAME), IP);
}

TEST(ResolverMapSuite, ExistingInsertTest) {
    const uint32_t IP = inet_addr("172.0.0.1");
    const std::string DOMAIN_NAME = "google.com";
    ResolverMap rmap = ResolverMap();

    rmap.insert_domain(DOMAIN_NAME, IP);

    const size_t EXISTING_INSERT_RESULT = rmap.insert_domain(DOMAIN_NAME, IP);

    ASSERT_EQ(EXISTING_INSERT_RESULT, 0);
    ASSERT_EQ(rmap.get_map_length(), 1);
}

TEST(ResolverMapSuite, RemovalTest) {
    const uint32_t IP = inet_addr("172.0.0.1");
    const std::string DOMAIN_NAME = "google.com";
    ResolverMap rmap = ResolverMap();

    rmap.insert_domain(DOMAIN_NAME, IP);
    const size_t REMOVE_RESULT = rmap.remove_domain(DOMAIN_NAME);

    ASSERT_EQ(REMOVE_RESULT, DOMAIN_NAME.size());
    ASSERT_EQ(rmap.get_map_length(), 0);
}

TEST(ResolverMapSuite, FalseRemovalTest) {
    const std::string DOMAIN_NAME = "google.com";
    ResolverMap rmap = ResolverMap();

    const size_t REMOVE_RESULT = rmap.remove_domain(DOMAIN_NAME);

    ASSERT_EQ(REMOVE_RESULT, -1);
    ASSERT_EQ(rmap.get_map_length(), 0);
}
