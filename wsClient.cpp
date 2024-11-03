#include "wsclient.h"
#include "settings.hpp"
#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

wsClient::wsClient() : ws_client_() {
	ws_client_.init_asio(&tunnel.getiocontext());
	ws_client_.start_perpetual();
	ws_client_.set_message_handler([this](websocketpp::connection_hdl, client::message_ptr msg) {
		msghandle(msg->get_payload());
		});

}

void wsClient::connect(clientsync& syncdata) {
	settingsreader wsSettingshelper("obswebsocket", globalsettings);
	websocketpp::lib::error_code ec;
	std::string port;
	wsSettingshelper.readsetting("port") = port;
	std::string wsurl = "ws://localhost:" + port;
	client::connection_ptr con = ws_client_.get_connection(wsurl, ec);
		if (ec) {
			std::cerr << "failed to connect: " << ec.message() << std::endl;
			return;
		}
		handle = con->get_handle();
		ws_client_.connect(con);
		{ 
			std::lock_guard<std::mutex> lock(syncdata.clientmtx);
			syncdata.ready = true;
		}
		syncdata.clientcv.notify_one();
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
		if (lastreponse.contains("op") && lastreponse["op"] == "0") {
			if (lastreponse.contains("d") && lastreponse["d"].contains("authentication")) {
				std::string challenge = lastreponse["d"]["authentication"]["challenge"];
				std::string salt = lastreponse["d"]["authentication"]["salt"];
				std::string authstring = createauth(challenge, salt);
				nlohmann::json identifymsg;
				identifymsg["op"] = "1";
				identifymsg["d"] = {
					{"rpcVersion", 1},
					{"authentication", authstring},
					{"eventsubscriptions", 33},
				};
				sendmsg(identifymsg);
			}
			else {
				nlohmann::json identifymsg;
				identifymsg["op"] = "1";
				identifymsg["d"] = {
					{"rpcVersion", 1},
					{"eventsubscriptions", 33},
				};
				sendmsg(identifymsg);
			}
		}
		if (lastreponse.contains("op") && lastreponse["op"] == "2") {
			handshake = true;
		}
	}
	catch (nlohmann::json::parse_error& e) {
		std::cerr << "failed to parse reponse message: " << e.what() << " returning blank json." << std::endl;
		lastreponse = nlohmann::json{};
	}
	responseready = true;
	responsecv.notify_one();
}

bool wsClient::checkcon() {
	return handshake;
}

std::string wsClient::createauth(std::string& challenge, std::string& salt) {
	settingsreader wsSettingshelper("obswebsocket", globalsettings);
	std::string password = wsSettingshelper.readsetting("password");
	std::string input = password + salt;

	// First hash (SHA256)
	std::string hash1;
	CryptoPP::SHA256 sha256;
	CryptoPP::StringSource ss1(input, true, new CryptoPP::HashFilter(sha256, new CryptoPP::StringSink(hash1)));

	// Encode first has into Base64
	std::string base64secret;
	CryptoPP::StringSource ss2(hash1, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(base64secret), false));

	// Put together base64secret and challenge for the next step
	std::string input2 = base64secret + challenge;

	// Second hash (SHA256)
	std::string digest;
	CryptoPP::StringSource ss3(input2, true, new CryptoPP::HashFilter(sha256, new CryptoPP::StringSink(digest)));

	// Encode the second hash into base64 for the final result
	std::string base64digest;
	CryptoPP::StringSource ss4(digest, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(base64digest), false));

	//returns final result
	return base64digest;
}

