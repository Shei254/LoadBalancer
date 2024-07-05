//
// Created by shei on 05/07/24.
//

#include "HTTPServer.h"

HTTPServer::HTTPServer(boost::asio::io_context &ioContext) : TCPServer(ioContext,reinterpret_cast<CONNECTION_HANDLER>(handle_connection)) {

}

void HTTPServer::handle_connection(TCPConnection::pointer &newConnection) {
    handle_response(newConnection);
}

void HTTPServer::handle_request(http::request<http::string_body> &request, TCPConnection::pointer &newConnection) {

}

void HTTPServer::handle_response(TCPConnection::pointer &newConnection) {
    http::response<http::string_body> response;
    response.result(http::status::ok);
    response.set(http::field::server, "My HTTP Server");
    response.set(http::field::content_type, "text/plain");
    response.body() = "Hello, World!";
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(newConnection->socket(), response);
}
