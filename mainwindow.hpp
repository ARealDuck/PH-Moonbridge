#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>
#include "text_panel.hpp"
#include "console_panel.hpp"
#include "obsws.hpp"


class mainwindow : public wxFrame {
public:
	mainwindow(const wxString& title);

private:
	TextPanel* textPanel;
	LogPanel* logPanel;
	void opensettingswindow(wxCommandEvent& event);
	void onobsconnect(wxCommandEvent& event);
	wxStaticText* obsconnect;
	wxBoxSizer* textline1;
	//wxBoxSizer* consolesizer;
	//wxBoxSizer* mwindow1;

	};

#endif // !MAINWINDOW_HPP

