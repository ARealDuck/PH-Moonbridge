#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "nlohmann/json.hpp"
#include <string>
#include <filesystem>

// Define all settings and values here globally with defaults
std::string OBSPassword;
std::string OBSPort;
std::string OBSUrl;


class settings {
public:
	settings();
	
	~settings();
private:
	bool isSettingsLoaded = false;
};

extern settings globalsettings;

#endif // !SETTINGS_HPP
