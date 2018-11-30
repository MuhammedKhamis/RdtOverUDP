cmake_minimum_required(VERSION 3.10)
project(RdtServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")


set(APP_SERVER ../Server)
set(APP_UTIL ../utilities)
set(APP_PACKET ../transport_packet)
set(APP_PROTOCOL ../transport_protocols)


include_directories(${APP_SERVER})
include_directories(${APP_UTIL})
include_directories(${APP_PACKET})
include_directories(${APP_PROTOCOL})



file(GLOB_RECURSE SRC_FILES ${APP_UTIL}/* ${APP_PACKET}/* ${APP_PROTOCOL}/*)

add_executable(RdtServer.out
        ${SRC_FILES}
        server-main.cpp
        server_controller/server_controller.h
        server_controller/connection_handler.h
        server_controller/connection_handler.cpp)
