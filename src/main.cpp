#include "winmain.hpp"
#include <wx/wx.h>

class Moonbridgeapp : public wxApp {
public:
	void SetMainHandler(wxEvtHandler* handler) {}
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Moonbridgeapp);

bool Moonbridgeapp::OnInit() {
	WinMain* frame = new WinMain(nullptr);
	frame->Show(true);

	return true;
}
