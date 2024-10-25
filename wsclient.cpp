#include "wsclient.h"
#include "settings.hpp"



void wsClient::connect() {
	settingsreader wsSettingshelper("obswebsocket", globalsettings);
	websocketpp::lib::error_code ec;
	std::string url;
	wsSettingshelper.readsetting("url") = url;
	client::connection_ptr con = ws_client_->get_connection(url, ec);
		if (ec) {
			std::cerr << "failed to connect: " << ec.message() << std::endl;
			return;
		}
}

std::future<std::string> wsClient::sendmsg(const std::string& message) {
	std::promise<std::string> responsepromise;
	auto reponsefuture = responsepromise.get_future();
	ws_client_->send(handle, message, websocketpp::frame::opcode::text);
	{
		std::lock_guard <std::mutex> lock(responsemtx);
		pending_reponses[message] = std::move(responsepromise);
	}

	return reponsefuture;
}
