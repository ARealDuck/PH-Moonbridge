#include "threadpool.h"
#include "logger.hpp"
#include <iostream>
#include <algorithm>

threadpool::threadpool(size_t minThreads) : stop(false), minThreads(minThreads) {}

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

void threadpool::start() {
	maxThreads = std::max(minThreads, static_cast<size_t>(std::thread::hardware_concurrency()));
	for (size_t i = 0; i < maxThreads; ++i) {
		threads.emplace_back(&threadpool::worker, this);
	}
	std::string logstring = "threadpool created with " + std::to_string(maxThreads) + "threads.";
	GLogger.add(info, logstring);
}


void threadpool::worker() {
	while (!stop) {
		std::function<void()> task;
		{
			std::unique_lock<std::mutex> lock(queuemtx);
			GLogger.add(info, "Worker waiting for task...");
			condition.wait(lock, [this]() {
				GLogger.add(info, "worker woke up: stop= " + std::to_string(stop) + ", task.size() = " + std::to_string(tasks.size()));
				return stop || !tasks.empty(); 
				
				}
			);

			if (stop && tasks.empty())
				GLogger.add(info, "Worker stopping: no tasks and stop requested.");
				return;
				if (!tasks.empty()) {
					try {
						GLogger.add(info, "fetching task from queue. Queue size before pop: " + std::to_string(tasks.size()));
						tasks.pop();
						GLogger.add(info, "task fetched and removed from queue. queue size after pop: " + std::to_string(tasks.size()));
					}
					catch (const std::exception& e) {
						std::string elog = e.what();
						GLogger.add(info, "Exception thrown while fetching task: " + elog);
					}
					catch (...) {
						GLogger.add(info, "Unknown Exception thrown while fetching task!");
					}
				}
				else {
					GLogger.add(warn, "Queue unexpectedly empty after waking up???");
				}
			GLogger.add(info, "Task fetched from queue.");
		}
		if (task) {
			try {
				GLogger.add(info, "executing task...");
				task();
				GLogger.add(info, "task executed successfully!");
			}
			catch(const std::exception& e) {
				std::string errormessage = e.what();
				GLogger.add(crit, "task threw exception! " + errormessage);
			}
			catch (...) {
				GLogger.add(crit, "task threw unknown exception!");
			}
		}
		else {
			GLogger.add(warn, "task is NULL. Skipping execution.");
		}
	}
	GLogger.add(info, "Worker Exiting.");
}

threadpool gthreadpool;
