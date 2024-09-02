#ifndef SETTINGS_H
#define SETTINGS_H

#include <nlohmann/json>
#include <string>
using namespace std;
class settings
{
public:
	// Module flags to be set for the main module
	

	// init function
	static settings& settingsinit(const string& filename = "settings.json");

	// External module functions & containers
	template <typename T>
	T cache(const string& key);
	template <typename T>
	T set(const string& key, const T& value);

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

#endif // !SETTINGS_H
