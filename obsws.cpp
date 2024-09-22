#include "obsws.hpp"
#include "settings.hpp"
#include "logger.hpp"
#include <iostream>
#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

std::mutex mtx;
std::condition_variable cv;

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
	logger->add(info, "starting OBSWS module.");
	// TODO: seperate this to the taskscheduler/multithreader module if possible and needed.
	std::thread(&obsws::processmsg, this).detach();
	logger->add(debug, "started message queue thread.");
	c.init_asio();
	c.set_message_handler([this](websocketpp::connection_hdl hdl, client::message_ptr msg) {
		this->on_message(hdl, msg);
		});
	
	logger->add(debug, "OBSWS Module constructed, starting payload...");
	startws();
}
// destructor
obsws::~obsws() {
	{
		std::lock_guard<std::mutex> lock(queuemutex);
		stopprocessing = true;
	}
	queuecv.notify_all();
	logger->add(debug, "Message queue thread stopped.");
	stopws();
}

// Handler for reciving messages from OBS Websocket
void obsws::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
	std::string payload = msg->get_payload();
	json jsonmsg = json::parse(payload);
	int opcode = jsonmsg.value("op", -1);
	if (opcode == 0 || 2) {
		pl_handshake(opcode, jsonmsg);
	}
	//else if (opcode == 5) {
		// TODO: setup an eventlistener function
		//pl_event(opcode, jsonmsg);
	}
	//else if (opcode == 7 || 9) {
		// TODO: setup an requestlistener function
		//pl_requestresponse(opcode, jsonmsg);
//}

// Starts Websocket client to connect to OBS websocket with
void obsws::startws() {
	logger->add(info, "Connecting to OBS-WebSocket...");
		std::string port = settings->cache<std::string>("port");
		std::string wsurl = "ws://localhost:" + port;
		websocketpp::lib::error_code ec;
		con = c.get_connection(wsurl, ec);
		if (ec) {
			logger->add(error, "could not establish connection: " + ec.message());
			return;

		}
		c.connect(con);
		// starts io loop on seperate thread
		// TODO: seperate thread call to the taskscheduler/multithreader module if possible and needed.
		eventloopthread = std::thread([this]() {
			c.run();
			});
}

// Closes Websocket Client
void obsws::stopws() {
	c.stop();
	if (eventloopthread.joinable()) {
		eventloopthread.join();
	}
	logger->add(debug, "OBS Websocket client closed.");
}

// Queues messages to be sent to the OBS websocket server.
void obsws::sendmsg(const json& jsonmessage) {
	std::lock_guard<std::mutex> lock(queuemutex);
	messagequeue.push(jsonmessage);
	queuecv.notify_one();
	logger->add(debug, "request successfully added to queue");
}

// Sends messages to the OBS websocket server
void obsws::processmsg() {
	while (true) {
		json jsonmessage;
		{
			// Keeps thread alive until program lifecycle ends.
			std::unique_lock<std::mutex> lock(queuemutex);
			queuecv.wait(lock, [this] { return !messagequeue.empty() || stopprocessing; });

			if (stopprocessing && messagequeue.empty()) {
				break;
			}

			jsonmessage = messagequeue.front();
			messagequeue.pop();
		}
		std::string message = jsonmessage.dump();
		std::unique_lock<std::mutex> lock(mtx);
		// If no requests in progress and handshake protocol is complete.
		if (!reqinprogress && handshake) {
			if (con) {
				c.send(con->get_handle(), message, websocketpp::frame::opcode::text);
				logger->add(debug, "OBSWS request sent.");
			}
		}
		// If handshake protocol is incomplete.
		else if (!handshake) {
			int opcode = jsonmessage.value("op", -1);
			if (opcode == 1) {
				logger->add(info, "Successfully connected to OBS Websocket!");
				if (con) {
					c.send(con->get_handle(), message, websocketpp::frame::opcode::text);
					logger->add(debug, "OBSWS handshake protocol request sent.");
				}
			}
			// if the json is malformed or opcode value is missing
			else if (opcode == -1) {
				logger->add(crit, "Opcode in handshake request is missing! Please report this issue to the github repository!");
			}
			// if message is not a handshake request
			else {
				logger->add(crit, "OBSWS Attempted to send a request before the handshake protocol was finished! Please report this issue to the github repository!");
			}
		}
		// If only requests are in progress.
		else if (reqinprogress) {
				logger->add(warn, "OBSWS module is waiting on OBS to finish its last request. if this takes too long or multiple of these messages start appearing OBS may be having problems.");
					cv.wait(lock, [this] { return !reqinprogress; });
				if (con) {
					c.send(con->get_handle(), message, websocketpp::frame::opcode::text);
					reqinprogress = true;
					logger->add(debug, "OBSWS request sent.");
				}
		}
		else {
			logger->add(crit, "OBSWS module is making a request while a request is in progress and handshake is not completed! there is a very big problem here!");
		}
	}
}

// Creates OBE Websockets auth key when requrired
std::string obsws::auth(std::string& challenge, std::string& salt) {
	std::string password = settings->cache<std::string>("password");
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

// Handles any messages recieved by on_message
void obsws::pl_handshake(int opcode, const json& jsonmsg) {
	if (opcode == 0) {
		json payload;
		payload["op"] = 1;
		if (jsonmsg["d"].contains("authentication")); {
			std::string challenge = jsonmsg["d"]["authentication"]["challenge"];
			std::string salt = jsonmsg["d"]["authentication"]["salt"];
			std::string authkey = auth(challenge, salt);
			payload["d"] = {
				{"rpcVersion", 1},
				{"authentication", authkey},
				{"eventSubscriptions", 33}
			};
			std::cout << "salt = " << salt << std::endl;
			std::cout << "challenge = " << challenge << std::endl;
			sendmsg(payload);
			return;
		}
			payload["d"] = {
				{"rpcVersion", 1},
				{"eventSubscriptions",33 }
			};
			sendmsg(payload);
			return;
	}
	else if (opcode == 2) {
		handshake = true;
		wxCommandEvent event(wxEVT_OBS_CONNECTED);
		event.SetString("");
		wxQueueEvent(handler, event.Clone());
		return;
	}
}
// flags
