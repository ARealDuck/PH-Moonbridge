#ifndef WINMAIN_HPP
#define WINMAIN_HPP

#include "winmainbase.h"
#include "customevents.h"

class WinMain : public WinMainBase {
public:
	WinMain(wxWindow* parent);

	// Define custom event functions here.
	void OutputTextCtrlTextUpdate(OutputTextCtrlTextUpdateEvent& event);

private:
	wxDECLARE_EVENT_TABLE();
};



#endif // !WINMAIN_HPP
