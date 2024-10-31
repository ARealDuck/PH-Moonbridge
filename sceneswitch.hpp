#ifndef SCENESWITCH_HPP
#define SCENESWITCH_HPP

#include "wsclient.h"
#include "threadpool.h"
#include "imageprocessor.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <chrono>

class sceneswitcher {
public:
	sceneswitcher();

	void start();

	void stop();
private:

	bool pollingactive = false;
	std::unique_ptr <wsClient> datastream;
	std::unique_ptr <wsClient> obscontroller;
	std::string gamesource;
	std::unordered_map <std::string, std::string> scenemap;

	void faaframe();
	void switchscenes(std::string& scenename);

};

extern sceneswitcher obssceneswitch;

#endif // !SCENESWITCH_HPP
