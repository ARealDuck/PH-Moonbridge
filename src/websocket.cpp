#include "websocket.hpp"
#include "settings.hpp"
#include "logger.hpp"

#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

wsTunnel::wsTunnel() : tunneliocontext(), WorkGuard_(asio::make_work_guard(tunneliocontext)), running_(false) {
	ws_client_.init_asio(&tunneliocontext);
}


void wsTunnel::start() {
	running_ = true;
	GLogger.add(debug, "Starting Websocket I/O Tunnel.");
	GThreadPool.submit([this]() {
		while (running_) {
			try {
				if (tunneliocontext.stopped()) {
					GLogger.add(info, "iocontext signaled as stopped, resetting.");
					tunneliocontext.reset();
				}
				GLogger.add(info, "Attempting to run iocontext.");
				tunneliocontext.run();
			}
			catch (const std::exception& e) {
				std::string error = e.what();
				GLogger.add(crit, "IOTunnel Ran into an exception!" + error);
			}
		}

		});

}

void wsTunnel::stop() {
	running_ = false;
	tunneliocontext.stop();
	GLogger.add(info, "iocontext stopped.");
	WorkGuard_.reset();
	ws_client_.stop();
}

asio::io_context& wsTunnel::getiocontext() {
	return tunneliocontext;
}

wsTunnel tunnel;

wsClient::wsClient() : ws_client_() {
	ws_client_.init_asio(&tunnel.getiocontext());
	GLogger.add(debug, "IOTunnel reference obtained.");
	ws_client_.start_perpetual();
	GLogger.add(debug, "Perpetual endpoint started.");
	ws_client_.set_message_handler([this](websocketpp::connection_hdl, Client::message_ptr msg) {
		msghandle(msg->get_payload());
		});
	GLogger.add(debug, "Message handler set.");
}

void wsClient::connect(clientsync& syncdata) {
	GLogger.add(debug, "Starting websocket connection.");
	websocketpp::lib::error_code ec;
	GLogger.add(debug, "Settings Checked for URL and Port... Got: " + settingsvar::OBSUrl + " " + settingsvar::OBSPort);
	std::string wsurl = settingsvar::OBSUrl + settingsvar::OBSPort;
	GLogger.add(debug, "Creating WebsocketURL for Connection, Final URL:" + wsurl);
	Client::connection_ptr con = ws_client_.get_connection(wsurl, ec);
	GLogger.add(debug, "Setting Connection pointer and getting handle");
	if (ec) {
		GLogger.add(info, "Client Failed to connect!");
		return;
	}
	handle = con->get_handle();
	GLogger.add(debug, "Handle Obtained, Starting connection...");
	ws_client_.connect(con);
	GLogger.add(debug, "Connection Started!");
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
			GLogger.add(info, "Websocket Client successfully established A connection with OBSWebsocket!");
		}
	}
	catch (nlohmann::json::parse_error& e) {
		GLogger.add(warn, "Failed to parse a Websocket message! Bug is likely to occur!!!");
		lastreponse = nlohmann::json{};
	}
	responseready = true;
	responsecv.notify_one();
}

bool wsClient::checkcon() {
	return handshake;
}

//creates a unique id
std::string wsClient::createid() {
	auto now = std::chrono::system_clock::now();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	return "req" + std::to_string(millis);
}

//authkey creation
std::string wsClient::createauth(std::string& challenge, std::string& salt) {
	std::string password = settingsvar::OBSPassword;
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