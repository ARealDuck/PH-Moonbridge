#include "taskscheduler.h"
#include <chrono>

// Constructor
TaskScheduler::TaskScheduler(int threadcount) : threadcount_(threadcount) {
	taskqueues.resize(threadcount);
}

// Destructor, finishes current ongoing tasks, and ensure all threads are properly joined before exiting.
TaskScheduler::~TaskScheduler() {
	// TODO: implement this block of code
}

// adds tasks to the task queue

void TaskScheduler::addtask(std::function<void()> task, int threadID, int flags = functionflags::NONE, int forcedthreadID = -1) {
	std::lock_guard<std::mutex> lock(mtx);
	taskqueues[threadID].push({ task,flags,forcedthreadID });
	cv.notify_all();
}

void TaskScheduler::threadworker(int threadID) {
	while (true) { 
		std::unique_lock<std::mutex> lock(mtx);
		// waits for task to be available to be worked on.
		cv.wait(lock, [&]() {return !taskqueues[threadID].empty(); });

		auto task = taskqueues[threadID].front();
		taskqueues[threadID].pop();
		lock.unlock();
		}
	}
}