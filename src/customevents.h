#ifndef CUSTOMEVENTS_H
#define CUSTOMEVENTS_H
#include <wx/event.h>

class OutputTextCtrlTextUpdateEvent : public wxCommandEvent {
public:
	OutputTextCtrlTextUpdateEvent(wxEventType eventType = wxEVT_NULL, int id = 0) : wxCommandEvent(eventType, id), text("") {}

	wxEvent* Clone() const override { return new OutputTextCtrlTextUpdateEvent(*this); }

	wxString text;
};

wxDECLARE_EVENT(OUTPUT_TEXT_CTRL_TEXT_UPDATE_EVENT, OutputTextCtrlTextUpdateEvent);

#endif // !CUSTOMEVENTS_H
