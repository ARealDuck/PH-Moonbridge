#ifndef SETTINGS_HPP
#define SETTINGS_HPP

// Includes
#include "nlohmann/json.hpp"
#include <string>
using namespace std;
class settings
{
public:
	// Module flags to be set for the main module
	
	// Modules dependencies 

	// init function
	static settings& settingsinit(const string& filename);

	// External module functions & containers
	template <typename T>
	T cache(const string& key);
	template <typename T>
	void set(const string& key, const T& value);

private:
	// Constructor, Destructor, and Singleton Disablers
	settings(const string& filename);
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
