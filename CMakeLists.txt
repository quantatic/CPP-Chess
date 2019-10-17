cmake_minimum_required(VERSION 3.13.4)
project(Chess CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -g -O3")
set(SOURCE_FILES board.cc piece.cc chess.cc)

add_executable(chess ${SOURCE_FILES})
