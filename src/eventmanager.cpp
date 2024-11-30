#include "eventmanager.hpp"

EventManager::EventManager(){

}

void EventManager::registerhandler(wxEvtHandler* handler) {
	mhandler = handler;
}

void EventManager::PostOutputCtrlEvent(const wxString& message) {
	if (mhandler) {
		OutputTextCtrlTextUpdateEvent event(OUTPUT_TEXT_CTRL_TEXT_UPDATE_EVENT);
		event.text = message;
		wxPostEvent(mhandler, event);
	}
}

EventManager GEventManager;
