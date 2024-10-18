#ifndef WSMANAGER_H
#define WSMANAGER_H

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <thread>
#include <mutex>
#include <functional>

typedef websocketpp::client<websocketpp::config::asio_client> Client;
typedef websocketpp::connection_hdl ConnectionHandle;

class wsManager {
public:
	wsManager();

	void start();
	void connect();
	void sendmessage();
	void setmessagehandler();

	bool isrunning() const { return m_isrunning; }

private:
	void run();

	Client m_client;
	ConnectionHandle m_hdl;
	std::thread m_thread;
	std::mutex m_mtx;
	std::function<void(const std::string&)> m_messageHandler;
	bool m_isrunning;
	
};
#endif // !WSMANAGER_H
