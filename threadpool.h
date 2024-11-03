#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class threadpool {
public:
	// Constructor only used to create object globally DOES NOT START THREADPOOL
	// minThreads is used to hardcode set a given minumum amount of threads
	threadpool(size_t minThreads = 6);

	// Destructor for cleanup if needed
	~threadpool();

	//method to call to enqueue tasks
	// REQUIRES TASK TO BE PUT IN THIS BLOCK OF CODE gthreadpool.enqueueTask([this]() { "CODE BLOCK HERE" });
	void enqueueTask(std::function<void()> task);

	// start function to create threadpool
	// I have to seperate this functionality away from the global contructor to avoid multithreading conflicts with the GUI Library regarding the main thread.
	void start();
private:
	// function executed by each thread
	void worker();

	// storage method for threads
	std::vector <std::thread> threads;
	// queue for tasks
	std::queue < std::function<void()>> tasks;
	std::mutex queuemtx;
	std::condition_variable condition;
	std::atomic<bool> stop;
	
	// min and max threads to be set
	// min threads is hardcoded in the constructor while max threads is set by hardware
	// min thread ignores maxthreads in the case where hardware threads is lower than the minimum
	size_t minThreads;
	size_t maxThreads;
};

extern threadpool gthreadpool;

#endif // !THREADPOOL_H

