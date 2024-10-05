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
	loadfromdisk();
}

// destructor
settings::~settings() {
	savetodisk();
}

// load
void settings::loadfromdisk() {
	std::ifstream sfile(filename);
	if (!sfile.is_open()) {
		std::cout << "json not loaded" << std::endl;
		logger->add(warn, "settings.json not found. reverting to defaults.");
		createfromdefaults();
		return;
	}
	try {
		mastersettings = nlohmann::json::parse(sfile);
		std::cout << "Loaded JSON: " << mastersettings.dump(4) << std::endl;
	}
		catch (const nlohmann::json::parse_error& e) {
			logger->add(warn, "settings.json is corrupted. reverting to defaults.");
			createfromdefaults();
			return;
		}
		sfile.close();
}

// save
void settings::savetodisk() {
	//TODO: add a check here to make sure settings file is intact. If check fails throw a warning into the logger and create a new settings file.
	std::ofstream settingsoutput(filename);
	if (!settingsoutput.is_open()) {
		logger->add(warn, "???is this the first time you used this program??? settings.json not found. failed to save settings.");
			return;
	}
	settingsoutput << mastersettings.dump(4);
	logger->add(info, "settings saved successfully.");
	settingsoutput.close();
}

// creates a json object from the defaults
// if a setting is needed to be set for a feature please set a default here.
void settings::createfromdefaults() {
	nlohmann::json newsettings;
	newsettings["port"] = "4455";
	newsettings["password"] = "********";

	//save function for settings
	std::ofstream newsettingsout(filename);
	if (!newsettingsout.is_open()) {
		logger->add(debug, "No settings.json found when setting defaults. creating new json.");
		newsettingsout << newsettings.dump(4);
		logger->add(debug, "New settings file created.");
		newsettingsout.close();
		loadfromdisk();
		return;
	}
	logger->add(debug, "settings.json found. setting defaults inside current settings.json");
	newsettingsout << newsettings.dump(4);
	logger->add(debug, "settings.json updated.");
	newsettingsout.close();
	loadfromdisk();
	return;
}
