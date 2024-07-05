//
// Created by shei on 04/07/24.
//

#include "TCPConnection.h"

#include <memory>
TCPConnection::TCPConnection(boost::asio::io_context &ioContext) : socket_(ioContext) {

}

TCPConnection::pointer TCPConnection::create(boost::asio::io_context &ioContext) {
    return std::make_shared<TCPConnection>(ioContext);
}

tcp::socket &TCPConnection::socket() {
    return socket_;
}
