#ifndef SETTINGS_HPP
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "main.cpp"

class settings {
public:
	settings();
	std::string grab(SettingID id);
	void set(std::string string_value);
	bool load();
	void save();
	// Setting keys to be used when grabbing settings using the "grab" and "set" methods.
	enum SettingID {
		OBS_PASSWORD,
		OBS_PORT,
		OBS_URL,
		BREAK
	};


private:
	bool check(std::vector<std::string>& keys);
	void apply(SettingID id, const nlohmann::json jsonfile);
	void defaults();
	std::string idtostring(SettingID id) const {
		return grab(id)
	}
	std::vector<std::string> SettingKeys = {
		"obs_password", "obs_port", "obs_url"
	};
	struct SETTINGS_DEFAULT {
		std::string obs_password = "unsafepassword";
		std::string obs_port = "4455";
		std::string obs_url = "localhost:";

	};
	SETTINGS_DEFAULT dsettings;
	std::string filelocation = "settings.json";
};

#endif // !SETTINGS_HPP
