#ifndef OBSPOLLING_HPP
#define OBSPOLLING_HPP

#include <condition_variable>
#include <shared_mutex>
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
	std::string getpollingdata();
	bool running = false;
private:
	clientsync syncdata;
	wsClient pollingclient;
	std::string sourcename;
	std::mutex imgdatamtx;
	std::string imagedata;
};

#endif // !OBSPOLLING_HPP
