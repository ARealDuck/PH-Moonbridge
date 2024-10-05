#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "nlohmann/json.hpp"
#include <string>
#include <filesystem>

class settings {
public:
	settings();

private:
	friend class settingshelper;

	void loadfromdisk();
	void savetodisk();
	nlohmann::json mastersettings;
	std::filesystem::path filename = "settings.json";
	void createfromdefaults();
};
settings globalsettings;
#define gsettings globalsettings;

class settingshelper {
protected:
	nlohmann::json* settingssection;
public: 
	settingshelper(nlohmann::json* section) : settingssection(section) {}
	virtual ~settingshelper() = default;

	virtual std::string readsetting(const std::string& key) = 0;
	virtual void writesettings(const std::string& key, const std::string& value) = 0;
};

#endif // !SETTINGS_HPP
