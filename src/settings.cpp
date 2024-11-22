#include "settings.hpp"
#include <iostream>
#include <fstream>

settings::settings() {
	loadsettings();
}

settings::~settings() {
	// this is not a good way to do this.
	// todo: dont do this, put this in a seperate function and have that function passed to the settings window handlers
	if (isSettingsLoaded) {
		nlohmann::json SettingsToSave;
		SettingsToSave["OBSPassword"] = settingsvar::OBSPassword;
		SettingsToSave["OBSPort"] = settingsvar::OBSPort;
		SettingsToSave["OBSUrl"] = settingsvar::OBSUrl;

		std::ofstream outputfile("settings.json");
		if (outputfile.is_open()) {
			outputfile << std::setw(4) << SettingsToSave;
			outputfile.close();
		}
	}
}

void settings::reloadsettings() {
	if (isSettingsLoaded) {
		isSettingsLoaded = false; 
		loadsettings();
	}
	else {
		// Logger handle here.
	}
}

void settings::loadsettings() {
	if (!isSettingsLoaded){
		std::ifstream settingsfile("settings.json");
		if (settingsfile.is_open()) {
			nlohmann::json loadedsettings;
			settingsfile >> loadedsettings;
			settingsfile.close();
			// This is a stupid awful terrible way of handling this. oh well im too lazy to figure out a better way of doing this.
			// if you add more settings to the program be sure to update this and if you dont then ill laugh at you (or my future self!)
			settingsvar::OBSPassword = loadedsettings["OBSPassword"];
			settingsvar::OBSPort = loadedsettings["OBSPort"];
			settingsvar::OBSUrl = loadedsettings["OBSUrl"];
			isSettingsLoaded = true;
		}
	}
}



settings globalsettings;