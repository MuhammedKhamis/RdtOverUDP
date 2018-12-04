cmake_minimum_required(VERSION 3.10)
project(RdtServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")


set(APP_SERVER ../Server)
set(APP_UTIL ../utilities)
set(APP_PACKET ../transport_packet)
set(APP_PROTOCOL ../transport_protocols)
set(APP_CONSTANTS ../constants)

include_directories(${APP_SERVER})
include_directories(${APP_UTIL})
include_directories(${APP_PACKET})
include_directories(${APP_PROTOCOL})
include_directories(${APP_CONSTANTS})



file(GLOB_RECURSE SRC_FILES ${APP_UTIL}/* ${APP_PACKET}/* ${APP_PROTOCOL}/* ${APP_CONSTANTS}/*)

add_executable(RdtServer.out
        ${SRC_FILES}
        server-main.cpp
        server_controller/server_controller.h
        connection_handler/connection_handler.h
        connection_handler/connection_handler.cpp server_controller/server_controller.cpp)
