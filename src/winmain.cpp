#include "winmain.hpp"

WinMain::WinMain(wxWindow* parent) : WinMainBase(parent) {
	Bind(OUTPUT_TEXT_CTRL_TEXT_UPDATE_EVENT, &WinMain::OutputTextCtrlTextUpdate, this);
}

// Updates the OutputTextCtrl with the sent text on a new line effectively creating a "console" box
void WinMain::OutputTextCtrlTextUpdate(OutputTextCtrlTextUpdateEvent& event) {
	wxString CurrentText = OutputTextCtrl->GetValue();
	if (!CurrentText.IsEmpty()) {
		CurrentText += "/n";
	}
	CurrentText += event.text;
	OutputTextCtrl->SetValue(CurrentText);
	OutputTextCtrl->SetInsertionPointEnd();
}