#include "settings.hpp"
#include "logger.hpp"
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
using namespace std;


// settingsinit
settings* settings::instance = nullptr;
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
		logger->add(warn, "settings.json could not be loaded. Loading settings from defaults.");
		return;
	}
	try {
		settingsfile >> settings_load;
		logger->add(info, "settings loaded successfully.");
	}
		catch (const nlohmann::json::parse_error& e) {
			logger->add(warn, "settings.json is corrupted. Loading settings from defaults.");
		}
		settingsfile.close();
}

// save
void settings::save() {
	ofstream settingsoutput(filename);
	if (settingsoutput.is_open()) {
		logger->add(warn, "settings.json could not be loaded. Loading settings from defaults.");
			return;
	}
	settingsoutput << settings_load.dump(4);
	logger->add(info, "settings saved successfully.");
	settingsoutput.close();
}
