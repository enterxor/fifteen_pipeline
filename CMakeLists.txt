cmake_minimum_required(VERSION 3.13)

PROJECT(fifteen)

SET(FIFTEEN_SRC main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${FIFTEEN_SRC})

set_property(TARGET fifteen PROPERTY CXX_STANDARD 11)
