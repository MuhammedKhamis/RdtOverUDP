cmake_minimum_required(VERSION 3.10)
project(RdtOverUDP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(Boost_INCLUDE_DIR /mnt/16BE8F73BE8F4A67/program/IDES/boost_1_65_0)

set(APP_SERVER ../Server)
set(APP_UTIL ../utilities)
set(APP_PACKET ../transport_packet)
set(APP_PROTOCOL ../transport_protocols)
set(APP_CONSTANTS ../constants)
set(APP_SERVER ../server_controller)


#find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

include_directories(${APP_SERVER})
include_directories(${APP_UTIL})
include_directories(${APP_PACKET})
include_directories(${APP_PROTOCOL})
include_directories(${APP_CONSTANTS})
include_directories(${APP_SERVER})


file(GLOB_RECURSE SRC_FILES ${APP_UTIL}/* ${APP_PACKET}/* ${APP_PROTOCOL}/*
        ${APP_CONSTANTS}/* ${APP_SERVER}/*)

add_executable(
        test.out
        ../../src/transport_protocols/transport_control/utilities/packet_window.h
        ../../src/transport_protocols/transport_control/utilities/packet_window.cpp
        utilities_tests.cpp
        test.cpp
        ${SRC_FILES})
