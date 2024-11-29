#include <wx/wx.h>
#include "winmain.hpp"

class Moonbridgeapp : public wxApp {
public:
	void SetMainHandler(wxEvtHandler* handler) {}
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Moonbridgeapp);

bool Moonbridgeapp::OnInit() {
	MoonbridgeWin *frame = new MoonbridgeWin(nullptr);
	frame->Show(true);
	return true;
}
