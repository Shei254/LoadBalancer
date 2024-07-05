//
// Created by shei on 04/07/24.
//

#ifndef LOADBALANCER_TCPSERVER_H
#define LOADBALANCER_TCPSERVER_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "../TCPConnection.h"

typedef void (*CONNECTION_HANDLER)(const TCPConnection::pointer& newConnection);

class TCPServer {
private:
    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    CONNECTION_HANDLER connection_handler;
    void handle_accept(const TCPConnection::pointer& newConnection, const boost::system::error_code &code);
public:
    explicit TCPServer(boost::asio::io_context& ioContext, CONNECTION_HANDLER connectionHandler);
    void accept_connections();
};


#endif //LOADBALANCER_TCPSERVER_H
