#include "settings.hpp"
#include <iostream>
#include <fstream>

settings::settings() {
	std::ifstream settingsfile("settings.json");
	if (settingsfile.is_open()) {
		nlohmann::json loadedsettings;
		settingsfile >> loadedsettings;
		settingsfile.close();
		// This is a stupid awful terrible way of handling this. too bad!
		// if you add more settings to the program be sure to update this and if you dont then ill laugh at you (or my future self!)
		OBSPassword = loadedsettings["OBSPassword"];
		OBSPort = loadedsettings["OBSPort"];
		OBSUrl = loadedsettings["OBSUrl"];

		isSettingsLoaded = true;
	}
}

settings::~settings() {
	if (isSettingsLoaded) {
		nlohmann::json SettingsToSave;
		SettingsToSave["OBSPassword"] = OBSPassword;
		SettingsToSave["OBSPort"] = OBSPort;
		SettingsToSave["OBSUrl"] = OBSUrl;

		std::ofstream outputfile("settings.json");
		if (outputfile.is_open()) {
			outputfile << std::setw(4) << SettingsToSave;
			outputfile.close();
		}
	}
}

settings globalsettings;