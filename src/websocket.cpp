#include "websocket.hpp"
#include "settings.hpp"
#include "logger.hpp"

#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

Websocket::Websocket(asio::io_context& io_context) {
	GLogger.add(debug, "websocket client creation started.");
	wsClient.init_asio(&io_context);
	wsClient.start_perpetual();
	GLogger.add(debug, "Setting Websocket Handlers...");
	wsClient.set_message_handler([this](websocketpp::connection_hdl, Client::message_ptr msg) {
		msghandle(msg->get_payload());
		});
	wsClient.set_fail_handler([](websocketpp::connection_hdl) {
		GLogger.add(crit, "Connection Failed!");
		});
	wsClient.set_close_handler([](websocketpp::connection_hdl) {
		GLogger.add(info, "Connection closed by server, Restarting...");
		// Implement wait timer before restart here.
		});
	GLogger.add(debug, "websocket client created.");
}

void Websocket::connect(clientsync& syncdata) {
	GLogger.add(debug, "Starting websocket connection.");
	websocketpp::lib::error_code ec;
	GLogger.add(debug, "Settings Checked for URL and Port... Got: " + settingsvar::OBSUrl + "and " + settingsvar::OBSPort);
	std::string wsurl = settingsvar::OBSUrl + settingsvar::OBSPort;
	GLogger.add(debug, "Creating WebsocketURL for Connection, Final URL: " + wsurl);
	Client::connection_ptr con = wsClient.get_connection(wsurl, ec);
	GLogger.add(debug, "Setting Connection pointer and getting handle");
	if (ec) {
		GLogger.add(info, "Client Failed to connect!");
		return;
	}
	handle = con->get_handle();
	GLogger.add(debug, "Handle Obtained, Starting connection...");
	wsClient.connect(con);
	GLogger.add(debug, "Connection Started!");
	{
		std::lock_guard<std::mutex> lock(syncdata.clientmtx);
		syncdata.ready = true;
	}
	handshake = false;
	syncdata.clientcv.notify_one();
}

nlohmann::json Websocket::sendmsg(const nlohmann::json& message) {
	GLogger.add(debug, "Websocket sendmsg function called... Preparing Message.");
	std::unique_lock <std::mutex> lock(responsemtx);
	std::string msg = message.dump();
	GLogger.add(debug, "Message Prepared, Size: "+std::to_string(msg.size())+" bytes");
	try {
		wsClient.send(handle, msg, websocketpp::frame::opcode::text);
	}
	catch (const websocketpp::exception& e) {
		std::string errorwhat = e.what();
		GLogger.add(error, "Error sending websocket message: " + errorwhat);
		throw;
	}
	GLogger.add(debug, "Message Sent, waiting for response...");
	responsecv.wait(lock, [this] {return responseready; });
	GLogger.add(debug, "Response Caught! checking response!");
	responseready = false;
	return lastreponse;
}

void Websocket::msghandle(const std::string& reponse) {
	std::lock_guard<std::mutex>lock(responsemtx);
	try {
		lastreponse = nlohmann::json::parse(reponse);
		GLogger.add(debug, "Message obtained: " + reponse);
		if (handshake==false) {
			GLogger.add(debug, "Successfully connected to OBS Websocket, Starting handshake.");
			if (lastreponse.contains("d") && lastreponse["d"].contains("authentication")) {
				GLogger.add(debug, "OBS requires auth, making authkey for response.");
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
				GLogger.add(debug, "OBS Does not require auth, sending normal response.");
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
	GLogger.add(debug, "Handshake opcodes not found. Setting response as ready.");
	responseready = true;
	responsecv.notify_one();
}

bool Websocket::checkcon() const {
	return handshake;
}

//authkey creation
std::string Websocket::createauth(std::string& challenge, std::string& salt) {
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