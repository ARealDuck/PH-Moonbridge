#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "customevents.h"
#include "winmain.hpp"
#include <string>
#include <vector>

enum loglevel {
	info,
	warn,
	crit,
	error,
	debug,
};

class logger
{
public:
	logger();
	~logger();
	void add(loglevel level, const std::string& message);
private:
	bool debugmode = false;
	std::string message;
	std::string time();
	std::string date();
	std::string format(loglevel level, const std::string& message);
	std::vector <std::string> history;
	std::string levelstring(loglevel level);
	void save();
	void wxevent(wxEvtHandler* handler, const wxString& text);

};

extern logger globallogger;

#endif // !LOGGER_HPP
