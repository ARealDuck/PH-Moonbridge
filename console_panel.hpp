#ifndef CONSOLE_PANEL_HPP
#define CONSOLE_PANEL_HPP

#include <wx/wx.h>

class LogPanel : public wxPanel {
public:
	LogPanel(wxWindow* parent);
	void appendtext(const wxString& text);

private:
	wxTextCtrl* consoletextctrl;

};

#endif // !CONSOLE_PANEL_HPP
