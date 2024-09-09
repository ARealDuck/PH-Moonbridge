#ifndef SETTINGS_HPP
#define SETTINGS_HPP

// Includes
#include "nlohmann/json.hpp"
#include <string>
#include <filesystem>
// dependencies
#include"logger.hpp"
class settings
{
public:
	// Module flags to be set for the main module
	
	// init function
	static settings* settingsinit();

	// External module functions & containers
	template<typename T>
	T cache(const std::string& key) const {
			return settings_load.at(key).get<T>();
	}
	template<typename T>
	void set(const std::string& key, const T& value) {
		settings_load[key] = value;
	}

private:
	// Module dependencies
	logger* logger;
	// Constructor, Destructor, and Singleton Disablers
	settings();
	~settings();
	settings(const settings&) = delete;
	settings& operator=(const settings&) = delete;

	// Internal module functions & containers
	void load();
	void save();
	nlohmann::json settings_load;
	std::filesystem::path filename = "settings.json";
};

#endif // !SETTINGS_HPP
