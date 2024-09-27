#include "text_panel.hpp"
TextPanel::TextPanel(wxWindow* parent)
	: wxPanel(parent) {
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	// Init all text widgets with defaults
	textplays = new wxStaticText(this, wxID_ANY, "Plays: 0");
	textstate = new wxStaticText(this, wxID_ANY, "Game State: init");
	textconnect = new wxStaticText(this, wxID_ANY, "OBS IS NOT CONNECTED!!!");

	// add all text widgets into ID map
	textids["textplays"] = textplays;
	textids["textstate"] = textstate;
	textids["textconnect"] = textconnect;

	// add all text widgets into panel boxsizer
	sizer->Add(textplays, 0, wxALIGN_LEFT | wxALL, 5);
	sizer->Add(textstate, 0, wxALIGN_LEFT | wxALL, 5);
	sizer->Add(textconnect, 0, wxALIGN_LEFT | wxALL, 5);

	// set sizer for the panel
	SetSizer(sizer);
}

void TextPanel::updatetext(const std::string& id, const wxString& newtext) {
	auto it = textids.find(id);
	if (it != textids.end()) {
		it->second->SetLabel(newtext);
		Layout();
	}
}