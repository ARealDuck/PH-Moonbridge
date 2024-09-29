#ifndef CONSOLE_PANEL_HPP
#define CONSOLE_PANEL_HPP

#include <wx/wx.h>
#include "logreceiver.hpp"

class LogPanel : public wxPanel {
public:
	LogPanel(wxWindow* parent);


private:
	void appendtext(const wxString& message);
	wxTextCtrl* consoletextctrl;
};

#endif // !CONSOLE_PANEL_HPP
