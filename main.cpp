// main.cpp is the main runtime file in the project
// TODO: Work and finish all modules
// Includes
// Modules
#include "logger.hpp"
#include "settings.hpp"
#include "obsws.hpp"

using namespace std;


void static runtimeinit() {
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
	logger* logger = logger::loggerinit();
	settings* settings = settings::settingsinit();
	obsws* obsws = obsws::obswsinit();
}

int main() {
	runtimeinit();
}