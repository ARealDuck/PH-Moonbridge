#include "logger.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>
#include <fstream>

void logger::add(loglevel level, const std::string& message) {
}
logger::logger() {
	std::ifstream debugcheck("debugmode.txt");
	if (!debugcheck.is_open()) {
		return;
	}
	else {
		debugmode& (true);
		add(debug, "Moonbridge started in debug mode.");
	}
}
logger::~logger() {
	add(debug, "logger module stop function called!!!");
	save();
	
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


logger globallogger;