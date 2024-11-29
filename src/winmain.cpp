#include "winmain.hpp"

MoonbridgeWin::MoonbridgeWin(wxWindow* parent) : WinMainBase(parent) {
	Bind(OUTPUT_TEXT_CTRL_TEXT_UPDATE_EVENT, &MoonbridgeWin::OutputTextCtrlTextUpdate, this);
}

// Updates the OutputTextCtrl with the sent text on a new line effectively creating a "console" box
void MoonbridgeWin::OutputTextCtrlTextUpdate(OutputTextCtrlTextUpdateEvent& event) {
	wxString CurrentText = OutputTextCtrl->GetValue();
	if (!CurrentText.IsEmpty()) {
		CurrentText += "/n";
	}
	CurrentText += event.text;
	OutputTextCtrl->SetValue(CurrentText);
	OutputTextCtrl->SetInsertionPointEnd();
}