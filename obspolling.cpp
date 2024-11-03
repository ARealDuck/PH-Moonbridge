#include "obspolling.hpp"

obspolling::obspolling() {}

void obspolling::startpolling() {
	gthreadpool.enqueueTask([this] {	
		pollingclient.connect(syncdata);

		running = true;
		pollingclient
	});

}

obspolling obspoll
