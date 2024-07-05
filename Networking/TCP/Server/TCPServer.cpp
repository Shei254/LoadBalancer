//
// Created by shei on 04/07/24.
//
#include <boost/asio/placeholders.hpp>

#include "TCPServer.h"
#include "../TCPConnection.h"

TCPServer::TCPServer(boost::asio::io_context &ioContext, CONNECTION_HANDLER connectionHandler) : connection_handler(connectionHandler), ioContext_(), acceptor_(ioContext, tcp::endpoint(tcp::v4(), 3333)) {

}

void TCPServer::accept_connections() {
    TCPConnection::pointer new_connection = TCPConnection::create(ioContext_);
    acceptor_.async_accept(new_connection->socket(),
                           [this, new_connection](const boost::system::error_code& ec) {
                               handle_accept(new_connection, ec);
                           });
}

void TCPServer::handle_accept(const TCPConnection::pointer& newConnection, const boost::system::error_code &error) {
    if (!error) {
        connection_handler(newConnection);
    }
    accept_connections();
}


