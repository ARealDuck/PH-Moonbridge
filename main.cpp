// main.cpp is the main runtime file in the project
// TODO: Work and finish all modules
// Includes
#include <vector>
// Modules
#include "logger.hpp"
#include "settings.hpp"

using namespace std;
// TODO: add a function to find this file inside of the settings module
// for now its okay being a hardcoded location.
string filename = "settings.json";

void static runtimeinit() {

	settings& settings = settings::settingsinit(filename);
	logger* logger = logger::loggerinit();

}