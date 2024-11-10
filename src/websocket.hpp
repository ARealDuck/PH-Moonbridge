#pragma once
#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#define ASIO_STANDALONE
#include <asio/io_context.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include "clientsync.hpp"
#include "threadpool.h"
#include <asio/io_context.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> Client;

extern wsTunnel tunnel;
class wsTunnel {
public:
	wsTunnel();

	void start();

	void stop();

	asio::io_context& getiocontext();

private:
	asio::io_context iocontext;
	Client ws_client_;
	bool running_;

};

class wsClient {
public:
	wsClient();
	void connect(clientsync&);
	nlohmann::json sendmsg(const nlohmann::json& message);
	void msghandle(const std::string& reponse);
	bool checkcon();
	std::string createid();

private:
	Client ws_client_;
	websocketpp::connection_hdl handle;
	std::mutex responsemtx;
	std::condition_variable responsecv;
	bool responseready = false;
	nlohmann::json lastreponse;
	bool handshake = false;
	std::string createauth(std::string& challenge, std::string& salt);
};

#endif // !WEBSOCKET_HPP
