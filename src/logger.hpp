#ifndef LOGGER_HPP
#define LOGGER_HPP

//includes
#include <string>
#include <vector>
#include "console_panel.hpp"

// enum declared before class declatation
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
	// Module Flags to be set
	bool debugmode = false;

	// Init function
	static logger* loggerinit();

	// Module Pointer
	static logger* instance;

	// External module functions & containers
	void add(loglevel level, const std::string& message);
	wxString lastlog();

private:
	// Constructor, Destructor, and Singleton Disablers
	logger();
	~logger();
	logger(const logger&) = delete;
	logger& operator=(const logger&) = delete;
	// Internal module functions & containers
	std::string message;
	std::string time();
	std::string date();
	std::string format(loglevel level, const std::string& message);
	std::vector <std::string> history;
	std::string levelstring(loglevel level);
	void save();

};

#endif // !LOGGER_HPP
