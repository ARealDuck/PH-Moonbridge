#ifndef SETTINGS_H
#define SETTINGS_H

#include <nlohmann/json>
#include <string>
class settings
{
public:
	std::string loadsettings(std::string& filename);
	void savesettings();
	std::string getsetting(std::string& identifier);


private:
	settings(std::string& filename) {

	}
	std::string filename;
	std::string identifier;
	nlohmann::json loadedsettings;

};

#endif // !SETTINGS_H
