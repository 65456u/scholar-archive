cmake_minimum_required(VERSION 3.22)
project(SimpleDNSRelayServer C)

set(CMAKE_C_STANDARD 11)

add_executable(SimpleDNSRelayServer main.c dns.c db.c dns.h utils.c utils.h lib/uthash.h db.h)

if (WIN32)
    target_link_libraries(SimpleDNSRelayServer wsock32 ws2_32)
endif ()

