add_library(dns_core resolver_map.cpp
                line_parser.cpp)

add_executable(dns_client dns_client.cpp)
add_executable(dns_server dns_server.cpp)
add_executable(dns_config dns_config.cpp)
#add_executable(dns_app main.cpp)

target_link_libraries(dns_client PRIVATE dns_core)
target_link_libraries(dns_server PRIVATE dns_core)
target_link_libraries(dns_config PRIVATE dns_core)
