#include "winmain.h"
#include <wx/wx.h>

class Moonbridgeapp : public wxApp {
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Moonbridgeapp);

bool Moonbridgeapp::OnInit() {
	mainwin* frame = new mainwin(nullptr);
	frame->Show(true);

	return true;
}
