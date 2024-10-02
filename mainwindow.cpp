#include "mainwindow.hpp"
#include "settingswindow.hpp"

// Window creation
// All objects needed to populate this window need to be held within here.
mainwindow::mainwindow(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title) {
	wxLogDebug("mainwindow constructor called");
	wxSize fixedsize(600, 300);
	SetMinSize(fixedsize);
	SetMaxSize(fixedsize);
	SetSize(fixedsize);
	// create object instances
	wxMenuBar* menubar = new wxMenuBar;
	wxMenu* settingsmenu = new wxMenu;
	wxMenu* infomenu = new wxMenu;
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	// TextPanel Instance
	textPanel = new TextPanel(this);
	logPanel = LogPanel::getinstance(this);
	sizer->Add(textPanel, 1, wxEXPAND | wxALL, 0);
	sizer->Add(logPanel, 1, wxEXPAND | wxALL, 0);
	SetSizer(sizer);

	// setup objects
	settingsmenu->Append(11, "Program Settings");
	settingsmenu->Append(12, "OBS Control Settings");
	settingsmenu->Append(13, "Discord Webhook Settings");
	infomenu->Append(51, "Credits");
	infomenu->Append(52, "Licenses");
	infomenu->Append(53, "Check for Updates");
	menubar->Append(settingsmenu, "Settings");
	menubar->Append(infomenu, "Info");

}

void mainwindow::opensettingswindow(wxCommandEvent& event) {
	wxLogDebug("opensettingswindow called");
	settingswindow* settings_window = new settingswindow(this);
	settings_window->Show(true);
}