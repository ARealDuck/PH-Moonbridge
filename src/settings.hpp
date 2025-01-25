#ifndef SETTINGS_HPP
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "main.cpp"

class settings {
public:
	settings();
	std::string grab();
	void set(std::string string_value);
	// Setting keys to be used when grabbing settings using the "grab" and "set" methods.
	enum SettingID {
		OBS_PASSWORD,
		OBS_PORT,
		OBS_URL,
		BREAK
	};

	struct SETTINGS_DEFAULT {
		std::string obs_password = "unsafepassword";
		std::string obs_port = "4455";
		std::string obs_url = "localhost:";

	};

private:
	bool check(std::vector<std::string>& keys);
	bool load();
	void apply(SettingID id, const nlohmann::json jsonfile);
	void save();
	void defaults();
	std::vector<std::string> SettingKeys = {
		"obs_password", "obs_port", "obs_url"
	};
	SETTINGS_DEFAULT dsettings;
	std::string filelocation = "settings.json";
};

#endif // !SETTINGS_HPP
