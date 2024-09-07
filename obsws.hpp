#ifndef OBSWS_HPP
#define OBSWS_HPP

// includes
#include "settings.hpp"
#include "nlohmann/json.hpp"
// shorteners
using namespace std;

class obsws
{
public:
	// Module Flags

	// Module Dependencies
		// settings
		
	// Init Function
	static obsws* obswsinit();
	// Module Pointer
	static obsws* instance;
	// External module functions & containers
	void request();
private:
	// Constructor, Destructor, and Singleton Disablers
	obsws();
	~obsws();
	obsws(const obsws&) = delete;
	obsws& operator=(const obsws&) = delete;
	// Internal module functions & containers
	int wsconnect();
	int wsdisconnect();
};

#endif // !OBSWS_HPP