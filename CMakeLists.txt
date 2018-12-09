cmake_minimum_required(VERSION 3.13)
project(ProgTest05_dalnice C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic")

add_executable(ProgTest05_dalnice main.c)