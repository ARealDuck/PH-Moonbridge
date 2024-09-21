#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>
#include "obsws.hpp"


class mainwindow : public wxFrame {
public:
	mainwindow(const wxString& title);

private:
	void opensettingswindow(wxCommandEvent& event);
	void onobsconnect(wxCommandEvent& event);

	};

#endif // !MAINWINDOW_HPP

