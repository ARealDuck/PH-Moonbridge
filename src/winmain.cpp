#include "winmain.hpp"

wxBEGIN_EVENT_TABLE(WinMain, WinMainBase)
	EVT_COMMAND(wxID_ANY, OUTPUT_TEXT_CTRL_TEXT_UPDATE_EVENT, WinMain::OutputTextCtrlTextUpdate)

wxEND_EVENT_TABLE()

WinMain::WinMain(wxWindow* parent) : WinMainBase(parent) {

}

void WinMain::OutputTextCtrlTextUpdate(OutputTextCtrlTextUpdateEvent& event) {


}