#ifndef LOGGER_HPP
#define LOGGER_HPP

//includes
#include <string>
#include <vector>

using namespace std;
// enum declared before class declatation
enum loglevel {
	info,
	warn,
	crit,
	error,
};

class logger
{
public:
	// Module Flags to be set

	// Module Dependencies

	// Init function
	static logger* loggerinit();

	// Module Pointer
	static logger* instance;

	// External module functions & containers
	void add(loglevel level, const string& message);

private:
	// Constructor, Destructor, and Singleton Disablers
	logger();
	~logger();
	logger(const logger&) = delete;
	logger& operator=(const logger&) = delete;
	// Internal module functions & containers
	string message;
	string time();
	string date();
	string format(loglevel level, const string& message);
	vector <string> history;
	string levelstring(loglevel level);
	void save();

};

#endif // !LOGGER_HPP
