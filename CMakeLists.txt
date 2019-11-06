cmake_minimum_required(VERSION 3.12)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
    SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
)

project(fifteen)

hunter_add_package(fmt)

set (CMAKE_CXX_STANDARD 11)

find_package(fmt CONFIG REQUIRED)

set(FIFTEEN_SRC main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${FIFTEEN_SRC})

set_property(TARGET fifteen PROPERTY CXX_STANDARD 11)

target_link_libraries(fifteen fmt)
