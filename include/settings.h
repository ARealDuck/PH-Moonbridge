#ifndef SETTINGS_H
#define SETTINGS_H
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;
class settings
{
private:
    //privately declared methods
    //descriptions are found in the source file.
    static void loadallsettings();
    static void saveallsettings();
    static void defaultsettings();
    static vector <nlohmann::json> loaded_settings;

    // settings constructor
    // see settingsinit for description.
    settings();

public:
    //publicly declared methods
    //descriptions are found in the source file.
    static void setsetting();
    static void savesetting();
    static void loadsetting();

    // settings contructor init method
    // used to load the settings object and calls loadallsettings to load the settings.json file into memory.
    static settings settingsinit(){

    }

};
#endif