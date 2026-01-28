#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "line_parser.h" 
#include <cstring>


/*
const std::string HOST_FILENAME = "hosts.txt";

void setup_test_host_file() 
{
    const std::string LINE_1 = "172.0.0.1   localhost   localdomain\n";
    const std::string LINE_2 = "8.8.8.8     google.com  app.google.com\n";
    const std::string LINE_3 = "203.118.3.2 ec2.aws.com aws.com";
    std::ofstream outfile(HOST_FILENAME, std::ios::out | std::ios::trunc);

    outfile << LINE_1 << LINE_2 << LINE_3;
}
*/

class LineParserTestFixture : public ::testing::Test  
{
 protected:
  const std::string RESOLVER_FILENAME = "hosts.txt";

  const std::string LINE_1_IP = "127.0.0.1";
  const std::string LINE_1_HOSTNAME = "google.com";
  const std::string LINE_1_ALIAS = "app.google.com";

  const std::string LINE_2_IP = "203.8.2.1";
  const std::string LINE_2_HOSTNAME = "ecs.aws";
  const std::string LINE_2_ALIAS = "aws.ecs.com";

  const std::string LINE_3_IP = "49.200.15.220";
  const std::string LINE_3_HOSTNAME = "mapua";
  const std::string LINE_3_ALIAS = "mapua.blackboard.com";

  /**
   * @brief Creates the sample resolver file for every tests under the fixture
   */
  void SetUp() override
  { 
    std::ofstream outfile(RESOLVER_FILENAME, std::ios::out | std::ios::trunc);
    outfile << LINE_1_IP << " " << LINE_1_HOSTNAME << " " << LINE_1_ALIAS << "\n";
    outfile << LINE_2_IP << " " << LINE_2_HOSTNAME << " " << LINE_2_ALIAS << "\n";
    outfile << LINE_3_IP << " " << LINE_3_HOSTNAME << " " << LINE_3_ALIAS;
  }
};


/**
* file: line_parser_tests.cpp
*
* Contains unit tests for the line parser API
*
* 1. keyword buffer
* 2. parse line
* 3. dns entry building
*/



TEST_F(LineParserTestFixture, LineParsingPopulationTest) {
  std::ifstream infile(RESOLVER_FILENAME);
  ASSERT_TRUE(infile); // make sure file is actually readable

  char buf[1024];
  std::memset(buf, 0, sizeof(buf));

  std::vector<std::string> keyword_buffer;


  while (infile.getline(buf,sizeof(buf))) {
    LineProcessor::ParseLine(buf, keyword_buffer);
  }
  
  ASSERT_EQ(keyword_buffer.size(), 9);
}


TEST_F(LineParserTestFixture, DnsEntryBuilding) {
  std::ifstream infile(RESOLVER_FILENAME);
  ASSERT_TRUE(infile); // make sure file is actually readable

  char buf[1024];
  std::memset(buf, 0, sizeof(buf));

  std::vector<DnsEntryLine> dns_list;


  while (infile.getline(buf,sizeof(buf))) {
    dns_list.push_back(LineProcessor::GetDnsEntry(buf));
  }


  // just test the first entry
  ASSERT_EQ(std::strcmp(dns_list[0].ip, LINE_1_IP.c_str()), 0);
  ASSERT_EQ(std::strcmp(dns_list[0].hostname, LINE_1_HOSTNAME.c_str()), 0);
  ASSERT_EQ(std::strcmp(dns_list[0].alias, LINE_1_ALIAS.c_str()), 0);
}
