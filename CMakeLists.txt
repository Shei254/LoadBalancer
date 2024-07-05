cmake_minimum_required(VERSION 3.27)
project(LoadBalancer)

FIND_PACKAGE(Boost REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)

add_executable(LoadBalancer main.cpp
        Networking/TCP/Server/TCPServer.cpp
        Networking/TCP/Server/TCPServer.h
        Networking/TCP/TCPConnection.cpp
        Networking/TCP/TCPConnection.h
        Networking/HTTP/Server/HTTPServer.cpp
        Networking/HTTP/Server/HTTPServer.h
        LoadBalancer/LoadBalancer.cpp
        LoadBalancer/LoadBalancer.h)
TARGET_LINK_LIBRARIES(LoadBalancer LINK_PUBLIC ${Boost_LIBRARIES} )