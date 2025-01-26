#include "settings.hpp"

bool settings::check(std::vector<std::string>& keys) {
    std::ifstream file(filelocation);
    if (!file.good()) {
        spdlog::warn("Settings file is not found... Creating new file.");
        return false;
    }
    nlohmann::json jsonfile;
    file >> jsonfile;
    // Validate Keys
    for (const auto& SettingKeys : keys) {
        if (!jsonfile.contains(SettingKeys)) {
            spdlog::warn("Settings file is found but is corrupted... Creating new file.");
            return false;
        }
    }
    return true;
}

bool settings::load() {
        if (check(SettingKeys)) {
        try {
            std::ifstream file(filelocation);
            nlohmann::json jsonfile;
            file >> jsonfile;
            for (int i = 0; i < BREAK; ++i) {
                apply(static_cast<SettingID>(i), jsonfile);
            }
            return true;
        }
        catch (const std::exception& e) {
            spdlog::error("ERROR: Settings File passed check but failed to apply settings to program!");
            defaults();
            exit(2);
        }
    }
}

void settings::save() {
    try {
        nlohmann::json jsonfile;
        for (int i = 0; i < BREAK; ++i) {
            SettingID id = static_cast <SettingID>(i);
            jsonfile[SettingKeys.at(id)] = 
        }
    }
}
