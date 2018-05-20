cmake_minimum_required(VERSION 3.10)
project(backend)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

add_executable(backend
        partition_list.cpp partition_list.h
        disk_usage_watcher.cpp disk_usage_watcher.h
        stat_file_reader.cpp stat_file_reader.h
        watcher.cpp
        )
