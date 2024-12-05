#include "threadpool.h"

ThreadPool::~ThreadPool() {
	// Stop tasks
	work_guard.reset();
	io_context.stop();

	// Join all threads
	for (std::thread& worker : workers) {
		if (worker.joinable())
			worker.join();
	}
}

ThreadPool GThreadPool;