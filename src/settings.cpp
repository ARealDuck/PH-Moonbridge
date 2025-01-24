#include "settings.hpp"

bool settings::load() {
    try {
        std::ifstream settingsload(filelocation);
        // Validate File
        if (!settingsload.is_open()) {
            spdlog::warn("No settings file found, Creating a new file with defaults...");
            defaults();
        }
        nlohmann::json settingsjson;
        settingsload >> settingsjson;
        // Validate Settings
        for (int i = 0; i < COUNT; ++i) {
            SettingID id = static_cast<SettingID>(i);

        }
    }
    return false;
}

void settings::apply(SettingID id, const nlohmann::json jsonfile) {
    try {
        switch (id) {
            case OBS_PASSWORD
                
        }
    }
}
