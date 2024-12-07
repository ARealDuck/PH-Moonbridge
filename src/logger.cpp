#include "logger.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

void logger::add(loglevel level, const std::string& message) {
	// Check if message is Debug and Debugging is enabled
	if (level == debug && debugmode == true) {
		std::string logformatted = format(level, message);
		history.push_back(logformatted);
		save();
		GEventManager.PostOutputCtrlEvent(logformatted);
	}
	// Check if message is Debug and Debug is NOT enabled
	else if (level == debug && debugmode == false) {
		return;
	}
	// If message is not debug
	else {
		std::string logformatted = format(level, message);
		history.push_back(logformatted);
		save();
		GEventManager.PostOutputCtrlEvent(logformatted);
	}
}
logger::logger() {}

logger::~logger() {
	save();
	
}
// Start function
void logger::start() {
	if (!Started) {
		std::ifstream settingsfile("settings.json");
		if (settingsfile.is_open()) {
			nlohmann::json loadedsettings;
			settingsfile >> loadedsettings;
			settingsfile.close();
			if (loadedsettings.contains("DebugMode") && loadedsettings["DebugMode"] == "true") {
				debugmode = true;
				Started = true;
				return;
			}
		}
		else {
			debugmode = false;
			Started = true;
		}
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


logger GLogger;