#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;
const char* HOME = std::getenv("HOME");

#define MAXARGLEN 1024

std::filesystem::path fix_path(char* path) 
{
  if (path[0] == '/') // path provided is absolute
  {
    return std::filesystem::path(path);
  }
  // otherwise, path is relative and must be appended to the absolute current path
  std::filesystem::path normalized_path = std::filesystem::current_path() / path;
  return normalized_path.lexically_normal();
}

int main(int argc, char* argv[]) 
{
  size_t arglen;
  if (argc < 2)   
  {
    std::cerr << "Argument error: lacking argument" << "\n";
    std::cout << "Usage: ./dns_config (create | config) (config_path)" << "\n";
    exit(EXIT_FAILURE);
  }
  else if (argc == 3)
  {
    arglen = strnlen(argv[2], MAXARGLEN);
    if (arglen >= MAXARGLEN) 
    {
      std::cerr << "Argument error: argument too large" << "\n";
      exit(EXIT_FAILURE);
    }
  }

  char type_buf[MAXARGLEN];
  char pconfig_buf[MAXARGLEN];
  char line_buf[1024];

  memset(type_buf, 0, sizeof(type_buf));
  memset(line_buf, 0, sizeof(line_buf));
  memset(pconfig_buf, 0, sizeof(pconfig_buf));

  size_t type_len = strnlen(argv[1], 1024);
  memcpy(type_buf, argv[1], type_len);


  for (int i=0; i<type_len; ++i) 
  {
    type_buf[i] = tolower(type_buf[i]);
  }

  std::filesystem::path pconfig_root = fs::path(HOME) / ".config" / "dummyns" / "config.dummy";
  if ( strncmp(type_buf, "create", 1024) == 0 ) 
  {
    if (!fs::exists(pconfig_root)) 
    {
      std::cout << "Default configuration file does not exist. Creating..."
                << "\n";
      std::fstream config(pconfig_root, std::ios::out | std::ios::trunc);
      if (!config.is_open()) 
      {
        std::cerr << "File error: failed to create default configuration file at " 
                  << pconfig_root << "\n";
        exit(EXIT_FAILURE);
      }
      config << "default";
      std::cout << "Created configuration file at " << pconfig_root << "\n";
    }
    else
    {
      std::cerr << "File error: configuration file already exists" 
                << "\n";
      exit(EXIT_FAILURE);
    }
  }
  else if ( strncmp(type_buf, "custom", 1024) == 0 )
  {
    if (argc < 3)
    {
      std::cerr << "Argument error: specify the path to the configuration file" << "\n";
      std::cout << "Usage: ./dns_config (create | config) (config_path)" << "\n";
      exit(EXIT_FAILURE);
    }
    
    size_t custom_path_length = strnlen(argv[2], 1024);
    memcpy(pconfig_buf, argv[2], custom_path_length);
    std::filesystem::path fixed_path = fix_path(pconfig_buf);
    
    std::fstream file(pconfig_root, std::ios::out | std::ios::trunc);
    if (!file.is_open()) 
    {
      std::cerr << "File error: custom configuration does not exist" << "\n";
      exit(EXIT_FAILURE);
    }

    file << fixed_path.string();

    std::cout << "Hosts file set to " << fixed_path << "\n";
  } else if (strncmp(type_buf, "reset", 1024) == 0)
  {
    std::ofstream outfile(pconfig_root, std::ios::out | std::ios::trunc);
    if (!outfile.is_open()) 
    {
      std::cerr << "File error: custom configuration does not exist" << "\n";
      exit(EXIT_FAILURE);
    }
    outfile << "default";

    std::cout << "Sucessfully reset configuration file to default" 
              << "\n";
  } else 
  {
    std::cerr << "Argument error: option does not exist" << "\n";
    std::cout << "Usage: ./dns_config (create | config) (config_path)" << "\n";
  }
 

  exit(EXIT_SUCCESS);
}

