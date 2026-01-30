# dummyNS: (basic) Lightweight DNS Resolver & Server 

A custom C++ implementation of a DNS resolution engine and server runtime program. This project focuses on low-level socket programming, packet serialization, and efficient record mapping.

This is somewhat of a simulation of how a basic DNS resolution would take place
between server and client. Apart from understanding the process, it is also 
an opportunity to understand socket programming since this project only uses
the default libraries for sockets with the use of C++17.

---
## How to use
1. Initialize the CMake project from the project root 
```
cmake -B build -S .
```
2. To build all executables, simply `make` from the project root
3. For a specific executable, perform `make <executable_name>`, i.e., `make dns_config`
4. To perform tests, do `ctest` from the project root
---

## Features

* **Custom DNS Parser:** Resolves hostnames using a local `hosts.txt` database.
* **UDP Client/Server:** Built using standard `<sys/socket.h>` for high-performance, connectionless communication.
* **Unit Tested:** Robust testing of parser and resolver map logic using GoogleTest (GTest).
* **Cross-Platform:** Designed to run on both macOS and Linux-based environments.

---

## Tech Stack

* **Language:** C++17
* **Build System:** CMake 3.10+
* **Testing:** GoogleTest
* **Target Hardware:** Raspberry Pi, Linux Servers, macOS

---
## Project Structure

```text
.
├── include/               # Header files
│   ├── dns_model.h        # DNS data structures
│   ├── line_parser.h      # Text parsing logic
│   └── resolver_map.h     # Mapping and lookup logic
├── src/                   # Implementation files
│   ├── dns_client.cpp     # DNS Client utility
│   ├── dns_config.cpp     # Configuration agent (use for changing host db file)
│   ├── dns_model.cpp      # Model implementations
│   ├── dns_server.cpp     # UDP Server implementation
│   ├── resolver_map.cpp   # Core lookup logic
│   ├── line_parser.cpp    # hosts.txt parsing
│   └── hosts.txt          # Default local database
├── tests/                 # Unit testing suite
│   ├── line_parser_tests.cpp
│   ├── resolver_map_tests.cpp
│   └── hosts.txt          # Test-specific fixtures
└── CMakeLists.txt         # Build configuration
