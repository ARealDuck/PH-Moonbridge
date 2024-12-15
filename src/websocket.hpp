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
	void messagesend(const std::string& message);
	void messagehandle(const std::string& reponse);
	void onopen(websocketpp::connection_hdl hdl);
	void onclose(websocketpp::connection_hdl hdl);
	void closecon();
	void handshakeprotocol(std::string message);
private:
	//client setup
	Client wsClient;
	asio::io_context wsiocontext;
	websocketpp::connection_hdl handle;
	bool handshake;
	std::string createauth(std::string& challenge, std::string& salt);
	std::string obsurl;
	std::string obsport;
	std::string obspass;
	// Message sync
	bool responsewait;
	std::mutex responsemtx;
	std::condition_variable responsecv;
	nlohmann::json lastreponse;
	//connection state
	std::mutex connectionmtx;
	std::condition_variable connectioncv;
	bool connected;
};

#endif // !WEBSOCKET_HPP
