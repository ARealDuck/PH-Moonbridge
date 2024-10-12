#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "nlohmann/json.hpp"
#include <string>
#include <filesystem>

class settings {
public:
	settings();
	nlohmann::json getsettings();
	int geteditver();

private:
	friend class settingsreader;
	friend class settingseditor;

	bool loadfromdisk();
	void savetodisk();
	nlohmann::json mastersettings;
	std::filesystem::path filename = "settings.json";
	void defaultstemplate();
	bool settingsempty;
	int editver = 1;
};
settings globalsettings;
#define gsettings globalsettings;

class settingsreader {

protected:
	nlohmann::json settingssection;
public: 
	settingsreader(std::string& section, settings& settingsmaster);
	~settingsreader() = default;

	std::string readsetting(const std::string& key) = 0;
private:
	int editsver;
};

class settingseditor {

protected:
	nlohmann::json settingssection;
public:
	settingseditor(std::string& section, settings& settingsmaster);
	~settingseditor() = default;

	void editsetting(std::string& key, std::string& value);
private:
	std::string sectionname;
	void applysetting();
};

#endif // !SETTINGS_HPP
