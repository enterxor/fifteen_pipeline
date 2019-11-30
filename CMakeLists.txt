cmake_minimum_required(VERSION 3.12)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
    SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
)

project(fifteen)

set (CMAKE_CXX_STANDARD 11)

option(BUILD_TESTING "on")

hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)

include_directories($CMAKE_CURRENT_SOURCE_DIR)

set(FIFTEEN_SOLVING_LIB_SRC
    src/fifteen_solve.cpp
    src/fifteen_solve.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${FIFTEEN_SOLVING_LIB_SRC})

set(FIFTEEN_SRC main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${FIFTEEN_SRC})

target_link_libraries(fifteen fmt ${CMAKE_PROJECT_NAME}_lib)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

