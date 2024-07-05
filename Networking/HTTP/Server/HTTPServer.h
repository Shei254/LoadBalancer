//
// Created by shei on 05/07/24.
//

#ifndef LOADBALANCER_HTTPSERVER_H
#define LOADBALANCER_HTTPSERVER_H


#include "../../TCP/Server/TCPServer.h"
#include <boost/beast/http.hpp>

using namespace boost::beast;

class HTTPServer : TCPServer {
private:
    static void handle_request(http::request<http::string_body>& request, TCPConnection::pointer &newConnection);
    static void handle_response(TCPConnection::pointer &newConnection);
protected:
    static void handle_connection(TCPConnection::pointer& newConnections);
public:
    explicit HTTPServer(boost::asio::io_context& ioContext);
};


#endif //LOADBALANCER_HTTPSERVER_H
