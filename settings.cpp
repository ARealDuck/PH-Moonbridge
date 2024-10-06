#include "settings.hpp"
#include <iostream>
#include <fstream>

settings::settings() {
	if (!loadfromdisk()) {
		std::cerr << "loadfromdisk failed to start";
	}
}

nlohmann::json settings::getsettings() {
	return mastersettings;
}

int settings::geteditver() {
	return editver;
}

bool settings::loadfromdisk() {
	std::ifstream settingsfile("settings.json");
	if (settingsfile.is_open()) {
		settingsfile >> mastersettings;
		settingsfile.close();
		settingsempty = true;
		return true;
	}
	else {
		defaultstemplate();
		settingsempty = false;
		return false;
	}
}

void settings::savetodisk() {
	std::ofstream settingsfile("settings.json");
	if (settingsfile.is_open()) {
		settingsfile << mastersettings.dump(4);
		settingsfile.close();
	}
	else {
		// Logger call here
	}
}

void settings::defaultstemplate() {
	// TODO: create template for defaults to fit into
	// start work on this when work on other modules starts.
}

settingsreader::settingsreader(std::string& section, settings& settingsmaster) {
	if (settingsmaster.getsettings().contains(section)) {
		settingssection = settingsmaster.getsettings()[section];
	}
	else {
	 // Logger call here
	}
	editsver = settingsmaster.geteditver();
}
