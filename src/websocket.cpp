#include "websocket.hpp"
#include "settings.hpp"
#include "logger.hpp"

#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

Websocket::Websocket(asio::io_context& io_context) : connected(false), handshake(false), responsewait(false) {
	wsClient.init_asio(&io_context);
	wsClient.start_perpetual();
	wsClient.set_message_handler([this](websocketpp::connection_hdl, Client::message_ptr msg) {
		messagesend(msg->get_payload());
		});
	wsClient.set_fail_handler([](websocketpp::connection_hdl) {
		GLogger.add(crit, "Connection Failed!");
		});
}

void Websocket::connect(clientsync& syncdata) {
	websocketpp::lib::error_code ec;
	obsurl = settingsvar::OBSUrl;
	obsport = settingsvar::OBSPort;
	obspass = settingsvar::OBSPassword;
	std::string wsurl = obsurl + obsport;
	Client::connection_ptr con = wsClient.get_connection(wsurl, ec);
	if (ec) {
		GLogger.add(info, "Client Failed to connect!");
		return;
	}
	handle = con->get_handle();
	wsClient.connect(con);
	{
		std::lock_guard<std::mutex> lock(syncdata.clientmtx);
		syncdata.ready = true;
		syncdata.clientcv.notify_one();
	}
	handshake = false;
	GLogger.add(debug, "Connection Started, awaiting handshake message...");
}

void Websocket::messagesend(const std::string& message) {
	std::unique_lock<std::mutex> lock(responsemtx);
	responsecv.wait(lock, [this]() {return !responsewait; });
	responsewait = true;
	websocketpp::lib::error_code ec;
	wsClient.send(handle, message, websocketpp::frame::opcode::text, ec);
	if (ec) {
		std::string errormsg = ec.message();
		GLogger.add(error, "Message failed to send: " + errormsg);
	}
}

void Websocket::messagehandle(const std::string& reponse) {
	std::lock_guard<std::mutex> lock(responsemtx);
	GLogger.add(debug, "recieved message: " + reponse);
	lastreponse = nlohmann::json::parse(reponse);
	responsewait = false;
	responsecv.notify_all();
	if (!handshake) {
		handshakeprotocol(reponse);
	}
}

void Websocket::onopen(websocketpp::connection_hdl hdl) {
	std::lock_guard<std::mutex> lock(connectionmtx);
	handshake = false;
	connected = true;
	connectioncv.notify_all();
}

void Websocket::onclose(websocketpp::connection_hdl hdl) {
	std::lock_guard<std::mutex> lock(connectionmtx);
	handshake = false;
	connected = false;
	connectioncv.notify_all();
}

void Websocket::closecon() {
	websocketpp::lib::error_code ec;
	wsClient.close(handle, websocketpp::close::status::normal, "Client Closed.", ec);
	if (ec) {
		std::string ercode = ec.message();
		GLogger.add(error, "Websocket ran into an error while closing connection: " + ercode);
	}
}

void Websocket::handshakeprotocol(std::string message) {
	nlohmann::json parsemsg = nlohmann::json::parse(message);
	bool authreq = false;
	if (parsemsg.contains("op") && parsemsg ["op"]==0) {
		if (parsemsg.contains("d")) {
			auto details = parsemsg["d"];
			if (details.contains("obsWebSocketVersion")) {
				std::string version = details["obsWebSocketVersion"];
				GLogger.add(debug, "obs websocket version is: " + version);
			}
			if (details.contains("authentication")) {
				GLogger.add(debug, "OBS requires authentication...");
				std::string salt = details["authentication"]["salt"];
				std::string challenge = details["authentication"]["challenge"];
				authreq = true;
			}
			else {
				GLogger.add(debug, "OBS does not require authentication...");
			}
		}
		GLogger.add(debug, "preforming handshake logic...");
		nlohmann::json identifymsg;
		identifymsg["rpcVersion"] = 1;
		identifymsg["d"] = {

		}

	}
	else {
		GLogger.add(error, "OBS send a nonhandshake message before handshake process is done, this will cause a bug!");
		throw;
	}
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