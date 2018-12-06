cmake_minimum_required(VERSION 3.10)
project(RdtServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(Boost_INCLUDE_DIR /home/muhammed/boost_1_68_0/)


set(APP_SERVER ../Server)
set(APP_UTIL ../utilities)
set(APP_PACKET ../transport_packet)
set(APP_PROTOCOL ../transport_protocols)
set(APP_CONSTANTS ../constants)
set(APP_CLIENT ../client_controller)


#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

include_directories(${APP_SERVER})
include_directories(${APP_UTIL})
include_directories(${APP_PACKET})
include_directories(${APP_PROTOCOL})
include_directories(${APP_CONSTANTS})
include_directories(${APP_CLIENT})


file(GLOB_RECURSE SRC_FILES ${APP_UTIL}/* ${APP_PACKET}/* ${APP_PROTOCOL}/* ${APP_CONSTANTS}/*)

add_executable(RdtClient.out
        ../main/client/client-main.cpp
        ${SRC_FILES}
        ${APP_CLIENT})

