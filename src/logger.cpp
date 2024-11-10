#include "logger.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>
#include <fstream>


// init
logger* logger::instance = nullptr;
logger* logger::loggerinit() {
	if (instance == nullptr) {
		instance = new logger();
	}
	return instance;
}
// contructor
logger::logger() {
	std::ifstream debugcheck("debugmode.txt");
	if (!debugcheck.is_open()) {
		add(info, "logger initialized");
		return;
	}
	else {
		debugmode& (true);
		add(debug, "logger initialized in debug mode");
	}
}
// destructor
logger::~logger() {
	add(debug, "logger module stop function called!!!");
	save();
	
}
// add
void logger::add(loglevel level, const std::string& message) {
	if (level == debug && debugmode == true) {
		std::string logformatted = format(level, message);
		history.push_back(logformatted);
		save();
		LogPanel* panel = LogPanel::getinstance();
		if (panel != nullptr) {
			panel->appendtext(logformatted);
		}
		return;
	}
	else if (level == debug && debugmode == false) {
		return;
	}
	else {
		std::string logformatted = format(level, message);
		history.push_back(logformatted);
		save();
		LogPanel* panel = LogPanel::getinstance();
		if (panel != nullptr) {
			panel->appendtext(logformatted);
		}
		return;
	}
}
// save
void logger::save() {
	std::string filename = date() + ".txt";
	std::ofstream logfile(filename);
	if (logfile.is_open())
		for (const auto& item : history)
			logfile << item << std::endl;
	logfile.close();
	add(debug, "log file saved.");
}
// time
std::string logger::time() {
	auto now = std::chrono::system_clock::now();
	time_t ttime = std::chrono::system_clock::to_time_t(now);
	tm* ltime = localtime(&ttime);
	std::stringstream ts;
	ts << std::put_time(ltime, "%H:%M:%S");
	return ts.str();
}
// date
std::string logger::date() {
	auto now = std::chrono::system_clock::now();
	time_t ttime = std::chrono::system_clock::to_time_t(now);
	tm* ltime = localtime(&ttime);
	std::stringstream ts;
	ts << std::put_time(ltime, "%Y-%m-%d");
	return ts.str();
}
// format
std::string logger::format(loglevel level, const std::string& message) {
	std::string leveltag = levelstring(level);
	std::string logtime = time();
	std::ostringstream ss;
	ss << logtime << leveltag << message;
	return ss.str();
}
// levelstring
std::string logger::levelstring(loglevel level) {
	switch (level) {
		case loglevel::info:
			return "[INFO]";
		case loglevel::warn:
			return "[WARN]";
		case loglevel::crit:
			return "[CRITICAL]";
		case loglevel::error:
			return "[ERROR]";
		case loglevel::debug:
			return "[DEBUG]";
		default:
			return "[UNKNOWN]";
	}
}
// lastlog
wxString logger::lastlog() {
	if (!logger::history.empty()) {
		wxString LastLog = history.back();
		return LastLog;
	}
	return "log is empty!!!";
}
