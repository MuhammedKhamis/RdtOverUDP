cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(
		
        client

        ../../src/client_main.cpp
        ../../src/client_controller/client_controller.cpp

        ../../src/transport_packet/packet.cpp
        ../../src/transport_packet/data_packet.cpp
        ../../src/transport_packet/ack_packet.cpp
        ../../src/transport_packet/utilities/packet_manager.cpp
        ../../src/transport_packet/utilities/packet_parser.cpp

        ../../src/transport_protocols/transport_control/rdt_strategy.cpp
        ../../src/transport_protocols/transport_control/rdt_strategy.cpp
        ../../src/transport_protocols/transport_control/stop_and_wait/stop_and_wait.cpp
        ../../src/transport_protocols/transport_control/stop_and_wait/saw_client.cpp
        ../../src/transport_protocols/transport_control/selective_repeat/selective_repeat.cpp
        ../../src/transport_protocols/transport_control/selective_repeat/sr_client.cpp

        ../../src/utilities/io_handler.cpp
        ../../src/utilities/port_handler.cpp


)