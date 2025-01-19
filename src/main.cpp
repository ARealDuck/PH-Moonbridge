#include <wx/wx.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <ctime>
#include <chrono>
#include "winmain.hpp"

std::string getcurrenttime() {
	auto now = std::chrono::system_clock::now();
	std::time_t CurrentTime = std::chrono::system_clock::to_time_t(now);
	return std::ctime(&CurrentTime);
}

class Moonbridgeapp : public wxApp {
public:
	void SetMainHandler(wxEvtHandler* handler) {}
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Moonbridgeapp);

bool Moonbridgeapp::OnInit() {
	MoonbridgeWin* frame = new MoonbridgeWin(nullptr);
	frame->Show(true);
	auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("Async Logger", "LogFile " + getcurrenttime()+".txt");
	return true;
}



