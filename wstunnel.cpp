#include "wstunnel.h"

wsTunnel::wsTunnel() : running_(false) {}

void wsTunnel::start() {
	running_ = true;
	gthreadpool.enqueueTask([this]() {
		while (running_) {
			try {
				ws_client_.run();

			}
			catch (const std::exception& e) {
				std::cerr << "wsTunnel error: " << e.what() << std::endl;
			}
		}

		});

	}

void wsTunnel::stop() {
	running_ = false;
	ws_client_.stop();
}

std::shared_ptr<client>get_client() {
	return std::make_shared<client>(ws_client_);
}

