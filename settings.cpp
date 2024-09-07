#include "settings.hpp"
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
#include "logger.hpp"
using namespace std;

// settingsinit
settings* ::instance = nullptr;
settings* settings::settingsinit() {
	if (instance == nullptr) {
		instance = new settings();
	}
	return instance;
}

// cache
template<typename T>
T settings::cache(const string& key) {
	return settings_load.at(key).get<T>();
}

// set
template<typename T>
void settings::set(const string& key, const T& value) {
	settings_load[key] = value;
}

// constructor
settings::settings() {
	logger = logger::loggerinit();
	load();
}

// destructor
settings::~settings() {
	save();
}

// load
void settings::load() {
	ifstream settingsfile(filename);
	if (!settingsfile.is_open()) {
		logger->add(warn, "settings.json not found. reverting to defaults.");
		return;
	}
	try {
		settingsfile >> settings_load;
	}
		catch (const nlohmann::json::parse_error& e) {
			logger->add(warn, "settings.json is corrupted. reverting to defaults.");
		}
		settingsfile.close();
}

// save
void settings::save() {
	//TODO: add a check here to make sure settings file is intact. If check fails throw a warning into the logger and create a new settings file.
	ofstream settingsoutput(filename);
	if (settingsoutput.is_open()) {
		logger->add(warn, "???is this the first time you used this program??? settings.json not found. failed to save settings.");
			return;
	}
	settingsoutput << settings_load.dump(4);
	logger->add(info, "settings saved successfully.");
	settingsoutput.close();
}
