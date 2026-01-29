add_library(dns_core resolver_map.cpp
                line_parser.cpp
                dns_model.cpp)

set(SOURCES_LIST dns_client.cpp
             dns_server.cpp
             dns_config.cpp)

foreach(SOURCE_FILE ${SOURCES_LIST})
  get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
  add_executable(${TARGET_NAME} ${SOURCE_FILE})
  target_link_libraries(${TARGET_NAME} PRIVATE dns_core)
endforeach()

#add_executable(dns_client dns_client.cpp)
#add_executable(dns_server dns_server.cpp)
#add_executable(dns_config dns_config.cpp)
#add_executable(dns_app main.cpp)

#target_link_libraries(dns_client PRIVATE dns_core)
#target_link_libraries(dns_server PRIVATE dns_core)
#target_link_libraries(dns_config PRIVATE dns_core)
