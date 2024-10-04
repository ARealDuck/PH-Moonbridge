#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>

class TaskScheduler {
public:
	// constructs the taskscheduler with a default of 4 threads
	TaskScheduler(size_t numthreads = 4);
	// destructor for graceful shutdown of threads
	~TaskScheduler();

	// queues a task
	void queuetask(std::function<void()> task);

	// stops the scheduler
	void stop();

private:
	// storage for worker threads
	std::vector<std::thread> wthreads;
	// Task queue
	std::vector<std::function<void()>> tasks;
	std::mutex queuemtx;
	std::condition_variable cv;
	std::atomic <bool> stopflag;
	void workerthread();
};
extern TaskScheduler gtaskscheduler;

#define ts gtaskscheduler
#endif // !TASKSCHEDULER_H

