#ifndef WINMAIN_HPP
#define WINMAIN_HPP

#include "winmainbase.h"
#include "customevents.h"

class MoonbridgeWin : public WinMainBase {
public:
	MoonbridgeWin(wxWindow* parent);

	// Define custom event functions here.
	void OutputTextCtrlTextUpdate(OutputTextCtrlTextUpdateEvent& event);

private:
};



#endif // !WINMAIN_HPP
