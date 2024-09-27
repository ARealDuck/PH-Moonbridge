#include "console_panel.hpp"

LogPanel::LogPanel(wxWindow* parent) : wxPanel(parent) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	consoletextctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 200), wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH);
	sizer->Add(consoletextctrl, 1, wxEXPAND | wxALL, 5);
	SetSizer(sizer);

}

void LogPanel::appendtext(const wxString& text) {
	consoletextctrl->AppendText(text + "\n");
	consoletextctrl->ShowPosition(consoletextctrl->GetLastPosition());
}