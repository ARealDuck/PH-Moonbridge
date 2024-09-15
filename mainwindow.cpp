#include "mainwindow.hpp"

// Window creation
// All objects needed to populate this window need to be held within here.
mainwindow::mainwindow(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title) {
	wxLogDebug("mainwindow constructor called");
	// create object instances
	wxMenuBar* menubar = new wxMenuBar;
	wxMenu* menu_settings = new wxMenu;
	
	// setup objects
	menu_settings->Append(1, "Settings");
	menu_settings->AppendSeparator();
	menu_settings->Append(wxID_EXIT);
	menubar->Append(menu_settings, "Settings");

	SetMenuBar(menubar);

	Bind(wxEVT_MENU, &mainwindow::opensettingswindow, this, 1);
}

void mainwindow::opensettingswindow(wxCommandEvent& event) {
	wxLogDebug("opensettingswindow called");
	wxFrame* settings_window = new wxFrame(this, wxID_ANY, "MoonBridge Settings");
	settings_window->Show(true);
}