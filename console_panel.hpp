#ifndef CONSOLE_PANEL_HPP
#define CONSOLE_PANEL_HPP

#include <wx/wx.h>
#include "logger.hpp"

class LogPanel : public wxPanel {
public:
	LogPanel(wxWindow* parent);


private:
	void appendtext(wxCommandEvent& event);
	wxTextCtrl* consoletextctrl;
	logger* logger;
};

#endif // !CONSOLE_PANEL_HPP
