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
	
	// Main Window code here



	return true;
}
