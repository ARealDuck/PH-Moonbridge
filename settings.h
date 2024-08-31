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
    void loadsettings();
    static void defaultsettings();
    string filename;
    json settingsdata;
    //mutable shared_mutex settingsMutex;

    // settings constructor
    // see settingsinit for description.
    settings(const string& filename);
    ~settings();
    settings(const settings&) = delete;
        settings& operator=(const settings&) = delete;

public:
    //Interface
    static settings& getInstance(const string& filename = "settings.json")
        //publicly declared methods
        //descriptions are found in the source file.
        template<typename T>
    t getsetting(const string& identifier);
    void savesettings();

    // settings contructor init method
    // used to load the settings object and calls loadallsettings to load the settings.json file into memory.
    static settings settingsinit(){

    }

};
#endif