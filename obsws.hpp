#ifndef OBSWS_HPP
#define OBSWS_HPP

// includes (holy shit this got huge LMAO)
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
#include <queue>
#include <wx/wx.h>
// shorteners
using json = nlohmann::json;

//wxWidgets events declaration
wxDEFINE_EVENT(wxEVT_OBS_CONNECTED, wxCommandEvent);

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
	void sendmsg(const json& jsonmessage);
private:
	// internal flags
	typedef websocketpp::client<websocketpp::config::asio_client> client;
	websocketpp::client<websocketpp::config::asio_client>::connection_ptr con;
	client c;
	std::mutex mtx;
	std::condition_variable cv;
	std::thread eventloopthread;
	bool reqinprogress = false;
	bool handshake = false;
	// Module Dependencies
	settings* settings;
	logger* logger;
	// Constructor, Destructor, and Singleton Disablers
	obsws();
	~obsws();
	obsws(const obsws&) = delete;
	obsws& operator=(const obsws&) = delete;
	// Internal module functions & containers
	std::string auth(std::string& challenge, std::string& salt);
	void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
	void startws();
	void stopws();
	void pl_handshake(int opcode, const json& jsonmsg);
	void processmsg();
	std::queue<json> messagequeue;
	std::mutex queuemutex;
	std::condition_variable queuecv;
	bool stopprocessing = false;
	wxEvtHandler* handler;
};

#endif // !OBSWS_HPP