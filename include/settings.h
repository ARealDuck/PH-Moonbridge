#ifndef SETTINGS_H
#define SETTINGS_H

class settings
{
private:
// constructor to init settings
settings();
// Load all settings from the designated json file
// On failure, throws a WARN level message to the logger and create a new json settings file from the defaults
static void loadallsettings() {

}

static void saveallsettings() {

}

public:
// settings contructor
static settings settingsinit();
};
static settings getsetting() {

}
static settings savesetting() {

}
static settings loadsetting() {

}

#endif