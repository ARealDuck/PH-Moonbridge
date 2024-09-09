#include "settings.hpp"
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
#include "logger.hpp"

// settingsinit
settings* instance = nullptr;
settings* settings::settingsinit() {
	if (instance == nullptr) {
		instance = new settings();
	}
	return instance;
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
	std::ifstream sfile(filename);
	if (!sfile.is_open()) {
		std::cout << "json not loaded" << std::endl;
		logger->add(warn, "settings.json not found. reverting to defaults.");
		//TODO create method to make a json object with default variables.
	}
	try {
		settings_load = nlohmann::json::parse(sfile);
		std::cout << "Loaded JSON: " << settings_load.dump(4) << std::endl;
	}
		catch (const nlohmann::json::parse_error& e) {
			logger->add(warn, "settings.json is corrupted. reverting to defaults.");
		}
		sfile.close();
}

// save
void settings::save() {
	//TODO: add a check here to make sure settings file is intact. If check fails throw a warning into the logger and create a new settings file.
	std::ofstream settingsoutput(filename);
	if (settingsoutput.is_open()) {
		logger->add(warn, "???is this the first time you used this program??? settings.json not found. failed to save settings.");
			return;
	}
	settingsoutput << settings_load.dump(4);
	logger->add(info, "settings saved successfully.");
	settingsoutput.close();
}
