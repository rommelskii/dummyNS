# dummyNS: (basic) DNS Resolver and Server

A custom C++ implementation of a DNS resolution engine and DHCP state machine. This project focuses on low-level socket programming, packet serialization, and efficient record mapping.

---

## Features

* **Custom DNS Parser:** Resolves hostnames using a local `hosts.txt` database.
* **UDP Client/Server:** Built using standard `<sys/socket.h>` for high-performance, connectionless communication.
* **Unit Tested:** Robust testing of the parser logic using GoogleTest (GTest).
* **Cross-Platform:** Designed to run on both macOS and Linux-based environments.

---

## Tech Stack

* **Language:** C++17
* **Build System:** CMake 3.10+
* **Testing:** GoogleTest
* **Target Hardware:** Raspberry Pi, macOS

---

## Project Structure

```text
.
├── include/           # Header files (.h)
├── src/               # Implementation files (.cpp)
├── tests/             # GTest unit tests
├── data/              # hosts.txt and configuration files
└── CMakeLists.txt     # Build configuration
