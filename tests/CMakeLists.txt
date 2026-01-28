enable_testing()

# 4. Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows compatibility and faster builds
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 5. Core Library (dns_core)
# I'm assuming you have your source files listed here
# add_library(dns_core src/resolver.cpp src/line_parser.cpp) 

# 6. Unit Tests - Resolver Map
add_executable(resolver_unit resolver_map_tests.cpp)
target_link_libraries(resolver_unit
    GTest::gtest_main 
    dns_core
)

# 7. Unit Tests - Line Parser
add_executable(line_parser_unit line_parser_tests.cpp)
target_link_libraries(line_parser_unit
    GTest::gtest_main
    dns_core
)

# 8. Test Discovery
include(GoogleTest)
gtest_discover_tests(resolver_unit)
gtest_discover_tests(line_parser_unit)
