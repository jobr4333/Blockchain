cmake_minimum_required(VERSION 3.15)
project(JonceChain)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(JonceChain main.cpp block.cpp block.h hash.cpp hash.h transaction.h block_header.h sha256.cpp sha256.h joncechain.cpp joncechain.h user.cpp user.h helper.h commit_or_rollback.h)