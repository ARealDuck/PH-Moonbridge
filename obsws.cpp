#include "obsws.hpp"
#include "settings.hpp"

// init
obsws* obsws::instance = nullptr;
obsws* obsws::obswsinit() {
	if (instance == nullptr) {
		instance = new obsws();
	}
	return instance;
}
// contructor
obsws::obsws() {
	
}
// destructor
obsws::~obsws() {

}
//
