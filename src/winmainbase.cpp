///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "winmainbase.h"

///////////////////////////////////////////////////////////////////////////

WinMainBase::WinMainBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );

	m_menubar1 = new wxMenuBar( 0 );
	mainmenusettings = new wxMenu();
	wxMenuItem* settingsprgmsettings;
	settingsprgmsettings = new wxMenuItem( mainmenusettings, wxID_ANY, wxString( _("Program Settings") ) , wxEmptyString, wxITEM_NORMAL );
	mainmenusettings->Append( settingsprgmsettings );

	wxMenuItem* settingsobssettings;
	settingsobssettings = new wxMenuItem( mainmenusettings, wxID_ANY, wxString( _("OBS Settings") ) , wxEmptyString, wxITEM_NORMAL );
	mainmenusettings->Append( settingsobssettings );

	wxMenuItem* SettingsDiscordWebhookSettings;
	SettingsDiscordWebhookSettings = new wxMenuItem( mainmenusettings, wxID_ANY, wxString( _("Discord Webhook Settings") ) , wxEmptyString, wxITEM_NORMAL );
	mainmenusettings->Append( SettingsDiscordWebhookSettings );
	SettingsDiscordWebhookSettings->Enable( false );

	m_menubar1->Append( mainmenusettings, _("Settings") );

	this->SetMenuBar( m_menubar1 );

	wxBoxSizer* WindowMainSizer;
	WindowMainSizer = new wxBoxSizer( wxVERTICAL );

	wxGridBagSizer* WindowMainGBSizer;
	WindowMainGBSizer = new wxGridBagSizer( 0, 0 );
	WindowMainGBSizer->SetFlexibleDirection( wxBOTH );
	WindowMainGBSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	wxStaticBoxSizer* OBSStatusSizer;
	OBSStatusSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("OBS Status:") ), wxVERTICAL );

	m_staticText5 = new wxStaticText( OBSStatusSizer->GetStaticBox(), wxID_ANY, _("Moonbridge is not connected to OBS!"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	OBSStatusSizer->Add( m_staticText5, 0, wxALL, 5 );


	WindowMainGBSizer->Add( OBSStatusSizer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxStaticBoxSizer* PlaysTextSizer;
	PlaysTextSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Plays:") ), wxVERTICAL );

	m_staticText6 = new wxStaticText( PlaysTextSizer->GetStaticBox(), wxID_ANY, _("12345678910"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	PlaysTextSizer->Add( m_staticText6, 0, wxALL, 5 );


	WindowMainGBSizer->Add( PlaysTextSizer, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxStaticBoxSizer* ConsoleSizer;
	ConsoleSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Console") ), wxVERTICAL );

	ConsoleSizer->SetMinSize( wxSize( 500,250 ) );
	OutputTextCtrl = new wxTextCtrl( ConsoleSizer->GetStaticBox(), wxID_ANY, _("Moonbridge is Starting..."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_RICH2 );
	OutputTextCtrl->Enable( false );

	ConsoleSizer->Add( OutputTextCtrl, 10, wxALL|wxEXPAND, 5 );


	WindowMainGBSizer->Add( ConsoleSizer, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );

	wxStaticBoxSizer* ScoreInfoSizer;
	ScoreInfoSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Score Info") ), wxVERTICAL );

	ScoreInfoSizer->SetMinSize( wxSize( 250,1000 ) );
	wxGridBagSizer* ScoreInfoGBSizer;
	ScoreInfoGBSizer = new wxGridBagSizer( 0, 0 );
	ScoreInfoGBSizer->SetFlexibleDirection( wxBOTH );
	ScoreInfoGBSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticBoxSizer* ScoreInfoJacketSizer;
	ScoreInfoJacketSizer = new wxStaticBoxSizer( new wxStaticBox( ScoreInfoSizer->GetStaticBox(), wxID_ANY, _("Jacket") ), wxVERTICAL );


	ScoreInfoGBSizer->Add( ScoreInfoJacketSizer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxStaticBoxSizer* ScoreInfoBestScoreSizer;
	ScoreInfoBestScoreSizer = new wxStaticBoxSizer( new wxStaticBox( ScoreInfoSizer->GetStaticBox(), wxID_ANY, _("Best Score") ), wxVERTICAL );


	ScoreInfoGBSizer->Add( ScoreInfoBestScoreSizer, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxStaticBoxSizer* ScoreInfoBestMedalSizer;
	ScoreInfoBestMedalSizer = new wxStaticBoxSizer( new wxStaticBox( ScoreInfoSizer->GetStaticBox(), wxID_ANY, _("Best Medal") ), wxVERTICAL );


	ScoreInfoGBSizer->Add( ScoreInfoBestMedalSizer, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxStaticBoxSizer* ScoreInfoScoreTitle;
	ScoreInfoScoreTitle = new wxStaticBoxSizer( new wxStaticBox( ScoreInfoSizer->GetStaticBox(), wxID_ANY, _("Title") ), wxVERTICAL );


	ScoreInfoGBSizer->Add( ScoreInfoScoreTitle, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxStaticBoxSizer* ScoreInfoScoreList;
	ScoreInfoScoreList = new wxStaticBoxSizer( new wxStaticBox( ScoreInfoSizer->GetStaticBox(), wxID_ANY, _("Previous Scores") ), wxVERTICAL );


	ScoreInfoGBSizer->Add( ScoreInfoScoreList, wxGBPosition( 0, 4 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );


	ScoreInfoSizer->Add( ScoreInfoGBSizer, 1, wxEXPAND, 5 );


	WindowMainGBSizer->Add( ScoreInfoSizer, wxGBPosition( 1, 2 ), wxGBSpan( 2, 10 ), wxEXPAND|wxSHAPED, 5 );

	wxStaticBoxSizer* OutputSizer;
	OutputSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Output") ), wxVERTICAL );


	WindowMainGBSizer->Add( OutputSizer, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );


	WindowMainSizer->Add( WindowMainGBSizer, 10, wxEXPAND, 5 );


	this->SetSizer( WindowMainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	mainmenusettings->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WinMainBase::opensettingswindow ), this, settingsprgmsettings->GetId());
}

WinMainBase::~WinMainBase()
{
}

SettingsFrame::SettingsFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxStaticBoxSizer* OBSWSSettingsSizer;
	OBSWSSettingsSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("OBS Websocket Settings") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	OBSPasswordLabel = new wxStaticText( OBSWSSettingsSizer->GetStaticBox(), wxID_ANY, _("OBS Password:"), wxDefaultPosition, wxDefaultSize, 0 );
	OBSPasswordLabel->Wrap( -1 );
	fgSizer3->Add( OBSPasswordLabel, 0, wxALIGN_LEFT|wxALL, 5 );

	OBSPasswordBox = new wxTextCtrl( OBSWSSettingsSizer->GetStaticBox(), wxID_ANY, _("Placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( OBSPasswordBox, 0, wxALIGN_LEFT|wxALL, 5 );

	OBSPortLabel = new wxStaticText( OBSWSSettingsSizer->GetStaticBox(), wxID_ANY, _("OBS Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	OBSPortLabel->Wrap( -1 );
	fgSizer3->Add( OBSPortLabel, 0, wxALL, 5 );

	OBSPortBox = new wxTextCtrl( OBSWSSettingsSizer->GetStaticBox(), wxID_ANY, _("Placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( OBSPortBox, 0, wxALL, 5 );

	OBSUrlLabel = new wxStaticText( OBSWSSettingsSizer->GetStaticBox(), wxID_ANY, _("OBS Url:"), wxDefaultPosition, wxDefaultSize, 0 );
	OBSUrlLabel->Wrap( -1 );
	fgSizer3->Add( OBSUrlLabel, 0, wxALL, 5 );

	OBSUrlBox = new wxTextCtrl( OBSWSSettingsSizer->GetStaticBox(), wxID_ANY, _("Placeholder"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( OBSUrlBox, 0, wxALL, 5 );


	OBSWSSettingsSizer->Add( fgSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( OBSWSSettingsSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

SettingsFrame::~SettingsFrame()
{
}
