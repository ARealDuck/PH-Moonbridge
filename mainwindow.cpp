#include "mainwindow.hpp"
#include "settingswindow.hpp"

// Window creation
// All objects needed to populate this window need to be held within here.
mainwindow::mainwindow(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title) {
	wxLogDebug("mainwindow constructor called");
	wxSize fixedsize(400, 300);
	SetMinSize(fixedsize);
	SetMaxSize(fixedsize);
	SetSize(fixedsize);
	// create object instances
	wxMenuBar* menubar = new wxMenuBar;
	wxMenu* settingsmenu = new wxMenu;
	wxMenu* infomenu = new wxMenu;
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxStaticText* playstext = new wxStaticText(panel, wxID_ANY, "Plays: 999999", wxPoint(10, 15), wxSize(10,60));
	wxStaticText* statustext = new wxStaticText(panel, wxID_ANY, "Status: init", wxPoint(150, 15));

	panel->Layout();
	// setup objects
	settingsmenu->Append(11, "Program Settings");
	settingsmenu->Append(12, "OBS Control Settings");
	settingsmenu->Append(13, "Discord Webhook Settings");
	infomenu->Append(51, "Credits");
	infomenu->Append(52, "Licenses");
	infomenu->Append(53, "Check for Updates");
	menubar->Append(settingsmenu, "Settings");
	menubar->Append(infomenu, "Info");

	wxFont defaultFont = playstext->GetFont();
	wxFont newFont(defaultFont.GetPointSize() + 6, defaultFont.GetFamily(), defaultFont.GetStyle(), defaultFont.GetWeight());
	playstext->SetFont(newFont);
	statustext->SetFont(newFont);
	SetMenuBar(menubar);

	Bind(wxEVT_MENU, &mainwindow::opensettingswindow, this, 11);
}

void mainwindow::opensettingswindow(wxCommandEvent& event) {
	wxLogDebug("opensettingswindow called");
	settingswindow* settings_window = new settingswindow(this);
	settings_window->Show(true);
}