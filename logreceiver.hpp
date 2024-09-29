#ifndef LOGRECEIVER_HPP
#define LOGRECEIVER_HPP

#include <wx/wx.h>
class LogPanel;

class logreceiver {
public:
	static logreceiver* getinstance();
	static logreceiver* createinstance();
	void addlogconsumer(LogPanel* panel);
	void addlog(const wxString& logmessage);
private:
	logreceiver() = default;
	static logreceiver* instance;
	std::vector<LogPanel*> consumers;

};
#endif // !LOGRECEIVER_HPP
