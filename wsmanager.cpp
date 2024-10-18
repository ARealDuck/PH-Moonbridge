#include "wsmanager.h"

wsManager::wsManager() : m_isrunning(false) {
	m_client.init_asio();
	m_client.set_message_handler([this](ConnectionHandle hdl, Client::message_ptr msg));
	std::lock_guard<std::mutex> lock(m_mtx);
	if (m_messageHandler) {
		m_messageHandler(msg->get_payload());
	}
}
