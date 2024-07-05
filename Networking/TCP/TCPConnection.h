//
// Created by shei on 04/07/24.
//

#ifndef LOADBALANCER_TCPCONNECTION_H
#define LOADBALANCER_TCPCONNECTION_H

#include <memory>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace boost::asio::ip;

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
private:
    tcp::socket socket_;
    std::string message_;

public:
    explicit TCPConnection(boost::asio::io_context &ioContext);
    typedef std::shared_ptr<TCPConnection> pointer;

    static pointer create (boost::asio::io_context& ioContext);
    tcp::socket& socket();
};


#endif //LOADBALANCER_TCPCONNECTION_H
