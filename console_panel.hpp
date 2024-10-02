#ifndef CONSOLE_PANEL_HPP
#define CONSOLE_PANEL_HPP

#include <wx/wx.h>

class LogPanel : public wxPanel {
public:
	static LogPanel* getinstance(wxWindow* parent = nullptr);
	void appendtext(const std::string& message);

private:
	LogPanel(wxWindow* parent);
	wxTextCtrl* consoletextctrl;
	static LogPanel* instance;
};

#endif // !CONSOLE_PANEL_HPP
