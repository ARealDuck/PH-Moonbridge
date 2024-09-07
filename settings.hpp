#ifndef SETTINGS_HPP
#define SETTINGS_HPP

// Includes
#include "nlohmann/json.hpp"
#include <string>
// Dependencies
#include "logger.hpp"
using namespace std;
// hardcoded settings path
string filename = "settings.json";

class settings
{
public:
	// Module flags to be set for the main module
	
	// Modules dependencies 
	logger* logger;
	// init function
	static settings* settingsinit();

	// module pointer
	static settings* instance;

	// External module functions & containers
	template <typename T>
	T cache(const string& key);
	template <typename T>
	void set(const string& key, const T& value);

private:
	// Constructor, Destructor, and Singleton Disablers
	settings();
	~settings();
	settings(const settings&) = delete;
	settings& operator=(const settings&) = delete;

	// Internal module functions & containers
	void load();
	void save();
	nlohmann::json settings_load;
	string filename;
};

#endif // !SETTINGS_HPP
