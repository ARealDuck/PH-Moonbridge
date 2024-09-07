#ifndef IMGRECOG_HPP
#define IMGRECOG_HPP

// includes
#include "settings.hpp"
#include "logger.hpp"
#include "obsws.hpp"

// shortneners
using namespace std;

class imgrecog {

public:
// module flags

// init function
	static imgrecog* imgrecoginit();

// modulepointer
	static imgrecog* instance;

// External module functions & containers

private:
// Module Dependencies
// settings, logger, and obsws

// Constructor, Destructor, and Singleton Disablers
	imgrecog();
	~imgrecog();
	imgrecog(const imgrecog&) = delete;
	imgrecog& operator=(const imgrecog&) = delete;
// Internal module functions & containers
	//NEEDS WORK 
};

#endif // !IMGRECOG_HPP
