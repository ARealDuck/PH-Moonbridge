#ifndef OBSWS_HPP
#define OBSWS_HPP

// includes
#include <string>
#include "settings.hpp"
#include "logger.hpp"
#include "nlohmann/json.hpp"
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unordered_map>
#include <functional>
// shorteners
using namespace std;


class obsws
{
public:
	// Module Flags
	bool connected = false;
	// Init Function
	static obsws* obswsinit();
	// Module Pointer
	static obsws* instance;
	// External module functions & containers
	void sendmsg();
private:
	// internal flags
	typedef websocketpp::client<websocketpp::config::asio_client> client;
	websocketpp::client<websocketpp::config::asio_client>::connection_ptr con;
	client c;
	std::mutex mtx;
	std::condition_variable cv;
	bool connected = false;
	std::thread eventloopthread;
	unordered_map<int, opcodehandler> handlers;
	// Module Dependencies
	settings* settings;
	logger* logger;
	// Constructor, Destructor, and Singleton Disablers
	obsws();
	~obsws();
	obsws(const obsws&) = delete;
	obsws& operator=(const obsws&) = delete;
	// Internal module functions & containers
	string auth(string& challenge, string& salt);
	void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
	void startws();
	void stopws();
	void msghndlr(int opcode, const json& jsonmsg);

	
};

#endif // !OBSWS_HPP