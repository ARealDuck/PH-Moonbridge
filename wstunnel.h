#ifndef WSTUNNEL_H
#define WSTUNNEL_H

#include "threadpool.h"
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
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

private:

	Client ws_client_;
	bool running_;
	
};
#endif // !WSTUNNEL_H
