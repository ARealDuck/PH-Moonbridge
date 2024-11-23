#ifndef LOGGER_HPP
#define LOGGER_HPP

//includes
#include <string>
#include <vector>

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

};

extern logger globallogger;

#endif // !LOGGER_HPP
