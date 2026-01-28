//
// Created by MJ Ronduen on 1/26/26.
//

#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: dns <PATH_TO_RESOLVER_FILE>" << "\n";
        exit(EXIT_FAILURE);
    }
    std::string buf;

    const std::string RESOLVER_PATH = argv[1];
    std::ifstream infile(RESOLVER_PATH);
    if (!infile) {
        std::cerr << "File error: cannot find " << RESOLVER_PATH << "\n";
        exit(EXIT_FAILURE);
    }

    while (std::getline(infile, buf)) {
        if (buf.empty()) continue;
        if (buf[0] == '#') continue;

        std::cout << buf << std::endl;
    }
    exit(EXIT_SUCCESS);
}
