#include "settings.hpp"
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
using namespace std;

// settingsinit
settings& settings::settingsinit(const string& filename) {
	static settings instance(filename);
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
settings::settings(const string& filename) : filename(filename) {
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
		cerr << "Failed to open settings.json" << endl;
		return;
	}
	try {
		settingsfile >> settings_load;
	}
		catch (const nlohmann::json::parse_error& e) {
			cerr << "Error parsing settings file: " << e.what() << endl;
		}
		settingsfile.close();
}

// save
void settings::save() {
	ofstream settingsoutput(filename);
	if (settingsoutput.is_open()) {
		cerr << "Failed to open settings.json" << endl;
			return;
	}
	settingsoutput << settings_load.dump(4);
	settingsoutput.close();
}
