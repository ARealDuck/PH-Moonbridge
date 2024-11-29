#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
//Includes
#include <wx/wx.h>

class EventManager {
public:
	void registerhandler(wxEvtHandler* handler) { mhandler = handler;  }
	void PostOutputCtrlEvent(const wxString& message);
};
#endif // !EVENTMANAGER_HPP



