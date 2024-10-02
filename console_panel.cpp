#include "console_panel.hpp"

LogPanel* LogPanel::instance = nullptr;

LogPanel::LogPanel(wxWindow* parent) : wxPanel(parent) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	consoletextctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 200), wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH);
	sizer->Add(consoletextctrl, 1, wxEXPAND | wxALL, 5);
	SetSizer(sizer);
}

LogPanel* LogPanel::getinstance(wxWindow* parent) {
	if (instance == nullptr) {
		if (parent != nullptr) {
			instance = new LogPanel(parent);
		}
	}
	return instance;
}

void LogPanel::appendtext(const std::string& message) {
	wxString wxmsg = message;
	consoletextctrl->AppendText(wxmsg + "\n");
	consoletextctrl->ShowPosition(consoletextctrl->GetLastPosition());
}

