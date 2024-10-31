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
	wsClient(asio::io_context& iocontext) : ws_client_(), responseready(false) {
		ws_client_.init_asio(&iocontext);
		ws_client_.start_perpetual();
		ws_client_.set_message_handler([this](websocketpp::connection_hdl, client::message_ptr msg) {
			msghandle(msg->get_payload());
			});

	}
	void connect();
	nlohmann::json sendmsg(const nlohmann::json& message);
	void msghandle(const std::string& reponse);


private:
	client ws_client_;
	websocketpp::connection_hdl handle;
	std::mutex responsemtx;
	std::condition_variable responsecv;
	bool responseready;
	nlohmann::json lastreponse;
};




#endif // !WSCLIENT_H
