cmake_minimum_required(VERSION 3.10)
project(RdtOverUDP)

set(CMAKE_CXX_STANDARD 11)

set(Boost_INCLUDE_DIR /mnt/16BE8F73BE8F4A67/program/IDES/boost_1_65_0)

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(src/Client/client_controller)
include_directories(src/Server/connection_handler)
include_directories(src/Server/server_controller)
include_directories(src/transport_packet)
include_directories(src/transport_protocols/congestion_control)
include_directories(src/transport_protocols/congestion_control/states)
include_directories(src/transport_protocols/transport_control)
include_directories(src/utilities)

add_executable(RdtOverUDP
        data/client/test.txt
        data/server/test.txt
        src/Client/client_controller/client_controller.h
        src/Client/client-main.cpp
        src/Server/connection_handler/connection_handler.cpp
        src/Server/connection_handler/connection_handler.h
        src/Server/server_controller/server_controller.cpp
        src/Server/server_controller/server_controller.h
        src/Server/server-main.cpp
        src/transport_packet/ack_packet.h
        src/transport_packet/data_packet.h
        src/transport_packet/packet.h
        src/transport_protocols/congestion_control/states/congestion_control.cpp
        src/transport_protocols/congestion_control/states/congestion_control.h
        src/transport_protocols/congestion_control/states/slow_start.cpp
        src/transport_protocols/congestion_control/states/slow_start.h
        src/transport_protocols/congestion_control/congestion_controller.cpp
        src/transport_protocols/congestion_control/congestion_controller.h
        src/transport_protocols/transport_control/rdt_strategy.cpp
        src/transport_protocols/transport_control/rdt_strategy.h
        src/transport_protocols/transport_control/selective_repeat.cpp
        src/transport_protocols/transport_control/selective_repeat.h
        src/transport_protocols/transport_control/stop_and_wait.cpp
        src/transport_protocols/transport_control/stop_and_wait.h
        src/utilities/io_handler.cpp
        src/utilities/io_handler.h
        src/utilities/packet_manager.cpp
        src/utilities/packet_manager.h
        src/utilities/packet_parser.cpp
        src/utilities/packet_parser.h
        tests/utilities_test/test.cpp
        LICENSE
        README.md src/transport_packet/packet.cpp src/transport_packet/ack_packet.cpp src/transport_packet/data_packet.cpp)
