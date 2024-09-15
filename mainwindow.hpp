#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <wx/wx.h>


class mainwindow : public wxFrame {
public:
	mainwindow(const wxString& title);

private:
	void opensettingswindow(wxCommandEvent& event);



};

#endif // !MAINWINDOW_HPP

