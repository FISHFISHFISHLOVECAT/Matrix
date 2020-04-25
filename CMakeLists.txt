cmake_minimum_required(VERSION 3.10.2)
project(Demo)

include_directories(./include)
set(CMAKE_CXX_STANDARD 11)
aux_source_directory(./src DIR_SRCS)
add_executable(demo ${DIR_SRCS})
