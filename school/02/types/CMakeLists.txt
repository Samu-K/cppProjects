cmake_minimum_required(VERSION 3.5)

project(types LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(types main.cpp)

install(TARGETS types
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
