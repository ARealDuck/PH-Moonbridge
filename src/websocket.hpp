#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <string>
#include <thread>
typedef websocketpp::client<websocketpp::config::asio_client> Client;


// TODO: setup settings for URL, PORT, and PASSWORD.
class obswebsocket {
public:
	//TODO handle the constructor with the ability to grab these parameters itself through the settings object.
	obswebsocket(std::string url, std::string port, std::string password);
	~obswebsocket();
	// Method to send messages through to OBS websocket.
	void sendmessage(const std::string& message);
	// TODO: handle this RIGHT AFTER the constructor gets its paramater handling
	// this way the OBS websocket server can keep itself handled after the user changes its settings.
	// void reload();
	std::string getmessage();
private:
	// Message handler for receiving messages
	void hdlmessage(websocketpp::connection_hdl, Client::message_ptr msg);
	bool connect();
	void close();
	bool connected = false;
	std::string lastmessage;
	Client wsclient;
	websocketpp::connection_hdl clienthdl;
	std::thread clientThread;
	// Websocket specific settings
	std::string OBSURL;
	std::string OBSPORT;
	std::string OBSPASSWORD;
};



#endif // !WEBSOCKET_HPP
