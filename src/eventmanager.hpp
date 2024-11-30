#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
//Includes
#include <wx/wx.h>
#include "customevents.h"

class EventManager {
public:
	EventManager();
	void registerhandler(wxEvtHandler* handler);
	void PostOutputCtrlEvent(const wxString& message);
private:
	wxEvtHandler* mhandler = nullptr;
};
extern EventManager GEventManager;
#endif // !EVENTMANAGER_HPP