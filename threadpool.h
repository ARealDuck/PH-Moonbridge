#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class threadpool {
public:
	threadpool();
	~threadpool();
	template <typename Func, typename... Args>
	auto enqueue(Func&& func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type>;
private:

};
extern TaskScheduler gtaskscheduler;

#define ts gtaskscheduler
#endif // !THREADPOOL_H

