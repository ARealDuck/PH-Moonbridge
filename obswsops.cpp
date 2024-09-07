#include "obswsops.hpp"
#include "obsws.hpp"

obswsops* obswsops::instance = nullptr;
obswsops* obswsops::obswsopsinit() {
	if (instance == nullptr) {
		instance = new obswsops();
	}
	return instance;
}
obswsops::obswsops() {
	obsws = obsws::obswsinit();

}
obswsops::~obswsops() {

}
void obswsops::closeobswsops() {
	obswsops::~obswsops();
}