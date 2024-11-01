#include "sceneswitch.hpp"

sceneswitcher::sceneswitcher() {


}

void sceneswitcher::start() {
	datastream = std::make_unique<wsClient>();
	obscontroller = std::make_unique<wsClient>();
	datastream->connect();
	obscontroller->connect();
	pollingactive = true;
	gthreadpool.enqueueTask([this]() {	
		while (pollingactive) {
			faaframe();

			}
		});

	
}

void sceneswitcher::faaframe() {

}
