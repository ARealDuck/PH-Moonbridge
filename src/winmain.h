///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/textctrl.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class mainwin
///////////////////////////////////////////////////////////////////////////////
class mainwin : public wxFrame
{
	private:
		wxDECLARE_EVENT_TABLE();
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* mainmenusettings;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxTextCtrl* OutputTextCtrl;

	public:

		mainwin( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("PH_Moonbridge"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~mainwin();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SettingsFrame
///////////////////////////////////////////////////////////////////////////////
class SettingsFrame : public wxFrame
{
	private:

	protected:

	public:

		SettingsFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Moonbridge Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~SettingsFrame();

};

