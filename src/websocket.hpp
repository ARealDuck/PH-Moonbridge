#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#define ASIO_STANDALONE
#include <asio.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include "clientsync.hpp"
#include "threadpool.h"
#include <asio/io_context.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> Client;

class Websocket {
public:
	Websocket(asio::io_context& io_context);
	void connect(clientsync&);
	nlohmann::json sendmsg(const nlohmann::json& message);
	void msghandle(const std::string& reponse);
	bool checkcon() const;
private:
	Client wsClient;
	websocketpp::connection_hdl handle;
	std::mutex responsemtx;
	std::condition_variable responsecv;
	bool responseready = false;
	nlohmann::json lastreponse;
	bool handshake = false;
	std::string createauth(std::string& challenge, std::string& salt);
};

#endif // !WEBSOCKET_HPP
