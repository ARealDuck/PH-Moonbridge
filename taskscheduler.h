#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <unordered_map>

class TaskScheduler {
public:
	// Flags for tasks when registering them
	enum functionflags {
		NONE = 0,
		// If the task starts an I/O loop
		IO_LOOP = 1 << 0,
		// Forces any task to be ran on this thread by default
		FORCED_THREAD = 1 << 1, 
	};
	
	// Structure for registered tasks
	struct tasks {
		std::function<void()> func;
		int flags;
		// only used if forced_thread flag is set.
		int forcedthreadID;
	};

	// task queue for each thread
	std::vector<std::queue<tasks>> taskqueues;
	std::mutex mtx;
	std::condition_variable cv;
	TaskScheduler(int threadcount);
	~TaskScheduler();

	// adds a task with flags if needed
	void addtask(std::function<void()> task, int threadID, int flags = functionflags::NONE, int forcedthreadID = -1);

	void startthreads();

	void threadworker(int threadID);

private:
	int threadcount_;

};

extern TaskScheduler gtaskscheduler;

#define ts gtaskscheduler
#endif // !TASKSCHEDULER_H

