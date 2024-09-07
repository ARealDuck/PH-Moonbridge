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
	ifstream debugcheck("debugmode.txt");
	if (debugcheck.is_open()) {
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
void logger::add(loglevel level, const string& message) {
	if (level == debug && debugmode == true) {
		string logformatted = format(level, message);
		history.push_back(logformatted);
		return;
	}
	else if (level == debug && debugmode == false) {
		return;
	}
	else {
		string logformatted = format(level, message);
		history.push_back(logformatted);
		save();
	}
}
// save
void logger::save() {
	string filename = date() + ".txt";
	ofstream logfile(filename);
	if (logfile.is_open())
		for (const auto& item : history)
			logfile << item << endl;
	logfile.close();
	add(debug, "log file saved.");
}
// time
string logger::time() {
	auto now = chrono::system_clock::now();
	time_t ttime = chrono::system_clock::to_time_t(now);
	tm* ltime = localtime(&ttime);
	stringstream ts;
	ts << put_time(ltime, "%H:%M:%S");
	return ts.str();
}
// date
string logger::date() {
	auto now = chrono::system_clock::now();
	time_t ttime = chrono::system_clock::to_time_t(now);
	tm* ltime = localtime(&ttime);
	stringstream ts;
	ts << put_time(ltime, "%Y-%m-%d");
	return ts.str();
}
// format
string logger::format(loglevel level, const string& message) {
	string leveltag = levelstring(level);
	string logtime = time();
	ostringstream ss;
	ss << logtime << leveltag << message;
	return ss.str();
}
// levelstring
string logger::levelstring(loglevel level) {
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