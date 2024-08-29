#include "settings.h"
#include "logger.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;
using json = nlohmann::json;

// Loads all of the settings from the settings.json file and dumps it into a vector to be accessed from.
// TODO: make a settingslocation function to put the settings file into a location away from the executeable file.
void settings::loadallsettings() {
	string settingloc = "settings.json";
	ifstream settingj(settingloc);
	if (!settingj.is_open()) {
		cerr << "settings.json found in: " << settingloc << " could not be found, reverting to defaults." << endl;
		defaultsettings();
	}
	json loadedsettings;
	settingj >> loadedsettings;
	settingj.close();
	if (!loadedsettings.is_string()) {
		cerr << "settings.json file is corrupted, reverting to defaults" << endl;
		return;
	}
	loaded_settings = loadedsettings.get<vector<json>>();
}

// Saves all of the currently set settings in the vector to the settings.json file allowing it to be recalled even after the program closes.
void settings::saveallsettings() {
	json jsonfile = loaded_settings;
	string settingloc = "settings.json";
		ofstream settingj(settingloc);
		if (settingj.is_open()) {
			// This function is only meant to be called after a function called loadallsettings gets loaded, which if that function executes successfully means that the settings.json file is intact and is useable. 
			// Meaning the only way that the file could ever fail to open is in the case of someone deliberately tampering with the file while the program is running
			cerr << "Are you intentionally trying to throw this message? settings.json is not found even after being loaded previously, reverting to defaults and recalling." << endl;
			defaultsettings();
			saveallsettings();
		}
		settingj << jsonfile.dump();
		settingj.close();
}

// In the case where the settings.json file has been corrupted or is missing completely from its designated spot this will create a brand new settings file set with default values.
// will not be started until a setting needs to be made, as well as this will be expanded as the program develops
//TODO: seperate this off into its own class that can be called and then set whenever it needs to be.
void settings::defaultsettings() {

}

void settings::setsetting() {

}

void settings::savesetting() {

}

void settings::loadsetting() {

}
