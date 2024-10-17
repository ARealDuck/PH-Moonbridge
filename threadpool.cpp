#include "threadpool.h"
#include <iostream>
#include <algorithm>

threadpool::threadpool(size_t minThreads) : stop(false), minThreads(minThreads) {
	maxThreads = std::max(minThreads, static_cast<size_t>(std::thread::hardware_concurrency()));
	for (size_t i = 0; i < maxThreads; ++i) {
		threads.emplace_back(&threadpool::worker, this);
	}
	std::cout << "threadpool created with " << maxThreads << "threads." << std::endl;
}

threadpool::~threadpool() {
	stop = true;
	condition.notify_all();
	for (std::thread &thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

void threadpool::enqueueTask(std::function<void()> task) {
	{ std::lock_guard<std::mutex> lock(queuemtx); tasks.push(std::move(task)); }
	condition.notify_one();
}

void threadpool::worker() {
	while (!stop) {
		std::function<void()> task;
		{
			std::unique_lock<std::mutex> lock(queuemtx);
			condition.wait(lock[this]() { return stop || !tasks.empty(); });
			if (stop && tasks.empty())
				return;
			task = std::move(tasks.front());
			tasks.pop();
		}
		task();
	}
}



