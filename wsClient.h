#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <memory>

class wsClient {
public:
	wsClient(std::shared_ptr<client> shared_client) : ws_client_(shared_client) {}

	void setmsghdl();
	void connect();

private:
	std::shared_ptr<client> ws_client_
};




#endif // !WSCLIENT_H
