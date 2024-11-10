#pragma once
#ifndef SCENESWITCHER_HPP
#define SCENESWITCHER_HPP

#include <condition_variable>
#include <shared_mutex>
#include <string>
#include "clientsync.hpp"
#include "websocket.hpp"
#include "threadpool.h"

// part used for polling OBSWebsocket
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

extern imgprocessor imgprocess;
class imgprocessor {
public:
	imgprocessor();
	void start();
	void stop();
private:
	std::string polledimgdata

};

extern sceneswitcher sceneswitch;
class sceneswitcher {
public:

private:

};

#endif // !SCENESWITCHER_HPP
