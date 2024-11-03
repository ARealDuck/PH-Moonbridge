#ifndef OBSPOLLING_HPP
#define OBSPOLLING_HPP

#include <condition_variable>
#include <string>
#include "clientsync.hpp"
#include "wsclient.h"
#include "threadpool.h"

extern obspolling obspoll;

class obspolling {
public:
	obspolling();
	void startpolling();
	std::string getimagedata();
	
private:
	clientsync syncdata;
	wsClient pollingclient;
	std::string sourcename;
	bool running = false;
	std::string imagedata;
	std::mutex imgdatamtx;

};

#endif // !OBSPOLLING_HPP
