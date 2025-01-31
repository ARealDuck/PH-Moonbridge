#include "websocket.hpp"
#include <spdlog/spdlog.h>

obswebsocket::obswebsocket(std::string url, std::string port, std::string password) {
	wsclient.init_asio();
	wsclient.set_message_handler(websocketpp::lib::bind(&obswebsocket::hdlmessage, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
}

obswebsocket::~obswebsocket() {
	close();
}

void obswebsocket::sendmessage(const std::string& message) {
	if (connected) {
		websocketpp::lib::error_code ec;
		wsclient.send(clienthdl, message, websocketpp::frame::opcode::text, ec);
		if (ec) {
			spdlog::warn("Failed to send message: " + ec.message());
		}
	}
}

void obswebsocket::close() {
	if (connected) {
		websocketpp::lib::error_code ec;
		wsclient.close(clienthdl, websocketpp::close::status::normal, "Client Closing: Closed by user.", ec);
		if (ec) {
			spdlog::warn("Attempted to close connection with OBS Websocket and failed: " + ec.message() );

		}
		connected = false;
		if (clientThread.joinable()) {
			clientThread.join();
		}
	}
}

