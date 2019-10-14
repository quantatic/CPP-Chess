cmake_minimum_required(VERSION 3.13.4)
project(Chess CXX)

set(SOURCE_FILES board.cc piece.cc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -O0")

add_executable(chess ${SOURCE_FILES})
