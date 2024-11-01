#include "wsclient.h"
#include "settings.hpp"

wsClient::wsClient() : ws_client_(), responseready(false) {
	ws_client_.init_asio(&tunnel.getiocontext());
	ws_client_.start_perpetual();
	ws_client_.set_message_handler([this](websocketpp::connection_hdl, client::message_ptr msg) {
		msghandle(msg->get_payload());
		});

}

void wsClient::connect() {
	settingsreader wsSettingshelper("obswebsocket", globalsettings);
	websocketpp::lib::error_code ec;
	std::string url;
	wsSettingshelper.readsetting("url") = url;
	client::connection_ptr con = ws_client_.get_connection(url, ec);
		if (ec) {
			std::cerr << "failed to connect: " << ec.message() << std::endl;
			return;
		}
		handle = con->get_handle();
		ws_client_.connect(con);
}

nlohmann::json wsClient::sendmsg(const nlohmann::json& message) {
	std::unique_lock <std::mutex> lock(responsemtx);
	std::string msg = message.dump();
	ws_client_.send(handle, msg, websocketpp::frame::opcode::text);
	responsecv.wait(lock, [this] {return responseready; });
	responseready = false;
	return lastreponse;
}

void wsClient::msghandle(const std::string& reponse) {
	std::lock_guard<std::mutex>lock(responsemtx);
	try {
		lastreponse = nlohmann::json::parse(reponse);
	}
	catch (nlohmann::json::parse_error& e) {
		std::cerr << "failed to parse reponse message: " << e.what() << " returning blank json." << std::endl;
		lastreponse = nlohmann::json{};
	}
	responseready = true;
	responsecv.notify_one();
}

