#ifndef WSCLIENT_H
#define WSCLIENT_H

#define ASIO_STANDALONE
#include <asio/io_context.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <memory>
#include "wstunnel.h"

typedef websocketpp::client<websocketpp::config::asio_client> client;

extern wsTunnel tunnel;

class wsClient {
public:
	wsClient();
	void connect();
	nlohmann::json sendmsg(const nlohmann::json& message);
	void msghandle(const std::string& reponse);
	bool checkcon();

private:
	client ws_client_;
	websocketpp::connection_hdl handle;
	std::mutex responsemtx;
	std::condition_variable responsecv;
	bool responseready;
	nlohmann::json lastreponse;
	bool handshake = false;
	std::string createauth(std::string& challenge, std::string& salt);
};




#endif // !WSCLIENT_H
