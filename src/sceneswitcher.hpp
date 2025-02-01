#ifndef SCENESWITCHER_HPP
#define SCENESWITCHER_HPP

#include <spdlog/spdlog.h>
#include "websocket.hpp"

class sceneswitcher {
public:
	sceneswitcher();
	~sceneswitcher();
	void start();

private:
	void stop();

	// Sceneswitcher specific settings
	std::string SCENE2WATCH;
};

#endif // !SCENESWITCHER_HPP
