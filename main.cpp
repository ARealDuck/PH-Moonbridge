// main.cpp is the main runtime file in the project
// TODO: Work and finish all modules
// Includes
#include <vector>
// Modules
#include "logger.h"
#include "settings.h"

using namespace std;

void runtimeinit() {
	settings* settings = settings::settingsinit("settings.json");
}