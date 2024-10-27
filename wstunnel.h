#ifndef WSTUNNEL_H
#define WSTUNNEL_H

#define ASIO_STANDALONE
#include "threadpool.h"
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <asio/io_context.hpp>
#include <memory>
#include <iostream>


extern threadpool gthreadpool;

typedef websocketpp::client<websocketpp::config::asio_client> Client;
typedef websocketpp::connection_hdl ConnectionHandle;

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
#endif // !WSTUNNEL_H
