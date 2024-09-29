#include "logreceiver.hpp"
logreceiver* logreceiver::instance = nullptr;

logreceiver* logreceiver::createinstance() {
	if (!instance) {
		instance = new logreceiver();
	}
	return instance;
}

logreceiver* logreceiver::getinstance() {
	return instance;
}

void logreceiver::addlogconsumer(LogPanel* panel) {
	consumers.push_back(panel);
}

void logreceiver::addlog(const wxString& logmessage) {
	for (LogPanel* consumer : consumers) {
		consumer->appendtext(logmessage)
	}
}