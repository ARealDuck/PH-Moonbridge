#include "logger.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>
#include <fstream>


// init
logger* logger::loggerinit() {
	if (instance == nullptr) {
		instance = new logger();
	}
	return instance;
}
// contructor
logger::logger() {
	add(info, "logger initialized");
}
// destructor
logger::~logger() {
	save();
}
// add
void logger::add(loglevel level, const string& message) {
	string leveltag = levelstring(level);
}
// save
void logger::save() {
	string filename = date() + ".txt";
	ofstream logfile(filename);
	if (logfile.is_open())
		for (const auto& item : history)
			logfile << item << endl;
	logfile.close();
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
		default:
			return "[UNKNOWN]";
	}
}