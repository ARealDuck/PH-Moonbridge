#include "websocket.hpp"
#include <spdlog/spdlog.h>

obswebsocket::obswebsocket(std::string url, std::string port, std::string password) {
	wsclient.init_asio();
	wsclient.set_message_handler(websocketpp::lib::bind(&obswebsocket::hdlmessage, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
	OBSURL = url;
	OBSPORT = port;
	OBSPASSWORD = password;
	return;
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

std::string obswebsocket::getmessage() {
	return lastmessage;
}

void obswebsocket::hdlmessage(websocketpp::connection_hdl, Client::message_ptr msg) {
	spdlog::debug("Got message: " + msg->get_payload());
	lastmessage = msg->get_payload();
}

bool obswebsocket::connect() {
	websocketpp::lib::error_code ec;
	std::string furl = OBSURL + ":" + OBSPORT;
	Client::connection_ptr con = wsclient.get_connection(furl, ec);
	if (ec) {
		spdlog::warn("Connection failed: " + ec.message());
		return false;
	}
	clienthdl = con->get_handle();
	wsclient.connect(con);
	clientThread = std::thread([this]() {wsclient.run(); });
	connected = true;
	return true;
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

