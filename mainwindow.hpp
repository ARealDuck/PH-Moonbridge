#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>
#include "text_panel.hpp"
#include "obsws.hpp"


class mainwindow : public wxFrame {
public:
	mainwindow(const wxString& title);

private:
	TextPanel* textPanel;
	void opensettingswindow(wxCommandEvent& event);
	void onobsconnect(wxCommandEvent& event);
	wxStaticText* obsconnect;
	wxBoxSizer* textline1;

	};

#endif // !MAINWINDOW_HPP

