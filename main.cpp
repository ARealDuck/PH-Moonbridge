// main.cpp is the main runtime file in the project
// TODO: Work and finish all modules
// Includes
// Modules
#include "logger.hpp"
#include "settings.hpp"
#include "obsws.hpp"
#include "mainwindow.hpp"
#include <wx/wx.h>

class moonbridgeapp : public wxApp {
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(moonbridgeapp);

bool moonbridgeapp::OnInit() {

	//create and show the main window
	mainwindow* mainWindow = new mainwindow("PH-MoonBridge v1.0");
	mainWindow->Show(true);

	//initialization function for the program
	logger* logger = logger::loggerinit();
	settings* settings = settings::settingsinit();
	obsws* obsws = obsws::obswsinit();

	return true;
}
