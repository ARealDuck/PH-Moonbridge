#ifndef OBSWS_HPP
#define OBSWS_HPP

// includes
#include <string>
#include "settings.hpp"
#include "nlohmann/json.hpp"
// shorteners
using namespace std;

class obsws
{
public:
	// Module Flags

	// Init Function
	static obsws* obswsinit();
	// Module Pointer
	static obsws* instance;
	// External module functions & containers
	void request();
private:
	// Module Dependencies
	settings* settings;
	// Constructor, Destructor, and Singleton Disablers
	obsws();
	~obsws();
	obsws(const obsws&) = delete;
	obsws& operator=(const obsws&) = delete;
	// Internal module functions & containers
	string auth(string& challenge, string& salt);
	void connect();
	void disconnect();
	
};

#endif // !OBSWS_HPP