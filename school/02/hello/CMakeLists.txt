cmake_minimum_required(VERSION 3.5)

project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello main.cpp)

install(TARGETS hello
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
