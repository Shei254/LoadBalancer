//
// Created by shei on 05/07/24.
//

#include <boost/asio.hpp>
#include "LoadBalancer.h"

std::vector<std::string> servers;
size_t currentIndex;
std::mutex mutex;

LoadBalancer::LoadBalancer(const std::vector<std::string> &serverList, boost::asio::io_context &ioContext) : TCPServer(ioContext,
                                                                                                                    reinterpret_cast<CONNECTION_HANDLER>(LoadBalancer::handle_connection)) {
    servers = serverList;
    currentIndex = 0;
}

std::string LoadBalancer::getNextServer() {
    std::lock_guard<std::mutex> lock(mutex);
    std::string server = servers[currentIndex];

    currentIndex = (currentIndex + 1) % servers.size();
    return server;
}

void LoadBalancer::handle_connection(const TCPConnection::pointer &newConnection) {
    auto server_address = getNextServer();
    auto server_socket = std::make_shared<tcp::socket>(newConnection->socket().get_executor());

    tcp::resolver resolver(newConnection->socket().get_executor());
    auto endpoints = resolver.resolve(server_address, "http");

    boost::asio::async_connect(*server_socket, endpoints, [newConnection, server_socket](const boost::system::error_code& err, const tcp::endpoint&){
        if (!err) {
            forwardRequest(
                    reinterpret_cast<const std::shared_ptr<boost::asio::basic_stream_socket<boost::asio::ip::tcp>> &>(newConnection->socket()), server_socket);
        }
    });
}

void LoadBalancer::forwardRequest(const std::shared_ptr<tcp::socket>& client_socket, const std::shared_ptr<tcp::socket>& server_socket) {
    auto buffer = std::make_shared<boost::asio::streambuf>();
    boost::asio::async_read_until(*client_socket, *buffer, "\r\n\r\n", [client_socket, server_socket, buffer](const boost::system::error_code &error, std::size_t) {
        if (!error) {
            boost::asio::async_write(*server_socket, *buffer, [client_socket, server_socket, buffer](const boost::system::error_code &error, std::size_t bytesWritten) {
                if (!error) {
                    recvResponse(client_socket, server_socket);
                }
            });
        }
    });
}

void LoadBalancer::recvResponse(const std::shared_ptr<tcp::socket>& client_socket, const std::shared_ptr<tcp::socket>& server_socket) {
    auto buffer = std::make_shared<boost::asio::streambuf>();

    boost::asio::async_read_until(*server_socket, *buffer, "\r\n\r\n", [client_socket, server_socket, buffer](const boost::system::error_code& error, std::size_t bytesTransferred) {
        if (!error) {
            boost::asio::async_write(*client_socket, *buffer, [client_socket, server_socket, buffer](const boost::system::error_code& error, std::size_t) {
               if (!error) {

               }
            });
        }
    });
}

