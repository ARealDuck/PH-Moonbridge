#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "nlohmann/json.hpp"
#include <string>
#include <filesystem>

// Define all settings and values here globally with defaults
// This is not a good way of doing this and in reality it should be encapsulated within the settings class itself but im lazy and want to get this over with.
// yes this will eventually cause a race condition but honestly the potential case for that happening is so slim its not worth writing the extra code to fix it.
namespace settingsvar {
	extern std::string OBSPassword;
	extern std::string OBSPort;
	extern std::string OBSUrl;
}

class settings {
public:
	settings();
	~settings();
	void reloadsettings();

private:
	void loadsettings();
	bool isSettingsLoaded = false;
};

extern settings globalsettings;

#endif // !SETTINGS_HPP
