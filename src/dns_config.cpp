#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

#define MAXARGLEN 256

int main(int argc, char* argv[]) 
{
  if (argc < 2)   
  {
    std::cerr << "Argument error: lacking argument" << "\n";
    exit(EXIT_FAILURE);
  }

  const size_t arglen = strnlen(argv[1], MAXARGLEN);

  if (arglen >= MAXARGLEN) 
  {
    std::cerr << "Argument error: argument too large" << "\n";
    exit(EXIT_FAILURE);
  }

  char arg_buf[MAXARGLEN];
  memset(arg_buf, 0, sizeof(arg_buf));

  memcpy(arg_buf, argv[1], arglen);


  //insert configuration file logic here for loading and replacing...



  exit(EXIT_SUCCESS);
}
