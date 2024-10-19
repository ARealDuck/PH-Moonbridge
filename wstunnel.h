#ifndef WSTUNNEL_H
#define WSTUNNEL_H

#include "threadpool.h"
#include <websocketpp/client.hpp>
#include <thread>
#include <mutex>
#include <functional>

typedef websocketpp::client<websocketpp::config::asio_client> Client;
typedef websocketpp::connection_hdl ConnectionHandle;

class wsTunnel {
public:
	wsTunnel();


private:
	void start();

	Client ws_client_;
	bool running_;
	
};
#endif // !WSTUNNEL_H
