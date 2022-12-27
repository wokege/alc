cmake_minimum_required(VERSION 3.17)
project(alc VERSION 1.0 DESCRIPTION "Randomly bubbles")

find_package(dpp CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

find_path(SYSTEM_INCLUDE_DIR dpp.h)
include_directories(${SYSTEM_INCLUDE_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE dpp::dpp ssl z) 

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)