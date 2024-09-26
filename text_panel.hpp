#ifndef TEXT_PANEL_HPP
#define TEXT_PANEL_HPP

#include <wx/wx.h>
#include <string>
#include <map>

class TextPanel : public wxPanel {
public:
	TextPanel(wxWindow* parent);
	// function to update any text within this panel
	void updatetext(const std::string& id, const wxString& newtext);

private:
	// text widget for plays
	wxStaticText* textplays;
	// text widget for game state
	wxStaticText* textstate;
	// text widget for obs connectivity
	wxStaticText* textconnect;

	// map to store text widget ID's
	std::map<std::string, wxStaticText*> textids;
};
#endif // !TEXT_PANEL_HPP
