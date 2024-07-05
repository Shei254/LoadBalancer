//
// Created by shei on 05/07/24.
//

#ifndef LOADBALANCER_LOADBALANCER_H
#define LOADBALANCER_LOADBALANCER_H

#include <vector>
#include <string>
#include <mutex>
#include "../Networking/HTTP/Server/HTTPServer.h"

class LoadBalancer : public TCPServer {
private:
    static std::string getNextServer();
    static void recvResponse(const std::shared_ptr<tcp::socket>& client_socket, const std::shared_ptr<tcp::socket>& server_socket);
    static void forwardRequest(const std::shared_ptr<tcp::socket>& client_socket, const std::shared_ptr<tcp::socket>& server_socket);
public:
    explicit LoadBalancer(const std::vector<std::string>& servers, boost::asio::io_context &ioContext);
    static void handle_connection (const TCPConnection::pointer& newConnection);
};
#endif //LOADBALANCER_LOADBALANCER_H
