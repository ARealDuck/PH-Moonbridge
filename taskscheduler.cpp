#include "taskscheduler.h"
#include <chrono>

// Constructor
TaskScheduler::TaskScheduler(int threadcount) : threadcount_(threadcount) {
	taskqueues.resize(threadcount);
	ioloopactive.resize(threadcount, false);
}

// Destructor, finishes current ongoing tasks, and ensure all threads are properly joined before exiting.
TaskScheduler::~TaskScheduler() {
	// TODO: implement this block of code
}

// pass function or method into the task queue
void TaskScheduler::executefunc(std::function<void()> task, int threadID, int flags = functionflags::NONE) {
	std::lock_guard <std::mutex> lock(mtx);
	// check if thread is protected or IOLooped
	if (flags & functionflags::IO_LOOP) {
		ioloopactive[threadID] = true;
	}
	// if thread is locked disallow queuing of tasks in that queue
	if (!ioloopactive[threadID]) {
		taskqueues[threadID].push({ task, flags, threadID });
		cv.notify_all();
	}
}

void TaskScheduler::threadworker(int threadID) {
	while (true) {
		std::unique_lock<std::mutex> lock(mtx);
		// waits till task becomes available to be executed on the current thread
		cv.wait(lock, [&]() {return !taskqueues[threadID].empty(); });

		// if thread is not locked execute a task
		while (!taskqueues[threadID].empty()) {
			auto task = taskqueues[threadID].front();
			taskqueues[threadID].pop();
			lock.unlock();
		}
		if (task.flags & functionflags::IO_LOOP) {
			// logger debug logmessage: "starting I/O loop on thread: " + threadID
			task.func();
			ioloopactive[threadID] = true;
		}
		else {
			task.func();
		}
		lock.lock();
}

}