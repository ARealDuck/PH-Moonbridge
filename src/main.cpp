#include <wx/wx.h>
#include "winmain.hpp"
#include "logger.hpp"
#include "threadpool.h"
#include "websocket.hpp"
#include "clientsync.hpp"

class Moonbridgeapp : public wxApp {
public:
	void SetMainHandler(wxEvtHandler* handler) {}
	virtual bool OnInit();
};

wxIMPLEMENT_APP(Moonbridgeapp);

bool Moonbridgeapp::OnInit() {
	MoonbridgeWin *frame = new MoonbridgeWin(nullptr);
	frame->Show(true);
	GLogger.start();
	clientsync clientsync;
	GLogger.add(debug, "starting websocket client");
	Websocket runtimeclient(GThreadPool.GetIOContext());
	GLogger.add(debug, "starting websocket connection...");
	runtimeclient.connect(clientsync);
	return true;
}
