#include <iostream>
#include <boost/asio/io_context.hpp>
#include "Networking/HTTP/Server/HTTPServer.h"
#include "LoadBalancer/LoadBalancer.h"


int main() {
    try {
        std::vector<std::string> serverList = {"93.184.215.14"};
        boost::asio::io_context ioContext{};

        LoadBalancer balancer(serverList, ioContext);

        balancer.accept_connections();
        ioContext.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
