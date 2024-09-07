#include "obsws.hpp"
#include "settings.hpp"
#include "logger.hpp"
#include <iostream>
#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

using namespace std;
using namespace CryptoPP;
using json = nlohmann::json;
// init
obsws* obsws::instance = nullptr;
obsws* obsws::obswsinit() {
	if (instance == nullptr) {
		instance = new obsws();
	}
	return instance;
}
// contructor
obsws::obsws() { 
	settings = settings::settingsinit();
	logger = logger::loggerinit();
	c.init_asio();
	c.set_message_handler([this](websocketpp::connection_hdl hdl, client::message_ptr msg) {
		this->on_message(hdl, msg);
		});
	
	logger->add(debug, "OBSws Module constructed, starting payload...");
	startws();
}
// destructor
obsws::~obsws() {
	stopws();
}

// Handler for reciving messages from OBS Websocket
void obsws::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
	string payload = msg->get_payload();
	json jsonmsg = json::parse(payload);
	if (jsonmsg.contains("op")) {
		int opcode = jsonmsg["op"];
		msghndlr(opcode, jsonmsg);
		}
	else {
		logger->add(error, "Unknown OBS Websocket OpCode:" + opcode);
	}
}

// Starts Websocket client to connect to OBS websocket with
void obsws::startws() {
	logger->add(info, "Connecting to OBS-WebSocket...");
	string wsurl = "ws://localhost:" + settings->cache<string>("port");
	websocketpp::lib::error_code ec;
	con = c.get_connection(wsurl, ec);
	if (ec) {
		logger->add(error, "could not establish connection: " + ec.message());
		return;
	}
	c.connect(con);
	//starts io loop on seperate thread
	eventloopthread = thread([this]() {
		c.run();
		});
		// waits for the response from OBS then lets the loop run
		std::unique_lock<mutex> lock(mtx);
		cv.wait(lock, [this]() { return connected; });
		logger->add(info, "Successfully connected to OBS Websocket!");
}

// Closes Websocket Client
void obsws::stopws() {
	c.stop();
	if (eventloopthread.joinable()) {
		eventloopthread.join();
	}
	logger->add(debug, "OBS Websocket client closed.");
}



// Sends messages to the OBS websocket server
void obsws::sendmsg() {

}

// Creates OBE Websockets auth key when requrired
string obsws::auth(string& challenge, string& salt) {
	string password = settings->cache<string>("password");
	stringstream passsalt;
	passsalt << password << salt;
	string input;
	passsalt.str(input);
	SHA256 hash;
	string base64secret;
	StringSource(input, true, new HashFilter(hash, new Base64Encoder(new StringSink(base64secret))));
	stringstream b64chal;
	b64chal << base64secret << challenge;
	b64chal.str(input);
	SHA256 hash;
	string digest;
	StringSource(input, true, new HashFilter(hash, new Base64Encoder(new StringSink(digest))));
	return digest;
}

// Handles any messages recieved by on_message
void obsws::msghndlr(int opcode,const json& jsonmsg) {
	if (opcode == 0) {
		opcode0(jsonmsg);
	}
	else if (opcode ==  {
	
	}
}
void opcode0(const json& msg) {

}

 // Example for return messages
json returnmsg;
returnmsg["op"] = 1;
returnmsg["d"] = {{}