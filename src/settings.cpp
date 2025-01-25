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
    return false;
}
