#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <memory>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class wsClient {
public:
	wsClient(std::shared_ptr<client> ws_client) : ws_client_(ws_client), connected(false) {
		// Client settings
		ws_client_->init_asio();
		ws_client_->start_perpetual();

		// Handlers
		ws_client_->set_open_handler([this](websocketpp::connection_hdl hdl) {
			std::cout << "connection opened" << std::endl;
			handle = hdl;
			connected = true;
			});
		ws_client_->set_message_handler([this](websocketpp::connection_hdl, client::message_ptr msg) {
			handle_message(msg->get_payload());
			});
		ws_client_->set_close_handler([this](websocketpp::connection_hdl hdl) {
			std::cout << "connection closed" << std::endl;
			connected = false;
			});
		ws_client_->set_fail_handler([this](websocketpp::connection_hdl hdl) {
			std::cout << "connection failed." << std::endl;
			connected = false;
			});

	}
	void connect();
	std::future<std::string> sendmsg(const std::string& message);

private:
	std::shared_ptr<client> ws_client_;
	websocketpp::connection_hdl handle;
	bool connected;
	std::mutex responsemtx;
};




#endif // !WSCLIENT_H
