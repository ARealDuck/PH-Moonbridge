#include "wstunnel.h"

wsTunnel::wsTunnel() : running_(false) {
	ws_client_.init_asio(&iocontext);
}

void wsTunnel::start() {
	running_ = true;
	gthreadpool.enqueueTask([this]() {
		while (running_) {
			try {
				iocontext.run();
				iocontext.reset();
			}
			catch (const std::exception& e) {
				std::cerr << "wsTunnel error: " << e.what() << std::endl;
			}
		}

		});

	}

void wsTunnel::stop() {
	running_ = false;
	iocontext.stop();
	ws_client_.stop();
}

asio::io_context& wsTunnel::getiocontext() {
	return iocontext;
}

wsTunnel tunnel;
