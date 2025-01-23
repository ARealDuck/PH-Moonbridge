#include <wx/wx.h>
#include<spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <ctime>
#include <chrono>
#include "winmain.hpp"



class Moonbridgeapp : public wxApp {
public:
	void SetMainHandler(wxEvtHandler* handler) {}
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Moonbridgeapp);

bool Moonbridgeapp::OnInit() {
	MoonbridgeWin* frame = new MoonbridgeWin(nullptr);
	frame->Show(true);
	return true;
}



