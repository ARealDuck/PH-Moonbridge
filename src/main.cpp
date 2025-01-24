#include <wx/wx.h>
#include <ctime>
#include <chrono>
#include "winmain.hpp"
#include "logger.hpp"



class Moonbridgeapp : public wxApp {
public:
	void SetMainHandler(wxEvtHandler* handler) {}
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Moonbridgeapp);

bool Moonbridgeapp::OnInit() {
	MoonbridgeWin* frame = new MoonbridgeWin(nullptr);
	frame->Show(true);
	Logger::init;
	return true;
}



