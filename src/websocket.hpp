#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <string>
#include <thread>
typedef websocketpp::client<websocketpp::config::asio_client> Client;

class obswebsocket {
public:
	obswebsocket(std::string url, std::string port, std::string password);
	~obswebsocket();
	void sendmessage(const std::string& message);

private:
	void hdlmessage(websocketpp::connection_hdl, Client::message_ptr msg);
	bool connect(std::string url, std::string port, std::string password);
	void close();
	bool connected = false;
	Client wsclient;
	websocketpp::connection_hdl clienthdl;
	std::thread clientThread;
};



#endif // !WEBSOCKET_HPP
